#include "screen_displayed.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Screens current_screen;

void init_tft()
{
	tft.begin();
	// origin in left-top landscape
	tft.setRotation(1);
}

void task_print_display(void *pvParameters)
{

  // Flags to track screen initialization status
  int page_initialized = 0;

  Screens old_screen = MAIN_PAGE;

  while(1){

    if(old_screen != current_screen){
      switch (old_screen)
      {
      case MAIN_PAGE:
        Serial.println("Borre la tarea del mainpage");
        delete_main_page();
        break;
      case POPUP:
        Serial.println("Borre la tarea del popup");
        delete_submit_popup();
        break;
      default:
        break;
      }
      old_screen = current_screen;
      page_initialized = 0;
    }

    switch (current_screen)
    {
    case MAIN_PAGE:
      if (!page_initialized) {
        init_mainpage();
        Serial.println("Inicie la tarea del mainpage");
        page_initialized = 1;
      }
      update_gui_mainpage();
      break;
    case POPUP:
      if(!page_initialized){
        init_submit_popup();
        page_initialized = 1;
      }
      update_popup();
      break;
    default:
      break;
    }
    vTaskDelay(1/ portTICK_PERIOD_MS);
  }

}