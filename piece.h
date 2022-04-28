#ifndef PIECE_H_
#define PIECE_H_

#include "square.h"
#include "color.h"
#include "piecename.h"

class Piece {
  // is a friend of class Board
  protected:
  Square cursq;
  Color color;
  public:
  Piece(Square s, Color c);
  Square get_cursq();
  virtual void move(Square to) = 0;
  virtual PieceName get_name() = 0;
  virtual bool is_checkmated();
  virtual bool is_stalemated();
  Color get_color();
  ~Piece();
};

class Pawn : public Piece{
  public: 
  using Piece::Piece;
  void move(Square to) override;
  PieceName get_name() override;
};

class Knight : public Piece{
  public: 
  using Piece::Piece;
  void move(Square to) override;
  PieceName get_name() override;
};

class Bishop : public Piece {
  public: 
  using Piece::Piece;
  void move(Square to) override;
  PieceName get_name() override;
};

class Rook : public Piece {
  public: 
  using Piece::Piece;
  void move(Square to) override;
  PieceName get_name() override;
};

class Queen : public Piece {
  public: 
  using Piece::Piece;
  void move(Square to) override;
  PieceName get_name() override;
};

class King : public Piece {
  public: 
  using Piece::Piece;
  void move(Square to) override;
  PieceName get_name() override;
  bool is_checkmated() override;
  bool is_stalemated() override;
};
#endif
