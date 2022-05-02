#include "piece.h"
#include "exception.h"
#include "board.h"

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

Color Piece::get_color(void) {
  return color;
}

bool Piece::is_checkmated(void) {
  return false;
}

bool Piece::is_stalemated(void) {
  return false;
}

Piece::~Piece(void) {}

//===Pawn===

void Pawn::move(Square to) {
  /*
     if (to == cursq) {
     throw Exception{"Invalid move"};
     }

     int trow = to->get_row();
     int tcol = to->get_col();
     int crow = cursq->get_row();
     int ccol = cursq->get_col();

     if (color == Color::White) {
     if ((trow < crow) ||
     (trow - crow > 2)) {
     throw Exception{"Invalid move"};
     }
     if (tcol == ccol) {
     Rook(cursq, color)->move(to);
     } else if (abs(tcol - ccol) > 1) {
     throw Exception{"Invalid move"};
     } else { // is a capture-like move
  // check if it is actually a capture
  bool is_capture = false;
  auto last_move = moves[moves.size() - 1]
  for (int i = 0; i < pieces.size(); i++) {
  if (pieces[i]->cursq == to && pieces[i]->color != this->color) {
  auto capture = pieces.remove(pieces[i]);
  capture->~Piece();
  is_capture = true;
  }
  }
  if (!is_capture) {
  throw {"Invalid move"};
  }
  } else if (color == Color::Black)
  */
  cursq = to;
}

PieceName Pawn::get_name(void) {
  return PieceName::Pawn;
}

//===Knight===

void Knight::move(Square to) {
  if (to == cursq) {
    throw Exception{"Destination square is current square"};
  }
  int piece_index = -1;
  for (int i = 0; i < b->pieces.size(); i++) {
    if (b->pieces[i]->get_cursq() == to &&
	b->pieces[i]->get_color() == this->color) {
      throw Exception{"Piece of same color already on Square"};
    } else if (b->pieces[i]->get_cursq() == to &&
	b->pieces[i]->get_color() != this->color) {
      int piece_index = i;
      break;
    }
  }
  if ((abs(to.get_row() - cursq.get_row()) + 
	abs(to.get_col() - cursq.get_col()) == 3) &&
      ((abs(to.get_row() - cursq.get_row()) != 3 &&
	abs(to.get_col() - cursq.get_col()) != 3))) {
    if (piece_index != -1) {
      b->pieces.erase(b->pieces.begin() + piece_index);
    }
    cursq = to;
  } else {
    throw Exception{"Invalid move"};
  }
  cursq = to;
}

PieceName Knight::get_name(void) {
  return PieceName::Knight;
}

//===Bishop===

void Bishop::move(Square to) {
  if (cursq == to) {
    throw Exception{"Destination square is current square"};
  }
  int trow = to.get_row();
  int tcol = to.get_col();
  int crow = cursq.get_row();
  int ccol = cursq.get_col();
  if ((abs(trow - tcol) != abs(crow - ccol)) &&
      abs(trow + tcol) != abs(crow + ccol)) {
    throw Exception{"Destination square is not on a diagonal"};
  }
  int lbrow = std::min(trow, crow);
  int lbcol = std::min(tcol, ccol);
  int ubrow = std::max(trow, crow);
  int ubcol = std::max(tcol, ccol);

  int piece_index = -1;
  for (int i = 0; i < b->pieces.size(); i++) {
    if (b->pieces[i]->get_cursq() == to &&
	b->pieces[i]->get_color() == this->color) {
      throw Exception{"Piece of same color already on Square"};
    } else if (b->pieces[i]->get_cursq() == to &&
	b->pieces[i]->get_color() != this->color) {
      piece_index = i;
      break;
    }
  }
  if (abs(trow - tcol) == abs(crow - ccol)) {
    for (int i = 0; i < b->pieces.size(); i++) {
      int prow = b->pieces[i]->get_cursq().get_row();
      int pcol = b->pieces[i]->get_cursq().get_col();
      if ((cursq.get_row() != prow && cursq.get_col() != pcol) &&
	  (abs(prow - pcol) == abs(trow - tcol)) &&
	  (prow < ubrow && prow > lbrow)) {
	throw Exception{"Piece is blocking the diagonal"};
      }
    }
  } else if (abs(trow + tcol) == abs(crow + ccol)) {
    for (int i = 0; i < b->pieces.size(); i++) {
      int prow = b->pieces[i]->get_cursq().get_row();
      int pcol = b->pieces[i]->get_cursq().get_col();
      if ((cursq.get_row() != prow && cursq.get_col() != pcol) &&
	  (abs(prow + pcol) == abs(trow + tcol)) &&
	  (prow < ubrow && prow > lbrow)) {
	throw Exception{"Piece is blocking the diagonal"};
      }
    }
  }
  if (piece_index != -1) {
    b->pieces.erase(b->pieces.begin() + piece_index);
  }
  cursq = to;
}

PieceName Bishop::get_name(void) {
  return PieceName::Bishop;
}

//===Rook===

void Rook::move(Square to) {
  if (cursq == to) {
    throw Exception{"Destination square is current square"};
  } else if ((to.get_col() != cursq.get_col()) &&
      to.get_row() != cursq.get_row()) {
    throw Exception{"Destination square is not on the same row or column"};
  }

  for (int i = 0; i < b->pieces.size(); i++) {
    if (b->pieces[i]->get_cursq() == to &&
	b->pieces[i]->get_color() == this->color) {
      throw Exception{"Piece of same color already on Square"};
    }
    int lbrow = std::min(to.get_row(), cursq.get_row());
    int lbcol = std::min(to.get_col(), cursq.get_col());
    int ubrow = std::max(to.get_row(), cursq.get_row());
    int ubcol = std::max(to.get_col(), cursq.get_col());
    if (b->pieces[i]->get_cursq().get_col() == cursq.get_col() &&
	b->pieces[i]->get_cursq().get_row() > lbrow &&
	b->pieces[i]->get_cursq().get_row() < ubrow) {
      throw Exception{"Piece is in the way to destination square"};
    } else if (b->pieces[i]->get_cursq().get_row() == cursq.get_row() &&
	b->pieces[i]->get_cursq().get_col() > lbcol &&
	b->pieces[i]->get_cursq().get_col() < ubcol) {
      throw Exception{"Piece is in the way to destination square"};
    }
  }
  
  int piece_index = -1;
  for (int i = 0; i < b->pieces.size(); i++) {
    if (b->pieces[i]->get_cursq() == to &&
	b->pieces[i]->get_color() != this->color) {
      piece_index = i;
    }
  }
  if (piece_index != -1) {
    b->pieces.erase(b->pieces.begin() + piece_index);
  }
  cursq = to;
}

PieceName Rook::get_name(void) {
  return PieceName::Rook;
}

//===Queen===

void Queen::move(Square to) {
  // return Rook(cursq, color)->move(to) || Bishop(cursq, color)->move(to);
  cursq = to;
}

PieceName Queen::get_name(void) {
  return PieceName::Queen;
}

//===King===

void King::move(Square to) {
  /*
     if (to == cursq) {
     throw Exception{"Invalid move"};
     } else if ((abs(to->get_col() - cursq->get_col()) > 1) ||
     (abs(to->get_row() - cursq->get_row()) > 1)) {
     throw Exception{"Invalid move"};
     } else if (this->in_check(to)) {
     throw Exception{"Invalid move"};
     }

     for (int i = 0; i < pieces.size(); i++) {
     if (pieces[i]->cursq == to &&
     pieces[i]->color == this->color) {
     throw Exception{"Invalid move"};
     }
     }
     cursq = to;
     */
  cursq = to;
}

bool King::is_checkmated(void) {
  return false;
}

bool King::is_stalemated(void) {
  return false;
}

PieceName King::get_name(void) {
  return PieceName::King;
}
