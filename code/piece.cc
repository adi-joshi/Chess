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
Piece::Piece(std::shared_ptr<Board> b, std::shared_ptr<Square> s, Color c)
  : b{b}, cursq{s}, color{c}
{}

std::shared_ptr<Square> Piece::get_cursq(void) {
  return cursq;
}

void Piece::set_cursq(std::shared_ptr<Square> to) {
  cursq = to;
}

void Piece::set_moved(bool b) {
  moved = b;
}

bool Piece::piece_moved(void) {
  return moved;
}

Color Piece::get_color(void) {
  return color;
}

bool Piece::move(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end, std::shared_ptr<Move> m) {
  auto to = m->to;
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
    m->error_str = "Cannot find King";
    return false;
  }
  if (thispiece == end) {
    m->error_str = "Cannot find this piece";
    return false;
  }
  if (this->can_move_to(begin, end, m)) {
    auto cur = cursq;
    (*thispiece)->set_cursq(to);
    auto it = m->pieces_to_capture.size() == 0 ? end : m->pieces_to_capture[0];
    if ((*king)->in_check(begin, end, it)) {// king->is_checkmated(begin, end, dontinclude)
      (*thispiece)->set_cursq(cur);
      m->error_str = "King would be in check";
      return false;
    }
    m->color = this->color;
    m->from = cursq;
    m->piecename = this->get_name();

    moved = true;
    return true;
  }
  return false;
}

bool Piece::in_check(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end,
    std::vector<std::shared_ptr<Piece>>::iterator ignore) {
  return false;
}

bool Piece::is_checkmated(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end,
    std::vector<std::shared_ptr<Piece>>::iterator ignore) {
  return false;
}

Result Piece::is_stalemated(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end,
    std::vector<std::shared_ptr<Piece>>::iterator ignore) {
  return Result::NoResult;
}

Result Piece::get_result(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end,
    std::vector<std::shared_ptr<Piece>>::iterator ignore) {
  return Result::NoResult;
}

Piece::~Piece(void) {}

//===Pawn===

bool Pawn::can_move_to(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end, std::shared_ptr<Move> m) {
  if (m == nullptr) {
    return false;
  }
  auto to = m->to;
  if (cursq->get_col() == to->get_col() &&
      cursq->get_row() == to->get_row()) {
    m->error_str = "Destination square is current square";
    return false;
  }
  if (color == Color::White) {
    if (to->get_col() == cursq->get_col()) { // non-capture
      if (abs(to->get_row() - cursq->get_row()) > 2 ||
	  to->get_row() < cursq->get_row()) {
	m->error_str = "Destination square is not reachable 1";
	return false;
      }
      if (abs(to->get_row() - cursq->get_row()) == 2 &&
	  cursq->get_row() != 2) {
	m->error_str = "Cannot move 2 spaces if not on starting square";
	return false;
      }
      auto temp = begin;
      while(temp != end) {
	if ((*temp)->get_cursq() == to) {
	  m->error_str = "Destination square already has a piece";
	  return false;
	} else if (abs(to->get_row() - cursq->get_row()) == 2 &&
	    (*temp)->get_cursq()->get_col() == cursq->get_col() &&
	    (*temp)->get_cursq()->get_row() == cursq->get_row() + 1) {
	  m->error_str = "Destination square is not reachable 2";
	  return false;
	}
	temp++;
      }
      if (m->mt == MoveType::Unknown) {
	m->mt = MoveType::Normal;
      }
      // return true; // this is not a capture
    } else { // is a capture
      if (abs(to->get_col() - cursq->get_col()) != 1 ||
	  abs(to->get_row() - cursq->get_row()) != 1 ||
	  to->get_row() < cursq->get_row()) {
	m->error_str = "Destination square is not reachable 3";
	return false;
      }
      std::shared_ptr<Move> prev_move = b->get_prev_move();
      auto need_sq = to;
      bool is_enpassant = false;
      if (prev_move != nullptr) {
	if (prev_move->piecename == PieceName::Pawn &&
	    prev_move->to->get_row() == cursq->get_row() &&
	    prev_move->to->get_row() == 5 &&
	    prev_move->from->get_row() == 7 &&
	    abs(prev_move->to->get_col() - cursq->get_col()) == 1) { // is en passant
	  need_sq = prev_move->to;
	  is_enpassant = true;
	}
      }
      auto temp = begin;
      for (; temp != end; temp++) {
	if ((*temp)->get_cursq()->get_col() == need_sq->get_col() &&
	    (*temp)->get_cursq()->get_row() == need_sq->get_row() &&
	    (*temp)->get_color() == this->color) {
	  m->error_str = "Piece of same color already on Square";
	  return false;
	} else if ((*temp)->get_cursq()->get_col() == need_sq->get_col() &&
	    (*temp)->get_cursq()->get_row() == need_sq->get_row() &&
	    (*temp)->get_color() != this->color) {
	  break;
	} 
      }
      if (temp == end) {
	m->error_str = "Move is not a capture";
	return false;
      }
      m->pieces_to_capture.push_back(temp);
      if (m->mt != MoveType::Unknown) {
	if (is_enpassant) {
	  m->mt = MoveType::EnPassant;
	} else {
	  m->mt = MoveType::Capture;
	}
      }
      // return true; // this is a capture
    }
    if (to->get_row() == 8 && m->mt != MoveType::Promotion) {
      m->error_str = "Illegal Promotion";
      return false;
    } else if (m->mt == MoveType::Promotion && m->promoted_to == PieceName::King) {
      m->error_str = "Cannot promote to a King";
      return false;
    } else if (m->mt == MoveType::Promotion && m->promoted_to == PieceName::Pawn) {
      m->error_str = "Cannot promote to a Pawn";
      return false;
    }
    return true;
  } else if (color == Color::Black) {
    if (to->get_col() == cursq->get_col()) { // non-capture
      if (abs(to->get_row() - cursq->get_row()) > 2 ||
	  to->get_row() > cursq->get_row()) {
	m->error_str = "Destination square is not reachable";
	return false;
      }
      if (abs(to->get_row() - cursq->get_row()) == 2 &&
	  cursq->get_row() != 7) {
	m->error_str = "Cannot move 2 spaces if not on starting square";
	return false;
      }
      auto temp = begin;
      while(temp != end) {
	if ((*temp)->get_cursq() == to) {
	  m->error_str = "Destination square already has a piece";
	  return false;
	} else if (abs(to->get_row() - cursq->get_row()) == 2 &&
	    (*temp)->get_cursq()->get_col() == cursq->get_col() &&
	    (*temp)->get_cursq()->get_row() == cursq->get_row() - 1) {
	  m->error_str = "Destination square is not reachable";
	  return false;
	}
	temp++;
      }
      if (m->mt == MoveType::Unknown) {
	m->mt = MoveType::Normal;
      }
      // return true; // this is not a capture.
    } else { // is a capture
      if (abs(to->get_col() - cursq->get_col()) != 1 ||
	  abs(to->get_row() - cursq->get_row()) != 1 ||
	  to->get_row() > cursq->get_row()) {
	m->error_str = "Destination square is not reachable";
	return false;
      }
      std::shared_ptr<Move> prev_move = b->get_prev_move();
      auto need_sq = to;
      bool is_enpassant = false;
      if (prev_move != nullptr) {
	if (prev_move->piecename == PieceName::Pawn &&
	    prev_move->to->get_row() == cursq->get_row() &&
	    prev_move->to->get_row() == 4 && 
	    prev_move->from->get_row() == 2 &&
	    abs(prev_move->to->get_col() - cursq->get_col()) == 1) { // is en passant
	  need_sq = prev_move->to;
	  is_enpassant = true;
	}
      }
      auto temp = begin;
      for (; temp != end; temp++) {
	if ((*temp)->get_cursq()->get_col() == need_sq->get_col() &&
	    (*temp)->get_cursq()->get_row() == need_sq->get_row() &&
	    (*temp)->get_color() == this->color) {
	  m->error_str = "Piece of same color already on Square";
	  return false;
	} else if ((*temp)->get_cursq()->get_col() == need_sq->get_col() &&
	    (*temp)->get_cursq()->get_row() == need_sq->get_row() &&
	    (*temp)->get_color() != this->color) {
	  break;
	}
      }
      if (temp == end) {
	m->error_str = "Move is not a capture";
	return false;
      }
      if (m->mt == MoveType::Unknown) {
	if (is_enpassant) {
	  m->mt = MoveType::EnPassant;
	} else {
	  m->mt = MoveType::Capture;
	}
      }
      m->pieces_to_capture.push_back(temp);
      // return true; // this is a capture
    }
    if (to->get_row() == 1 && m->mt != MoveType::Promotion) {
      m->error_str = "Illegal Promotion";
      return false;
    } else if (m->mt == MoveType::Promotion && m->promoted_to == PieceName::King) {
      m->error_str = "Cannot promote to a King";
      return false;
    } else if (m->mt == MoveType::Promotion && m->promoted_to == PieceName::Pawn) {
      m->error_str = "Cannot promote to a Pawn";
      return false;
    }
    return true;
  }
  return false;
}

PieceName Pawn::get_name(void) {
  return PieceName::Pawn;
}

//===Knight===

bool Knight::can_move_to(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end, std::shared_ptr<Move> m) {
  auto to = m->to;
  if (to->get_row() == cursq->get_row() &&
      to->get_col() == cursq->get_col()) {
    m->error_str = "Destination square is current square";
    return false;
  }
  auto temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq()->get_col() == to->get_col() &&
	(*temp)->get_cursq()->get_row() == to->get_row() &&
	(*temp)->get_color() == this->color) {
      m->error_str = "Piece of same color already on Square";
      return false;
    } else if ((*temp)->get_cursq()->get_col() == to->get_col() &&
	(*temp)->get_cursq()->get_row() == to->get_row() &&
	(*temp)->get_color() != this->color) {
      break;
    }
    temp++;
  }
  if ((abs(to->get_row() - cursq->get_row()) + 
	abs(to->get_col() - cursq->get_col()) == 3) &&
      ((abs(to->get_row() - cursq->get_row()) != 3 &&
	abs(to->get_col() - cursq->get_col()) != 3))) {
    if (temp != end) {
      m->pieces_to_capture.push_back(temp);
      m->mt = MoveType::Capture;
    } else {
      m->mt = MoveType::Normal;
    }
    return true;
  } else {
    m->error_str = "Invalid move";
    return false;
  }
  return false;
}

PieceName Knight::get_name(void) {
  return PieceName::Knight;
}

//===Bishop===

bool Bishop::can_move_to(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end, std::shared_ptr<Move> m) {
  auto to = m->to;
  if (to->get_row() == cursq->get_row() &&
      to->get_col() == cursq->get_col()) {
    m->error_str = "Destination square is current square";
    return false;
  }
  int trow = to->get_row();
  int tcol = to->get_col();
  int crow = cursq->get_row();
  int ccol = cursq->get_col();
  if (trow - tcol != crow - ccol &&
      trow + tcol != crow + ccol) {
    m->error_str = "Destination square is not on a diagonal";
    return false;
  }
  int lbrow = std::min(trow, crow);
  int lbcol = std::min(tcol, ccol);
  int ubrow = std::max(trow, crow);
  int ubcol = std::max(tcol, ccol);

  auto temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq()->get_row() == to->get_row() &&
	(*temp)->get_cursq()->get_col() == to->get_col() &&
	(*temp)->get_color() == this->color) {
      m->error_str = "Piece of same color already on Square";
      return false;
    } else if ((*temp)->get_cursq()->get_row() == to->get_row() &&
	(*temp)->get_cursq()->get_col() == to->get_col() &&
	(*temp)->get_color() != this->color) {
      break;
    }
    temp++;
  }
  if (trow - tcol == crow - ccol) {
    auto temp2 = begin;
    while(temp2 != end) {
      int prow = (*temp2)->get_cursq()->get_row();
      int pcol = (*temp2)->get_cursq()->get_col();
      if ((cursq->get_row() != prow && cursq->get_col() != pcol) &&
	  prow - pcol == trow - tcol &&
	  (prow < ubrow && prow > lbrow) &&
	  (pcol < ubcol && pcol > lbcol)) {
	m->error_str = "Piece is blocking the diagonal";
	return false;
	// throw Exception{"Piece is blocking the diagonal " + std::to_string(prow) + " " + std::to_string(pcol) + " and " + std::to_string(trow) + " " + std::to_string(tcol)};
      }
      temp2++;
    }
  } else if (trow + tcol == crow + ccol) {
    auto temp2 = begin;
    while(temp2 != end) {
      int prow = (*temp2)->get_cursq()->get_row();
      int pcol = (*temp2)->get_cursq()->get_col();
      if ((cursq->get_row() != prow && cursq->get_col() != pcol) &&
	  (prow + pcol == trow + tcol) &&
	  (prow < ubrow && prow > lbrow) &&
	  (pcol < ubcol && pcol > lbcol)) {
	m->error_str = "Piece is blocking the diagonal";
	return false;
      }
      temp2++;
    }
  }
  if (temp != end) {
    m->mt = MoveType::Capture;
    m->pieces_to_capture.push_back(temp);
  } else {
    m->mt = MoveType::Normal;
  }
  return true;
}

PieceName Bishop::get_name(void) {
  return PieceName::Bishop;
}

//===Rook===

bool Rook::can_move_to(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end, std::shared_ptr<Move> m) {
  auto to = m->to;
  if (to->get_row() == cursq->get_row() &&
      to->get_col() == cursq->get_col()) {
    m->error_str = "Destination square is current square";
    return false;
  } else if ((to->get_col() != cursq->get_col()) &&
      to->get_row() != cursq->get_row()) {
    m->error_str = "Destination square is not on the same row or column";
    return false;
  }
  auto temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq()->get_row() == to->get_row() &&
	(*temp)->get_cursq()->get_col() == to->get_col() &&
	(*temp)->get_color() == this->color) {
      m->error_str = "Piece of same color already on Square";
      return false;
    }
    int lbrow = std::min(to->get_row(), cursq->get_row());
    int lbcol = std::min(to->get_col(), cursq->get_col());
    int ubrow = std::max(to->get_row(), cursq->get_row());
    int ubcol = std::max(to->get_col(), cursq->get_col());
    if ((*temp)->get_cursq()->get_col() == cursq->get_col() &&
	(*temp)->get_cursq()->get_row() > lbrow &&
	(*temp)->get_cursq()->get_row() < ubrow) {
      m->error_str = "Piece is in the way to destination square";
      return false;
    } else if ((*temp)->get_cursq()->get_row() == cursq->get_row() &&
	(*temp)->get_cursq()->get_col() > lbcol &&
	(*temp)->get_cursq()->get_col() < ubcol) {
      m->error_str = "Piece is in the way to destination square";
      return false;
    }
    temp++;
  }

  temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq()->get_row() == to->get_row() &&
	(*temp)->get_cursq()->get_col() == to->get_col() &&
	(*temp)->get_color() != this->color) {
      break;
    }
    temp++;
  }
  if (temp != end) {
    m->pieces_to_capture.push_back(temp);
    m->mt = MoveType::Normal;
  } else {
    m->mt = MoveType::Capture;
  }
  return true;
}

PieceName Rook::get_name(void) {
  return PieceName::Rook;
}

//===Queen===

bool Queen::can_move_to(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end, std::shared_ptr<Move> m) {
  auto to = m->to;
  if (to->get_row() == cursq->get_row() &&
      to->get_col() == cursq->get_col()) {
    m->error_str = "Destination square is current square";
    return false;
  }
  if (cursq->get_row() == to->get_row() ||
      cursq->get_col() == to->get_col()) { // moves like a rook
    return Rook(b, cursq, color).can_move_to(begin, end, m);
  } else { // moves like a bishop
    return Bishop(b, cursq, color).can_move_to(begin, end, m);
  }
}

PieceName Queen::get_name(void) {
  return PieceName::Queen;
}

//===King===

bool King::king_can_move(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end, std::vector<std::shared_ptr<Piece>>::iterator ignore) {
  std::vector<std::shared_ptr<Square>> possible_moves;
  for (int i = std::max(cursq->get_row() - 1, 1); i < std::min(cursq->get_row() + 1, 8); i++) {
    for (int j = std::max(cursq->get_col() - 1, 1); j < std::min(cursq->get_col() + 1, 8); j++) {
      if (i == cursq->get_row() && j == cursq->get_col()) {
	continue;
      }
      auto s = std::make_shared<Square>(i, j);
      possible_moves.push_back(s);
    }
  }

  for (int i = 0; i < possible_moves.size(); i++) {
    auto m = std::make_shared<Move>();
    m->from = this->cursq;
    m->to = possible_moves[i];
    if (this->can_move_to(begin, end, m)) {
      if (!King(b, possible_moves[i], color).in_check(begin, end, ignore)) {
	return true;
      }
    }
  }
  return false;
}

bool King::can_move_to(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end, std::shared_ptr<Move> m) {
  auto to = m->to;
  if (to->get_row() == cursq->get_row() &&
      to->get_col() == cursq->get_col()) {
    m->error_str = "Destination square is current square";
    return false;
  } else if (moved == false &&
      (abs(to->get_row() - cursq->get_row()) == 0) &&
      (abs(to->get_col() - cursq->get_col()) == 2)) { // castling
    if (this->in_check(begin, end, end)) {
      m->error_str = "Cannot castle while in check";
      return false;
    }
    auto rook = begin;
    for(; rook != end; rook++) {
      if ((*rook)->get_color() == this->color &&
	  (*rook)->get_cursq()->get_row() == cursq->get_row() &&
	  (*rook)->piece_moved() == false &&
	  (((*rook)->get_cursq()->get_col() - cursq->get_col()) *
	   (to->get_col() - cursq->get_col()) > 0)) {
	break;
      }
    }
    if (rook == end) {
      m->error_str = "Cannot castle as rook has moved";
      return false;
    }
    /*
    auto m2 = new Move();
    m2->from = (*rook)->get_cursq();
    m2->to = new Square(to->get_row(), (to->get_col() + (*rook)->get_cursq()->get_col()) / 2);
    */
    auto m2 = std::make_shared<Move>();
    m2->from = cursq;
    m2->to = std::make_shared<Square>(to->get_row(), (to->get_col() + cursq->get_col()) / 2);
    if (Rook(b, cursq, color).can_move_to(begin, end, m2)) {
      if (!this->in_check(begin, end, end) &&
	  !King(b, std::make_shared<Square>(cursq->get_row(), (cursq->get_col() + to->get_col()) / 2), color).in_check(begin, end, end) &&
	  !King(b, to, color).in_check(begin, end, end)) {
	(*rook)->move(begin, end, m2);
	cursq = to;
	m->mt = MoveType::Castling;
	return true;
      }
    } else {
      m->error_str = "Piece is in the way";
      return false;
    }
    return false;
  } else if ((abs(to->get_col() - cursq->get_col()) > 1) ||
      (abs(to->get_row() - cursq->get_row()) > 1)) {
    m->error_str = "Destination square is unreachable";
    return false;
  }
  auto temp = begin;
  while(temp != end) {
    if ((*temp)->get_cursq()->get_row() == to->get_row() &&
	(*temp)->get_cursq()->get_col() == to->get_col() &&
	(*temp)->get_color() == this->color) {
      m->error_str = "Piece of same color already on Square";
      return false;
    } else if ((*temp)->get_cursq()->get_row() == to->get_row() &&
	(*temp)->get_cursq()->get_col() == to->get_col() &&
	(*temp)->get_color() != this->color) {
      break;
    }
    temp++;
  }
  if (temp != end) {
    m->pieces_to_capture.push_back(temp);
    m->mt = MoveType::Capture;
  } else {
    m->mt = MoveType::Normal;
  }
  return true;
}

bool King::in_check(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end,
    std::vector<std::shared_ptr<Piece>>::iterator ignore) {
  for (auto temp = begin; temp != end; temp++) {
    if ((*temp)->get_color() != this->color) {
      auto m = std::make_shared<Move>();
      m->from = (*temp)->get_cursq();
      m->to = this->cursq;
      if ((*temp)->can_move_to(begin, end, m)) {
	return true;
      }
    }
  }
  return false;
}

bool King::is_checkmated(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end,
    std::vector<std::shared_ptr<Piece>>::iterator ignore) {
  // if !this->king_can_move == false && in check, then is_checkmated is true
  // otherwise, king is not checkmated
  if (!this->king_can_move(begin, end, ignore) &&
      this->in_check(begin, end, ignore)) {
    bool canblock = false;
    for (int i = 1; i <= 8; i++) {
      for (int j = 1; j <= 8; j++) {
	auto temp = begin;
	for (; temp != end; temp++) {
	  if ((*temp)->get_color() == this->color &&
	      (*temp)->get_name() != PieceName::King) { // king cant block for itself
	    auto m = std::make_shared<Move>();
	    m->from = (*temp)->get_cursq();
	    m->to = std::make_shared<Square>(i, j);

	    if ((*temp)->can_move_to(begin, end, m)) {
	      auto sq = (*temp)->get_cursq();
	      (*temp)->set_cursq(std::make_shared<Square>(i,j));
	      if (!this->in_check(begin,end,ignore)) {
		(*temp)->set_cursq(sq);
		canblock = true;
		goto outside; // I downloaded all of C++, I'm going to use all of C++
	      }
	      (*temp)->set_cursq(sq);
	    }
	  }
	}
      }
    }
outside:
    return !canblock;
  }
  return false;
}

Result King::get_result(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end,
    std::vector<std::shared_ptr<Piece>>::iterator ignore) {
  if (this->is_checkmated(begin, end, ignore) &&
      color == Color::White) {
    return Result::BlackWins;
  } else if (this->is_checkmated(begin, end, ignore) &&
      color == Color::Black) {
    return Result::WhiteWins;
  }
  return this->is_stalemated(begin, end, ignore); // nothing uses is_stalemated, so change it
}

Result King::is_stalemated(std::vector<std::shared_ptr<Piece>>::iterator begin,
    std::vector<std::shared_ptr<Piece>>::iterator end,
    std::vector<std::shared_ptr<Piece>>::iterator ignore) {

  // draw by stalemate
  bool canmove = false;
  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) {
      for (auto temp = begin; temp != end; temp++) {
	if ((*temp)->get_color() == this->color &&
	    (*temp)->get_name() != PieceName::King) {
	  try {
	    auto sq = (*temp)->get_cursq();
	    auto has_moved = (*temp)->piece_moved();
	    auto m = std::make_shared<Move>();
	    m->from = (*temp)->get_cursq();
	    m->to = std::make_shared<Square>(i,j);
	    (*temp)->move(begin, end, m);
	    (*temp)->set_cursq(sq);
	    (*temp)->set_moved(has_moved);
	    canmove = true;
	  } catch(...) {}
	}
      }
    }
  }
  if (!canmove && !king_can_move(begin, end, ignore)) {
    return Result::DrawByStalemate;
  }

  // draw by insufficient material
  std::vector<std::vector<std::shared_ptr<Piece>>::iterator> white;
  std::vector<std::vector<std::shared_ptr<Piece>>::iterator> black;
  int white_bishops = 0;
  int white_knights = 0;
  int black_bishops = 0;
  int black_knights = 0;
  for (auto temp = begin; temp != end; temp++) {
    if ((*temp)->get_color() == Color::White) {
      white.push_back(temp);
      if ((*temp)->get_name() == PieceName::Knight) {
	white_knights++;
      } else if ((*temp)->get_name() == PieceName::Bishop) {
	white_bishops++;
      }
    } else if ((*temp)->get_color() == Color::Black) {
      black.push_back(temp);
      if ((*temp)->get_name() == PieceName::Knight) {
	black_knights++;
      } else if ((*temp)->get_name() == PieceName::Bishop) {
	black_bishops++;
      }
    }
  }
  int size = white.size() + black.size();
  if (size <= 2) {
    return Result::DrawByInsufficientMaterial;
  }
  auto temp = begin;
  for (; temp != end; temp++) {
    if ((*temp)->get_name() != PieceName::King) {
      break;
    }
  }
  if (size == 3 &&
      (white_bishops == 1 || white_knights == 1 ||
       black_bishops == 1 || black_knights == 1)) {
    return Result::DrawByInsufficientMaterial;
  }
  if (size == 4 &&
      (white_knights + black_knights == size - 2)) {
    return Result::DrawByInsufficientMaterial;
  }
  if (size == 5 &&
      white_knights + black_knights == 5 &&
      white_knights != 3 &&
      black_knights != 3) {
    return Result::DrawByInsufficientMaterial;
  }

  // TODO: draw by threefold repetition

  return Result::NoResult;
}

PieceName King::get_name(void) {
  return PieceName::King;
}
