#include "gtest/gtest.h"
#include "../../code/piece.h"
#include "../../code/board.h"
#include "../../code/textdisplay.h"

//=== Pawn Tests ===
TEST(PawnTests, PawnInitialization) {
  auto white_pawn = new Pawn(nullptr, new Square(2, 5), Color::White);
  ASSERT_EQ(white_pawn->get_cursq()->get_row(), 2);
  ASSERT_EQ(white_pawn->get_cursq()->get_col(), 5);
  ASSERT_EQ(white_pawn->piece_moved(), false);
  ASSERT_EQ(white_pawn->get_color(), Color::White);
  ASSERT_EQ(white_pawn->get_name(), PieceName::Pawn);
  auto black_pawn = new Pawn(nullptr, new Square(5, 2), Color::Black);
  ASSERT_EQ(black_pawn->get_cursq()->get_row(), 5);
  ASSERT_EQ(black_pawn->get_cursq()->get_col(), 2);
  ASSERT_EQ(black_pawn->piece_moved(), false);
  ASSERT_EQ(black_pawn->get_color(), Color::Black);
  ASSERT_EQ(black_pawn->get_name(), PieceName::Pawn);
}

TEST(PawnTests, PawnSetters) {
  auto wp_setter = new Pawn(nullptr, new Square(2, 5), Color::White);
  wp_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(wp_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(wp_setter->get_cursq()->get_col(), 4);
  wp_setter->set_moved(true);
  ASSERT_EQ(wp_setter->piece_moved(), true);
  auto bp_setter = new Pawn(nullptr, new Square(2, 5), Color::Black);
  bp_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(bp_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(bp_setter->get_cursq()->get_col(), 4);
  bp_setter->set_moved(true);
  ASSERT_EQ(bp_setter->piece_moved(), true);
}

TEST(PawnTests, PawnMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wpeb1 = new Pawn(b, new Square(2, 5), Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(wpeb1);
  // a few random tests, rather programming pawn moves in the test suite (can lead to errors).
  auto m = new Move();
  m->from = new Square(2,5);
  m->to = new Square(3,5);
  ASSERT_TRUE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4,5);
  ASSERT_TRUE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,5);
  ASSERT_FALSE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,6);
  ASSERT_FALSE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,5);
  ASSERT_FALSE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,4);
  ASSERT_FALSE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,6);
  ASSERT_FALSE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,4);
  ASSERT_FALSE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,5);
  ASSERT_FALSE(wpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  // out of bounds not checked, as Square always produces row and column that are in bounds
  pieces.clear();
  auto wpeb2 = new Pawn(b, new Square(7, 5), Color::White);
  pieces.push_back(wpeb2);
  m->from = new Square(7,5);
  m->to = new Square(8,5);
  ASSERT_FALSE(wpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,6);
  ASSERT_FALSE(wpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,4);
  ASSERT_FALSE(wpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,5);
  ASSERT_FALSE(wpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,5);
  ASSERT_FALSE(wpeb2->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto bpeb1 = new Pawn(b, new Square(7,3), Color::Black);
  pieces.push_back(bpeb1);
  m->from = new Square(7,3);
  m->to = new Square(6,3);
  ASSERT_TRUE(bpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,3);
  ASSERT_TRUE(bpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,3);
  ASSERT_FALSE(bpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,4);
  ASSERT_FALSE(bpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,2);
  ASSERT_FALSE(bpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,2);
  ASSERT_FALSE(bpeb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,3);
  ASSERT_FALSE(bpeb1->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto bpeb2 = new Pawn(b, new Square(2,3), Color::Black);
  pieces.push_back(bpeb2);
  m->from = new Square(2,3);
  m->to = new Square(1,3);
  ASSERT_FALSE(bpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,2);
  ASSERT_FALSE(bpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,4);
  ASSERT_FALSE(bpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,3);
  ASSERT_FALSE(bpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4,3);
  ASSERT_FALSE(bpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,4);
  ASSERT_FALSE(bpeb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,2);
  ASSERT_FALSE(bpeb2->can_move_to(pieces.begin(), pieces.end(), m));

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
	      ASSERT_TRUE(wp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "Exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	    }
	  } else if (y == j && i != 8 && (x - i == 1)) {
	    ASSERT_TRUE(wp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "Exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	  } else {
	    ASSERT_FALSE(wp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "No exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
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
	      ASSERT_TRUE(bp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "Exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	    }
	  } else if (y == j && i != 1 && (i - x == 1)) {
	    ASSERT_TRUE(bp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "Exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
	  } else {
	    ASSERT_FALSE(bp_move_on_eb->can_move_to(pieces.begin(), pieces.end(), {x, y})) << "No exception when moving from (" << i << "," << j << ") to (" << x << "," << y << ")";
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
  auto wpc1 = new Pawn(b, new Square(5, 5), Color::White);
  auto bpiece_to_be_captured1 = new Rook(b, new Square(6, 6), Color::Black);
  auto bpiece_to_be_captured2 = new Queen(b, new Square(6, 4), Color::Black);
  auto bpiece_to_be_captured3 = new Bishop(b, new Square(4, 6), Color::Black);
  auto bpiece_to_be_captured4 = new Knight(b, new Square(4, 4), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(wpc1);
  pieces.push_back(bpiece_to_be_captured1);
  pieces.push_back(bpiece_to_be_captured2);
  pieces.push_back(bpiece_to_be_captured3);
  pieces.push_back(bpiece_to_be_captured4);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(6, 6);
  ASSERT_TRUE(wpc1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6, 4);
  ASSERT_TRUE(wpc1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 6);
  ASSERT_FALSE(wpc1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 4);
  ASSERT_FALSE(wpc1->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.pop_back();
  pieces.pop_back();
  pieces.pop_back();
  pieces.pop_back();

  auto wp_cant_be_captured1 = new Pawn(b, new Square(6,4), Color::White);
  auto wp_cant_be_captured2 = new Pawn(b, new Square(6,6), Color::White);
  pieces.push_back(wp_cant_be_captured1);
  pieces.push_back(wp_cant_be_captured2);
  m->to = new Square(6, 6);
  ASSERT_FALSE(wpc1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6, 4);
  ASSERT_FALSE(wpc1->can_move_to(pieces.begin(), pieces.end(), m));


  auto bpc1 = new Pawn(b, new Square(5, 5), Color::Black);
  auto wpiece_to_be_captured1 = new Rook(b, new Square(6, 6), Color::White);
  auto wpiece_to_be_captured2 = new Queen(b, new Square(6, 4), Color::White);
  auto wpiece_to_be_captured3 = new Bishop(b, new Square(4, 6), Color::White);
  auto wpiece_to_be_captured4 = new Knight(b, new Square(4, 4), Color::White);
  pieces.clear();
  pieces.push_back(wpc1);
  pieces.push_back(wpiece_to_be_captured1);
  pieces.push_back(wpiece_to_be_captured2);
  pieces.push_back(wpiece_to_be_captured3);
  pieces.push_back(wpiece_to_be_captured4);
  m->from = new Square(5,5);
  m->to = new Square(6, 6);
  ASSERT_FALSE(bpc1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6, 4);
  ASSERT_FALSE(bpc1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 6);
  ASSERT_TRUE(bpc1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 4);
  ASSERT_TRUE(bpc1->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.pop_back();
  pieces.pop_back();
  pieces.pop_back();
  pieces.pop_back();

  auto bp_cant_be_captured1 = new Pawn(b, new Square(4,4), Color::Black);
  auto bp_cant_be_captured2 = new Pawn(b, new Square(4,6), Color::Black);
  pieces.push_back(bp_cant_be_captured1);
  pieces.push_back(bp_cant_be_captured2);
  m->to = new Square(4, 4);
  ASSERT_FALSE(bpc1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 6);
  ASSERT_FALSE(bpc1->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(PawnTests, PawnMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto pmwbc1 = new Pawn(b, new Square(2,5), Color::White);
  auto pmwbc2 = new Pawn(b, new Square(2,6), Color::White);
  auto king = new King(b, new Square(1,6), Color::White);
  auto bishop = new Bishop(b, new Square(4,3), Color::Black);
  auto rook = new Rook(b, new Square(7,6), Color::Black);
  auto pawn = new Pawn(b, new Square(3,7), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(pmwbc1);
  pieces.push_back(pmwbc2);
  pieces.push_back(king);
  pieces.push_back(bishop);
  pieces.push_back(rook);
  pieces.push_back(pawn);
  auto m = new Move();
  m->from = new Square(2,5);
  m->to = new Square(4,5);
  ASSERT_FALSE(pmwbc1->move(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,7);
  ASSERT_FALSE(pmwbc1->move(pieces.begin(), pieces.end(), m));
}

TEST(PawnTests, PawnPromotion) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wp1 = new Pawn(b, new Square(7,1), Color::White);
  auto wp2 = new Pawn(b, new Square(7,2), Color::White);
  auto wp3 = new Pawn(b, new Square(7,3), Color::White);
  auto wp4 = new Pawn(b, new Square(7,4), Color::White);
  auto bp1 = new Pawn(b, new Square(2,5), Color::Black);
  auto bp2 = new Pawn(b, new Square(2,6), Color::Black);
  auto bp3 = new Pawn(b, new Square(2,7), Color::Black);
  auto bp4 = new Pawn(b, new Square(2,8), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(wp1);
  pieces.push_back(wp2);
  pieces.push_back(wp3);
  pieces.push_back(wp4);
  pieces.push_back(bp1);
  pieces.push_back(bp2);
  pieces.push_back(bp3);
  pieces.push_back(bp4);
  auto m = new Move();
  m->mt = MoveType::Promotion;
  m->from = new Square(7,1);
  m->to = new Square(8,1);
  m->promoted_to = PieceName::King;
  ASSERT_FALSE(wp1->can_move_to(pieces.begin(), pieces.end(), m));
  m->promoted_to = PieceName::Queen;
  ASSERT_TRUE(wp1->can_move_to(pieces.begin(), pieces.end(), m));

  m->from = new Square(2,5);
  m->to = new Square(1,5);
  m->promoted_to = PieceName::King;
  ASSERT_FALSE(bp1->can_move_to(pieces.begin(), pieces.end(), m));
  m->promoted_to = PieceName::Queen;
  ASSERT_TRUE(bp1->can_move_to(pieces.begin(), pieces.end(), m));

  m->from = new Square(7,2);
  m->to = new Square(8,2);
  m->promoted_to = PieceName::Pawn;
  ASSERT_FALSE(wp2->can_move_to(pieces.begin(), pieces.end(), m));
  m->promoted_to = PieceName::Rook;
  ASSERT_TRUE(wp2->can_move_to(pieces.begin(), pieces.end(), m));

  m->from = new Square(2,6);
  m->to = new Square(1,6);
  m->promoted_to = PieceName::Pawn;
  ASSERT_FALSE(bp2->can_move_to(pieces.begin(), pieces.end(), m));
  m->promoted_to = PieceName::Rook;
  ASSERT_TRUE(bp2->can_move_to(pieces.begin(), pieces.end(), m));

  m->from = new Square(7,3);
  m->to = new Square(8,3);
  m->promoted_to = PieceName::Bishop;
  ASSERT_TRUE(wp3->can_move_to(pieces.begin(), pieces.end(), m));
  
  m->from = new Square(7,4);
  m->to = new Square(8,4);
  m->promoted_to = PieceName::Knight;
  ASSERT_TRUE(wp4->can_move_to(pieces.begin(), pieces.end(), m));

  m->from = new Square(2,7);
  m->to = new Square(1,7);
  m->promoted_to = PieceName::Bishop;
  ASSERT_TRUE(bp3->can_move_to(pieces.begin(), pieces.end(), m));

  m->from = new Square(2,8);
  m->to = new Square(1,8);
  m->promoted_to = PieceName::Knight;
  ASSERT_TRUE(bp4->can_move_to(pieces.begin(), pieces.end(), m));
}

//=== Knight Tests ===
TEST(KnightTests, KnightInitialization) {
  auto white_knight = new Knight(nullptr, new Square(2, 5), Color::White);
  ASSERT_EQ(white_knight->get_cursq()->get_row(), 2);
  ASSERT_EQ(white_knight->get_cursq()->get_col(), 5);
  ASSERT_EQ(white_knight->piece_moved(), false);
  ASSERT_EQ(white_knight->get_color(), Color::White);
  ASSERT_EQ(white_knight->get_name(), PieceName::Knight);
  auto black_knight = new Knight(nullptr, new Square(5, 2), Color::Black);
  ASSERT_EQ(black_knight->get_cursq()->get_row(), 5);
  ASSERT_EQ(black_knight->get_cursq()->get_col(), 2);
  ASSERT_EQ(black_knight->piece_moved(), false);
  ASSERT_EQ(black_knight->get_color(), Color::Black);
  ASSERT_EQ(black_knight->get_name(), PieceName::Knight);
}

TEST(KnightTests, KnightSetters) {
  auto wn_setter = new Knight(nullptr, new Square(2, 5), Color::White);
  wn_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(wn_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(wn_setter->get_cursq()->get_col(), 4);
  wn_setter->set_moved(true);
  ASSERT_EQ(wn_setter->piece_moved(), true);
  auto bn_setter = new Knight(nullptr, new Square(2, 5), Color::Black);
  bn_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(bn_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(bn_setter->get_cursq()->get_col(), 4);
  bn_setter->set_moved(true);
  ASSERT_EQ(bn_setter->piece_moved(), true);
}

TEST(KnightTests, KnightMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wneb1 = new Knight(b, new Square(5, 5), Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(wneb1);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(5, 5);
  ASSERT_FALSE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7, 6);
  ASSERT_TRUE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7, 4);
  ASSERT_TRUE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3, 6);
  ASSERT_TRUE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3, 4);
  ASSERT_TRUE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 7);
  ASSERT_TRUE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6, 7);
  ASSERT_TRUE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 3);
  ASSERT_TRUE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6, 3);
  ASSERT_TRUE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8, 5);
  ASSERT_FALSE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2, 5);
  ASSERT_FALSE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5, 8);
  ASSERT_FALSE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5, 2);
  ASSERT_FALSE(wneb1->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto wneb2 = new Knight(b, new Square(2, 3), Color::White);
  m->from = new Square(2,3);
  m->to = new Square(1, 1);
  ASSERT_TRUE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1, 5);
  ASSERT_TRUE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3, 1);
  ASSERT_TRUE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3, 5);
  ASSERT_TRUE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 2);
  ASSERT_TRUE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4, 4);
  ASSERT_TRUE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,2);
  ASSERT_FALSE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,4);
  ASSERT_FALSE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,3);
  ASSERT_FALSE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,2);
  ASSERT_FALSE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,4);
  ASSERT_FALSE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,2);
  ASSERT_FALSE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,3);
  ASSERT_FALSE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,4);
  ASSERT_FALSE(wneb2->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto bneb1 = new Knight(b, new Square(1, 4), Color::Black);
  pieces.push_back(bneb1);
  m->from = new Square(1,4);
  m->to = new Square(2, 6);
  ASSERT_TRUE(bneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2, 2);
  ASSERT_TRUE(bneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3, 5);
  ASSERT_TRUE(bneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3, 3);
  ASSERT_TRUE(bneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3, 6);
  ASSERT_FALSE(bneb1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3, 2);
  ASSERT_FALSE(bneb1->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto bneb2 = new Knight(b, new Square(1, 1), Color::Black);
  pieces.push_back(bneb2);
  m->from = new Square(1,1);
  m->to = new Square(3,2);
  ASSERT_TRUE(bneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,3);
  ASSERT_TRUE(bneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,3);
  ASSERT_FALSE(bneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,2);
  ASSERT_FALSE(bneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,2);
  ASSERT_FALSE(bneb2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,1);
  ASSERT_FALSE(bneb2->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(KnightTests, KnightMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wknight = new Knight(b, new Square(5,5), Color::White);
  auto rook = new Rook(b, new Square(7,6), Color::Black);
  auto bishop = new Bishop(b, new Square(3, 6), Color::White);
  auto bknight = new Knight(b, new Square(5,7), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(wknight);
  pieces.push_back(rook);
  pieces.push_back(bishop);
  pieces.push_back(bknight);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(7,6);
  ASSERT_TRUE(wknight->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,6);
  ASSERT_FALSE(wknight->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,6);
  ASSERT_TRUE(bknight->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,6);
  ASSERT_FALSE(bknight->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(KnightTests, KnightMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto wknight = new Knight(b, new Square(2,2), Color::White);
  auto wking = new King(b, new Square(1,2), Color::White);
  auto bknight = new Knight(b, new Square(7,2), Color::Black);
  auto bking = new King(b, new Square(8,2), Color::Black);
  auto wrook = new Rook(b, new Square(6,2), Color::White);
  auto brook = new Rook(b, new Square(3,2), Color::Black);
  auto bbishop = new Bishop(b, new Square(1,4), Color::Black);
  auto wbishop = new Bishop(b, new Square(8,4), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(wknight);
  pieces.push_back(wking);
  pieces.push_back(wrook);
  pieces.push_back(wbishop);
  pieces.push_back(bknight);
  pieces.push_back(bking);
  pieces.push_back(brook);
  pieces.push_back(bbishop);
  auto m = new Move();
  m->from = new Square(2,2);
  m->to = new Square(3,4);
  ASSERT_FALSE(wknight->move(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,4);
  ASSERT_FALSE(wknight->move(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,4);
  ASSERT_FALSE(wknight->move(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,4);
  ASSERT_FALSE(wknight->move(pieces.begin(), pieces.end(), m));
}

//=== Bishop Tests ===
TEST(BishopTests, BishopInitialization) {
  auto white_bishop = new Bishop(nullptr, new Square(2, 5), Color::White);
  ASSERT_EQ(white_bishop->get_cursq()->get_row(), 2);
  ASSERT_EQ(white_bishop->get_cursq()->get_col(), 5);
  ASSERT_EQ(white_bishop->piece_moved(), false);
  ASSERT_EQ(white_bishop->get_color(), Color::White);
  ASSERT_EQ(white_bishop->get_name(), PieceName::Bishop);
  auto black_bishop = new Bishop(nullptr, new Square(5, 2), Color::Black);
  ASSERT_EQ(black_bishop->get_cursq()->get_row(), 5);
  ASSERT_EQ(black_bishop->get_cursq()->get_col(), 2);
  ASSERT_EQ(black_bishop->piece_moved(), false);
  ASSERT_EQ(black_bishop->get_color(), Color::Black);
  ASSERT_EQ(black_bishop->get_name(), PieceName::Bishop);
}

TEST(BishopTests, BishopSetters) {
  auto wb_setter = new Bishop(nullptr, new Square(2, 5), Color::White);
  wb_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(wb_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(wb_setter->get_cursq()->get_col(), 4);
  wb_setter->set_moved(true);
  ASSERT_EQ(wb_setter->piece_moved(), true);
  auto bb_setter = new Bishop(nullptr, new Square(2, 5), Color::Black);
  bb_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(bb_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(bb_setter->get_cursq()->get_col(), 4);
  bb_setter->set_moved(true);
  ASSERT_EQ(bb_setter->piece_moved(), true);
}

TEST(BishopTests, BishopMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto b1 = new Bishop(b, new Square(5,5), Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(b1);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(1,1);
  ASSERT_TRUE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,8);
  ASSERT_TRUE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,2);
  ASSERT_TRUE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,8);
  ASSERT_TRUE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,8);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,1);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,7);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,1);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,1);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto b2 = new Bishop(b, new Square(5,4), Color::Black);
  pieces.push_back(b2);
  m->from = new Square(5,4);
  m->to = new Square(1,1);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,8);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,2);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,8);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,8);
  ASSERT_TRUE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,1);
  ASSERT_TRUE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,7);
  ASSERT_TRUE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,1);
  ASSERT_TRUE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,2);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(BishopTests, BishopMovementPieceBlocking) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto b1 = new Bishop(b, new Square(5,5), Color::White);
  auto pawn = new Pawn(b, new Square(2,2), Color::White);
  auto rook = new Rook(b, new Square(7,7), Color::Black);
  auto knight = new Knight(b, new Square(7,3), Color::White);
  auto queen = new Queen(b, new Square(3,7), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(b1);
  pieces.push_back(pawn);
  pieces.push_back(rook);
  pieces.push_back(knight);
  pieces.push_back(queen);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(1,1);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,8);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,2);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,8);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto b2 = new Bishop(b, new Square(5,4), Color::Black);
  auto pawn2 = new Pawn(b, new Square(2,7), Color::White);
  auto rook2 = new Rook(b, new Square(7,2), Color::Black);
  auto knight2 = new Knight(b, new Square(7,6), Color::White);
  auto queen2 = new Queen(b, new Square(3,2), Color::Black);
  pieces.push_back(b2);
  pieces.push_back(pawn2);
  pieces.push_back(rook2);
  pieces.push_back(knight2);
  pieces.push_back(queen2);
  m->from = new Square(5,4);
  m->to = new Square(1,8);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,1);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,7);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,1);
  ASSERT_FALSE(b2->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(BishopTests, BishopMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto b1 = new Bishop(b, new Square(5,5), Color::White);
  auto pawn = new Pawn(b, new Square(2,2), Color::White);
  auto rook = new Rook(b, new Square(7,7), Color::Black);
  auto knight = new Knight(b, new Square(7,3), Color::White);
  auto queen = new Queen(b, new Square(3,7), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(b1);
  pieces.push_back(pawn);
  pieces.push_back(rook);
  pieces.push_back(knight);
  pieces.push_back(queen);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(7,7);
  ASSERT_TRUE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,7);
  ASSERT_TRUE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,2);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,3);
  ASSERT_FALSE(b1->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(BishopTests, BishopMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto b1 = new Bishop(b, new Square(5,5), Color::White);
  auto b2 = new Bishop(b, new Square(5,6), Color::White);
  auto king = new King(b, new Square(6,6), Color::White);
  auto rook = new Rook(b, new Square(1,6), Color::Black);
  auto queen = new Queen(b, new Square(1,1), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(b1);
  pieces.push_back(b2);
  pieces.push_back(king);
  pieces.push_back(rook);
  pieces.push_back(queen);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(6,4);
  ASSERT_FALSE(b1->move(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,7);
  ASSERT_FALSE(b2->move(pieces.begin(), pieces.end(), m));
}

//=== Rook Tests ===
TEST(RookTests, RookInitialization) {
  auto white_rook = new Rook(nullptr, new Square(2, 5), Color::White);
  ASSERT_EQ(white_rook->get_cursq()->get_row(), 2);
  ASSERT_EQ(white_rook->get_cursq()->get_col(), 5);
  ASSERT_EQ(white_rook->piece_moved(), false);
  ASSERT_EQ(white_rook->get_color(), Color::White);
  ASSERT_EQ(white_rook->get_name(), PieceName::Rook);
  auto black_rook = new Rook(nullptr, new Square(5, 2), Color::Black);
  ASSERT_EQ(black_rook->get_cursq()->get_row(), 5);
  ASSERT_EQ(black_rook->get_cursq()->get_col(), 2);
  ASSERT_EQ(black_rook->piece_moved(), false);
  ASSERT_EQ(black_rook->get_color(), Color::Black);
  ASSERT_EQ(black_rook->get_name(), PieceName::Rook);
}

TEST(RookTests, RookSetters) {
  auto wr_setter = new Rook(nullptr, new Square(2, 5), Color::White);
  wr_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(wr_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(wr_setter->get_cursq()->get_col(), 4);
  wr_setter->set_moved(true);
  ASSERT_EQ(wr_setter->piece_moved(), true);
  auto br_setter = new Rook(nullptr, new Square(2, 5), Color::Black);
  br_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(br_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(br_setter->get_cursq()->get_col(), 4);
  br_setter->set_moved(true);
  ASSERT_EQ(br_setter->piece_moved(), true);
}

TEST(RookTests, RookMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto rook = new Rook(b, new Square(5,5), Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(rook);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(1,5);
  ASSERT_TRUE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,5);
  ASSERT_TRUE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,1);
  ASSERT_TRUE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,5);
  ASSERT_TRUE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,8);
  ASSERT_FALSE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,1);
  ASSERT_FALSE(rook->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(RookTests, RookMovementPieceBlocking) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto rook = new Rook(b, new Square(5,5), Color::White);
  auto queen = new Queen(b, new Square(2,5), Color::White);
  auto knight = new Knight(b, new Square(7,5), Color::Black);
  auto bishop = new Bishop(b, new Square(5,2), Color::White);
  auto pawn = new Pawn(b, new Square(5,7), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(rook);
  pieces.push_back(queen);
  pieces.push_back(knight);
  pieces.push_back(bishop);
  pieces.push_back(pawn);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(1,5);
  ASSERT_FALSE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,5);
  ASSERT_FALSE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,1);
  ASSERT_FALSE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,5);
  ASSERT_FALSE(rook->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(RookTests, RookMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto rook = new Rook(b, new Square(5,5), Color::White);
  auto queen = new Queen(b, new Square(2,5), Color::White);
  auto knight = new Knight(b, new Square(7,5), Color::Black);
  auto bishop = new Bishop(b, new Square(5,2), Color::White);
  auto pawn = new Pawn(b, new Square(5,7), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(rook);
  pieces.push_back(queen);
  pieces.push_back(knight);
  pieces.push_back(bishop);
  pieces.push_back(pawn);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(2,5);
  ASSERT_FALSE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,5);
  ASSERT_TRUE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,2);
  ASSERT_FALSE(rook->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,7);
  ASSERT_TRUE(rook->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(RookTests, RookMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto rook = new Rook(b, new Square(5,5), Color::White);
  auto king = new King(b, new Square(6,5), Color::White);
  auto queen = new Queen(b, new Square(2,5), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(rook);
  pieces.push_back(king);
  pieces.push_back(queen);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(5,7);
  ASSERT_FALSE(rook->move(pieces.begin(), pieces.end(), m));
}

//=== Queen Tests ===
TEST(QueenTests, QueenInitialization) {
  auto white_queen = new Queen(nullptr, new Square(2, 5), Color::White);
  ASSERT_EQ(white_queen->get_cursq()->get_row(), 2);
  ASSERT_EQ(white_queen->get_cursq()->get_col(), 5);
  ASSERT_EQ(white_queen->piece_moved(), false);
  ASSERT_EQ(white_queen->get_color(), Color::White);
  ASSERT_EQ(white_queen->get_name(), PieceName::Queen);
  auto black_queen = new Queen(nullptr, new Square(5, 2), Color::Black);
  ASSERT_EQ(black_queen->get_cursq()->get_row(), 5);
  ASSERT_EQ(black_queen->get_cursq()->get_col(), 2);
  ASSERT_EQ(black_queen->piece_moved(), false);
  ASSERT_EQ(black_queen->get_color(), Color::Black);
  ASSERT_EQ(black_queen->get_name(), PieceName::Queen);
}

TEST(QueenTests, QueenSetters) {
  auto wq_setter = new Queen(nullptr, new Square(2, 5), Color::White);
  wq_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(wq_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(wq_setter->get_cursq()->get_col(), 4);
  wq_setter->set_moved(true);
  ASSERT_EQ(wq_setter->piece_moved(), true);
  auto bq_setter = new Queen(nullptr, new Square(2, 5), Color::Black);
  bq_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(bq_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(bq_setter->get_cursq()->get_col(), 4);
  bq_setter->set_moved(true);
  ASSERT_EQ(bq_setter->piece_moved(), true);
}

TEST(QueenTests, QueenMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto queen = new Queen(b, new Square(5,5), Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(queen);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(1,5);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,5);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,1);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,5);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,1);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,8);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,2);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,8);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,8);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,1);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,7);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,1);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto queen2 = new Queen(b, new Square(5,4), Color::Black);
  pieces.push_back(queen2);
  m->from = new Square(5,4);
  m->to = new Square(1,1);
  ASSERT_FALSE(queen2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,8);
  ASSERT_FALSE(queen2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,2);
  ASSERT_FALSE(queen2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,8);
  ASSERT_FALSE(queen2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,8);
  ASSERT_TRUE(queen2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,1);
  ASSERT_TRUE(queen2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,7);
  ASSERT_TRUE(queen2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,1);
  ASSERT_TRUE(queen2->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(QueenTests, QueenMovementPieceBlocking) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto queen = new Queen(b, new Square(5,5), Color::White);
  auto rook = new Rook(b, new Square(2,5), Color::White);
  auto knight = new Knight(b, new Square(7,5), Color::Black);
  auto bishop = new Bishop(b, new Square(5,2), Color::White);
  auto pawn = new Pawn(b, new Square(5,7), Color::Black);
  auto pawn2 = new Pawn(b, new Square(2,2), Color::White);
  auto rook2 = new Rook(b, new Square(7,7), Color::Black);
  auto knight2 = new Knight(b, new Square(7,3), Color::White);
  auto queen2 = new Queen(b, new Square(3,7), Color::Black);
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
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(1,5);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,5);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,1);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,5);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,1);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,8);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(8,2);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,8);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(QueenTests, QueenMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto queen = new Queen(b, new Square(5,5), Color::White);
  auto rook = new Rook(b, new Square(2,5), Color::White);
  auto knight = new Knight(b, new Square(7,5), Color::Black);
  auto bishop = new Bishop(b, new Square(5,2), Color::White);
  auto pawn = new Pawn(b, new Square(5,7), Color::Black);
  auto pawn2 = new Pawn(b, new Square(2,2), Color::White);
  auto rook2 = new Rook(b, new Square(7,7), Color::Black);
  auto knight2 = new Knight(b, new Square(7,3), Color::White);
  auto queen2 = new Queen(b, new Square(3,7), Color::Black);
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
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(2,5);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,5);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,2);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,7);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,2);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,7);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,3);
  ASSERT_FALSE(queen->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,7);
  ASSERT_TRUE(queen->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(QueenTests, QueenMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto queen = new Queen(b, new Square(5,5), Color::White);
  auto rook = new Rook(b, new Square(1,5), Color::Black);
  auto king = new King(b, new Square(6,5), Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(queen);
  pieces.push_back(rook);
  pieces.push_back(king);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(5,8);
  ASSERT_FALSE(queen->move(pieces.begin(), pieces.end(), m));
}

//=== King Tests ===
TEST(KingTests, KingInitialization) {
  auto white_king = new King(nullptr, new Square(2, 5), Color::White);
  ASSERT_EQ(white_king->get_cursq()->get_row(), 2);
  ASSERT_EQ(white_king->get_cursq()->get_col(), 5);
  ASSERT_EQ(white_king->piece_moved(), false);
  ASSERT_EQ(white_king->get_color(), Color::White);
  ASSERT_EQ(white_king->get_name(), PieceName::King);
  auto black_king = new King(nullptr, new Square(5, 2), Color::Black);
  ASSERT_EQ(black_king->get_cursq()->get_row(), 5);
  ASSERT_EQ(black_king->get_cursq()->get_col(), 2);
  ASSERT_EQ(black_king->piece_moved(), false);
  ASSERT_EQ(black_king->get_color(), Color::Black);
  ASSERT_EQ(black_king->get_name(), PieceName::King);
}

TEST(KingTests, KingSetters) {
  auto wk_setter = new King(nullptr, new Square(2, 5), Color::White);
  wk_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(wk_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(wk_setter->get_cursq()->get_col(), 4);
  wk_setter->set_moved(true);
  ASSERT_EQ(wk_setter->piece_moved(), true);
  auto bk_setter = new King(nullptr, new Square(2, 5), Color::Black);
  bk_setter->set_cursq(new Square(3,4));
  ASSERT_EQ(bk_setter->get_cursq()->get_row(), 3);
  ASSERT_EQ(bk_setter->get_cursq()->get_col(), 4);
  bk_setter->set_moved(true);
  ASSERT_EQ(bk_setter->piece_moved(), true);
}

TEST(KingTests, KingMovementOnEmptyBoard) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto king = new King(b, new Square(5,5), Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(king);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(4,4);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4,5);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4,6);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,4);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(5,6);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,4);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,5);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,6);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(7,6);
  ASSERT_FALSE(king->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto king2 = new King(b, new Square(1,5), Color::Black);
  pieces.push_back(king2);
  m->from = new Square(1,5);
  m->to = new Square(1,4);
  ASSERT_TRUE(king2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,6);
  ASSERT_TRUE(king2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,4);
  ASSERT_TRUE(king2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,5);
  ASSERT_TRUE(king2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,6);
  ASSERT_TRUE(king2->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(1,7);
  ASSERT_FALSE(king2->can_move_to(pieces.begin(), pieces.end(), m));

  pieces.clear();
  auto king3 = new King(b, new Square(1,1), Color::White);
  pieces.push_back(king3);
  m->from = new Square(1,1);
  m->to = new Square(1,2);
  ASSERT_TRUE(king3->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,1);
  ASSERT_TRUE(king3->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(2,2);
  ASSERT_TRUE(king3->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(3,3);
  ASSERT_FALSE(king3->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(KingTests, KingMovementCapture) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto king = new King(b, new Square(5,5), Color::White);
  auto pawn = new Pawn(b, new Square(4,4), Color::Black);
  auto bishop = new Bishop(b, new Square(6,6), Color::Black);
  auto rook = new Rook(b, new Square(4,6), Color::White);
  auto queen = new Queen(b, new Square(6,4), Color::White);
  std::vector<Piece*> pieces;
  pieces.push_back(king);
  pieces.push_back(pawn);
  pieces.push_back(bishop);
  pieces.push_back(rook);
  pieces.push_back(queen);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(4,4);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(4,6);
  ASSERT_FALSE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,4);
  ASSERT_FALSE(king->can_move_to(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,6);
  ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
}

TEST(KingTests, KingMovementWillBeCheck) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  auto king = new King(b, new Square(5,5), Color::White);
  auto bishop = new Bishop(b, new Square(5,4), Color::Black);
  auto rook = new Rook(b, new Square(1,6), Color::Black);
  std::vector<Piece*> pieces;
  pieces.push_back(king);
  pieces.push_back(bishop);
  pieces.push_back(rook);
  auto m = new Move();
  m->from = new Square(5,5);
  m->to = new Square(6,5);
  ASSERT_FALSE(king->move(pieces.begin(), pieces.end(), m));
  m->to = new Square(6,6);
  ASSERT_FALSE(king->move(pieces.begin(), pieces.end(), m));
}

TEST(KingTests, KingCastling) {
  auto td = new TextDisplay();
  auto b = new Board(td);
  std::vector<Piece*> pieces;
  {
    auto king = new King(b, new Square(1,5), Color::White);
    auto rook1 = new Rook(b, new Square(1,8), Color::White);
    pieces.push_back(king);
    pieces.push_back(rook1);
    auto m = new Move();
    m->from = new Square(1,5);
    m->to = new Square(1,7);
    ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  }

  {
    auto king = new King(b, new Square(1,5), Color::White);
    auto rook1 = new Rook(b, new Square(1,1), Color::White);
    pieces.push_back(king);
    pieces.push_back(rook1);
    auto m = new Move();
    m->from = new Square(1,5);
    m->to = new Square(1,3);
    ASSERT_TRUE(king->can_move_to(pieces.begin(), pieces.end(), m));
  }

  {
    auto king = new King(b, new Square(2,5), Color::White);
    auto rook1 = new Rook(b, new Square(1,1), Color::White);
    pieces.push_back(king);
    pieces.push_back(rook1);
    auto m = new Move();
    m->from = new Square(2,5);
    m->to = new Square(1,5);
    king->move(pieces.begin(), pieces.end(), m);
    m->to = new Square(1,3);
    ASSERT_FALSE(king->can_move_to(pieces.begin(), pieces.end(), m));
  }

  {
    auto king = new King(b, new Square(1,5), Color::White);
    auto rook1 = new Rook(b, new Square(2,1), Color::White);
    pieces.push_back(king);
    pieces.push_back(rook1);
    auto m = new Move();
    m->from = new Square(2,1);
    m->to = new Square(1,1);
    rook1->move(pieces.begin(), pieces.end(), m);
    m->to = new Square(1,3);
    ASSERT_FALSE(king->can_move_to(pieces.begin(), pieces.end(), m));
  }
}
