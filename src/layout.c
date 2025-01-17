#include <stdio.h>
#include <assert.h>
#include <raylib.h>

typedef struct {
  float x;
  float y;
  float w;
  float h;
} Layout_Rect;

void widget(Layout_Rect r, Color c)
{
  DrawRectangle(r.x, r.y, r.w, r.h, c);
  printf("widget(%f, %, %f, %f)\n", r.x, r.y, r.w, r.h);
}

// Orientation of Layout

typedef enum {
  LO_HORZ,
  LO_VERT,
} Layout_Orient;

typedef struct {
  Layout_Orient orient;
  Layout_Rect rect;
  size_t count;
} Layout;

Layout_Rect layout_slot(Layout *l, size_t i)
{
  assert(i < l->count);

  Layout_Rect r = {0};
  switch (l->orient) {
  case LO_HORZ:
    r.w = l->rect.w/l->count;
    r.h = l->rect.h;
    r.x = l->rect.x + i*r.w;
    r.y = l->rect.y;
    break;

  case LO_VERT:
    r.w = l->rect.w;
    r.h = l->rect.h/l->count;
    r.x = l->rect.x;
    r.y = l->rect.y + i*r.h;
    break;

  default:
    assert(0 && "unreachable");
  }
  return r;
}

int main(void)
{
  size_t factor = 80;
  size_t width = 16*factor;
  size_t height = 9*factor;

  InitWindow(width, height, "test_layout");
  SetTargetFPS(60);

  Layout root = {
    .orient = LO_VERT,
    .rect = {0, 0, width, height},
    .count = 3,
  };

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    widget(layout_slot(&root, 0), BLUE);
    widget(layout_slot(&root, 1), RED);
    widget(layout_slot(&root, 2), GREEN);
    EndDrawing();
  }
  return 0;
}
