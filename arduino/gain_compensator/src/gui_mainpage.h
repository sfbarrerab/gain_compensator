#pragma once
#include "widgets_gui.h"
#include "gui_popup.h"
#include "touch_screen.h"

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

extern Adafruit_ILI9341 tft;

void init_tft();
void init_mainpage();
void task_display(void *pvParameters);