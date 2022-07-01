#include <iostream>
#include "gui.h"
#include "textdisplay.h"

SDL_Surface *load_image(std::string file, const SDL_Surface *window_surface) {
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
  SDL_Init(SDL_INIT_EVERYTHING);
  window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cout << SDL_GetError() << std::endl;
  }
  auto window_surface = SDL_GetWindowSurface(window);
  board = load_image("images/wood.bmp", window_surface);
  if (board == NULL) {
    std::cout << SDL_GetError() << std::endl;
  }
  std::pair<Color, PieceName> p{Color::White, PieceName::King};
  piece_surfaces[std::make_pair(Color::White, PieceName::King)] = load_image("images/wK.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Queen)] = load_image("images/wQ.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Rook)] = load_image("images/wR.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Bishop)] = load_image("images/wB.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Knight)] = load_image("images/wN.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::White, PieceName::Pawn)] = load_image("images/wP.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::King)] = load_image("images/bK.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Queen)] = load_image("images/bQ.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Rook)] = load_image("images/bR.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Bishop)] = load_image("images/bB.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Knight)] = load_image("images/bN.bmp", window_surface);
  piece_surfaces[std::pair<Color, PieceName>(Color::Black, PieceName::Pawn)] = load_image("images/bP.bmp", window_surface);
  SDL_Rect *cb_rect = new SDL_Rect();
  cb_rect->x = 0; cb_rect->y = 0; cb_rect->w = win_w; cb_rect->h = win_h;
  SDL_BlitScaled(board, NULL, window_surface, cb_rect);
  cb_rect->x = 100; cb_rect->y = 100; cb_rect->w = win_w / 8; cb_rect->h = win_h / 8;
  SDL_BlitScaled(piece_surfaces[std::make_pair(Color::White, PieceName::King)], NULL, window_surface, cb_rect);
  SDL_UpdateWindowSurface(window);
  delete cb_rect;
}

void GUI::welcome_msg(void) {}

Move *GUI::ask_move(Color turn) {
  Move *m = new Move();
  m->it = InputType::Move;
  m->color = turn;
  SDL_Event e;
  ScreenPos origpos{0,0};
  while(SDL_WaitEvent(&e)) {
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    // std::cout << "Hi" << std::endl;
    if (e.type == SDL_QUIT) {
      // std::cout << "Quit" << std::endl;
      return new Move();
    } else if (e.type == SDL_MOUSEBUTTONDOWN) { // if mouse button is clicked
      // get current position of mouse
      // std::cout << "Mouse button is down" << std::endl;
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
	// std::cout << "Got piece" << std::endl;
	m->from = new Square{ 8 - (y) / (win_h / 8), (x + (win_w/8)) / (win_w / 8) }; 
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
	    m->to = new Square{ 8 - (y) / (win_h / 8), (x + (win_w/8)) / (win_w / 8) }; 
	    // std::cout << x << " " << y << ": " << m->to->get_row() << " " << m->to->get_col() << " " << m->from->get_row() << " " << m->from->get_col() << std::endl;
	    std::get<2>(positions[id]) = origpos;
	    this->print_board();
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

std::string GUI::draw_board(std::vector<Piece*>::const_iterator begin,
    std::vector<Piece*>::const_iterator end) {
  positions.clear();
  auto temp = begin;
  while(temp != end) {
    ScreenPos sp{ ((*temp)->get_cursq()->get_col() - 1) * (win_h / 8), (win_w - ((*temp)->get_cursq()->get_row() * (win_w / 8))) };
    positions.push_back(std::tuple<Color, PieceName, ScreenPos>((*temp)->get_color(), (*temp)->get_name(), sp));
    // std::cout << sp.x << " " << sp.y << std::endl;
    temp++;
  }
  // std::cout << "Board drawn" << std::endl;
  return TextDisplay().draw_board(begin, end);
}

void GUI::print_board(void) {
  int len = positions.size();
  auto window_surface = SDL_GetWindowSurface(window);
  SDL_Rect *cb_rect = new SDL_Rect();
  cb_rect->x = 0;
  cb_rect->y = 0;
  cb_rect->w = win_w;
  cb_rect->h = win_h;
  SDL_BlitScaled(board, NULL, window_surface, cb_rect);
  for (int i = 0; i < len; i++) {
    // std::cout << std::get<2>(positions[i]).get_row() << " " << std::get<2>(positions[i]).get_col() << std::endl;
    cb_rect->x = std::get<2>(positions[i]).x;
    cb_rect->y = std::get<2>(positions[i]).y;
    cb_rect->w = win_w / 8;
    cb_rect->h = win_h / 8;
    SDL_BlitScaled(piece_surfaces[std::make_pair(std::get<0>(positions[i]), std::get<1>(positions[i]))],
	NULL,
	window_surface,
	cb_rect);
  }
  SDL_UpdateWindowSurface(window);
  delete cb_rect;
  // std::cout << "Board drawn helper" << std::endl;
}

void GUI::print_moves(std::vector<Move*>::const_iterator begin,
    std::vector<Move*>::const_iterator end) {}

void GUI::print_error(Exception e) {
  std::cout << e.error() << std::endl;
}

void GUI::print_winner(Result r) {}

GUI::~GUI(void) {
  for (auto surface : piece_surfaces) {
    SDL_FreeSurface(surface.second);
  }
  SDL_FreeSurface(board);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
