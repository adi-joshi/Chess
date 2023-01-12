#include <iostream>
#include "gui.h"
#include "textdisplay.h"
#include "SDL_image.h"

SDL_Texture *load_image(std::string file, SDL_Renderer *winren) {
  auto retval = IMG_LoadTexture(winren, file.c_str());
  if (retval == NULL) {
    std::cout << SDL_GetError() << ": " << "Texture could not be created from " << file << std::endl;
  }
  return retval;
}

void render(SDL_Renderer *ren, SDL_Texture *t, SDL_Rect r) {
  SDL_RenderCopy(ren, t, NULL, &r);
}

GUI::GUI(void)
  : win_w{800}, win_h{800}
{
  SDL_Init(SDL_INIT_EVERYTHING);
  auto b = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  auto window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cout << SDL_GetError() << std::endl;
  }
  winren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  board = load_image("images/wood.jpg", winren);
  if (board == NULL) {
    std::cout << SDL_GetError() << std::endl;
  }
  std::pair<Color, PieceName> p{Color::White, PieceName::King};
  piece_textures[std::make_pair(Color::White, PieceName::King)] = load_image("images/wK.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::White, PieceName::Queen)] = load_image("images/wQ.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::White, PieceName::Rook)] = load_image("images/wR.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::White, PieceName::Bishop)] = load_image("images/wB.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::White, PieceName::Knight)] = load_image("images/wN.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::White, PieceName::Pawn)] = load_image("images/wP.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::Black, PieceName::King)] = load_image("images/bK.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::Black, PieceName::Queen)] = load_image("images/bQ.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::Black, PieceName::Rook)] = load_image("images/bR.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::Black, PieceName::Bishop)] = load_image("images/bB.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::Black, PieceName::Knight)] = load_image("images/bN.svg", winren); 
  piece_textures[std::pair<Color, PieceName>(Color::Black, PieceName::Pawn)] = load_image("images/bP.svg", winren); 
  /*
     SDL_Rect *cb_rect = new SDL_Rect();
     cb_rect->x = 0; cb_rect->y = 0; cb_rect->w = win_w; cb_rect->h = win_h;
     SDL_BlitScaled(board, NULL, window_surface, cb_rect);
     */
  // render(winren, board, {0, 0, win_w, win_h});
  /*
     cb_rect->x = 100; cb_rect->y = 100; cb_rect->w = win_w / 8; cb_rect->h = win_h / 8;
     SDL_BlitScaled(piece_surfaces[std::make_pair(Color::White, PieceName::King)], NULL, window_surface, cb_rect);
     */
  // render(winren, piece_textures[std::make_pair(Color::White, PieceName::Knight)], {100, 100, win_w / 4, win_h / 4});
  // SDL_UpdateWindowSurface(window);
  // SDL_RenderPresent(winren);
}

void GUI::welcome_msg(void) {}

std::shared_ptr<Move> GUI::ask_move(Color turn) {
  auto m = std::make_shared<Move>();
  m->it = InputType::Move;
  m->color = turn;
  SDL_Event e;
  ScreenPos origpos{0,0};
  while(1) {
    // std::cout << "Hi" << std::endl;
    SDL_WaitEvent(&e);
    if (e.type == SDL_QUIT) {
      // std::cout << "Quit" << std::endl;
      m->it = InputType::Quit;
      return m;
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
        if (thiscolor == turn &&
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
        this->print_board();
        while(SDL_WaitEvent(&e)) {
          if (e.type == SDL_MOUSEMOTION) { // if mouse is moving, refresh the board to reflect the current position
                                           // std::cout << "Mouse In Motion" << std::endl;
            int x, y;
            SDL_GetMouseState(&x, &y);
            std::get<2>(positions[id]) = { x - win_w / 16, y - win_h / 16 };
            this->print_board();
          } else if (e.type == SDL_MOUSEBUTTONUP) { // mouse button is now up, so find the square that the current position corresponds to, and return this as the move
                                                    // std::cout << "Mouse button is up" << std::endl;
            int x, y;
            SDL_GetMouseState(&x, &y);
            std::get<2>(positions[id]) = { x - win_w / 16, y - win_h / 16 };
            this->print_board();
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
  return m;
}

// called by observer (i.e. Board, after verifying that move is valid)
void GUI::clear_board(void) {
  positions.clear();
}

void GUI::draw_board(std::vector<std::shared_ptr<Piece>>::const_iterator begin,
    std::vector<std::shared_ptr<Piece>>::const_iterator end) {
  positions.clear();
  auto temp = begin;
  while(temp != end) {
    ScreenPos sp{ ((*temp)->get_cursq()->get_col() - 1) * (win_h / 8), (win_w - ((*temp)->get_cursq()->get_row() * (win_w / 8))) };
    positions.push_back(std::tuple<Color, PieceName, ScreenPos>((*temp)->get_color(), (*temp)->get_name(), sp));
    // std::cout << sp.x << " " << sp.y << std::endl;
    temp++;
  }
}

void GUI::print_board(void) {
  int len = positions.size();
  /*
     SDL_Rect *cb_rect = new SDL_Rect();
     cb_rect->x = 0;
     cb_rect->y = 0;
     cb_rect->w = win_w;
     cb_rect->h = win_h;
     SDL_BlitScaled(board, NULL, window_surface, cb_rect);
     */
  render(winren, board, {0, 0, win_w, win_h});
  for (int i = 0; i < len; i++) {
    // std::cout << std::get<2>(positions[i]).get_row() << " " << std::get<2>(positions[i]).get_col() << std::endl;
    /*
       cb_rect->x = std::get<2>(positions[i]).x;
       cb_rect->y = std::get<2>(positions[i]).y;
       cb_rect->w = win_w / 8;
       cb_rect->h = win_h / 8;
       SDL_BlitScaled(piece_textures[std::make_pair(std::get<0>(positions[i]), std::get<1>(positions[i]))],
       NULL,
       window_surface,
       cb_rect);
       */
    render(winren, piece_textures[std::make_pair(std::get<0>(positions[i]), std::get<1>(positions[i]))],
        { std::get<2>(positions[i]).x, std::get<2>(positions[i]).y, win_w / 8, win_h / 8 });
  }
  // SDL_UpdateWindowSurface(window);
  SDL_RenderPresent(winren);
  // std::cout << "Board drawn helper" << std::endl;
}

void GUI::print_moves(std::vector<std::shared_ptr<Move>>::const_iterator begin,
    std::vector<std::shared_ptr<Move>>::const_iterator end) {}

void GUI::print_error(Exception e) {
  std::cout << e.error() << std::endl;
}

void GUI::print_winner(Result r) {}

GUI::~GUI(void) {
  /*
     for (auto surface : piece_textures) {
     SDL_FreeSurface(surface.second);
     }
     SDL_FreeSurface(board);
     SDL_DestroyWindow(window);
     SDL_Quit();
     */

  for (auto texture : piece_textures) {
    SDL_DestroyTexture(texture.second);
  }
  SDL_DestroyTexture(board);
  SDL_DestroyRenderer(winren);
  SDL_Quit();
}
