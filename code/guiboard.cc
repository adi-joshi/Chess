#include "guiboard.h"
#include "SDL_image.h"

static SDL_Texture *load_image(std::string file, SDL_Renderer *winren) {
  auto retval = IMG_LoadTexture(winren, file.c_str());
  if (retval == NULL) {
    return nullptr;
    //std::cout << SDL_GetError() << ": " << "Texture could not be created from " << file << std::endl;
  }
  return retval;
}

static void render(SDL_Renderer *ren, SDL_Texture *t, SDL_Rect r) {
  SDL_RenderCopy(ren, t, NULL, &r);
}

GUIBoard::GUIBoard(std::shared_ptr<Board> b)
  : GUIElem(b)
{}

void GUIBoard::load_assets(SDL_Renderer *r) {
  board = load_image("assets/images/wood.jpg", r);
  piece_textures[std::make_pair(Color::White, PieceName::King)] = load_image("assets/images/wK.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Queen)] = load_image("assets/images/wQ.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Rook)] = load_image("assets/images/wR.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Bishop)] = load_image("assets/images/wB.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Knight)] = load_image("assets/images/wN.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Pawn)] = load_image("assets/images/wP.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::King)] = load_image("assets/images/bK.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Queen)] = load_image("assets/images/bQ.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Rook)] = load_image("assets/images/bR.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Bishop)] = load_image("assets/images/bB.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Knight)] = load_image("assets/images/bN.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Pawn)] = load_image("assets/images/bP.svg", r); 
}

void GUIBoard::set_viewport(SDL_Rect *vp) {
  GUIElem::set_viewport(vp);
  auto board_size = std::min(viewport->w, viewport->h);
  this->board_region = {(viewport->w / 2) - (board_size / 2),
                        (viewport->h / 2) - (board_size / 2),
                        board_size,
                        board_size };
}


// handles input and edits the GUI board as required.
void GUIBoard::handle(SDL_Renderer *r) {
  if (r == nullptr) {
    return;
  }
  auto win_h = viewport->h;
  auto win_w = viewport->w;
  SDL_RenderSetViewport(r, viewport);
  auto m = std::make_shared<Move>();
  SDL_Event e;
  ScreenPos origpos{0,0};
  while(1) {
    SDL_WaitEvent(&e);
    if (e.type == SDL_QUIT) {
      exit(0);
      return;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) { // if mouse button is clicked
      // get current position of mouse
      int x, y;
      SDL_GetMouseState(&x, &y);
      int id = -1;
      int len = positions.size();
      for (int i = 0; i < len; i++) {
        auto thispos = std::get<2>(positions[i]);
        auto thiscolor = std::get<0>(positions[i]);
        auto turn = b->whose_move();
        // std::cout << thispos.x << " " << thispos.y << " " << x << " " << y << " " << win_h / 8 << std::endl; 
        // GUI shouldn't care about whose turn it is.
        if (thiscolor == turn &&
            thispos.x < x && thispos.y < y &&
            x < thispos.x + board_region.w / 8 && y < thispos.y + board_region.h / 8) {
          id = i;
          break;
        }
      }
      if (id != -1) { // i.e. clicked a piece
                      // put the piece under the mouse
        m->from = std::make_shared<Square>( 8 - (y - board_region.y) / (board_region.h / 8), (x - board_region.x + (board_region.w / 8)) / (board_region.w / 8) );
        m->color = b->whose_move();
        origpos = std::get<2>(positions[id]);
        std::get<2>(positions[id]) = { x - board_region.w / 16, y - board_region.h / 16 };
        this->draw_board(r);
        while(SDL_WaitEvent(&e)) {
          if (e.type == SDL_MOUSEMOTION) { // if mouse is moving, refresh the board to reflect the current position
                                           // std::cout << "Mouse In Motion" << std::endl;
            int x, y;
            SDL_GetMouseState(&x, &y);
            std::get<2>(positions[id]) = { x - board_region.w / 16, y - board_region.h / 16 };
            this->draw_board(r);
          } else if (e.type == SDL_MOUSEBUTTONUP) { // mouse button is now up, so find the square that the current position corresponds to, and return this as the move
                                                    // std::cout << "Mouse button is up" << std::endl;
            int x, y;
            SDL_GetMouseState(&x, &y);
            std::get<2>(positions[id]) = { x - board_region.w / 16, y - board_region.h / 16 };
            this->draw_board(r);
            m->to = std::make_shared<Square>( 8 - (y - board_region.y) / (board_region.h / 8), (x - board_region.x + (board_region.w / 8)) / (board_region.w / 8) );
            // std::cout << x << " " << y << ": " << m->to->get_row() << " " << m->to->get_col() << " " << m->from->get_row() << " " << m->from->get_col() << std::endl;
            std::get<2>(positions[id]) = origpos;
            // this->print_board();
            goto outer;
          }
        }
      }
      // std::cout << "Didn't get piece" << std::endl;
    }
    // std::cout << "End" << std::endl;
  }
outer:
  // TODO: Make b->move just return true or false, and not throw. Will be faster.
  try {
    b->move(m);
  } catch(...) {}
  this->update(r);
  this->notify_observers(r);
  return;
}

// gets info that this element needs from Board class, and then
// call draw_board.
void GUIBoard::update(SDL_Renderer *r) {
  auto win_h = viewport->h;
  auto win_w = viewport->w;
  SDL_RenderSetViewport(r, viewport);
  auto begin = b->get_pieces_cbegin();
  auto end = b->get_pieces_cend();
  positions.clear();
  auto temp = begin;
  while(temp != end) {
    ScreenPos sp{ board_region.x + ((*temp)->get_cursq()->get_col() - 1) * (board_region.h / 8),
                  board_region.y + (board_region.w - ((*temp)->get_cursq()->get_row() * (board_region.w / 8))) };
    positions.push_back(std::tuple<Color, PieceName, ScreenPos>((*temp)->get_color(), (*temp)->get_name(), sp));
    temp++;
  }
  this->draw_board(r);
  return;
}

// draws the board on the screen.
void GUIBoard::draw_board(SDL_Renderer *r) {
  auto win_h = viewport->h;
  auto win_w = viewport->w;
  SDL_RenderSetViewport(r, viewport);
  int len = positions.size();

  // rendering board
  render(r, board, board_region);

  for (int i = 0; i < len; i++) {
    render(r, piece_textures[std::make_pair(std::get<0>(positions[i]), std::get<1>(positions[i]))],
        { std::get<2>(positions[i]).x, std::get<2>(positions[i]).y,
        board_region.w / 8, board_region.h / 8});
  }
  SDL_RenderPresent(r);
  return;
}

GUIBoard::~GUIBoard(void) {
  for (auto p : piece_textures) {
    SDL_DestroyTexture(std::get<1>(p));
  }
  SDL_DestroyTexture(board);
}
