#include "widgets_gui.h"

//Touchscreen X+ X- Y+ Y- pins
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 5   // can be a digital pin
#define XP 4   // can be a digital pin

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


void init_tft();
void task_display(void *pvParameters);