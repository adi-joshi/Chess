#include <iostream>
#include "board.h"
#include "textdisplay.h"
#include "gui.h"

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

static std::string get_boardstring(std::vector<std::shared_ptr<Piece>>::const_iterator begin,
    std::vector<std::shared_ptr<Piece>>::const_iterator end) {
  std::string piece_positions = "";
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      piece_positions += ' ';
    }
  }
  for (auto temp = begin; temp != end; temp++) {
    auto c = piecename_to_str((*temp)->get_name(), (*temp)->get_color());
    piece_positions[(8 - (*temp)->get_cursq()->get_row()) * 8 + (*temp)->get_cursq()->get_col()] = c;
  }
  std::string retval = "";
  for (int i = 0; i < 8; i++) {
    int blank = 0;
    for (int j = 0; j < 8; j++) {
      if (piece_positions[8*i + j] == ' ') {
        blank++;
      } else {
        if (blank != 0) {
          retval += static_cast<char>(blank);
        }
        retval += piece_positions[8*i + j];
      }
    }
    retval += '/';
  }
  return retval;
}

Board::Board(void) {
  moves.push_back(nullptr);
}

void Board::setup_board(void) {
  for (int i = 1; i <= 8; i++) {
    auto white_pawn = std::make_shared<Pawn>(shared_from_this(), std::make_shared<Square>(2,i), Color::White);
    pieces.push_back(white_pawn);
    auto black_pawn = std::make_shared<Pawn>(shared_from_this(), std::make_shared<Square>(7,i), Color::Black);
    pieces.push_back(black_pawn);
  }

  auto white_rook1 = std::make_shared<Rook>(shared_from_this(), std::make_shared<Square>(1, 1), Color::White);
  auto white_knight1 = std::make_shared<Knight>(shared_from_this(), std::make_shared<Square>(1, 2), Color::White);
  auto white_bishop1 = std::make_shared<Bishop>(shared_from_this(), std::make_shared<Square>(1, 3), Color::White);
  auto white_queen = std::make_shared<Queen>(shared_from_this(), std::make_shared<Square>(1, 4), Color::White);
  auto white_king = std::make_shared<King>(shared_from_this(), std::make_shared<Square>(1, 5), Color::White);
  auto white_bishop2 = std::make_shared<Bishop>(shared_from_this(), std::make_shared<Square>(1, 6), Color::White);
  auto white_knight2 = std::make_shared<Knight>(shared_from_this(), std::make_shared<Square>(1, 7), Color::White);
  auto white_rook2 = std::make_shared<Rook>(shared_from_this(), std::make_shared<Square>(1, 8), Color::White);
  auto black_rook1 = std::make_shared<Rook>(shared_from_this(), std::make_shared<Square>(8, 1), Color::Black);
  auto black_knight1 = std::make_shared<Knight>(shared_from_this(), std::make_shared<Square>(8, 2), Color::Black);
  auto black_bishop1 = std::make_shared<Bishop>(shared_from_this(), std::make_shared<Square>(8, 3), Color::Black);
  auto black_queen = std::make_shared<Queen>(shared_from_this(), std::make_shared<Square>(8, 4), Color::Black);
  auto black_king = std::make_shared<King>(shared_from_this(), std::make_shared<Square>(8, 5), Color::Black);
  auto black_bishop2 = std::make_shared<Bishop>(shared_from_this(), std::make_shared<Square>(8, 6), Color::Black);
  auto black_knight2 = std::make_shared<Knight>(shared_from_this(), std::make_shared<Square>(8, 7), Color::Black);
  auto black_rook2 = std::make_shared<Rook>(shared_from_this(), std::make_shared<Square>(8, 8), Color::Black);

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

}

void Board::setup_board(std::vector<std::shared_ptr<Piece>> pieces) {
  this->pieces = pieces;
}

std::vector<std::shared_ptr<Piece>>::const_iterator Board::get_pieces_cbegin(void) {
  return pieces.cbegin();
}

std::vector<std::shared_ptr<Piece>>::const_iterator Board::get_pieces_cend(void) {
  return pieces.cend();
}

bool Board::move(std::shared_ptr<Move> m) {
  /*
     if (s.size() == 1 && s[0] == 'p') {
     auto placeholder = moves.cbegin();
     placeholder++;
     td->print_moves(placeholder, moves.cend());
     return false;
     }
     */
  if (m == nullptr) {
    return false;
  } else if (m->it != InputType::Move) {
    return false;
  }
  auto from = m->from;
  auto to = m->to;
  auto turn = m->color;
  bool moved = false;
  for (int i = 0; i < pieces.size(); i++) {
    if (pieces[i]->get_cursq()->get_row() == from->get_row() && pieces[i]->get_cursq()->get_col() == from->get_col() && pieces[i]->get_color() == turn) {
      std::string prefix_row = "";
      std::string prefix_col = "";
      if (pieces[i]->get_name() != PieceName::King) { // assuming that only 1 king on the board
        for (int j = 0; j < pieces.size(); j++) {
          if (j == i) {
            continue;
          } else {
            if (pieces[j]->get_name() == pieces[i]->get_name() &&
                pieces[j]->get_color() == pieces[i]->get_color()) { // another piece of the same type can move to the same square
              try {
                pieces[j]->can_move_to(pieces.begin(), pieces.end(), m);
                int r = pieces[j]->get_cursq()->get_row();
                int c = pieces[j]->get_cursq()->get_col();
                if (c != from->get_col() && prefix_col == "") {
                  prefix_col += static_cast<char>(from->get_col() + 'a' - 1);
                } else if (r != from->get_row() && prefix_row == "") {
                  prefix_row += static_cast<char>(from->get_row() + '0');
                }
              } catch(...) {}
            }
          }
        }
      }

      auto thispiece = pieces[i];
      auto name_before = m->piecename;

      if (!thispiece->move(pieces.begin(), pieces.end(), m)) { // edits m and returns true, or returns false
        if (m->error_str != "") {
          throw Exception{m->error_str};
        } else {
          throw Exception{"Illegal move"};
        }
      }

      if (m->mt == MoveType::Promotion) {
        if (m->promoted_to == PieceName::King ||
            m->promoted_to == PieceName::Pawn) {
          throw Exception{"Invalid promotion"};
        } else {
          auto thissq = std::make_shared<Square>(thispiece->get_cursq()->get_row(), thispiece->get_cursq()->get_col());
          auto thiscolor = thispiece->get_color();
          std::shared_ptr<Piece> p = nullptr;
          switch(m->promoted_to) {
            case PieceName::Queen: p = std::make_shared<Queen>(shared_from_this(), thissq, thiscolor); pieces.push_back(p); break;
            case PieceName::Rook: p = std::make_shared<Rook>(shared_from_this(), thissq, thiscolor); pieces.push_back(p); break;
            case PieceName::Bishop: p = std::make_shared<Bishop>(shared_from_this(), thissq, thiscolor); pieces.push_back(p); break;
            case PieceName::Knight: p = std::make_shared<Knight>(shared_from_this(), thissq, thiscolor); pieces.push_back(p); break;
            default: break;
          }
          pieces.erase(pieces.begin() + i);
        }
      }

      halfmoves++;

      if (name_before == PieceName::Pawn) {
        halfmoves = 0;
      }

      if (m->pieces_to_capture.size() != 0) {
        halfmoves = 0;
        std::cout << "# pieces to capture: " << m->pieces_to_capture.size() << std::endl;
        for (int i = 0; i < m->pieces_to_capture.size(); i++) {
          
          pieces.erase(m->pieces_to_capture[i]);
        }
      }

      std::string curboard = get_boardstring(pieces.cbegin(), pieces.cend());
      board_string[curboard]++;
      moves.push_back(m);

      turn = static_cast<Color>(static_cast<int>(turn) + 1 % 2);
      moved = true;
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
    std::string s = "Invalid Movement Command: No piece on starting square (";
    s += static_cast<char>(from->get_col() + 'a' - 1);
    s += static_cast<char>(from->get_row() + '0');
    s += ")";
    throw Exception{s};
  }
  return false;
}

std::shared_ptr<Move> Board::get_prev_move(void) {
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
  } else if (r == Result::NoResult) {
    for (auto it = board_string.begin(); it != board_string.end(); it++) {
      if (it->second >= 3) {
        return Result::DrawByThreefoldRepetition;
      }
    }
  }
  return r;
}

Board::~Board(void) {}
