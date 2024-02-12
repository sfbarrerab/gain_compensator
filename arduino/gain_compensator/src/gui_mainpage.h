#pragma once
#include "widgets_gui.h"
#include "gui_popup.h"
#include "touch_screen.h"
#include "screen_displayed.h"

#define TFT_CS 10
#define TFT_DC 9

typedef struct gui_mainpage_t
{
    Radio* read_radiobox;
    Radio* write_radiobox;
    Radio* pid_radiobox;
    Slider* channel_slider;
    Slider* value_slider;
    Button* submit_button;
}gui_mainpage_t;

void init_mainpage();
void delete_main_page();
void update_gui_mainpage();