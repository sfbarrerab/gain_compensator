#include "screen_displayed.h"

void init_tft()
{
	tft.begin();
	// origin in left-top landscape
	tft.setRotation(1);
}


void delete_previous_page(int old_screen){
  switch (old_screen)
  {
    case SET_PAGE:
      delete_set_page();
      break;
    case POWERS_PAGE:
      delete_powers_page();
      break;
    case STATUS_PAGE:
      delete_status_page();
      break;
    case POPUP:
      delete_submit_popup();
      print_again_tab_btns();
      break;
    default:
      break;
  }
}

void task_print_display(void *pvParameters)
{

  // Flags to track screen initialization status
  int page_initialized = 0;

  Screens old_screen = SET_PAGE;
  init_main_page();
  
  while(1){
    update_gui_main_page();
    if(old_screen != current_screen){
      delete_previous_page(old_screen);
      old_screen = current_screen;
      page_initialized = 0;
    }

    switch (current_screen)
    {
    case SET_PAGE:
      if (!page_initialized) {
        init_set_page();
        page_initialized = 1;
      }
      update_gui_set_page();
      break;
    case POWERS_PAGE:
      if (!page_initialized) {
        init_powers_page();
        page_initialized = 1;
      }
      update_gui_powers_page();
      break;
    case STATUS_PAGE:
      if (!page_initialized) {
        init_status_page();
        page_initialized = 1;
      }
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