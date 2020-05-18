//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#include "board.h"
#include "graphic.h"
#include "info.h"
#include "global_variables.h"

void Board::Reset() {
  // Reset the board.
  memset(board_, kI, sizeof(board_));  // Sentinels.
  for (int y = 0; y < kHeight; ++y) {
    for (int x = 0; x < kWidth; ++x)
      set_board(kNone, x, y);
  }

  // Reset others.
  is_full_ = false;
  command_.Reset();
  message_.Reset();
}

void Board::Draw(Graphic* graphic) const {
  // Draw blocks on the board.
  for (int y = 0; y < kHeight; ++y) {
    for (int x = 0; x < kWidth; ++x) {
      Type type = board(x, y);
      if (type == kNone)
        continue;
      Point dest(x, y);
      graphic->DrawObject(type, dest);
    }
  }
}

void Board::PlaySE(Graphic* graphic) const {
  if (message_.moved_horizontally) graphic->PlaySEMove();
  if (message_.rotated)            graphic->PlaySERotation();
  if (message_.placed)             graphic->PlaySEShock();
}

void Board::MoveBlock(Info* info) {
  command_.Update();
  message_.Reset();

  // Move down.
  bool is_frame_to_move_down = (g_frame_id % info->frames_per_row() == 0);
  if (is_frame_to_move_down || command_.down() || command_.up()) {
    block()->move_down();
    if (command_.up()) {
      // Drop.
      while (!IsHovered())
        block()->move_down();
    }

    if (IsHovered()) {
      // Fix the block at a previous position.
      block()->move_up();  // Undo.
      PlaceBlock();
      int num_deleted_lines = DeleteFullLines();
      DropEmptyLines();

      info->Update(num_deleted_lines);
      message_.placed = true;
      return;
    }
  }

  // Move left or right.
  if (command_.left()) {
    block()->move_left();
    if (IsHovered())
      block()->move_right();  // Undo.
    else
      message_.moved_horizontally = true;
  }
  if (command_.right()) {
    block()->move_right();
    if (IsHovered())
      block()->move_left();  // Undo.
    else
      message_.moved_horizontally = true;
  }

  // Rotate.
  if (command_.c()) {
    block()->rotate_right();
    if (IsHovered())
      block()->rotate_left();  // Undo.
    else
      message_.rotated = true;
  }
  if (command_.x()) {
    block()->rotate_left();
    if (IsHovered())
      block()->rotate_right();  // Undo.
    else
      message_.rotated = true;
  }
}

bool Board::IsHovered() const {
  for (int dy = 0; dy < Block::kMaxHeight; ++dy) {
    for (int dx = 0; dx < Block::kMaxWidth; ++dx) {
      if (!block()->block(dx, dy))
        continue;

      // Suppose an element of the block is placed here.
      Point dp(dx, dy);
      Point dest = block()->position().Add(dp);
      bool is_not_dest_empty = (board(dest) != kNone);
      if (is_not_dest_empty)  // The element is hovered.
        return true;
    }
  }
  return false;
}

void Board::PlaceBlock() {
  // Copy the block on the board.
  for (int dy = 0; dy < Block::kMaxHeight; ++dy) {
    for (int dx = 0; dx < Block::kMaxWidth; ++dx) {
      if (!block()->block(dx, dy))
        continue;

      // Place an element of the block.
      Point dp(dx, dy);
      Point dest = block()->position().Add(dp);
      bool is_not_dest_empty = (board(dest) != kNone);
      is_full_ |= is_not_dest_empty;
      set_board(block()->type(), dest);
    }
  }

  // Delete the copied block from blocks queue and add a new one.
  blocks_->PopBlock();
  blocks_->AddBlockRandomly();
}

int Board::DeleteFullLines() {
  int num_deleted_lines = 0;
  for (int y = 0; y < kHeight; ++y) {
    // Check whether this line is full with blocks.
    bool is_line_full = true;
    for (int x = 0; x < kWidth; ++x)
      is_line_full &= (board(x, y) != kNone);
    if (!is_line_full)
      continue;

    // Delete the full line.
    ++num_deleted_lines;
    for (int x = 0; x < kWidth; ++x)
      set_board(kNone, x, y);
  }
  return num_deleted_lines;
}

void Board::DropEmptyLines() {
  int dest_y = kHeight - 1;
  for (int y = kHeight - 1; 0 <= y; --y) {
    // Check whether this line is empty.
    bool is_line_empty = true;
    for (int x = 0; x < kWidth; ++x)
      is_line_empty &= (board(x, y) == kNone);
    if (is_line_empty)
      continue;

    // Drop the current line.
    if (y < dest_y) {
      for (int x = 0; x < kWidth; ++x) {
        set_board(board(x, y), x, dest_y);
        set_board(kNone, x, y);
      }
    }

    // Update a destination.
    --dest_y;
  }
}