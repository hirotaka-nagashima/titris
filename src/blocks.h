//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_BLOCKS_H_
#define TETRIS_BLOCKS_H_

#include <ctime>  // time()
#include <vector>
#include "block.h"

class Blocks {
public:
  Blocks() { srand(static_cast<unsigned int>(time(NULL))); }
  ~Blocks();

  void InitializeRandomly(int num_blocks);
  void AddBlockRandomly();
  void PopBlock();

  Block* current_block() const { return blocks_[0]; }
  Block* next_block() const { return blocks_[1]; }

private:
  std::vector<Block*> blocks_;
};

#endif  // TETRIS_BLOCKS_H_