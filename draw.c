#include "draw.h"
#include <stdlib.h>

void plot_line(const Vector2 start, const Vector2 end, const Color color) {
    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    int dx = abs(x1 - x0);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy; // error term (dx + (-dy))

    for (;;) {
        DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 >= dy) {         // step in x
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {         // step in y
            err += dx;
            y0 += sy;
        }
    }
}