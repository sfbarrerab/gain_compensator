#include "gui_popup.h"

confirmation_popup_t submit_popup_layout;

void submit_popup(){
  int x = 70;
  int y = 50;
  int width = 220;
  int height = 150;

  tft.drawRect(x-1, y-1, width+2, height+2, ILI9341_BLUE);
  tft.drawRect(x-2, y-2, width+4, height+4, ILI9341_BLUE);
	tft.fillRect(x, y, width, height, ILI9341_BLACK);
 
  submit_popup_layout.close_button = new Button(120, 190, 70, 30, "Close", init_mainpage, NULL);
	submit_popup_layout.close_button->is_released(tft);

  // bloqueando ando...
  while(1){
    submit_popup_layout.close_button->update_state(x,y,tft);
    vTaskDelay((DEBOUNCE_TIME/4)/ portTICK_PERIOD_MS);
  }
}

