#ifndef GUI_H
#define GUI_H

#include "../util/type.h"
#include "../util/vec.h"
#include "../util/indices.h"
#include "../window/window.h"
#include "component/component.h"

typedef struct {
    Component *root;
    u32 length, max_length;
    f32 *buffer;
} GUI;

extern GUI gui;
extern Window window;

void gui_init(void);
void gui_push_data(void);
bool gui_interact(void);
void gui_destroy(void);

#endif