#pragma once
#include "gui_mainpage.h"
#include "touch_screen.h"
#include "screen_displayed.h"

#define MIN_CHANNEL_SLIDER 1
#define MIN_VALUE_SLIDER 0

#define RADIOBOX_RADIUS 15
#define SLIDER_WIDTH (SCREEN_WIDTH-MENU_BTN_WIDTH - 6*PADDING)

typedef struct gui_set_page_t
{
    Radio* attenuation_radiobox;
    Radio* pid_radiobox;
    Slider* channel_slider;
    Slider* value_slider;
    Button* submit_button;
}gui_set_page_t;

void init_set_page();
void delete_set_page();
void update_gui_set_page();