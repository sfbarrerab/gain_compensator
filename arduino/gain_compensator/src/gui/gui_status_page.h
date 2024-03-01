#pragma once
#include "screen_displayed.h"
#include "gui_mainpage.h"
#include "rw_ch_settings.h"

#define SPACING_BETWEEN_LINES 25

typedef struct gui_status_page_t
{
  Textbox* header_status;
  Textbox* channels_status[MAX_NUMBER_OF_CHANNELS];
}gui_status_page_t;


void init_status_page();
void delete_status_page();