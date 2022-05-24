#include "gtest/gtest.h"
#include "../../code/square.h"

TEST(SquareTests, SquareConstructorInBoundsTest) {
  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) {
      Square in_bounds{i,j};
      ASSERT_EQ(in_bounds.get_row(), i) << "Square Constructor in-bounds checking failed: Got row = " << in_bounds.get_row() << " instead of row = " << i;
      ASSERT_EQ(in_bounds.get_col(), j) << "Square Constructor in-bounds checking failed: Got col = " << in_bounds.get_col() << " instead of col = " << j;
    }
  }
}

TEST(SquareTests, SquareConstructorOutOfBoundsTest) {
  Square out_of_bounds1{-1, -1};
  ASSERT_EQ(out_of_bounds1.get_row(), 1) << "Square Constructor out-of-bounds checking failed: Constructed with row = " << -1 << ", got row = " << out_of_bounds1.get_row() << " instead of row = " << 1;
  ASSERT_EQ(out_of_bounds1.get_col(), 1) << "Square Constructor out-of-bounds checking failed: Constructed with col = " << -1 << ", got col = " << out_of_bounds1.get_col() << " instead of col = " << 1;
  Square out_of_bounds2{9, 9};
  ASSERT_EQ(out_of_bounds2.get_row(), 8) << "Square Constructor out-of-bounds checking failed: Constructed with row = " << 9 << ", got row = " << out_of_bounds2.get_row() << " instead of row = " << 8;
  ASSERT_EQ(out_of_bounds2.get_col(), 8) << "Square Constructor out-of-bounds checking failed: Constructed with col = " << 9 << ", got col = " << out_of_bounds2.get_col() << " instead of col = " << 8;
}

TEST(SquareTests, SquareSettersInBoundsTest) {
  Square in_bounds_setter{1, 1};
  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) {
      in_bounds_setter.set_row(i);
      in_bounds_setter.set_col(j);
      ASSERT_EQ(in_bounds_setter.get_row(), i) << "Square Constructor in-bounds checking failed: Got row = " << in_bounds_setter.get_row() << " instead of row = " << i;
      ASSERT_EQ(in_bounds_setter.get_col(), j) << "Square Constructor in-bounds checking failed: Got col = " << in_bounds_setter.get_col() << " instead of col = " << j;
    }
  }
}

TEST(SquareTests, SquareSettersOutOfBoundsTest) {
  Square out_of_bounds_setter1{5,5};
  out_of_bounds_setter1.set_row(-1);
  out_of_bounds_setter1.set_col(-1);
  ASSERT_EQ(out_of_bounds_setter1.get_row(), 1) << "Square Constructor out-of-bounds checking failed: Constructed with row = " << -1 << ", got row = " << out_of_bounds_setter1.get_row() << " instead of row = " << 1;
  ASSERT_EQ(out_of_bounds_setter1.get_col(), 1) << "Square Constructor out-of-bounds checking failed: Constructed with col = " << -1 << ", got col = " << out_of_bounds_setter1.get_col() << " instead of col = " << 1;
  Square out_of_bounds_setter2{5,5};
  out_of_bounds_setter2.set_row(9);
  out_of_bounds_setter2.set_col(9);
  ASSERT_EQ(out_of_bounds_setter2.get_row(), 8) << "Square Constructor out-of-bounds checking failed: Constructed with row = " << 9 << ", got row = " << out_of_bounds_setter2.get_row() << " instead of row = " << 8;
  ASSERT_EQ(out_of_bounds_setter2.get_col(), 8) << "Square Constructor out-of-bounds checking failed: Constructed with col = " << 9 << ", got col = " << out_of_bounds_setter2.get_col() << " instead of col = " << 8;
}
