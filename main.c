#include "../raylib/include/raylib.h"
#include "../raylib/include/rlgl.h"
#include "../raylib/include/raymath.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "ui.h"
#include "app.h"
#include "draw.h"

int main() {
  init_app();

  while (!WindowShouldClose()) {
    app.mouse.pos.last = app.mouse.pos.now;
    app.mouse.pos.now  = GetScreenToWorld2D(GetMousePosition(), app.camera);
    const float wheel  = GetMouseWheelMove();

    // Moving
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f / app.camera.zoom);
      app.camera.target = Vector2Add(app.camera.target, delta);
    }
    if (wheel != 0 && !IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_SHIFT)) {
      const float base = 45.0f;
      app.camera.target.y += (base / app.camera.zoom) * -wheel;
    }
    if (wheel != 0 && !IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT)) {
      const float base = 45.0f;
      app.camera.target.x += (base / app.camera.zoom) * -wheel;
    }

    // Zooming
    if (wheel != 0 && IsKeyDown(KEY_LEFT_CONTROL)) {
      app.camera.offset = GetMousePosition();
      app.camera.target = app.mouse.pos.now;
      const float scale = 0.2f * wheel;
      app.camera.zoom = Clamp(expf(logf(app.camera.zoom) + scale), 0.25f, 64.0f);
    }

    // Drawing
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      BeginTextureMode(app.canvas);
      plot_line(app.mouse.pos.last, app.mouse.pos.now, app.drawing.color.primary);
      EndTextureMode();
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
      BeginTextureMode(app.canvas);
      plot_line(app.mouse.pos.last, app.mouse.pos.now, app.drawing.color.secondary);
      EndTextureMode();
    }

    // Saving
    if (IsKeyDown(KEY_S) && IsKeyDown(KEY_LEFT_CONTROL)) {
      char filename[128] = {0};
      time_t now;
      struct tm * local;
      time(&now);
      local = localtime(&now);
      snprintf(filename, sizeof(filename), "saved_images/" "out_%02d_%02d_%d_%02d_%02d_%02d.png", 
        local->tm_mday,
        local->tm_mon + 1,
        local->tm_year + 1900,
        local->tm_hour,
        local->tm_min,
        local->tm_sec
      );

      Image img = LoadImageFromTexture(app.canvas.texture);
      ImageFlipVertical(&img);
      ExportImage(img, filename);
      UnloadImage(img);
    }

    BeginDrawing();
    ClearBackground(DARKGRAY);

    BeginMode2D(app.camera);
    DrawTextureRec(app.canvas.texture, (Rectangle) {0, 0, (float)app.canvas.texture.width, (float)-app.canvas.texture.height}, (Vector2){0, 0}, WHITE);
    DrawRectangleLines(0, 0, app.canvas.texture.width, app.canvas.texture.height, BLACK);
    draw_ref_pixel();
    EndMode2D();

    draw_top_bar();
    draw_bottom_bar();
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}