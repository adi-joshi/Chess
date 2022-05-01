#include "board.h"
// #include <iostream>

Board::Board(TextDisplay *td) {
  ob.push_back(td);
  for (int i = 0; i < 8; i++) {
    auto white_pawn = new Pawn(Square(2,i), Color::White);
    pieces.push_back(white_pawn);
    auto black_pawn = new Pawn(Square(7,i), Color::Black);
    pieces.push_back(black_pawn);
  }

  auto white_rook1 = new Rook(Square(1, 1), Color::White);
  auto white_knight1 = new Knight(Square(1, 2), Color::White);
  auto white_bishop1 = new Bishop(Square(1, 3), Color::White);
  auto white_queen = new Queen(Square(1, 4), Color::White);
  auto white_king = new King(Square(1, 5), Color::White);
  auto white_bishop2 = new Bishop(Square(1, 6), Color::White);
  auto white_knight2 = new Knight(Square(1, 7), Color::White);
  auto white_rook2 = new Rook(Square(1, 8), Color::White);
  auto black_rook1 = new Rook(Square(8, 1), Color::Black);
  auto black_knight1 = new Knight(Square(8, 2), Color::Black);
  auto black_bishop1 = new Bishop(Square(8, 3), Color::Black);
  auto black_queen = new Queen(Square(8, 4), Color::Black);
  auto black_king = new King(Square(8, 5), Color::Black);
  auto black_bishop2 = new Bishop(Square(8, 6), Color::Black);
  auto black_knight2 = new Knight(Square(8, 7), Color::Black);
  auto black_rook2 = new Rook(Square(8, 8), Color::Black);

  pieces.push_back(white_rook1);
  pieces.push_back(white_knight1);
  pieces.push_back(white_bishop1);
  pieces.push_back(white_queen);
  pieces.push_back(white_king);
  pieces.push_back(white_bishop2);
  pieces.push_back(white_knight2);
  pieces.push_back(white_rook2);
  pieces.push_back(black_rook1);
  pieces.push_back(black_knight1);
  pieces.push_back(black_bishop1);
  pieces.push_back(black_queen);
  pieces.push_back(black_king);
  pieces.push_back(black_bishop2);
  pieces.push_back(black_knight2);
  pieces.push_back(black_rook2);

}

bool Board::move(std::string s, Color turn) {
  if (s.size() == 1 && s[0] == 'p') {
    ob[0]->print_moves(moves.begin());
    return false;
  }
  if ((s.size() == 4) &&
      (s[0] >= 'a' && s[0] <= 'h') &&
      (s[1] >= '1' && s[1] <= '8') &&
      (s[2] >= 'a' && s[2] <= 'h') &&
      (s[3] >= '1' && s[3] <= '8')) {
    Square from{s[1] - '0', s[0] - 'a' + 1};
    Square to{s[3] - '0', s[2] - 'a' + 1};
    bool moved = false;
    for (int i = 0; i < pieces.size(); i++) {
      if (pieces[i]->get_cursq() == from && pieces[i]->get_color() == turn) {
	std::tuple<Square, PieceName, Color> before{from, pieces[i]->get_name(), pieces[i]->get_color()};

	pieces[i]->move(to); // if this piece captures another piece, it removes it from the pieces vector.
	ob[0]->notify(from, to, pieces[i]->get_color(), pieces[i]->get_name());

	std::tuple<Square, PieceName, Color> after{from, pieces[i]->get_name(), pieces[i]->get_color()};
	std::pair<std::tuple<Square, PieceName, Color>, std::tuple<Square, PieceName, Color>> thismove{before, after};

	moves.push_back(thismove);
	moved = true;
	turn = static_cast<Color>(static_cast<int>(turn) + 1 % 2);
	return true;
      }
    }
    if (!moved) {
      /* Debugging pieces array
      for (int i = 0; i < pieces.size(); i++) {
	std::cout << pieces[i]->get_cursq().get_row() << " " << pieces[i]->get_cursq().get_col() << std::endl;
      }
      */
      throw Exception{"Invalid Movement Command: No piece on starting square (" + s + ")"};
    }
  } else {
    throw Exception{"Invalid Movement Command: " + s};
  }
  return false;
}

bool Board::game_end(void) {
  try {
    Result r = this->winner();
    return true;
  } catch (Exception &e) {
    return false;
  }
}

Result Board::winner(void) {

  // cases for black wins, white wins or draw by stalemate
  for (int i = 0; i < pieces.size(); i++) {
    if (pieces[i]->get_name() == PieceName::King) {
      if (pieces[i]->get_color() == Color::White &&
	pieces[i]->is_checkmated() == true) {
	return Result::BlackWins;
      } else if (pieces[i]->get_color() == Color::White &&
	pieces[i]->is_checkmated() == true) {
	return Result::WhiteWins;
      } else if (pieces[i]->is_stalemated() == true) {
	return Result::DrawByStalemate;
      }
    }
  }

  throw Exception{"No result"};

  // TODO:
  // cases for draw by insufficient material
  // cases for draw by threefold repetition
}
