#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>

typedef struct {
  float x;
  float y;
  float w;
  float h;
} Layout_Rect;

void widget(Layout_Rect r, Color c)
{
  Rectangle rr = {
    ceilf(r.x), ceilf(r.y), ceilf(r.w), ceilf(r.h)
  };
  if (CheckCollisionPointRec(GetMousePosition(), rr)) {
    c = ColorBrightness(c, 0.75f);
  }
  DrawRectangleRec(rr, c);
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
  size_t i;
  float padding;
  float gap;
} Layout;

Layout_Rect make_layout_rect(float x, float y, float w, float h)
{
  Layout_Rect r = {0};
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  return r;
}

// function to make sure all fields of Layout are initialized except i, should be called everytime a new layout gets created
// when adding new parameter to this function it will fail at other places telling you to initialize field
Layout make_layout(Layout_Orient orient, Layout_Rect rect, size_t count, float gap)
{
  Layout l = {0};
  l.orient = orient;
  l.rect = rect;
  l.count = count;
  l.gap = gap;

  return l;
}

Layout_Rect layout_slot(Layout *l)
{
  assert(l->i < l->count);

  Layout_Rect r = {0};
  switch (l->orient) {
  case LO_HORZ:
    r.w = l->rect.w/l->count;
    r.h = l->rect.h;
    r.x = l->rect.x + l->i*r.w;
    r.y = l->rect.y;

    if(l->i == 0) { //First
      r.w -= l->gap/2;
    } else if (l->i >= l->count - 1) { //Last
      r.x += l->gap/2;
      r.w -= l->gap/2;
    } else { //Middle
      r.x += l->gap/2;
      r.w -= l->gap;
    }

    break;

  case LO_VERT:
    r.w = l->rect.w;
    r.h = l->rect.h/l->count;
    r.x = l->rect.x;
    r.y = l->rect.y + l->i*r.h;

    if(l->i == 0) { //First
      r.h -= l->gap/2;
    } else if (l->i >= l->count - 1) { //Last
      r.y += l->gap/2;
      r.h -= l->gap/2;
    } else { //Middle
      r.y += l->gap/2;
      r.h -= l->gap;
    }

    break;

  default:
    assert(0 && "unreachable");
  }

  l-> i += 1;

  return r;
}

//dynamic array
typedef struct {
  Layout *items;
  size_t count;
  size_t capacity;
} Layout_Stack;

#define DA_INIT_CAP 256
#define da_append(da, item)                                                          \
    do {                                                                             \
        if ((da)->count >= (da)->capacity) {                                         \
            (da)->capacity = (da)->capacity == 0 ? DA_INIT_CAP : (da)->capacity*2;   \
            (da)->items = realloc((da)->items, (da)->capacity*sizeof(*(da)->items)); \
            assert((da)->items != NULL && "Buy more RAM lol");                       \
        }                                                                            \
                                                                                     \
        (da)->items[(da)->count++] = (item);                                         \
    } while (0)

void layout_stack_push(Layout_Stack *ls, Layout_Orient orient, Layout_Rect rect, size_t count, float padding)
{
  Layout l = make_layout(orient, rect, count, padding);
  da_append(ls, l);
}

Layout_Rect layout_stack_slot(Layout_Stack *ls)
{
  assert(ls->count > 0);
  return layout_slot(&ls->items[ls->count-1]);
}

void layout_stack_pop(Layout_Stack *ls)
{
  assert(ls->count > 0);
  ls->count -= 1;
}

int main(void)
{
  size_t factor = 80;
  size_t width = 16*factor;
  size_t height = 9*factor;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(width, height, "test_layout");
  SetTargetFPS(60);

  Layout_Stack ls = {0};

  while(!WindowShouldClose()) {

    float w = GetRenderWidth();
    float h = GetRenderHeight();
    size_t frame = h*0.15;
    float gap = 10.0f;

    BeginDrawing();
    ClearBackground(BLACK);

    layout_stack_push(&ls, LO_HORZ, make_layout_rect(0, frame, w, h - 2*frame), 3, gap);
    widget(layout_stack_slot(&ls), RED);
    widget(layout_stack_slot(&ls), BLUE);

    // 3 nested vertical widgets in 3rd vertical widget
    layout_stack_push(&ls, LO_VERT, layout_stack_slot(&ls), 3, gap);
    // 2 nested horizontal widgets in first nested vertical widget of 3rd vertical widget
    layout_stack_push(&ls, LO_HORZ, layout_stack_slot(&ls), 2, gap);
    widget(layout_stack_slot(&ls), GREEN);
    widget(layout_stack_slot(&ls), PURPLE);
    layout_stack_pop(&ls);

    // 3 nested horizontal widgets in second widget of 3rd vertical widget
    layout_stack_push(&ls, LO_HORZ, layout_stack_slot(&ls), 3, gap);
    widget(layout_stack_slot(&ls), YELLOW);
    widget(layout_stack_slot(&ls), YELLOW);
    widget(layout_stack_slot(&ls), YELLOW);
    layout_stack_pop(&ls);

    widget(layout_stack_slot(&ls), PURPLE);
    layout_stack_pop(&ls);
    layout_stack_pop(&ls);

    EndDrawing();

    assert(ls.count == 0);
  }
  return 0;
}
