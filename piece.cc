#include "piece.h"

//===Helper===
int abs(int a) {
  return (a < 0) ? -a : a;
}

//===Piece===
Piece::Piece(Square s, Color c)
  : cursq{s}, color{c}
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
  /*
  for (int i = 0; i < pieces.size(); i++) {
    if (pieces[i]->cursq == to &&
	pieces[i]->color == this->color) {
      throw Exception{"Invalid move"};
    }
  }
  if ((abs(to->get_row() - cursq->get_row()) + 
	abs(to->get_col() - cursq->get_col()) == 3) &&
      ((abs(to->get_row() - cur->get_row()) != 3 &&
	abs(to->get_col() - cur->get_col()) != 3))) {
    cursq = to;
  } else {
    throw Exception{"Invalid move"};
  }
  */
  cursq = to;
}

PieceName Knight::get_name(void) {
  return PieceName::Knight;
}

//===Bishop===

void Bishop::move(Square to) {
  /*
  if (cursq == to) {
    throw Exception{"Invalid move"};
  }
  int trow = to->get_row();
  int tcol = to->get_col();
  int crow = cursq->get_row();
  int ccol = cursq->get_col();
  if ((abs(trow - tcol) != abs(crow - ccol)) &&
      abs(trow + tcol) != abs(crow + ccol)) {
    throw Exception{"Invalid move"};
  }
  int lbrow = min(trow, crow);
  int lbcol = min(tcol, ccol);
  int ubrow = max(trow, crow);
  int ubcol = max(tcol, ccol);
  if (abs(trow - tcol) == abs(crow - ccol)) {
    for (int i = 0; i < pieces.size(); i++) {
      int prow = pieces[i]->cursq->get_row();
      int pcol = pieces[i]->cursq->get_col();
      if ((abs(prow - pcol) == abs(trow - tcol)) &&
	  (prow <= ubrow && prow >= lbrow)) {
	throw Exception{"Invalid move"};
      }
    }
  } else if (abs(trow + tcol) == abs(crow + ccol)) {
    for (int i = 0; i < pieces.size(); i++) {
      int prow = pieces[i]->cursq->get_row();
      int pcol = pieces[i]->cursq->get_col();
      if ((abs(prow + pcol) == abs(trow + tcol)) &&
	  (prow <= ubrow && prow >= lbrow)) {
	throw Exception{"Invalid move"};
      }
    }
  }
  cursq = to;
  */
  cursq = to;
}

PieceName Bishop::get_name(void) {
  return PieceName::Bishop;
}

//===Rook===

void Rook::move(Square to) {
  /*
  if (cursq == to) {
    throw Exception{"Invalid move"};
  } else if ((to->get_col() != cursq->get_col()) &&
      to->get_row() != cursq->get_row()) {
    throw Exception{"Invalid move"};
  }

  for (int i = 0; i < pieces.size(); i++) {
    if (pieces[i]->cursq == to &&
	pieces[i]->color == this->color) {
      throw Exception{"Invalid move"};
    }
    int lbrow = min(to->get_row(), cursq->get_row());
    int lbcol = min(to->get_col(), cursq->get_col());
    int ubrow = max(to->get_row(), cursq->get_row());
    int ubcol = max(to->get_col(), cursq->get_col());
    if (pieces[i]->cursq.get_col() == this->get_col() &&
	pieces[i]->cursq.get_row() > lbrow &&
	pieces[i]->cursq.get_row() < ubrow) {
      throw Exception{"Invalid move"};
    } else if (pieces[i]->cursq.get_row() == this->get_row() &&
	pieces[i]->cursq.get_col() > lbrow &&
	pieces[i]->cursq.get_col() < ubrow) {
      throw Exception{"Invalid move"};
    }
  }
  cursq = to;
  */
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
