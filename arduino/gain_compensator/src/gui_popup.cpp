#include "gui_popup.h"

confirmation_popup_t submit_popup_layout;

void init_submit_popup(){
  current_screen = POPUP;
  tft.drawRect(POPUP_X0-1, POPUP_Y0-1, POPUP_WIDTH+2, POPUP_HEIGHT+2, ILI9341_BLUE);
  tft.drawRect(POPUP_X0-2, POPUP_Y0-2, POPUP_WIDTH+4, POPUP_HEIGHT+4, ILI9341_BLUE);
	tft.fillRect(POPUP_X0, POPUP_Y0, POPUP_WIDTH, POPUP_HEIGHT, ILI9341_BLACK);

  submit_popup_layout.close_button = new Button(120, 190, 70, 30, "Close", init_mainpage, NULL);
	submit_popup_layout.close_button->is_released(tft);
}

void update_popup(){
  submit_popup_layout.close_button->update_state(x,y,tft);
}

void delete_submit_popup(){
  delete submit_popup_layout.close_button;
}
