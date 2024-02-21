#pragma once
#include "gui_mainpage.h"
#include "gui_popup.h"

extern Adafruit_ILI9341 tft;

typedef enum {
  MAIN_PAGE,
  POPUP,
} Screens;

extern Screens current_screen;

void init_tft();
void task_print_display(void *pvParameters);