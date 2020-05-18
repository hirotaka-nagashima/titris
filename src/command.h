//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_COMMAND_H_
#define TETRIS_COMMAND_H_

#include "window.h"

class Command {
public:
  Command() { Reset(); }

  void Reset() { up_ = down_ = left_ = right_ = c_ = x_ = 0; }
  void Update() {
    Uint8* key = SDL_GetKeyState(NULL);
    up_    = key[SDLK_UP]    ? up_ + 1    : 0;
    down_  = key[SDLK_DOWN]  ? down_ + 1  : 0;
    left_  = key[SDLK_LEFT]  ? left_ + 1  : 0;
    right_ = key[SDLK_RIGHT] ? right_ + 1 : 0;
    c_     = key[SDLK_c]     ? c_ + 1     : 0;
    x_     = key[SDLK_x]     ? x_ + 1     : 0;
  }

  bool up() const { return is_beginning_push(up_); }
  bool down() const { return is_during_push(down_); }
  bool left() const {
    return is_beginning_push(left_) || is_frame_to_fast_move(left_);
  }
  bool right() const {
    return is_beginning_push(right_) || is_frame_to_fast_move(right_);
  }
  bool c() const { return is_beginning_push(c_); }
  bool x() const { return is_beginning_push(x_); }

private:
  // 0[Å´]11111111111...111[Å™]0...
  bool is_during_push(int counter) const { return 0 < counter; }
  // 0[Å´]10000000000...000[Å™]0...
  bool is_beginning_push(int counter) const { return 1 == counter; }
  // 0[Å´]00000011111...111[Å™]0...
  bool is_in_fast_move_phase(int counter) const {
    static const int kDurationTillFastMove = 7;
    return kDurationTillFastMove <= counter;
  }
  // 0[Å´]00000001010...101[Å™]0...
  bool is_frame_to_fast_move(int counter) const {
    static const int kFramesPerRow = 2;
    return is_in_fast_move_phase(counter) && counter % kFramesPerRow == 0;
  }

  int up_, down_, left_, right_;
  int c_, x_;
};

#endif  // TETRIS_COMMAND_H_