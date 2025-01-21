#include <stdio.h>

#define NN_IMPLEMENTATION
#define NN_ENABLE_GYM
#include "nn.h"

#include <raylib.h>

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
    gym_render_nn(nn, 0, 0, w, h);
    EndDrawing();
  }
  return 0;
}
