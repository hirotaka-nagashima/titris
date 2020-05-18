//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_INFO_H_
#define TETRIS_INFO_H_

#include <algorithm>  // std::min(), std::max()
#include "type.h"

class Info {
public:
  Info() { Reset(); }

  void Reset() { score_ = lines_ = 0; Update(0); }
  void Update(int num_deleted_lines) {
    // Score.
    static const int kMaxLines = 4;
    static const int kScore[1 + kMaxLines] = {0, 40, 100, 300, 1200};
    score_ += kScore[num_deleted_lines];

    // Lines.
    lines_ += num_deleted_lines;

    // Level.
    static const int kLinesToIncrementLevel = 10;
    static const int kMaxLevel = 20;
    level_ = lines_ / kLinesToIncrementLevel;
    level_ = std::min(level_, kMaxLevel);

    // Speed.
    static const int kFramesPerRow[1 + kMaxLevel] = {
        18, 16, 15, 14, 12, 11, 10, 7, 6, 4,  // [0]~[9]
        3, 3, 3, 2, 2, 2, 2, 2, 1, 1, 1};     // [10]~[20]
    frames_per_row_ = kFramesPerRow[level_];
  }

  int score() const { return score_; }
  int level() const { return level_; }
  int lines() const { return lines_; }
  int frames_per_row() const { return frames_per_row_; }

private:
  int score_;
  int level_;
  int lines_;
  int frames_per_row_;
};

#endif  // TETRIS_INFO_H_
