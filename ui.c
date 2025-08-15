#include "app.h"

bool mouse_on_canvas() {
    return app.mouse.pos.now.x >= 0 &&
           app.mouse.pos.now.y >= 0 &&
           app.mouse.pos.now.x <= app.canvas.texture.width &&
           app.mouse.pos.now.y <= app.canvas.texture.height;
}

void draw_ref_pixel() {
  if (!(app.mouse.pos.now.x >= 0 &&
    app.mouse.pos.now.x <= app.canvas.texture.width &&
    app.mouse.pos.now.y >= 0 &&
    app.mouse.pos.now.y <= app.canvas.texture.height
  )) {return;}

  DrawPixel((int)app.mouse.pos.now.x, (int)app.mouse.pos.now.y, (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) ? app.drawing.color.secondary : app.drawing.color.primary);
}

void draw_top_bar() {
  DrawRectangle(0, 0, GetScreenWidth(), 80, BLACK);
}

void draw_bottom_bar() {
  DrawRectangle(0, GetScreenHeight() - 22, GetScreenWidth(), 22, BLACK);
  if (mouse_on_canvas()) {
      DrawText(TextFormat("%d, %d", (int)app.mouse.pos.now.x+1, (int)app.mouse.pos.now.y+1), 4, GetScreenHeight() - 20, 20, WHITE);
  }
}