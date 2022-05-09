#include "board.h"

Board::Board(TextDisplay *td) {
  this->td = td;
  for (int i = 1; i <= 8; i++) {
    auto white_pawn = new Pawn(this, Square(2,i), Color::White);
    pieces.push_back(white_pawn);
    auto black_pawn = new Pawn(this, Square(7,i), Color::Black);
    pieces.push_back(black_pawn);
  }

  auto white_rook1 = new Rook(this, Square(1, 1), Color::White);
  auto white_knight1 = new Knight(this, Square(1, 2), Color::White);
  auto white_bishop1 = new Bishop(this, Square(1, 3), Color::White);
  auto white_queen = new Queen(this, Square(1, 4), Color::White);
  auto white_king = new King(this, Square(1, 5), Color::White);
  auto white_bishop2 = new Bishop(this, Square(1, 6), Color::White);
  auto white_knight2 = new Knight(this, Square(1, 7), Color::White);
  auto white_rook2 = new Rook(this, Square(1, 8), Color::White);
  auto black_rook1 = new Rook(this, Square(8, 1), Color::Black);
  auto black_knight1 = new Knight(this, Square(8, 2), Color::Black);
  auto black_bishop1 = new Bishop(this, Square(8, 3), Color::Black);
  auto black_queen = new Queen(this, Square(8, 4), Color::Black);
  auto black_king = new King(this, Square(8, 5), Color::Black);
  auto black_bishop2 = new Bishop(this, Square(8, 6), Color::Black);
  auto black_knight2 = new Knight(this, Square(8, 7), Color::Black);
  auto black_rook2 = new Rook(this, Square(8, 8), Color::Black);

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
    td->print_moves(moves.begin());
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
	auto thispiece = pieces[i];
	std::tuple<Square, PieceName, Color> before{from, thispiece->get_name(), thispiece->get_color()};


	auto removepiece = thispiece->move(pieces.begin(), pieces.end(), to); // returns the iterator to the piece to remove, or returns end. 

	td->notify(from, to, thispiece->get_color(), thispiece->get_name());

	std::tuple<Square, PieceName, Color> after{from, thispiece->get_name(), thispiece->get_color()};
	std::pair<std::tuple<Square, PieceName, Color>, std::tuple<Square, PieceName, Color>> thismove{before, after};

	if (removepiece != pieces.end()) {
	  pieces.erase(removepiece);
	}

	moves.push_back(thismove);
	moved = true;
	turn = static_cast<Color>(static_cast<int>(turn) + 1 % 2);
	return true;
      }
    }
    if (!moved) {
      /*
      for (int i = 0; i < pieces.size(); i++) {
	std::cout << pieces[i]->get_cursq().get_row() << " " << pieces[i]->get_cursq().get_col() << std::endl;
      }
      std::cout << "Asked square: " << from.get_row() << " " << from.get_col() << " -> " << to.get_row() << " " << to.get_col() << std::endl;
      std::cout << "Current turn is " << (turn == Color::White ? "White" : "Black") << std::endl;
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
	pieces[i]->is_checkmated(pieces.begin(), pieces.end(), pieces.end()) == true) {
	return Result::BlackWins;
      } else if (pieces[i]->get_color() == Color::Black &&
	pieces[i]->is_checkmated(pieces.begin(), pieces.end(), pieces.end()) == true) {
	return Result::WhiteWins;
      } else if (pieces[i]->is_stalemated(pieces.begin(), pieces.end(), pieces.end()) == true) {
	return Result::DrawByStalemate;
      }
    }
  }

  throw Exception{"No result"};

  // TODO:
  // cases for draw by insufficient material
  // cases for draw by threefold repetition
}
