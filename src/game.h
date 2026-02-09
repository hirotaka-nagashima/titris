//-----------------------------------------------------------------------------
// Copyright (c) 2017 Hirotaka Nagashima. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TITRIS_GAME_H_
#define TITRIS_GAME_H_

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

#endif // TITRIS_GAME_H_