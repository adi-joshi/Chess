#include "guimoves.h"
#include <string>
#include <iostream>

static char piecename_to_str(PieceName p, Color c) {
  char piece = ' ';
  if (c == Color::White) {
    switch(p) {
      case PieceName::King: piece = 'K'; break;
      case PieceName::Queen: piece = 'Q'; break;
      case PieceName::Bishop: piece = 'B'; break;
      case PieceName::Knight: piece = 'N'; break;
      case PieceName::Rook: piece = 'R'; break;
      case PieceName::Pawn: piece = 'P'; break;
    }
  } else if (c == Color::Black) {
    switch(p) {
      case PieceName::King: piece = 'k'; break;
      case PieceName::Queen: piece = 'q'; break;
      case PieceName::Bishop: piece = 'b'; break;
      case PieceName::Knight: piece = 'n'; break;
      case PieceName::Rook: piece = 'r'; break;
      case PieceName::Pawn: piece = 'p'; break;
    }
  }
  return piece;
}


GUIMoves::GUIMoves(std::shared_ptr<Board> b)
  : GUIElem(b)
{
  if(TTF_Init() != 0) {
    exit(1);
  }
  this->reg = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 20);
  this->bold = TTF_OpenFont("assets/fonts/OpenSans-Bold.ttf", 20);
}

void GUIMoves::load_assets(SDL_Renderer *r) {
  return;
}

void GUIMoves::handle(SDL_Renderer *r, SDL_Event *e) {
  return;
  std::cout << "This function is called" << std::endl;
  SDL_RenderSetViewport(r, viewport);
  auto text_surface = TTF_RenderText_Solid_Wrapped(reg, "Helloaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", { 255,255,255, 255 }, 300);
  auto text_texture = SDL_CreateTextureFromSurface(r, text_surface);
  SDL_Rect rect = {0, 0, text_surface->w, text_surface->h};
  SDL_RenderCopy(r, text_texture, NULL, &rect);
  SDL_RenderPresent(r);
  return;
}

void GUIMoves::update(SDL_Renderer *r) {
  auto [begin, end] = b->get_moves_const_iter();
  std::string movestring = "";
  int i = 1;
  for (auto temp = begin; temp != end; temp++) {
    char name = piecename_to_str((*temp)->piecename, Color::White);
    if ((*temp)->color == Color::White) {
      movestring += static_cast<char>('0' + i);
      movestring += ". ";
      i++;
    }
    if (name != 'P') {
      movestring += name;
    }
    movestring += (*temp)->pref;
    if ((*temp)->mt == MoveType::Capture) {
        movestring += "x";
    }
    char c = 'a' - 1 + (*temp)->to->get_col();
    char r = '0' + (*temp)->to->get_row();
    movestring += c;
    movestring += r;
    movestring += " ";
  }
  SDL_RenderSetViewport(r, viewport);
  auto text_surface = TTF_RenderText_Solid_Wrapped(reg, movestring.c_str() , { 0, 0, 0, 255 }, 300);
  if (text_surface == nullptr) {
    return;
  }
  auto text_texture = SDL_CreateTextureFromSurface(r, text_surface);
  SDL_Rect rect = {0, 0, text_surface->w, text_surface->h};
  SDL_RenderCopy(r, text_texture, NULL, &rect);
  SDL_RenderPresent(r);
  return;
}

GUIMoves::~GUIMoves(void) {
  TTF_CloseFont(reg);
  TTF_CloseFont(bold);
  TTF_Quit();
}
