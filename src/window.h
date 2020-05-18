//-----------------------------------------------------------------------------
// Copyright (c) 2017 @hirodotexe. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef TETRIS_WINDOW_H_
#define TETRIS_WINDOW_H_

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

struct Point;
enum Status;

class Window {
public:
  Window(int width, int height, std::string title, std::string icon_url)
      : kWidth(width),
        kHeight(height),
        kTitle(title),
        kIconUrl(icon_url),
        video_surface_(NULL) {}
  Window(int width, int height, std::string title)
      : Window(width, height, title, "") {}

  Status Initialize();
  void Terminate();
  SDL_Surface* LoadOptimizedImage(const char* url) const;
  void ClearScreen();
  void ClearScreenWith(Uint8 r, Uint8 g, Uint8 b);
  void DrawSingleImage(SDL_Surface* image, int dest_x, int dest_y);
  void DrawImage(SDL_Surface* image, int dest_x, int dest_y,
                 int id, int width, int height);
  void DrawString(const char* text, int dest_x, int dest_y, TTF_Font* font,
                  const SDL_Color& color = {0x08, 0x18, 0x20});
  void DrawStringCenter(const char* text, int dest_y, TTF_Font* font,
                        const SDL_Color& color = {0x08, 0x18, 0x20});
  void Display();
  void PlayBGM(Mix_Music* bgm);
  void PlaySEOnce(Mix_Chunk* se);
  Status Sleep(int msec) const;
  Status CheckClose() const;
  // Returns clicked coordinate.
  Status WaitClick(bool distinguish_mouse_down, Point* cursor);
  // Wait till enter key is pressed.
  Status WaitEnterKey() const;

  int width() const { return kWidth; }
  int height() const { return kHeight; }

private:
  const int kWidth;
  const int kHeight;
  const std::string kTitle;
  const std::string kIconUrl;
  SDL_Surface* video_surface_;
};

#endif  // TETRIS_WINDOW_H_
