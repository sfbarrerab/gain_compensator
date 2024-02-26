#pragma once
#include "gui_mainpage.h"
#include "analog_read_write.h"

#define TEXTBOX_X0 ((i<4)?MENU_BTN_WIDTH+3*PADDING:MENU_BTN_WIDTH+3*PADDING+(SCREEN_WIDTH-MENU_BTN_WIDTH)/2)
#define REFRESHING_POWER_VALUES_PERIOD (1000/ portTICK_PERIOD_MS)

typedef struct gui_powers_page_t
{
  Textbox* channels_power[MAX_NUMBER_OF_CHANNELS];
}gui_powers_page_t;

void init_powers_page();
void update_gui_powers_page();
void delete_powers_page();