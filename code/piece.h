#ifndef PIECE_H_
#define PIECE_H_

#include <vector>
#include <memory>
#include "square.h"
#include "color.h"
#include "piecename.h"
#include "result.h"

class Board;
struct Move;

class Piece {
  // is a friend of class Board
  protected:
  std::shared_ptr<Board> b;
  std::shared_ptr<Square> cursq;
  Color color;
  bool moved = false;
  public:
  Piece(std::shared_ptr<Board> b, std::shared_ptr<Square> cursq, Color c);
  std::shared_ptr<Square> get_cursq();
  void set_cursq(std::shared_ptr<Square> to);
  void set_moved(bool b);
  bool piece_moved();
  Color get_color();

  // this one called by a King to check if this piece can move to the king's square
  virtual bool can_move_to(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end, std::shared_ptr<Move> m) = 0;

  // this one checks if piece can move to destination, and then checks if the King of this
  // piece's color will be in check after moving to the destination square.
  bool move(std::vector<Piece *>::iterator it,
      std::vector<Piece *>::iterator end, std::shared_ptr<Move> m);

  virtual PieceName get_name() = 0;
  virtual bool in_check(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore);
  virtual bool is_checkmated(std::vector<Piece *>::iterator it,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore);
  virtual Result is_stalemated(std::vector<Piece *>::iterator it,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore);
  virtual Result get_result(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore);
  ~Piece();
};

class Pawn : public Piece{
  public: 
  using Piece::Piece;
  // for usage of can_move_to and move, check the comments in the class Piece defintion.
  bool can_move_to(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end, std::shared_ptr<Move> m) override;
  PieceName get_name() override;
};

class Knight : public Piece{
  public: 
  using Piece::Piece;
  // for usage of can_move_to and move, check the comments in the class Piece defintion.
  bool can_move_to(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end, std::shared_ptr<Move> m) override;
  PieceName get_name() override;
};

class Bishop : public Piece {
  public: 
  using Piece::Piece;
  // for usage of can_move_to and move, check the comments in the class Piece defintion.
  bool can_move_to(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end, std::shared_ptr<Move> m) override;
  PieceName get_name() override;
};

class Rook : public Piece {
  public: 
  using Piece::Piece;
  // for usage of can_move_to and move, check the comments in the class Piece defintion.
  bool can_move_to(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end, std::shared_ptr<Move> m) override;
  PieceName get_name() override;
};

class Queen : public Piece {
  public: 
  using Piece::Piece;
  // for usage of can_move_to and move, check the comments in the class Piece defintion.
  bool can_move_to(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end, std::shared_ptr<Move> m) override;
  PieceName get_name() override;
};

class King : public Piece {
  bool king_can_move(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore);
  public: 
  using Piece::Piece;
  // for usage of can_move_to and move, check the comments in the class Piece defintion.
  bool can_move_to(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end, std::shared_ptr<Move> m) override;
  PieceName get_name() override;
  bool in_check(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore) override;
  bool is_checkmated(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore) override;
  Result is_stalemated(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore) override;
  Result get_result(std::vector<Piece *>::iterator begin,
      std::vector<Piece *>::iterator end,
      std::vector<Piece *>::iterator ignore) override;
};
#endif
