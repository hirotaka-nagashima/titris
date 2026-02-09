//-----------------------------------------------------------------------------
// Copyright (c) 2017 Hirotaka Nagashima. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TITRIS_COMMAND_H_
#define TITRIS_COMMAND_H_

#include "window.h"

class Command {
public:
  Command() { Reset(); }

  void Reset() { up_ = down_ = left_ = right_ = c_ = x_ = 0; }
  void Update() {
    const Uint8* key = SDL_GetKeyboardState(NULL);
    up_    = key[SDL_SCANCODE_UP]    ? up_ + 1    : 0;
    down_  = key[SDL_SCANCODE_DOWN]  ? down_ + 1  : 0;
    left_  = key[SDL_SCANCODE_LEFT]  ? left_ + 1  : 0;
    right_ = key[SDL_SCANCODE_RIGHT] ? right_ + 1 : 0;
    c_     = key[SDL_SCANCODE_C]     ? c_ + 1     : 0;
    x_     = key[SDL_SCANCODE_X]     ? x_ + 1     : 0;
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
  // 0[��]11111111111...111[��]0...
  bool is_during_push(int counter) const { return 0 < counter; }
  // 0[��]10000000000...000[��]0...
  bool is_beginning_push(int counter) const { return 1 == counter; }
  // 0[��]00000011111...111[��]0...
  bool is_in_fast_move_phase(int counter) const {
    static const int kDurationTillFastMove = 7;
    return kDurationTillFastMove <= counter;
  }
  // 0[��]00000001010...101[��]0...
  bool is_frame_to_fast_move(int counter) const {
    static const int kFramesPerRow = 2;
    return is_in_fast_move_phase(counter) && counter % kFramesPerRow == 0;
  }

  int up_, down_, left_, right_;
  int c_, x_;
};

#endif  // TITRIS_COMMAND_H_