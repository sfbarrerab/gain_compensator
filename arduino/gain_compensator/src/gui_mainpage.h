#pragma once
#include "widgets_gui.h"
#include "gui_popup.h"

#define TFT_CS 10
#define TFT_DC 9

extern Adafruit_FT6206 ctp;
extern Adafruit_ILI9341 tft;

typedef struct gui_mainpage_t
{
    Radio* read_radiobox;
    Radio* write_radiobox;
    Radio* pid_radiobox;
    Slider* channel_slider;
    Slider* value_slider;
    Button* submit_button;
}gui_mainpage_t;

void init_tft();
void task_display(void *pvParameters);