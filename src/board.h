//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_BOARD_H_
#define TETRIS_BOARD_H_

#include "type.h"
#include "command.h"
#include "blocks.h"

class Graphic;
class Info;

class Board {
public:
  Board(Blocks* blocks) : blocks_(blocks) { Reset(); }

  void Reset();
  void Draw(Graphic* graphic) const;
  void PlaySE(Graphic* graphic) const;
  void MoveBlock(Info* info);

  bool is_full() const { return is_full_; }

private:
  struct Message {
    Message() { Reset(); }

    void Reset() { moved_horizontally = rotated = placed = false; }

    bool moved_horizontally, rotated, placed;
  };

  static const int kWidth = 10;
  static const int kHeight = 19;

  bool IsHovered() const;
  // Also update "is_full."
  void PlaceBlock();
  // Return the number of deleted lines.
  int DeleteFullLines();
  void DropEmptyLines();

  Block* block() const { return blocks_->current_block(); }
  Type board(int x, int y) const { return board_[y][1 + x]; }
  Type board(const Point& position) const {
    return board(position.x, position.y);
  }
  void set_board(Type type, int x, int y) { board_[y][1 + x] = type; }
  void set_board(Type type, const Point& dest) {
    set_board(type, dest.x, dest.y);
  }

  Type board_[1 + kHeight + 1][1 + kWidth + 1];
  bool is_full_;
  // How long each key is held down.
  Command command_;
  Blocks* blocks_;
  Message message_;
};

#endif  // TETRIS_BOARD_H_