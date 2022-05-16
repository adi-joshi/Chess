#ifndef RESULT_H_
#define RESULT_H_

enum class Result {
  NoResult,
  WhiteWins,
  BlackWins,
  DrawByThreefoldRepetition,
  DrawByInsufficientMaterial,
  DrawByStalemate,
  DrawBy50MoveRule
};

#endif
