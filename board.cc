#include "board.h"

Board::Board(TextDisplay *td) {
  moves.push_back(nullptr);
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

  /*
  auto white_king = new King(this, Square(6, 7), Color::White);
  auto black_king = new King(this, Square(8, 8), Color::Black);
  auto white_knight1 = new Knight(this, Square(6, 8), Color::White);
  auto white_knight2 = new Knight(this, Square(7, 6), Color::White);

  pieces.push_back(white_king);
  pieces.push_back(black_king);
  pieces.push_back(white_knight1);
  pieces.push_back(white_knight2);
  */

  td->draw_board(pieces.cbegin(), pieces.cend());

}

bool Board::move(std::string s, Color turn) {
  if (s.size() == 1 && s[0] == 'p') {
    td->print_moves(moves.cbegin(), moves.cend());
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
	auto name_before = thispiece->get_name();
	auto color = thispiece->get_color();

	auto removepiece = thispiece->move(pieces.begin(), pieces.end(), to); // returns the iterator to the piece to remove, or returns end. 

	halfmoves++;

	auto name_after = thispiece->get_name();

	if (name_before == PieceName::Pawn) {
	  halfmoves = 0;
	}

	if (removepiece != pieces.end()) {
	  halfmoves = 0;
	  pieces.erase(removepiece);
	}

	td->draw_board(pieces.cbegin(), pieces.cend());

	Move *m = new Move{color, name_before, from, name_after, to, ""};
	moves.push_back(m);
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

Move *Board::get_prev_move(void) {
  return moves[moves.size() - 1];
}

bool Board::game_end(void) {
  return !(this->winner() == Result::NoResult);
}

Result Board::winner(void) {
  // cases for black wins, white wins or draw by stalemate
  Result r = Result::NoResult;
  for (int i = 0; i < pieces.size(); i++) {
    if (pieces[i]->get_name() == PieceName::King) {
      if (r == Result::BlackWins ||
	  r == Result::WhiteWins) {
	continue;
      }
      Result thisresult = pieces[i]->get_result(pieces.begin(), pieces.end(), pieces.end());
      if (thisresult == Result::WhiteWins ||
	  thisresult == Result::BlackWins) {
	r = thisresult;
      } else if (r == Result::NoResult &&
	  thisresult != Result::NoResult) {
	r = thisresult;
      }
    }
  }
  if (r == Result::NoResult &&
      halfmoves == 100) {
    return Result::DrawBy50MoveRule;
  }
  return r;
}

Board::~Board(void) {
  for (auto m : moves) {
    delete m;
  }
}
