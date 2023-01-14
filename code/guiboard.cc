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

GUIBoard::GUIBoard(int win_w, int win_h, std::shared_ptr<Board> b)
  : GUIElem(win_w, win_h, b)
{}

void GUIBoard::load_assets(SDL_Renderer *r) {
  board = load_image("images/wood.jpg", r);
  piece_textures[std::make_pair(Color::White, PieceName::King)] = load_image("images/wK.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Queen)] = load_image("images/wQ.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Rook)] = load_image("images/wR.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Bishop)] = load_image("images/wB.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Knight)] = load_image("images/wN.svg", r); 
  piece_textures[std::make_pair(Color::White, PieceName::Pawn)] = load_image("images/wP.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::King)] = load_image("images/bK.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Queen)] = load_image("images/bQ.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Rook)] = load_image("images/bR.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Bishop)] = load_image("images/bB.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Knight)] = load_image("images/bN.svg", r); 
  piece_textures[std::make_pair(Color::Black, PieceName::Pawn)] = load_image("images/bP.svg", r); 
}

// handles input and edits the GUI board as required.
// TODO
void GUIBoard::handle(SDL_Renderer *r) {
  if (r == nullptr) {
    return;
  }
  std::shared_ptr<Move> m;
  SDL_Event e;
  ScreenPos origpos{0,0};
  while(1) {
    SDL_WaitEvent(&e);
    if (e.type == SDL_QUIT) {
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
        // std::cout << thispos.x << " " << thispos.y << " " << x << " " << y << " " << win_h / 8 << std::endl; 
        // GUI shouldn't care about whose turn it is.
        if (//thiscolor == turn &&
            thispos.x < x && thispos.y < y &&
            x < thispos.x + win_w / 8 && y < thispos.y + win_h / 8) {
          id = i;
          break;
        }
      }
      if (id != -1) { // i.e. clicked a piece
                      // put the piece under the mouse
        m->from = std::make_shared<Square>( 8 - (y) / (win_h / 8), (x + (win_w/8)) / (win_w / 8) );
        origpos = std::get<2>(positions[id]);
        std::get<2>(positions[id]) = { x - win_w / 16, y - win_h / 16 };
        this->draw_board(r);
        while(SDL_WaitEvent(&e)) {
          if (e.type == SDL_MOUSEMOTION) { // if mouse is moving, refresh the board to reflect the current position
                                           // std::cout << "Mouse In Motion" << std::endl;
            int x, y;
            SDL_GetMouseState(&x, &y);
            std::get<2>(positions[id]) = { x - win_w / 16, y - win_h / 16 };
            this->draw_board(r);
          } else if (e.type == SDL_MOUSEBUTTONUP) { // mouse button is now up, so find the square that the current position corresponds to, and return this as the move
                                                    // std::cout << "Mouse button is up" << std::endl;
            int x, y;
            SDL_GetMouseState(&x, &y);
            std::get<2>(positions[id]) = { x - win_w / 16, y - win_h / 16 };
            this->draw_board(r);
            m->to = std::make_shared<Square>( 8 - (y) / (win_h / 8), (x + (win_w/8)) / (win_w / 8) );
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
  auto begin = b->get_pieces_cbegin();
  auto end = b->get_pieces_cend();
  positions.clear();
  auto temp = begin;
  while(temp != end) {
    ScreenPos sp{ ((*temp)->get_cursq()->get_col() - 1) * (win_h / 8), (win_w - ((*temp)->get_cursq()->get_row() * (win_w / 8))) };
    positions.push_back(std::tuple<Color, PieceName, ScreenPos>((*temp)->get_color(), (*temp)->get_name(), sp));
    temp++;
  }
  this->draw_board(r);
  return;
}

// draws the board on the screen.
void GUIBoard::draw_board(SDL_Renderer *r) {
  int len = positions.size();
  render(r, board, {0, 0, win_w, win_h});
  for (int i = 0; i < len; i++) {
    render(r, piece_textures[std::make_pair(std::get<0>(positions[i]), std::get<1>(positions[i]))],
        { std::get<2>(positions[i]).x, std::get<2>(positions[i]).y, win_w / 8, win_h / 8 });
  }
  SDL_RenderPresent(r);
  return;
}
