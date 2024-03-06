#pragma once
#include "widgets_gui.h"
#include "touch_screen.h"

#define TFT_CS 10
#define TFT_DC 9

#define MENU_BTN_WIDTH 90
#define MENU_BTN_HEIGHT (230/3)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define PADDING 10

typedef struct gui_mainpage_t
{
    Button* set_page_button;
    Button* powers_page_button;
    Button* attenuations_page_button;
}gui_mainpage_t;

typedef enum {
  SET_PAGE,
  POWERS_PAGE,
  STATUS_PAGE,
  POPUP,
} Screens;

extern Adafruit_ILI9341 tft;
extern Screens current_screen;


void init_main_page();
void delete_main_page();
void print_again_tab_btns();
void update_gui_main_page();