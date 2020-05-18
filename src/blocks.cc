//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#include "blocks.h"

Blocks::~Blocks() {
  while (!blocks_.empty())
    PopBlock();
}

void Blocks::InitializeRandomly(int num_blocks) {
  for (int i = 0; i < num_blocks; ++i)
    AddBlockRandomly();
}

void Blocks::AddBlockRandomly() {
  Type random_type = static_cast<Type>(rand() % kNumTypes);
  blocks_.push_back(new Block(random_type));
}

void Blocks::PopBlock() {
  if (!blocks_.empty()) {
    delete blocks_[0];
    blocks_.erase(blocks_.begin());
  }
}