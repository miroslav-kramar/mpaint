#include "app.h"

App app = {0};

void init_app() {
  // init window
  app.title = "MPaint";
  InitWindow(800, 450, app.title);
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(0);

  // init canvas
  app.canvas = LoadRenderTexture(1920, 1080);
  BeginTextureMode(app.canvas);
  ClearBackground(WHITE);
  EndTextureMode();
  
  // init mouse
  app.mouse.pos.now  = (Vector2){0,0};
  app.mouse.pos.last = app.mouse.pos.now;

  // init drawing
  app.drawing.color.primary   = BLACK;
  app.drawing.color.secondary = WHITE;

  // init camera
  app.camera.zoom = 1.0f;
  app.camera.target = (Vector2){0,0};
  app.camera.offset = (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2};
}