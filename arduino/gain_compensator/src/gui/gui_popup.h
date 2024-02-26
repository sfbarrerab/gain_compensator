#pragma once
#include "gui_mainpage.h"
#include "analog_read_write.h"

#define POPUP_WIDTH 220
#define POPUP_HEIGHT 170

#define POPUP_X0 ((SCREEN_WIDTH-POPUP_WIDTH)/2)
#define POPUP_Y0 ((SCREEN_HEIGHT-POPUP_HEIGHT)/2)
#define POPUP_BUTTON_WIDTH 70

typedef struct confirmation_popup_t
{
  Textbox* message_popup;
  Button* close_button;
} confirmation_popup_t;

void init_submit_popup();
void update_popup();
void delete_submit_popup();