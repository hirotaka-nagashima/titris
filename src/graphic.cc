//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include "graphic.h"
#include "status.h"
#include "type.h"
#include "info.h"
#include "best_scores.h"
#include "board.h"
#include "blocks.h"
#include "point.h"

Status Graphic::Initialize() {
  if (window_.Initialize() == kError)
    return kError;

  // Load fonts.
  static const int kFontSize = 22;
  font_ = TTF_OpenFont("resources/font.ttf", kFontSize);
  if (!font_) {
    fprintf(stderr, "ERROR: %s\n", TTF_GetError());
    return kError;
  }

  // Load musics.
  bgm_         = Mix_LoadMUS("resources/bgm.ogg");
  se_move_     = Mix_LoadWAV("resources/se_move.ogg");
  se_rotation_ = Mix_LoadWAV("resources/se_rotation.ogg");
  se_shock_    = Mix_LoadWAV("resources/se_shock.ogg");
  if (!bgm_ || !se_move_ || !se_rotation_ || !se_shock_) {
    fprintf(stderr, "ERROR: %s\n", Mix_GetError());
    return kError;
  }

  // Load images.
  image_objects_    = window_.LoadOptimizedImage("resources/objects.png");
  image_title_      = window_.LoadOptimizedImage("resources/title.png");
  image_background_ = window_.LoadOptimizedImage("resources/background.png");
  image_game_over_  = window_.LoadOptimizedImage("resources/game_over.png");
  if (!image_objects_ || !image_title_ || !image_background_ ||
      !image_game_over_) {
    fprintf(stderr, "ERROR: %s\n", IMG_GetError());
    return kError;
  }

  return kSuccess;
}

void Graphic::Terminate() {
  // Release fonts.
  TTF_CloseFont(font_); font_ = NULL;

  // Release musics.
  Mix_FreeMusic(bgm_);         bgm_ = NULL;
  Mix_FreeChunk(se_move_);     se_move_ = NULL;
  Mix_FreeChunk(se_rotation_); se_rotation_ = NULL;
  Mix_FreeChunk(se_shock_);    se_shock_ = NULL;

  // Release images.
  SDL_FreeSurface(image_objects_);    image_objects_ = NULL;
  SDL_FreeSurface(image_title_);      image_title_ = NULL;
  SDL_FreeSurface(image_background_); image_background_ = NULL;
  SDL_FreeSurface(image_game_over_);  image_game_over_ = NULL;

  window_.Terminate();
}

void Graphic::DrawObject(Type type, const Point& dest) {
  static const int kObjectSize = 24;
  window_.DrawImage(image_objects_,
                    kObjectSize * (dest.x + 2), kObjectSize * (dest.y - 1),
                    type, kObjectSize, kObjectSize);
}

Status Graphic::DisplayScreen(const Board& board, const Blocks& blocks,
                              const Info& info, int fps) {
  window_.PlayBGM(bgm_);
  board.PlaySE(this);

  // Background.
  window_.DrawSingleImage(image_background_, 0, 0);
  // Board.
  board.Draw(this);
  // Block on the board.
  blocks.current_block()->Draw(this);
  // Next block.
  blocks.next_block()->Draw(10, 13, this);

  // Information.
  char value[12];
  sprintf(value, "%6d", info.score());
  window_.DrawString(value, 332, 75, font_);
  sprintf(value, "%5d", info.level());
  window_.DrawString(value, 332, 171, font_);
  sprintf(value, "%5d", info.lines());
  window_.DrawString(value, 332, 243, font_);

  window_.Display();
  StabilizeFPS(fps);
  return window_.CheckClose();
}

Status Graphic::DisplayTitle() {
  Mix_HaltMusic();

  // Background.
  window_.DrawSingleImage(image_title_, 0, 0);

  window_.Display();
  return window_.WaitEnterKey();
}

Status Graphic::DisplayResult(int score, const BestScores& best_scores) {
  Mix_HaltMusic();

  // Background.
  window_.DrawSingleImage(image_game_over_, 0, 0);

  // Title.
  static const char kTitle[] = " RANKING ";
  window_.DrawString(kTitle, 72, 240, font_);

  // Best scores.
  bool is_score_registered = false;
  for (int place = 1; place <= best_scores.num_best_scores(); ++place) {
    // String.
    int best_score = best_scores.best_score(place);
    char line[14];
    sprintf(line, "%d.%6d", place, best_score);
    // Color.
    static const SDL_Color kBlack = {0x08, 0x18, 0x20};
    static const SDL_Color kGreen = {0x34, 0x68, 0x56};
    bool is_new_score = (best_score == score && !is_score_registered);
    const SDL_Color& kColor = is_new_score ? kGreen : kBlack;

    window_.DrawString(line, 79, 240 + 48 * place, font_, kColor);
    is_score_registered |= is_new_score;
  }

  window_.Display();
  return window_.Sleep(4000);
}

void Graphic::StabilizeFPS(int fps) const {
  static int prev_time = SDL_GetTicks();
  int duration = SDL_GetTicks() - prev_time;
  int given_duration = 1000 / fps;  // [ms]
  if (0 < given_duration - duration)
    SDL_Delay(given_duration - duration);
  prev_time = SDL_GetTicks();
}