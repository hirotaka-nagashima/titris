//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_GAME_H_
#define TETRIS_GAME_H_

#include "graphic.h"
#include "file_handler.h"

class Game {
public:
  void Run();

private:
  Status Play(BestScores* best_scores);

  Graphic graphic_;
  FileHandler file_handler_;
};

#endif // TETRIS_GAME_H_