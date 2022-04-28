#include "textdisplay.h"
#include <iostream>

TextDisplay::TextDisplay(void) {
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
}

void TextDisplay::welcome_msg(void) {
  std::cout << "Welcome to Chess!" << std::endl;
}

std::string TextDisplay::ask_move(Color turn) {
  std::string retval;
  std::cout << ((turn == Color::White) ? "White" : "Black") << " to move. Please enter your move: " << std::endl;
  std::cin >> retval;
  return retval;
}

// makes the move on this->board.
void TextDisplay::notify(Square *from, Square *to, Color c, PieceName p) {
  board[from->get_row()][from->get_col()] = ' ';
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

  board[to->get_row()][to->get_col()] = piece;
}

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

void TextDisplay::print_error(Exception e) {
  std::cout << e.error() << std::endl;
}

void TextDisplay::print_winner(Result r) {
  std::string out;
  switch (r) {
    case Result::WhiteWins: out = "White wins!"; break;
    case Result::BlackWins: out = "Black wins!"; break;
    case Result::DrawByThreefold: out = "Draw by Threefold Repetition"; break;
    case Result::DrawByInsufficientMaterial: out = "Draw by Insufficient Material"; break;
    case Result::DrawByStalemate: out = "Draw by Stalemate"; break;
    default: break;
  }

  std::cout << out << std::endl;
}

TextDisplay::~TextDisplay(void) {}
