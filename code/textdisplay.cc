#include "textdisplay.h"
#include <iostream>
#include <iomanip>

//===Helper===

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

//===


TextDisplay::TextDisplay(std::shared_ptr<Board> b)
  : Display(b)
{
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      board[i][j] = ' ';
    }
  }

  for (int i = 0; i < 8; i++) {
    board[1][i] = 'P';
    board[6][i] = 'p';
  }

  board[0][0] = 'R';
  board[0][1] = 'N';
  board[0][2] = 'B';
  board[0][3] = 'Q';
  board[0][4] = 'K';
  board[0][5] = 'B';
  board[0][6] = 'N';
  board[0][7] = 'R';
  board[7][0] = 'r';
  board[7][1] = 'n';
  board[7][2] = 'b';
  board[7][3] = 'q';
  board[7][4] = 'k';
  board[7][5] = 'b';
  board[7][6] = 'n';
  board[7][7] = 'r';

  // welcome message
  std::cout << "Welcome to Chess!" << std::endl;
}

/*
void TextDisplay::welcome_msg(void) {
  std::cout << "Welcome to Chess!" << std::endl;
}
*/

void TextDisplay::handle_input(void) {
  while(!b->game_end()) {
    std::string s;
    auto turn = b->whose_move();
    std::cout << ((turn == Color::White) ? "White" : "Black") << " to move. Please enter your move: " << std::endl;
    std::cin >> s;
    if (s.size() == 1 && s[0] == 'p') {
      auto m = std::make_shared<Move>();
      m->it = InputType::Print;
      auto [begin, end] = b->get_moves_const_iter();
      this->print_moves(begin, end);
    } else if (s == "quit") {
      auto m = std::make_shared<Move>();
      m->it = InputType::Quit;
      return;
    } else if ((s.size() >= 4) &&
        (s[0] >= 'a' && s[0] <= 'h') &&
        (s[1] >= '1' && s[1] <= '8') &&
        (s[2] >= 'a' && s[2] <= 'h') &&
        (s[3] >= '1' && s[3] <= '8')) {
      auto from = std::make_shared<Square>(s[1] - '0', s[0] - 'a' + 1);
      auto to = std::make_shared<Square>(s[3] - '0', s[2] - 'a' + 1);
      auto retval = std::make_shared<Move>();
      retval->mt = MoveType::Unknown;
      retval->color = turn;
      retval->from = from;
      retval->to = to;
      if ((s.size() == 6) &&
    ((s[5] == 'q' || s[5] == 'Q'))) {
        retval->mt = MoveType::Promotion;
        retval->promoted_to = PieceName::Queen;
      } else if ((s.size() == 6) &&
    ((s[5] == 'r' || s[5] == 'R'))) {
        retval->mt = MoveType::Promotion;
        retval->promoted_to = PieceName::Rook;
      } else if ((s.size() == 6) &&
    ((s[5] == 'b' || s[5] == 'B'))) {
        retval->mt = MoveType::Promotion;
        retval->promoted_to = PieceName::Bishop;
      } else if ((s.size() == 6) &&
    ((s[5] == 'n' || s[5] == 'N'))) {
        retval->mt = MoveType::Promotion;
        retval->promoted_to = PieceName::Knight;
      }
      retval->it = InputType::Move;
      try {
        b->move(retval);
      } catch(...) {}
      this->clear_board();
      auto [begin, end] = b->get_pieces_const_iter();
      this->draw_board(begin, end);
      this->print_board();
    } else {
      std::cout << "Invalid Move" << std::endl;
      continue;
    }
  }
  this->print_winner(b->winner());
  return;
}

void TextDisplay::clear_board(void) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      board[i][j] = ' ';
    }
  }
}

// draws the board on screen, and returns the drawn board (in condensed form (pseudo-FEN form)).
void TextDisplay::draw_board(std::vector<std::shared_ptr<Piece>>::const_iterator begin,
                             std::vector<std::shared_ptr<Piece>>::const_iterator end) {
  this->clear_board();
  for (auto temp = begin; temp != end; temp++) {
    auto c = piecename_to_str((*temp)->get_name(), (*temp)->get_color());
    board[(*temp)->get_cursq()->get_row() - 1][(*temp)->get_cursq()->get_col() - 1] = c;
  }
}

/*
// makes the move on this->board.
void TextDisplay::notify(Square from, Square to, Color c, PieceName p) {
  board[from.get_row() - 1][from.get_col() - 1] = ' ';
  char piece = piecename_to_str(p, c);
  board[to.get_row() - 1][to.get_col() - 1] = piece;
}
*/

void TextDisplay::print_board(void) {
  /* The board shoud look like this:
   *  +-+-+-+-+-+-+-+-+
   * 8|r|n|b|q|k|b|n|r|
   *  +-+-+-+-+-+-+-+-+
   * 7|p|p|p|p|p|p|p|p|
   *  +-+-+-+-+-+-+-+-+
   * 6| | | | | | | | |
   *  +-+-+-+-+-+-+-+-+
   * 5| | | | | | | | |
   *  +-+-+-+-+-+-+-+-+
   * 4| | | | | | | | |
   *  +-+-+-+-+-+-+-+-+
   * 3| | | | | | | | |
   *  +-+-+-+-+-+-+-+-+
   * 2|P|P|P|P|P|P|P|P|
   *  +-+-+-+-+-+-+-+-+
   * 1|R|N|B|Q|K|B|N|R|
   *  +-+-+-+-+-+-+-+-+
   *   a b c d e f g h
   */
  std::string limiter = " +-+-+-+-+-+-+-+-+";
  for (int i = 7; i >= 0; i--) {
    std::cout << limiter << std::endl;
    std::cout << i + 1;
    for (int j = 0; j < 8; j++) {
      std::cout << "|" << board[i][j];
    }
    std::cout << "|" << std::endl;
  }
  std::cout << limiter << std::endl;
  std::cout << "  a b c d e f g h" << std::endl;
}

void TextDisplay::print_moves(MoveTree::const_iterator begin,
                              MoveTree::const_iterator end) {
  int i = 1;
  for (auto temp = begin; temp != end; temp++) {
    std::string p = "";
    p += piecename_to_str((*temp)->piecename, Color::White);
    auto sq = (*temp)->to;
    std::string prefix = (*temp)->pref;
    if ((*temp)->color == Color::White) {
      std::cout << i << ". ";
    }
    std::cout << (p == "P" ? "" : p) << prefix << static_cast<char>(sq->get_col() + 'a' - 1) << static_cast<char>(sq->get_row() + '0') << " ";
    if ((*temp)->color == Color::Black) {
      i++;
      std::cout << std::endl;
    }
  }
}

void TextDisplay::print_error(Exception e) {
  std::cout << e.error() << std::endl;
}

void TextDisplay::print_winner(Result r) {
  std::string out;
  switch (r) {
    case Result::WhiteWins: out = "White wins!"; break;
    case Result::BlackWins: out = "Black wins!"; break;
    case Result::DrawByThreefoldRepetition: out = "Draw by Threefold Repetition"; break;
    case Result::DrawByInsufficientMaterial: out = "Draw by Insufficient Material"; break;
    case Result::DrawByStalemate: out = "Draw by Stalemate"; break;
    case Result::DrawBy50MoveRule: out = "Draw by 50 Move Rule"; break;
    default: break;
  }

  std::cout << out << std::endl;
}

TextDisplay::~TextDisplay(void) {}
