#include "gui_set_page.h"

void init_status_page(){
  tft.fillRect(MENU_BTN_WIDTH,0,SCREEN_WIDTH-MENU_BTN_WIDTH,SCREEN_HEIGHT,ILI9341_BLACK);
  read_config_epprom();
}