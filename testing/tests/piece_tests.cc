#include "gtest/gtest.h"
#include "../../code/piece.h"
#include "../../code/board.h"
#include "../../code/textdisplay.h"

//=== Pawn Tests ===
TEST(PawnTests, PawnInitialization) {
  auto white_pawn = new Pawn(nullptr, {2, 5}, Color::White);
  ASSERT_EQ(white_pawn->get_cursq().get_row(), 2);
  ASSERT_EQ(white_pawn->get_cursq().get_col(), 5);
  ASSERT_EQ(white_pawn->piece_moved(), false);
  ASSERT_EQ(white_pawn->get_color(), Color::White);
  ASSERT_EQ(white_pawn->get_name(), PieceName::Pawn);
  auto black_pawn = new Pawn(nullptr, {5, 2}, Color::Black);
  ASSERT_EQ(black_pawn->get_cursq().get_row(), 5);
  ASSERT_EQ(black_pawn->get_cursq().get_col(), 2);
  ASSERT_EQ(black_pawn->piece_moved(), false);
  ASSERT_EQ(black_pawn->get_color(), Color::Black);
  ASSERT_EQ(black_pawn->get_name(), PieceName::Pawn);
}

TEST(PawnTests, PawnSetters) {
  auto wp_setter = new Pawn(nullptr, {2, 5}, Color::White);
  wp_setter->set_cursq({3,4});
  ASSERT_EQ(wp_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(wp_setter->get_cursq().get_col(), 4);
  wp_setter->set_moved(true);
  ASSERT_EQ(wp_setter->piece_moved(), true);
  auto bp_setter = new Pawn(nullptr, {2, 5}, Color::Black);
  bp_setter->set_cursq({3,4});
  ASSERT_EQ(bp_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(bp_setter->get_cursq().get_col(), 4);
  bp_setter->set_moved(true);
  ASSERT_EQ(bp_setter->piece_moved(), true);
}

TEST(PawnTests, PawnMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wpeb1 = new Pawn(b, {2, 5}, Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(wpeb1);
  // a few random tests, rather programming pawn moves in the test suite (can lead to errors).
  ASSERT_NO_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {3,5}));
  ASSERT_NO_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {4,5}));
  ASSERT_ANY_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {5,5}));
  ASSERT_ANY_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {2,6}));
  ASSERT_ANY_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {2,5}));
  ASSERT_ANY_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {2,4}));
  ASSERT_ANY_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {3,6}));
  ASSERT_ANY_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {3,4}));
  ASSERT_ANY_THROW(wpeb1->can_move_to(pieces.begin(), pieces.end(), {1,5}));
  // out of bounds not checked, as Square always produces row and column that are in bounds
  pieces.clear();
  auto wpeb2 = new Pawn(b, {7, 5}, Color::White);
  pieces.push_back(wpeb2);
  ASSERT_NO_THROW(wpeb2->can_move_to(pieces.begin(), pieces.end(), {8,5}));
  ASSERT_ANY_THROW(wpeb2->can_move_to(pieces.begin(), pieces.end(), {8,6}));
  ASSERT_ANY_THROW(wpeb2->can_move_to(pieces.begin(), pieces.end(), {8,4}));
  ASSERT_ANY_THROW(wpeb2->can_move_to(pieces.begin(), pieces.end(), {6,5}));
  ASSERT_ANY_THROW(wpeb2->can_move_to(pieces.begin(), pieces.end(), {5,5}));

  pieces.clear();
  auto bpeb1 = new Pawn(b, {7,3}, Color::Black);
  pieces.push_back(bpeb1);
  ASSERT_NO_THROW(bpeb1->can_move_to(pieces.begin(), pieces.end(), {6,3}));
  ASSERT_NO_THROW(bpeb1->can_move_to(pieces.begin(), pieces.end(), {5,3}));
  ASSERT_ANY_THROW(bpeb1->can_move_to(pieces.begin(), pieces.end(), {8,3}));
  ASSERT_ANY_THROW(bpeb1->can_move_to(pieces.begin(), pieces.end(), {6,4}));
  ASSERT_ANY_THROW(bpeb1->can_move_to(pieces.begin(), pieces.end(), {6,2}));
  ASSERT_ANY_THROW(bpeb1->can_move_to(pieces.begin(), pieces.end(), {7,2}));
  ASSERT_ANY_THROW(bpeb1->can_move_to(pieces.begin(), pieces.end(), {7,3}));

  pieces.clear();
  auto bpeb2 = new Pawn(b, {2,3}, Color::Black);
  pieces.push_back(bpeb2);
  ASSERT_NO_THROW(bpeb2->can_move_to(pieces.begin(), pieces.end(), {1,3}));
  ASSERT_ANY_THROW(bpeb2->can_move_to(pieces.begin(), pieces.end(), {1,2}));
  ASSERT_ANY_THROW(bpeb2->can_move_to(pieces.begin(), pieces.end(), {1,4}));
  ASSERT_ANY_THROW(bpeb2->can_move_to(pieces.begin(), pieces.end(), {3,3}));
  ASSERT_ANY_THROW(bpeb2->can_move_to(pieces.begin(), pieces.end(), {4,3}));
  ASSERT_ANY_THROW(bpeb2->can_move_to(pieces.begin(), pieces.end(), {2,4}));
  ASSERT_ANY_THROW(bpeb2->can_move_to(pieces.begin(), pieces.end(), {2,2}));

  /*
  for (int i = 2; i <= 8; i++) { // pawns start on 2nd row
    for (int j = 1; j <= 8; j++) {
      auto wp_move_on_eb = new Pawn(b, {i, j}, Color::White);
      std::vector<Piece*> pieces;
      pieces.push_back(wp_move_on_eb);
      for (int x = 1; x <= 8; x++) {
	for (int y = 1; y <= 8; y++) {
	  if (i == x && j == y) {
	    continue;
	  }
	  if (i == 2) {
	    if (y == j && (x - i > 0 && x - i <= 2)) {
	      ASSERT_NO_THROW(wp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "Exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	    }
	  } else if (y == j && i != 8 && (x - i == 1)) {
	    ASSERT_NO_THROW(wp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "Exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	  } else {
	    ASSERT_ANY_THROW(wp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "No exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	  }
	}
      }
    }
  }
  for (int i = 1; i <= 7; i++) { // pawns start on 2nd row
    for (int j = 1; j <= 8; j++) {
      auto bp_move_on_eb = new Pawn(b, {i, j}, Color::Black);
      std::vector<Piece*> pieces;
      pieces.push_back(bp_move_on_eb);
      for (int x = 1; x <= 8; x++) {
	for (int y = 1; y <= 8; y++) {
	  if (i == x && j == y) {
	    continue;
	  }
	  if (i == 7) {
	    if (y == j && (i - x > 0 && i - x <= 2)) {
	      ASSERT_NO_THROW(bp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "Exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	    }
	  } else if (y == j && i != 1 && (i - x == 1)) {
	    ASSERT_NO_THROW(bp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "Exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	  } else {
	    ASSERT_ANY_THROW(bp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "No exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	  }
	}
      }
    }
  }
  */
}

TEST(PawnTests, PawnMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wpc1 = new Pawn(b, {5, 5}, Color::White);
  auto bpiece_to_be_captured1 = new Rook(b, {6, 6}, Color::Black);
  auto bpiece_to_be_captured2 = new Queen(b, {6, 4}, Color::Black);
  auto bpiece_to_be_captured3 = new Bishop(b, {4, 6}, Color::Black);
  auto bpiece_to_be_captured4 = new Knight(b, {4, 4}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(wpc1);
  pieces.push_back(bpiece_to_be_captured1);
  pieces.push_back(bpiece_to_be_captured2);
  pieces.push_back(bpiece_to_be_captured3);
  pieces.push_back(bpiece_to_be_captured4);
  ASSERT_NO_THROW(wpc1->can_move_to(pieces.begin(), pieces.end(), {6, 6}));
  ASSERT_NO_THROW(wpc1->can_move_to(pieces.begin(), pieces.end(), {6, 4}));
  ASSERT_ANY_THROW(wpc1->can_move_to(pieces.begin(), pieces.end(), {4, 6}));
  ASSERT_ANY_THROW(wpc1->can_move_to(pieces.begin(), pieces.end(), {4, 4}));

  pieces.pop_back();
  pieces.pop_back();
  pieces.pop_back();
  pieces.pop_back();

  auto wp_cant_be_captured1 = new Pawn(b, {6,4}, Color::White);
  auto wp_cant_be_captured2 = new Pawn(b, {6,6}, Color::White);
  pieces.push_back(wp_cant_be_captured1);
  pieces.push_back(wp_cant_be_captured2);
  ASSERT_ANY_THROW(wpc1->can_move_to(pieces.begin(), pieces.end(), {6, 6}));
  ASSERT_ANY_THROW(wpc1->can_move_to(pieces.begin(), pieces.end(), {6, 4}));


  auto bpc1 = new Pawn(b, {5, 5}, Color::Black);
  auto wpiece_to_be_captured1 = new Rook(b, {6, 6}, Color::White);
  auto wpiece_to_be_captured2 = new Queen(b, {6, 4}, Color::White);
  auto wpiece_to_be_captured3 = new Bishop(b, {4, 6}, Color::White);
  auto wpiece_to_be_captured4 = new Knight(b, {4, 4}, Color::White);
  pieces.clear();
  pieces.push_back(wpc1);
  pieces.push_back(wpiece_to_be_captured1);
  pieces.push_back(wpiece_to_be_captured2);
  pieces.push_back(wpiece_to_be_captured3);
  pieces.push_back(wpiece_to_be_captured4);
  ASSERT_ANY_THROW(bpc1->can_move_to(pieces.begin(), pieces.end(), {6, 6}));
  ASSERT_ANY_THROW(bpc1->can_move_to(pieces.begin(), pieces.end(), {6, 4}));
  ASSERT_NO_THROW(bpc1->can_move_to(pieces.begin(), pieces.end(), {4, 6}));
  ASSERT_NO_THROW(bpc1->can_move_to(pieces.begin(), pieces.end(), {4, 4}));

  pieces.pop_back();
  pieces.pop_back();
  pieces.pop_back();
  pieces.pop_back();

  auto bp_cant_be_captured1 = new Pawn(b, {4,4}, Color::Black);
  auto bp_cant_be_captured2 = new Pawn(b, {4,6}, Color::Black);
  pieces.push_back(bp_cant_be_captured1);
  pieces.push_back(bp_cant_be_captured2);
  ASSERT_ANY_THROW(bpc1->can_move_to(pieces.begin(), pieces.end(), {4, 4}));
  ASSERT_ANY_THROW(bpc1->can_move_to(pieces.begin(), pieces.end(), {4, 6}));
}

TEST(PawnTests, PawnMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto pmwbc1 = new Pawn(b, {2,5}, Color::White);
  auto pmwbc2 = new Pawn(b, {2,6}, Color::White);
  auto king = new King(b, {1,6}, Color::White);
  auto bishop = new Bishop(b, {4,3}, Color::Black);
  auto rook = new Rook(b, {7,6}, Color::Black);
  auto pawn = new Pawn(b, {3,7}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(pmwbc1);
  pieces.push_back(pmwbc2);
  pieces.push_back(king);
  pieces.push_back(bishop);
  pieces.push_back(rook);
  pieces.push_back(pawn);
  ASSERT_ANY_THROW(pmwbc1->move(pieces.begin(), pieces.end(), {4,5}));
  ASSERT_ANY_THROW(pmwbc1->move(pieces.begin(), pieces.end(), {3,7}));
}

TEST(PawnTests, PawnPromotion) {
}

//=== Knight Tests ===
TEST(KnightTests, KnightInitialization) {
  auto white_knight = new Knight(nullptr, {2, 5}, Color::White);
  ASSERT_EQ(white_knight->get_cursq().get_row(), 2);
  ASSERT_EQ(white_knight->get_cursq().get_col(), 5);
  ASSERT_EQ(white_knight->piece_moved(), false);
  ASSERT_EQ(white_knight->get_color(), Color::White);
  ASSERT_EQ(white_knight->get_name(), PieceName::Knight);
  auto black_knight = new Knight(nullptr, {5, 2}, Color::Black);
  ASSERT_EQ(black_knight->get_cursq().get_row(), 5);
  ASSERT_EQ(black_knight->get_cursq().get_col(), 2);
  ASSERT_EQ(black_knight->piece_moved(), false);
  ASSERT_EQ(black_knight->get_color(), Color::Black);
  ASSERT_EQ(black_knight->get_name(), PieceName::Knight);
}

TEST(KnightTests, KnightSetters) {
  auto wn_setter = new Knight(nullptr, {2, 5}, Color::White);
  wn_setter->set_cursq({3,4});
  ASSERT_EQ(wn_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(wn_setter->get_cursq().get_col(), 4);
  wn_setter->set_moved(true);
  ASSERT_EQ(wn_setter->piece_moved(), true);
  auto bn_setter = new Knight(nullptr, {2, 5}, Color::Black);
  bn_setter->set_cursq({3,4});
  ASSERT_EQ(bn_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(bn_setter->get_cursq().get_col(), 4);
  bn_setter->set_moved(true);
  ASSERT_EQ(bn_setter->piece_moved(), true);
}

TEST(KnightTests, KnightMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wneb1 = new Knight(b, {5, 5}, Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(wneb1);
  ASSERT_ANY_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {5, 5}));
  ASSERT_NO_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {7, 6}));
  ASSERT_NO_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {7, 4}));
  ASSERT_NO_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {3, 6}));
  ASSERT_NO_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {3, 4}));
  ASSERT_NO_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {4, 7}));
  ASSERT_NO_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {6, 7}));
  ASSERT_NO_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {4, 3}));
  ASSERT_NO_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {6, 3}));
  ASSERT_ANY_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {8, 5}));
  ASSERT_ANY_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {2, 5}));
  ASSERT_ANY_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {5, 8}));
  ASSERT_ANY_THROW(wneb1->can_move_to(pieces.begin(), pieces.end(), {5, 2}));

  pieces.clear();
  auto wneb2 = new Knight(b, {2, 3}, Color::White);
  ASSERT_NO_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {1, 1}));
  ASSERT_NO_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {1, 5}));
  ASSERT_NO_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {3, 1}));
  ASSERT_NO_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {3, 5}));
  ASSERT_NO_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {4, 2}));
  ASSERT_NO_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {4, 4}));
  ASSERT_ANY_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {1,2}));
  ASSERT_ANY_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {1,4}));
  ASSERT_ANY_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {1,3}));
  ASSERT_ANY_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {2,2}));
  ASSERT_ANY_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {2,4}));
  ASSERT_ANY_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {3,2}));
  ASSERT_ANY_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {3,3}));
  ASSERT_ANY_THROW(wneb2->can_move_to(pieces.begin(), pieces.end(), {3,4}));

  pieces.clear();
  auto bneb1 = new Knight(b, {1, 4}, Color::Black);
  pieces.push_back(bneb1);
  ASSERT_NO_THROW(bneb1->can_move_to(pieces.begin(), pieces.end(), {2, 6}));
  ASSERT_NO_THROW(bneb1->can_move_to(pieces.begin(), pieces.end(), {2, 2}));
  ASSERT_NO_THROW(bneb1->can_move_to(pieces.begin(), pieces.end(), {3, 5}));
  ASSERT_NO_THROW(bneb1->can_move_to(pieces.begin(), pieces.end(), {3, 3}));
  ASSERT_ANY_THROW(bneb1->can_move_to(pieces.begin(), pieces.end(), {3, 6}));
  ASSERT_ANY_THROW(bneb1->can_move_to(pieces.begin(), pieces.end(), {3, 2}));

  pieces.clear();
  auto bneb2 = new Knight(b, {1, 1}, Color::Black);
  pieces.push_back(bneb2);
  ASSERT_NO_THROW(bneb2->can_move_to(pieces.begin(), pieces.end(), {3,2}));
  ASSERT_NO_THROW(bneb2->can_move_to(pieces.begin(), pieces.end(), {2,3}));
  ASSERT_ANY_THROW(bneb2->can_move_to(pieces.begin(), pieces.end(), {3,3}));
  ASSERT_ANY_THROW(bneb2->can_move_to(pieces.begin(), pieces.end(), {2,2}));
  ASSERT_ANY_THROW(bneb2->can_move_to(pieces.begin(), pieces.end(), {1,2}));
  ASSERT_ANY_THROW(bneb2->can_move_to(pieces.begin(), pieces.end(), {2,1}));
}

TEST(KnightTests, KnightMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wknight = new Knight(b, {5,5}, Color::White);
  auto rook = new Rook(b, {7,6}, Color::Black);
  auto bishop = new Bishop(b, {3, 6}, Color::White);
  auto bknight = new Knight(b, {5,7}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(wknight);
  pieces.push_back(rook);
  pieces.push_back(bishop);
  pieces.push_back(bknight);
  ASSERT_NO_THROW(wknight->can_move_to(pieces.begin(), pieces.end(), {7,6}));
  ASSERT_ANY_THROW(wknight->can_move_to(pieces.begin(), pieces.end(), {3,6}));
  ASSERT_NO_THROW(bknight->can_move_to(pieces.begin(), pieces.end(), {3,6}));
  ASSERT_ANY_THROW(bknight->can_move_to(pieces.begin(), pieces.end(), {7,6}));
}

TEST(KnightTests, KnightMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wknight = new Knight(b, {2,2}, Color::White);
  auto wking = new King(b, {1,2}, Color::White);
  auto bknight = new Knight(b, {7,2}, Color::Black);
  auto bking = new King(b, {8,2}, Color::Black);
  auto wrook = new Rook(b, {6,2}, Color::White);
  auto brook = new Rook(b, {3,2}, Color::Black);
  auto bbishop = new Bishop(b, {1,4}, Color::Black);
  auto wbishop = new Bishop(b, {8,4}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(wknight);
  pieces.push_back(wking);
  pieces.push_back(wrook);
  pieces.push_back(wbishop);
  pieces.push_back(bknight);
  pieces.push_back(bking);
  pieces.push_back(brook);
  pieces.push_back(bbishop);
  ASSERT_ANY_THROW(wknight->move(pieces.begin(), pieces.end(), {3,4}));
  ASSERT_ANY_THROW(wknight->move(pieces.begin(), pieces.end(), {1,4}));
  ASSERT_ANY_THROW(wknight->move(pieces.begin(), pieces.end(), {6,4}));
  ASSERT_ANY_THROW(wknight->move(pieces.begin(), pieces.end(), {8,4}));
}

//=== Bishop Tests ===
TEST(BishopTests, BishopInitialization) {
  auto white_bishop = new Bishop(nullptr, {2, 5}, Color::White);
  ASSERT_EQ(white_bishop->get_cursq().get_row(), 2);
  ASSERT_EQ(white_bishop->get_cursq().get_col(), 5);
  ASSERT_EQ(white_bishop->piece_moved(), false);
  ASSERT_EQ(white_bishop->get_color(), Color::White);
  ASSERT_EQ(white_bishop->get_name(), PieceName::Bishop);
  auto black_bishop = new Bishop(nullptr, {5, 2}, Color::Black);
  ASSERT_EQ(black_bishop->get_cursq().get_row(), 5);
  ASSERT_EQ(black_bishop->get_cursq().get_col(), 2);
  ASSERT_EQ(black_bishop->piece_moved(), false);
  ASSERT_EQ(black_bishop->get_color(), Color::Black);
  ASSERT_EQ(black_bishop->get_name(), PieceName::Bishop);
}

TEST(BishopTests, BishopSetters) {
  auto wb_setter = new Bishop(nullptr, {2, 5}, Color::White);
  wb_setter->set_cursq({3,4});
  ASSERT_EQ(wb_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(wb_setter->get_cursq().get_col(), 4);
  wb_setter->set_moved(true);
  ASSERT_EQ(wb_setter->piece_moved(), true);
  auto bb_setter = new Bishop(nullptr, {2, 5}, Color::Black);
  bb_setter->set_cursq({3,4});
  ASSERT_EQ(bb_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(bb_setter->get_cursq().get_col(), 4);
  bb_setter->set_moved(true);
  ASSERT_EQ(bb_setter->piece_moved(), true);
}

TEST(BishopTests, BishopMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto b1 = new Bishop(b, {5,5}, Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(b1);
  ASSERT_NO_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {1,1}));
  ASSERT_NO_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {8,8}));
  ASSERT_NO_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {8,2}));
  ASSERT_NO_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {2,8}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {1,8}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {8,1}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {8,7}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {2,1}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {5,1}));

  pieces.clear();
  auto b2 = new Bishop(b, {5,4}, Color::Black);
  pieces.push_back(b2);
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {1,1}));
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {8,8}));
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {8,2}));
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {2,8}));
  ASSERT_NO_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {1,8}));
  ASSERT_NO_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {8,1}));
  ASSERT_NO_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {8,7}));
  ASSERT_NO_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {2,1}));
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {1,2}));
}

TEST(BishopTests, BishopMovementPieceBlocking) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto b1 = new Bishop(b, {5,5}, Color::White);
  auto pawn = new Pawn(b, {2,2}, Color::White);
  auto rook = new Rook(b, {7,7}, Color::Black);
  auto knight = new Knight(b, {7,3}, Color::White);
  auto queen = new Queen(b, {3,7}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(b1);
  pieces.push_back(pawn);
  pieces.push_back(rook);
  pieces.push_back(knight);
  pieces.push_back(queen);
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {1,1}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {8,8}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {8,2}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {2,8}));

  pieces.clear();
  auto b2 = new Bishop(b, {5,4}, Color::Black);
  auto pawn2 = new Pawn(b, {2,7}, Color::White);
  auto rook2 = new Rook(b, {7,2}, Color::Black);
  auto knight2 = new Knight(b, {7,6}, Color::White);
  auto queen2 = new Queen(b, {3,2}, Color::Black);
  pieces.push_back(b2);
  pieces.push_back(pawn2);
  pieces.push_back(rook2);
  pieces.push_back(knight2);
  pieces.push_back(queen2);
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {1,8}));
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {8,1}));
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {8,7}));
  ASSERT_ANY_THROW(b2->can_move_to(pieces.begin(), pieces.end(), {2,1}));
}

TEST(BishopTests, BishopMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto b1 = new Bishop(b, {5,5}, Color::White);
  auto pawn = new Pawn(b, {2,2}, Color::White);
  auto rook = new Rook(b, {7,7}, Color::Black);
  auto knight = new Knight(b, {7,3}, Color::White);
  auto queen = new Queen(b, {3,7}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(b1);
  pieces.push_back(pawn);
  pieces.push_back(rook);
  pieces.push_back(knight);
  pieces.push_back(queen);
  ASSERT_NO_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {7,7}));
  ASSERT_NO_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {3,7}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {2,2}));
  ASSERT_ANY_THROW(b1->can_move_to(pieces.begin(), pieces.end(), {7,3}));
}

TEST(BishopTests, BishopMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto b1 = new Bishop(b, {5,5}, Color::White);
  auto b2 = new Bishop(b, {5,6}, Color::White);
  auto king = new King(b, {6,6}, Color::White);
  auto rook = new Rook(b, {1,6}, Color::Black);
  auto queen = new Queen(b, {1,1}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(b1);
  pieces.push_back(b2);
  pieces.push_back(king);
  pieces.push_back(rook);
  pieces.push_back(queen);
  ASSERT_ANY_THROW(b1->move(pieces.begin(), pieces.end(), {6,4}));
  ASSERT_ANY_THROW(b2->move(pieces.begin(), pieces.end(), {6,7}));
}

//=== Rook Tests ===
TEST(RookTests, RookInitialization) {
  auto white_rook = new Rook(nullptr, {2, 5}, Color::White);
  ASSERT_EQ(white_rook->get_cursq().get_row(), 2);
  ASSERT_EQ(white_rook->get_cursq().get_col(), 5);
  ASSERT_EQ(white_rook->piece_moved(), false);
  ASSERT_EQ(white_rook->get_color(), Color::White);
  ASSERT_EQ(white_rook->get_name(), PieceName::Rook);
  auto black_rook = new Rook(nullptr, {5, 2}, Color::Black);
  ASSERT_EQ(black_rook->get_cursq().get_row(), 5);
  ASSERT_EQ(black_rook->get_cursq().get_col(), 2);
  ASSERT_EQ(black_rook->piece_moved(), false);
  ASSERT_EQ(black_rook->get_color(), Color::Black);
  ASSERT_EQ(black_rook->get_name(), PieceName::Rook);
}

TEST(RookTests, RookSetters) {
  auto wr_setter = new Rook(nullptr, {2, 5}, Color::White);
  wr_setter->set_cursq({3,4});
  ASSERT_EQ(wr_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(wr_setter->get_cursq().get_col(), 4);
  wr_setter->set_moved(true);
  ASSERT_EQ(wr_setter->piece_moved(), true);
  auto br_setter = new Rook(nullptr, {2, 5}, Color::Black);
  br_setter->set_cursq({3,4});
  ASSERT_EQ(br_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(br_setter->get_cursq().get_col(), 4);
  br_setter->set_moved(true);
  ASSERT_EQ(br_setter->piece_moved(), true);
}

TEST(RookTests, RookMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto rook = new Rook(b, {5,5}, Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(rook);
  ASSERT_NO_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {1,5}));
  ASSERT_NO_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {8,5}));
  ASSERT_NO_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {5,1}));
  ASSERT_NO_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {8,5}));
  ASSERT_ANY_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {8,8}));
  ASSERT_ANY_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {1,1}));
}

TEST(RookTests, RookMovementPieceBlocking) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto rook = new Rook(b, {5,5}, Color::White);
  auto queen = new Queen(b, {2,5}, Color::White);
  auto knight = new Knight(b, {7,5}, Color::Black);
  auto bishop = new Bishop(b, {5,2}, Color::White);
  auto pawn = new Pawn(b, {5,7}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(rook);
  pieces.push_back(queen);
  pieces.push_back(knight);
  pieces.push_back(bishop);
  pieces.push_back(pawn);
  ASSERT_ANY_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {1,5}));
  ASSERT_ANY_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {8,5}));
  ASSERT_ANY_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {5,1}));
  ASSERT_ANY_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {8,5}));
}

TEST(RookTests, RookMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto rook = new Rook(b, {5,5}, Color::White);
  auto queen = new Queen(b, {2,5}, Color::White);
  auto knight = new Knight(b, {7,5}, Color::Black);
  auto bishop = new Bishop(b, {5,2}, Color::White);
  auto pawn = new Pawn(b, {5,7}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(rook);
  pieces.push_back(queen);
  pieces.push_back(knight);
  pieces.push_back(bishop);
  pieces.push_back(pawn);
  ASSERT_ANY_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {2,5}));
  ASSERT_NO_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {7,5}));
  ASSERT_ANY_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {5,2}));
  ASSERT_NO_THROW(rook->can_move_to(pieces.begin(), pieces.end(), {5,7}));
}

TEST(RookTests, RookMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto rook = new Rook(b, {5,5}, Color::White);
  auto king = new King(b, {6,5}, Color::White);
  auto queen = new Queen(b, {2,5}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(rook);
  pieces.push_back(king);
  pieces.push_back(queen);
  ASSERT_ANY_THROW(rook->move(pieces.begin(), pieces.end(), {5,7}));
}

//=== Queen Tests ===
TEST(QueenTests, QueenInitialization) {
  auto white_queen = new Queen(nullptr, {2, 5}, Color::White);
  ASSERT_EQ(white_queen->get_cursq().get_row(), 2);
  ASSERT_EQ(white_queen->get_cursq().get_col(), 5);
  ASSERT_EQ(white_queen->piece_moved(), false);
  ASSERT_EQ(white_queen->get_color(), Color::White);
  ASSERT_EQ(white_queen->get_name(), PieceName::Queen);
  auto black_queen = new Queen(nullptr, {5, 2}, Color::Black);
  ASSERT_EQ(black_queen->get_cursq().get_row(), 5);
  ASSERT_EQ(black_queen->get_cursq().get_col(), 2);
  ASSERT_EQ(black_queen->piece_moved(), false);
  ASSERT_EQ(black_queen->get_color(), Color::Black);
  ASSERT_EQ(black_queen->get_name(), PieceName::Queen);
}

TEST(QueenTests, QueenSetters) {
  auto wq_setter = new Queen(nullptr, {2, 5}, Color::White);
  wq_setter->set_cursq({3,4});
  ASSERT_EQ(wq_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(wq_setter->get_cursq().get_col(), 4);
  wq_setter->set_moved(true);
  ASSERT_EQ(wq_setter->piece_moved(), true);
  auto bq_setter = new Queen(nullptr, {2, 5}, Color::Black);
  bq_setter->set_cursq({3,4});
  ASSERT_EQ(bq_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(bq_setter->get_cursq().get_col(), 4);
  bq_setter->set_moved(true);
  ASSERT_EQ(bq_setter->piece_moved(), true);
}

TEST(QueenTests, QueenMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto queen = new Queen(b, {5,5}, Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(queen);
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {1,5}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,5}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {5,1}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,5}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {1,1}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,8}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,2}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {2,8}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {1,8}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,1}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,7}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {2,1}));

  pieces.clear();
  auto queen2 = new Queen(b, {5,4}, Color::Black);
  pieces.push_back(queen2);
  ASSERT_ANY_THROW(queen2->can_move_to(pieces.begin(), pieces.end(), {1,1}));
  ASSERT_ANY_THROW(queen2->can_move_to(pieces.begin(), pieces.end(), {8,8}));
  ASSERT_ANY_THROW(queen2->can_move_to(pieces.begin(), pieces.end(), {8,2}));
  ASSERT_ANY_THROW(queen2->can_move_to(pieces.begin(), pieces.end(), {2,8}));
  ASSERT_NO_THROW(queen2->can_move_to(pieces.begin(), pieces.end(), {1,8}));
  ASSERT_NO_THROW(queen2->can_move_to(pieces.begin(), pieces.end(), {8,1}));
  ASSERT_NO_THROW(queen2->can_move_to(pieces.begin(), pieces.end(), {8,7}));
  ASSERT_NO_THROW(queen2->can_move_to(pieces.begin(), pieces.end(), {2,1}));
}

TEST(QueenTests, QueenMovementPieceBlocking) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto queen = new Queen(b, {5,5}, Color::White);
  auto rook = new Rook(b, {2,5}, Color::White);
  auto knight = new Knight(b, {7,5}, Color::Black);
  auto bishop = new Bishop(b, {5,2}, Color::White);
  auto pawn = new Pawn(b, {5,7}, Color::Black);
  auto pawn2 = new Pawn(b, {2,2}, Color::White);
  auto rook2 = new Rook(b, {7,7}, Color::Black);
  auto knight2 = new Knight(b, {7,3}, Color::White);
  auto queen2 = new Queen(b, {3,7}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(queen);
  pieces.push_back(rook);
  pieces.push_back(knight);
  pieces.push_back(bishop);
  pieces.push_back(pawn);
  pieces.push_back(pawn2);
  pieces.push_back(rook2);
  pieces.push_back(knight2);
  pieces.push_back(queen2);
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {1,5}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,5}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {5,1}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,5}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {1,1}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,8}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {8,2}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {2,8}));
}

TEST(QueenTests, QueenMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto queen = new Queen(b, {5,5}, Color::White);
  auto rook = new Rook(b, {2,5}, Color::White);
  auto knight = new Knight(b, {7,5}, Color::Black);
  auto bishop = new Bishop(b, {5,2}, Color::White);
  auto pawn = new Pawn(b, {5,7}, Color::Black);
  auto pawn2 = new Pawn(b, {2,2}, Color::White);
  auto rook2 = new Rook(b, {7,7}, Color::Black);
  auto knight2 = new Knight(b, {7,3}, Color::White);
  auto queen2 = new Queen(b, {3,7}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(queen);
  pieces.push_back(rook);
  pieces.push_back(knight);
  pieces.push_back(bishop);
  pieces.push_back(pawn);
  pieces.push_back(pawn2);
  pieces.push_back(rook2);
  pieces.push_back(knight2);
  pieces.push_back(queen2);
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {2,5}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {7,5}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {5,2}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {5,7}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {2,2}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {7,7}));
  ASSERT_ANY_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {7,3}));
  ASSERT_NO_THROW(queen->can_move_to(pieces.begin(), pieces.end(), {3,7}));
}

TEST(QueenTests, QueenMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto queen = new Queen(b, {5,5}, Color::White);
  auto rook = new Rook(b, {1,5}, Color::Black);
  auto king = new King(b, {6,5}, Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(queen);
  pieces.push_back(rook);
  pieces.push_back(king);
  ASSERT_ANY_THROW(queen->move(pieces.begin(), pieces.end(), {5,8}));
}

//=== King Tests ===
TEST(KingTests, KingInitialization) {
  auto white_king = new King(nullptr, {2, 5}, Color::White);
  ASSERT_EQ(white_king->get_cursq().get_row(), 2);
  ASSERT_EQ(white_king->get_cursq().get_col(), 5);
  ASSERT_EQ(white_king->piece_moved(), false);
  ASSERT_EQ(white_king->get_color(), Color::White);
  ASSERT_EQ(white_king->get_name(), PieceName::King);
  auto black_king = new King(nullptr, {5, 2}, Color::Black);
  ASSERT_EQ(black_king->get_cursq().get_row(), 5);
  ASSERT_EQ(black_king->get_cursq().get_col(), 2);
  ASSERT_EQ(black_king->piece_moved(), false);
  ASSERT_EQ(black_king->get_color(), Color::Black);
  ASSERT_EQ(black_king->get_name(), PieceName::King);
}

TEST(KingTests, KingSetters) {
  auto wk_setter = new King(nullptr, {2, 5}, Color::White);
  wk_setter->set_cursq({3,4});
  ASSERT_EQ(wk_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(wk_setter->get_cursq().get_col(), 4);
  wk_setter->set_moved(true);
  ASSERT_EQ(wk_setter->piece_moved(), true);
  auto bk_setter = new King(nullptr, {2, 5}, Color::Black);
  bk_setter->set_cursq({3,4});
  ASSERT_EQ(bk_setter->get_cursq().get_row(), 3);
  ASSERT_EQ(bk_setter->get_cursq().get_col(), 4);
  bk_setter->set_moved(true);
  ASSERT_EQ(bk_setter->piece_moved(), true);
}

TEST(KingTests, KingMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto king = new King(b, {5,5}, Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(king);
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {4,4}));
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {4,5}));
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {4,6}));
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {5,4}));
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {5,6}));
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {6,4}));
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {6,5}));
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {6,6}));
  ASSERT_ANY_THROW(king->can_move_to(pieces.begin(), pieces.end(), {7,6}));

  pieces.clear();
  auto king2 = new King(b, {1,5}, Color::Black);
  pieces.push_back(king2);
  ASSERT_NO_THROW(king2->can_move_to(pieces.begin(), pieces.end(), {1,4}));
  ASSERT_NO_THROW(king2->can_move_to(pieces.begin(), pieces.end(), {1,6}));
  ASSERT_NO_THROW(king2->can_move_to(pieces.begin(), pieces.end(), {2,4}));
  ASSERT_NO_THROW(king2->can_move_to(pieces.begin(), pieces.end(), {2,5}));
  ASSERT_NO_THROW(king2->can_move_to(pieces.begin(), pieces.end(), {2,6}));
  ASSERT_ANY_THROW(king2->can_move_to(pieces.begin(), pieces.end(), {1,7}));

  pieces.clear();
  auto king3 = new King(b, {1,1}, Color::White);
  pieces.push_back(king3);
  ASSERT_NO_THROW(king3->can_move_to(pieces.begin(), pieces.end(), {1,2}));
  ASSERT_NO_THROW(king3->can_move_to(pieces.begin(), pieces.end(), {2,1}));
  ASSERT_NO_THROW(king3->can_move_to(pieces.begin(), pieces.end(), {2,2}));
  ASSERT_ANY_THROW(king3->can_move_to(pieces.begin(), pieces.end(), {3,3}));
}

TEST(KingTests, KingMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto king = new King(b, {5,5}, Color::White);
  auto pawn = new Pawn(b, {4,4}, Color::Black);
  auto bishop = new Bishop(b, {6,6}, Color::Black);
  auto rook = new Rook(b, {4,6}, Color::White);
  auto queen = new Queen(b, {6,4}, Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(king);
  pieces.push_back(pawn);
  pieces.push_back(bishop);
  pieces.push_back(rook);
  pieces.push_back(queen);
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {4,4}));
  ASSERT_ANY_THROW(king->can_move_to(pieces.begin(), pieces.end(), {4,6}));
  ASSERT_ANY_THROW(king->can_move_to(pieces.begin(), pieces.end(), {6,4}));
  ASSERT_NO_THROW(king->can_move_to(pieces.begin(), pieces.end(), {6,6}));
}

TEST(KingTests, KingMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto king = new King(b, {5,5}, Color::White);
  auto bishop = new Bishop(b, {5,4}, Color::Black);
  auto rook = new Rook(b, {1,6}, Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(king);
  pieces.push_back(bishop);
  pieces.push_back(rook);
  ASSERT_ANY_THROW(king->move(pieces.begin(), pieces.end(), {6,5}));
  ASSERT_ANY_THROW(king->move(pieces.begin(), pieces.end(), {6,6}));
}
