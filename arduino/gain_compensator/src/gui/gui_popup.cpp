#include "gui_popup.h"

confirmation_popup_t submit_popup_layout;

void to_main_page(){
	current_screen = SET_PAGE;
}

void init_submit_popup(){

  command_t message_received_from_gui;  
  String message_popup = "";

  if(x_messages_to_send_to_gui_queue != NULL && xQueueReceive(x_messages_to_send_to_gui_queue, (void *)&message_received_from_gui, 0) == pdTRUE)
  {
    if(message_received_from_gui.command == 0){
      
      message_popup += "    Channel: ";
      message_popup += String(message_received_from_gui.channel + 1);

      message_popup += "\n\n         Value: "; 
      message_popup += String(message_received_from_gui.value);

    }else if(message_received_from_gui.command == 1){
      message_popup += " Value: ";
      message_popup += String(message_received_from_gui.value);
      message_popup += " write \n\n       in Channel: ";
      message_popup += String(message_received_from_gui.channel + 1);

    }else if(message_received_from_gui.command == 2){
      message_popup += "    PID mode \n\n         activated";
    }

  }

  tft.fillRect(POPUP_X0,POPUP_Y0,POPUP_WIDTH,POPUP_HEIGHT,ILI9341_BLACK);
  tft.drawRect(POPUP_X0-2, POPUP_Y0-2, POPUP_WIDTH+4, POPUP_HEIGHT+4, ILI9341_DARKGREEN);
	tft.drawRect(POPUP_X0-1, POPUP_Y0-1, POPUP_WIDTH+2, POPUP_HEIGHT+2, ILI9341_DARKGREEN);

  submit_popup_layout.message_popup = new Textbox(POPUP_X0+PADDING,POPUP_Y0+5*PADDING,200,100,message_popup.c_str(),NULL,ILI9341_BLACK, ILI9341_WHITE,2);
  submit_popup_layout.message_popup->update_label(tft,NULL);

  submit_popup_layout.close_button = new Button(POPUP_X0+(POPUP_WIDTH/2)-(POPUP_BUTTON_WIDTH/2), 160, POPUP_BUTTON_WIDTH, 30, "Close", to_main_page, NULL);
	submit_popup_layout.close_button->is_released(tft);
}

void update_popup(){
  submit_popup_layout.close_button->update_state(x,y,tft);
}

void delete_submit_popup(){
  delete submit_popup_layout.close_button;
  delete submit_popup_layout.message_popup;
}
