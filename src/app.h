#ifndef MPAINT_APP
#define MPAINT_APP

#include "../../raylib/include/raylib.h"

typedef struct {
  RenderTexture2D canvas;

  struct {
    struct {
      Vector2 now;
      Vector2 last;
    } pos;
  } mouse;

  struct {
    struct {
      Color primary;
      Color secondary;
    } color;
  } drawing;

  Camera2D camera;
  const char * title;
} App;

extern App app;

void init_app();

#endif