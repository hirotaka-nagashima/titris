//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_FILE_HANDLER_H_
#define TETRIS_FILE_HANDLER_H_

#include "window.h"

enum Status;
class BestScores;

class FileHandler {
public:
  Status LoadBestScores(BestScores* scores) const;
  void SaveBestScores(const BestScores& scores) const;

private:
  static const char kScoresUrl[];
};

#endif  // TETRIS_FILE_HANDLER_H_
