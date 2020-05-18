//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------
// 2017/03/15: The project was created.
//-----------------------------------------------------------------------------
// [©][«][¨]  : Move.
// [ª]        : Drop.
// [x][c]     : Rotate.
//-----------------------------------------------------------------------------

#include "game.h"
#include "status.h"
#include "info.h"
#include "best_scores.h"
#include "board.h"
#include "blocks.h"

int g_fps = 20;
int g_frame_id = 0;

// NOTE: Comment out below to use SDL in VS2015 or later versions.
// https://stackoverflow.com/questions/30412951/
FILE _iob[] = {*stdin, *stdout, *stderr};
extern "C" FILE * __cdecl __iob_func() {
  return _iob;
}

int main(int argc, char* argv[]) {
  Game game;
  game.Run();
  return 0;
}

void Game::Run() {
  // Initialization.
  if (graphic_.Initialize() == kError)
    return;
  BestScores best_scores;
  file_handler_.LoadBestScores(&best_scores);

  // Main.
  while (Play(&best_scores) == kSuccess) {}

  // Termination.
  file_handler_.SaveBestScores(best_scores);
  graphic_.Terminate();
}

Status Game::Play(BestScores* best_scores) {
  // Display a title.
  if (graphic_.DisplayTitle() == kClosed)
    return kClosed;

  Info info;

  // Play.
  static const int kNumDisplayedBlocks = 1;
  Blocks blocks;
  blocks.InitializeRandomly(1 + kNumDisplayedBlocks);
  Board board(&blocks);
  while (!board.is_full()) {
    ++g_frame_id;

    // Display game screen.
    if (graphic_.DisplayScreen(board, blocks, info, g_fps) == kClosed)
      return kClosed;

    // Move block.
    board.MoveBlock(&info);
  }

  // Display result.
  best_scores->UpdateBestScores(info.score());
  return graphic_.DisplayResult(info.score(), *best_scores);
}