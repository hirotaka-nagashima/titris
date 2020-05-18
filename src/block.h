//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_BLOCK_H_
#define TETRIS_BLOCK_H_

#include "point.h"
#include "type.h"

class Graphic;

class Block {
public:
  static const int kMaxWidth = 4;
  static const int kMaxHeight = 4;

  Block(Type type) : kType(type), id_(0), position_(kDefaultPosition) {
    if (type == kI)
      move_up();
  }

  void Draw(int dx, int dy, Graphic* graphic) const;
  void Draw(Graphic* graphic) const { Draw(0, 0, graphic); }

  void move_up() { --position_.y; }
  void move_down() { ++position_.y; }
  void move_left() { --position_.x; }
  void move_right() { ++position_.x; }
  void rotate_left() { id_ = (id_ - 1 + kNumVariations) % kNumVariations; }
  void rotate_right() { id_ = (id_ + 1) % kNumVariations; }
  bool block(int x, int y) const { return kBlock[kType][id_][y][x]; }
  Type type() const { return kType; }
  Point position() const { return position_; }

protected:
  static const int kNumVariations = 4;
  static const Point kDefaultPosition;
  static const bool kBlock[kNumTypes][kNumVariations][kMaxHeight][kMaxWidth];

  const Type kType;
  Point position_;
  int id_;
};

#endif  // TETRIS_BLOCK_H_