#include <iostream>
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
{
  m = std::make_shared<Move>();
}

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
void GUIBoard::handle(SDL_Renderer *r, SDL_Event *e) {
  if (r == nullptr || e == nullptr) {
    return;
  }
  auto win_h = viewport->h;
  auto win_w = viewport->w;
  SDL_RenderSetViewport(r, &board_region);
  ScreenPos origpos{0,0};
  int x, y;
  int len = positions.size();
  switch(e->type) {
    case SDL_MOUSEBUTTONDOWN:
      std::cout << "Mouse Button Down" << std::endl;
      // get current position of mouse
      SDL_GetMouseState(&x, &y);
      id = -1;
      x -= board_region.x;
      y -= board_region.y;
      for (int i = 0; i < len; i++) {
	auto thispos = std::get<2>(positions[i]);
	auto thiscolor = std::get<0>(positions[i]);
	auto turn = b->whose_move();
	if (thiscolor == turn &&
	    thispos.x < x && thispos.y < y &&
	    x < thispos.x + board_region.w / 8 && y < thispos.y + board_region.h / 8) {
	  id = i;
	  break;
	}
      }
      if (id != -1) { // i.e. clicked a piece
		      // put the piece under the mouse
	m->from = std::make_shared<Square>( 8 - y / (board_region.h / 8), (x + (board_region.w / 8)) / (board_region.w / 8) );
	m->color = b->whose_move();
	// origpos = std::get<2>(positions[id]);
	std::get<2>(positions[id]) = { x - board_region.w / 16, y - board_region.h / 16 };
	this->draw_board(r);
      }
      return;
    case SDL_MOUSEMOTION:
      std::cout << "Mouse Motion" << std::endl;
      if (id < 0) {
	return;
      }
      SDL_GetMouseState(&x, &y);
      x -= board_region.x;
      y -= board_region.y;
      std::get<2>(positions[id]) = { x - board_region.w / 16, y - board_region.h / 16 };
      this->draw_board(r);
      return;
    case SDL_MOUSEBUTTONUP:
      std::cout << "Mouse Button Up" << std::endl;
      SDL_GetMouseState(&x, &y);
      x -= board_region.x;
      y -= board_region.y;
      std::get<2>(positions[id]) = { x - board_region.w / 16, y - board_region.h / 16 };
      this->draw_board(r);
      m->to = std::make_shared<Square>( 8 - y / (board_region.h / 8), (x + (board_region.w / 8)) / (board_region.w / 8) );
      // std::cout << x << " " << y << ": " << m->to->get_row() << " " << m->to->get_col() << " " << m->from->get_row() << " " << m->from->get_col() << std::endl;
      std::get<2>(positions[id]) = origpos;
      id = -1;
      goto outer;
    default: return;
  }
outer:
  // TODO: Make b->move just return true or false, and not throw. Will be faster.
  try {
    b->move(m);
    auto temp = m;
    m = std::make_shared<Move>();
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
  SDL_RenderSetViewport(r, &board_region);
  auto begin = b->get_pieces_cbegin();
  auto end = b->get_pieces_cend();
  positions.clear();
  auto temp = begin;
  while(temp != end) {
    ScreenPos sp{ ((*temp)->get_cursq()->get_col() - 1) * (board_region.h / 8),
      (board_region.w - ((*temp)->get_cursq()->get_row() * (board_region.w / 8))) };
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
  SDL_RenderSetViewport(r, &board_region);
  int len = positions.size();

  // rendering board
  render(r, board, { 0, 0, board_region.w, board_region.h });

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
