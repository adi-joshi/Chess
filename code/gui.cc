#include <iostream>
#include "gui.h"
#include "textdisplay.h"

std::tuple<Color, PieceName, Square> get_piece_details(const std::vector<Piece*>::const_iterator t) {
  Square sq{ (*t)->get_cursq()->get_row(), (*t)->get_cursq()->get_col() };
  return std::tuple<Color, PieceName, Square>((*t)->get_color(), (*t)->get_name(), sq);
}

SDL_Surface *load_image(std::string file) {
  SDL_Surface *img = SDL_LoadBMP(file.c_str());
  if (img == NULL) {
    std::cout << SDL_GetError() << ": " << file << " could not be loaded" << std::endl;
    return nullptr;
  }
  return img;
}

GUI::GUI(void)
  : win_w{800}, win_h{800}
{
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cout << SDL_GetError() << std::endl;
  }
  board = load_image("images/wood.bmp");
  if (board == NULL) {
    std::cout << SDL_GetError() << std::endl;
  }
  std::pair<Color, PieceName> p{Color::White, PieceName::King};
  piece_surfaces[std::make_pair(Color::White, PieceName::King)] = load_image("images/wK.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Queen)] = load_image("images/wQ.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Rook)] = load_image("images/wR.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Bishop)] = load_image("images/wB.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Knight)] = load_image("images/wN.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Pawn)] = load_image("images/wP.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::King)] = load_image("images/bK.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Queen)] = load_image("images/bQ.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Rook)] = load_image("images/bR.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Bishop)] = load_image("images/bB.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Knight)] = load_image("images/bN.bmp");
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Pawn)] = load_image("images/bP.bmp");
  SDL_Rect *cb_rect = new SDL_Rect();
  cb_rect->x = 0;
  cb_rect->y = 0;
  cb_rect->w = win_w;
  cb_rect->h = win_h;
  auto window_surface = SDL_GetWindowSurface(window);
  SDL_BlitScaled(board, NULL, window_surface, cb_rect);
  SDL_BlitScaled(piece_surfaces[std::make_pair(Color::White, PieceName::King)], NULL, window_surface, new SDL_Rect{100, 100, win_w/8, win_h/8});
  SDL_UpdateWindowSurface(window);
}

void GUI::welcome_msg(void) {}

Move *GUI::ask_move(Color turn) {
  SDL_Delay(3000);
  return new Move();
}

// called by observer (i.e. Board, after verifying that move is valid)
void GUI::clear_board(void) {
  positions.clear();
}

std::string GUI::draw_board(std::vector<Piece*>::const_iterator begin,
		std::vector<Piece*>::const_iterator end) {
  auto temp = begin;
  while(temp != end) {
    positions.push_back(get_piece_details(temp));
    temp++;
  }
  int len = positions.size();
  auto window_surface = SDL_GetWindowSurface(window);
  SDL_BlitScaled(board, NULL, window_surface, new SDL_Rect{0, 0, win_w, win_h});
  for (int i = 0; i < len; i++) {
    std::cout << std::get<2>(positions[i]).get_row() << " " << std::get<2>(positions[i]).get_col() << std::endl;
    SDL_BlitScaled(piece_surfaces[std::make_pair(std::get<0>(positions[i]), std::get<1>(positions[i]))],
	           NULL,
		   window_surface,
		   new SDL_Rect{(std::get<2>(positions[i]).get_col() - 1) * (win_w / 8), 
		                (win_w - std::get<2>(positions[i]).get_row() * (win_w / 8)), 
				win_w/8,
				win_h/8});
  }
  SDL_UpdateWindowSurface(window);
  return TextDisplay().draw_board(begin, end);
}

void GUI::print_board(void) {
}

void GUI::print_moves(std::vector<Move*>::const_iterator begin,
		 std::vector<Move*>::const_iterator end) {}
void GUI::print_error(Exception e) {}
void GUI::print_winner(Result r) {}

GUI::~GUI(void) {
  SDL_Quit();
}
