#include "piece.h"
#include "exception.h"
#include "board.h"
#include <string>
#include <iostream>

//===Helper===
int abs(int a) {
  return (a < 0) ? -a : a;
}

//===Piece===
Piece::Piece(Board *b, Square s, Color c)
  : b{b}, cursq{s}, color{c}
{}

Square Piece::get_cursq(void) {
  return cursq;
}

void Piece::set_cursq(Square to) {
  cursq = to;
}

Color Piece::get_color(void) {
  return color;
}

std::vector<Piece *>::iterator Piece::move(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end, Square to) {
  auto king = begin;
  while(king != end) {
    if ((*king)->get_name() == PieceName::King &&
	(*king)->get_color() == this->color) {
      break;
    }
    king++;
  }
  auto thispiece = begin;
  while(thispiece != end) {
    if ((*thispiece)->get_cursq() == this->cursq) {
      break;
    }
    thispiece++;
  }
  if (king == end) {
    throw Exception{"Cannot find King"};
  }
  if (thispiece == end) {
    throw Exception{"Cannot find this piece"};
  }
  auto it = this->can_move_to(begin, end, to);
  auto cur = cursq;
  
  // TODO: Make it such that the this piece iterator has cursq as to, so that
  // the king can determine if it is in check.
  (*thispiece)->set_cursq(to);
  if ((*king)->in_check(begin, end, it)) {// king->is_checkmated(begin, end, dontinclude)
    (*thispiece)->set_cursq(cur);
    throw Exception{"King would be in check"};
  }
  cursq = to;
  return it;
}

bool Piece::in_check(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end,
    std::vector<Piece *>::iterator ignore) {
  return false;
}

bool Piece::is_checkmated(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end,
    std::vector<Piece *>::iterator ignore) {
  return false;
}

bool Piece::is_stalemated(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end,
    std::vector<Piece *>::iterator ignore) {
  return false;
}

Piece::~Piece(void) {}

//===Pawn===

std::vector<Piece *>::iterator Pawn::can_move_to(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end, Square to) {

  // TODO: Code en passant
  if (cursq == to) {
    throw Exception{"Destination square is current square"};
  }
  if (color == Color::White) {
    if (to.get_col() == cursq.get_col()) { // non-capture
      if (abs(to.get_row() - cursq.get_row()) > 2 ||
	  to.get_row() < cursq.get_row()) {
	throw Exception{"Destination square is not reachable"};
      }
      if (abs(to.get_row() - cursq.get_row()) == 2 &&
	  cursq.get_row() != 2) {
	throw Exception{"Cannot move 2 spaces if not on starting square"};
      }
      auto temp = begin;
      while(temp != end) {
	if ((*temp)->get_cursq() == to) {
	  throw Exception{"Destination square already has a piece"};
	} else if (abs(to.get_row() - cursq.get_row()) == 2 &&
	    (*temp)->get_cursq().get_col() == cursq.get_col() &&
	    (*temp)->get_cursq().get_row() == cursq.get_row() + 1) {
	  throw Exception{"Destination square is not reachable"};
	}
	temp++;
      }
      return end; // this is not a capture.
    } else { // is a capture
      if (abs(to.get_col() - cursq.get_col()) != 1 ||
	  abs(to.get_row() - cursq.get_row()) != 1 ||
	  to.get_row() < cursq.get_row()) {
	throw Exception{"Destination square is not reachable"};
      }
      Move *m = b->get_prev_move();
      auto need_sq = to;
      if (m != nullptr) {
	if (m->get_dst_piecename() == PieceName::Pawn &&
	    m->get_dst_square().get_row() == cursq.get_row() &&
	    m->get_dst_square().get_row() == 5 &&
	    m->get_src_square().get_row() == 7 &&
	    abs(m->get_dst_square().get_col() - cursq.get_col()) == 1) { // is en passant
	  need_sq = m->get_dst_square();
	}
      }
      auto temp = begin;
      for (; temp != end; temp++) {
	if ((*temp)->get_cursq() == need_sq &&
	    (*temp)->get_color() == this->color) {
	  throw Exception{"Piece of same color already on Square"};
	} else if ((*temp)->get_cursq() == need_sq &&
	    (*temp)->get_color() != this->color) {
	  break;
	} 
      }
      if (temp == end) {
	throw Exception{"Move is not a capture"};
      }
      return temp; // this is a capture
    }
  } else if (color == Color::Black) {
    if (to.get_col() == cursq.get_col()) { // non-capture
      if (abs(to.get_row() - cursq.get_row()) > 2 ||
	  to.get_row() > cursq.get_row()) {
	throw Exception{"Destination square is not reachable"};
      }
      if (abs(to.get_row() - cursq.get_row()) == 2 &&
	  cursq.get_row() != 7) {
	throw Exception{"Cannot move 2 spaces if not on starting square"};
      }
      auto temp = begin;
      while(temp != end) {
	if ((*temp)->get_cursq() == to) {
	  throw Exception{"Destination square already has a piece"};
	} else if (abs(to.get_row() - cursq.get_row()) == 2 &&
	    (*temp)->get_cursq().get_col() == cursq.get_col() &&
	    (*temp)->get_cursq().get_row() == cursq.get_row() - 1) {
	  throw Exception{"Destination square is not reachable"};
	}
	temp++;
      }
      return end; // this is not a capture.
    } else { // is a capture
      if (abs(to.get_col() - cursq.get_col()) != 1 ||
	  abs(to.get_row() - cursq.get_row()) != 1 ||
	  to.get_row() > cursq.get_row()) {
	throw Exception{"Destination square is not reachable"};
      }
      Move *m = b->get_prev_move();
      auto need_sq = to;
      if (m != nullptr) {
	if (m->get_dst_piecename() == PieceName::Pawn &&
	    m->get_dst_square().get_row() == cursq.get_row() &&
	    m->get_dst_square().get_row() == 4 && 
	    m->get_src_square().get_row() == 2 &&
	    abs(m->get_dst_square().get_col() - cursq.get_col()) == 1) { // is en passant
	  need_sq = m->get_dst_square();
	}
      }
      auto temp = begin;
      for (; temp != end; temp++) {
	if ((*temp)->get_cursq() == need_sq &&
	    (*temp)->get_color() == this->color) {
	  throw Exception{"Piece of same color already on Square"};
	} else if ((*temp)->get_cursq() == need_sq &&
	    (*temp)->get_color() != this->color) {
	  break;
	}
      }
      if (temp == end) {
	throw Exception{"Move is not a capture"};
      }
      return temp; // this is a capture
    }
  }
  return end;
}

PieceName Pawn::get_name(void) {
  return PieceName::Pawn;
}

//===Knight===

std::vector<Piece *>::iterator Knight::can_move_to(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end, Square to) {
  if (to == cursq) {
    throw Exception{"Destination square is current square"};
  }
  auto temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq() == to &&
	(*temp)->get_color() == this->color) {
      throw Exception{"Piece of same color already on Square"};
    } else if ((*temp)->get_cursq() == to &&
	(*temp)->get_color() != this->color) {
      break;
    }
    temp++;
  }
  if ((abs(to.get_row() - cursq.get_row()) + 
	abs(to.get_col() - cursq.get_col()) == 3) &&
      ((abs(to.get_row() - cursq.get_row()) != 3 &&
	abs(to.get_col() - cursq.get_col()) != 3))) {
    return temp;
  } else {
    throw Exception{"Invalid move"};
  }
  return temp;
}

PieceName Knight::get_name(void) {
  return PieceName::Knight;
}

//===Bishop===

std::vector<Piece *>::iterator Bishop::can_move_to(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end, Square to) {
  if (cursq == to) {
    throw Exception{"Destination square is current square"};
  }
  int trow = to.get_row();
  int tcol = to.get_col();
  int crow = cursq.get_row();
  int ccol = cursq.get_col();
  if (trow - tcol != crow - ccol &&
      trow + tcol != crow + ccol) {
    throw Exception{"Destination square is not on a diagonal"};
  }
  int lbrow = std::min(trow, crow);
  int lbcol = std::min(tcol, ccol);
  int ubrow = std::max(trow, crow);
  int ubcol = std::max(tcol, ccol);

  auto temp = begin;
  while(temp != begin) {
    if ((*temp)->get_cursq() == to &&
	(*temp)->get_color() == this->color) {
      throw Exception{"Piece of same color already on Square"};
    } else if ((*temp)->get_cursq() == to &&
	(*temp)->get_color() != this->color) {
      break;
    }
    temp++;
  }
  if (trow - tcol == crow - ccol) {
    auto temp2 = begin;
    while(temp2 != end) {
      int prow = (*temp2)->get_cursq().get_row();
      int pcol = (*temp2)->get_cursq().get_col();
      if ((cursq.get_row() != prow && cursq.get_col() != pcol) &&
	  prow - pcol == trow - tcol &&
	  (prow < ubrow && prow > lbrow) &&
	  (pcol < ubcol && pcol > lbcol)) {
	throw Exception{"Piece is blocking the diagonal"};
	// throw Exception{"Piece is blocking the diagonal " + std::to_string(prow) + " " + std::to_string(pcol) + " and " + std::to_string(trow) + " " + std::to_string(tcol)};
      }
      temp2++;
    }
  } else if (trow + tcol == crow + ccol) {
    auto temp2 = begin;
    while(temp2 != end) {
      int prow = (*temp2)->get_cursq().get_row();
      int pcol = (*temp2)->get_cursq().get_col();
      if ((cursq.get_row() != prow && cursq.get_col() != pcol) &&
	  (prow + pcol == trow + tcol) &&
	  (prow < ubrow && prow > lbrow) &&
	  (pcol < ubcol && pcol > lbcol)) {
	throw Exception{"Piece is blocking the diagonal"};
      }
      temp2++;
    }
  }
  return temp;
}

PieceName Bishop::get_name(void) {
  return PieceName::Bishop;
}

//===Rook===

std::vector<Piece *>::iterator Rook::can_move_to(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end, Square to) {
  if (cursq == to) {
    throw Exception{"Destination square is current square"};
  } else if ((to.get_col() != cursq.get_col()) &&
      to.get_row() != cursq.get_row()) {
    throw Exception{"Destination square is not on the same row or column"};
  }
  auto temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq() == to &&
	(*temp)->get_color() == this->color) {
      throw Exception{"Piece of same color already on Square"};
    }
    int lbrow = std::min(to.get_row(), cursq.get_row());
    int lbcol = std::min(to.get_col(), cursq.get_col());
    int ubrow = std::max(to.get_row(), cursq.get_row());
    int ubcol = std::max(to.get_col(), cursq.get_col());
    if ((*temp)->get_cursq().get_col() == cursq.get_col() &&
	(*temp)->get_cursq().get_row() > lbrow &&
	(*temp)->get_cursq().get_row() < ubrow) {
      throw Exception{"Piece is in the way to destination square"};
    } else if ((*temp)->get_cursq().get_row() == cursq.get_row() &&
	(*temp)->get_cursq().get_col() > lbcol &&
	(*temp)->get_cursq().get_col() < ubcol) {
      throw Exception{"Piece is in the way to destination square"};
    }
    temp++;
  }

  temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq() == to &&
	(*temp)->get_color() != this->color) {
      break;
    }
    temp++;
  }
  return temp;
}

PieceName Rook::get_name(void) {
  return PieceName::Rook;
}

//===Queen===

std::vector<Piece *>::iterator Queen::can_move_to(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end, Square to) {
  if (cursq == to) {
    throw Exception{"Destination square is current square"};
  }
  if (cursq.get_row() == to.get_row() ||
      cursq.get_col() == to.get_col()) { // moves like a rook
    return Rook(b, cursq, color).can_move_to(begin, end, to);
  } else { // moves like a bishop
    return Bishop(b, cursq, color).can_move_to(begin, end, to);
  }
}

PieceName Queen::get_name(void) {
  return PieceName::Queen;
}

//===King===

bool King::king_can_move(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end, std::vector<Piece *>::iterator ignore) {
  std::vector<Square> possible_moves;
  for (int i = std::max(cursq.get_row() - 1, 1); i < std::min(cursq.get_row() + 1, 8); i++) {
    for (int j = std::max(cursq.get_col() - 1, 1); j < std::min(cursq.get_col() + 1, 8); j++) {
      if (i == cursq.get_row() && j == cursq.get_col()) {
	continue;
      }
      Square s{i, j};
      possible_moves.push_back(s);
    }
  }

  for (int i = 0; i < possible_moves.size(); i++) {
    try {
      this->can_move_to(begin, end, possible_moves[i]); // if can move, won't throw
      if (!King(b, possible_moves[i], color).in_check(begin, end, ignore)) {
	return true;
      }
    } catch (...) {}
  }
  return false;
}

std::vector<Piece *>::iterator King::can_move_to(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end, Square to) {
  if (to == cursq) {
    throw Exception{"Destination square is current square"};
  } else if ((abs(to.get_col() - cursq.get_col()) > 1) ||
      (abs(to.get_row() - cursq.get_row()) > 1)) {
    throw Exception{"Destination square is unreachable"};
  }

  auto temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq() == to &&
	(*temp)->get_color() == this->color) {
      throw Exception{"Piece of same color already on Square"};
    } else if ((*temp)->get_cursq() == to &&
	(*temp)->get_color() != this->color) {
      break;
    }
    temp++;
  }
  return temp;
}

bool King::in_check(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end,
    std::vector<Piece *>::iterator ignore) {
  for (auto temp = begin; temp != end; temp++) {
    if ((*temp)->get_color() != this->color) {
      try {
	(*temp)->can_move_to(begin, end, cursq);
	return true;
      } catch(Exception &e) {}
    }
  }
  return false;
}

bool King::is_checkmated(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end,
    std::vector<Piece *>::iterator ignore) {
  // if !this->king_can_move == false && in check, then is_checkmated is true
  // otherwise, king is not checkmated
  if (!this->king_can_move(begin, end, ignore) &&
      this->in_check(begin, end, ignore)) {
    return true;
  }
  return false;
}

bool King::is_stalemated(std::vector<Piece *>::iterator begin,
    std::vector<Piece *>::iterator end,
    std::vector<Piece *>::iterator ignore) {
  /*
     auto temp = begin;
     while(temp != end) {
     if (temp != ignore) {
     try {
     if((*temp)->can_move_to(begin, end, cursq) != end) {
     return true;
     }
     } catch(...) {}
     }
     temp++;
     }
     */
  return false;
}

PieceName King::get_name(void) {
  return PieceName::King;
}
