#ifndef RESULT_H_
#define RESULT_H_

enum class Result {
  NoResult,
  WhiteWins,
  BlackWins,
  DrawByThreefold,
  DrawByInsufficientMaterial,
  DrawByStalemate,
  DrawBy50MoveRule
};

#endif
