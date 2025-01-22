#include <stdio.h>

#define NN_IMPLEMENTATION
#define NN_ENABLE_GYM
#include "nn.h"

#include <raylib.h>

void gym_render_weights(Gym_Rect r, Mat m)
{
  Color low_color = {0xFF, 0x00, 0xFF, 0xFF};
  Color high_color = {0x00, 0xFF, 0x00, 0xFF};

  float cell_width = r.w/m.cols;
  float cell_height = r.h/m.rows;

  for (size_t y = 0; y < m.rows; ++y) {
    for (size_t x = 0; x < m.cols; ++x) {
      float alpha = sigmoidf(MAT_AT(m, y, x));
      high_color.a = floorf(255.f*alpha);
      Color color = ColorAlphaBlend(low_color, high_color, WHITE);
      DrawRectangle(r.x + x*cell_width, r.y + y*cell_height, cell_width, cell_height, color);
    }
  }
}

int main (void)
{
  size_t arch[] = {2, 3, 4, 2};
  NN nn = nn_alloc(arch, ARRAY_LEN(arch));
  nn_rand(nn, -1, 1);
  NN_PRINT(nn);

  int w = 800;
  int h = 600;
  InitWindow(w, h, "Simple_UI");

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    Gym_Rect r = {0, 0, w, h};
    gym_layout_begin(GLO_HORZ, r, 2, 0);
    gym_render_nn(nn, gym_layout_slot());
    gym_render_weights(gym_layout_slot(), nn.ws[0]);
    gym_layout_end();
    EndDrawing();
  }
  return 0;
}
