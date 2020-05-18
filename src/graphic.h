//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_GRAPHIC_H_
#define TETRIS_GRAPHIC_H_

#include "window.h"

enum Type;
class Info;
class BestScores;
class Board;
class Blocks;

class Graphic {
public:
  Graphic() : window_(480, 432, "TETRIS", "resources/icon.png"),
              font_(NULL), bgm_(NULL), se_move_(NULL), se_rotation_(NULL),
              se_shock_(NULL), image_objects_(NULL),
              image_title_(NULL), image_background_(NULL),
              image_game_over_(NULL) {}

  Status Initialize();
  void Terminate();
  void DrawObject(Type type, const Point& dest);
  Status DisplayScreen(const Board& board, const Blocks& blocks,
                       const Info& info, int fps);
  Status DisplayTitle();
  Status DisplayResult(int score, const BestScores& best_scores);
  void PlaySEMove() { window_.PlaySEOnce(se_move_); }
  void PlaySERotation() { window_.PlaySEOnce(se_rotation_); }
  void PlaySEShock() { window_.PlaySEOnce(se_shock_); }

  int width() { return window_.width(); }
  int height() { return window_.height(); }

private:
  void StabilizeFPS(int fps) const;

  Window window_;
  // Resources.
  TTF_Font* font_;
  Mix_Music* bgm_;
  Mix_Chunk* se_move_;
  Mix_Chunk* se_rotation_;
  Mix_Chunk* se_shock_;
  SDL_Surface* image_objects_;
  SDL_Surface* image_title_;
  SDL_Surface* image_background_;
  SDL_Surface* image_game_over_;
};

#endif  // TETRIS_GRAPHIC_H_