#include <stdio.h>
#include <assert.h>

typedef struct {
  float x;
  float y;
  float w;
  float h;
} Layout_Rect;

void widget(Layout_Rect r)
{
  printf("widget(%f, %, %f, %f)\n", r.x, r.y, r.w, r.h);
  (void) r;
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
  size_t width = 1920;
  size_t height = 1080;

  Layout root = {
    .orient = LO_HORZ,
    .rect = {0, 0, width, height},
    .count = 3,
  };

  widget(layout_slot(&root, 0));
  widget(layout_slot(&root, 1));
  widget(layout_slot(&root, 2));

  return 0;
}
