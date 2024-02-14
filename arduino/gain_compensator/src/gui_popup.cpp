#include "gui_popup.h"

confirmation_popup_t submit_popup_layout;

void to_main_page(){
	current_screen = MAIN_PAGE;
}

void init_submit_popup(){

  command_t message_received_from_gui;  
  String message_popup = "";

  if(x_messages_to_send_to_gui_queue != NULL && xQueueReceive(x_messages_to_send_to_gui_queue, (void *)&message_received_from_gui, 0) == pdTRUE)
  {
    if(message_received_from_gui.command == 0){
      
      message_popup += "Channel: ";
      message_popup += String(message_received_from_gui.channel + 1);

      message_popup += "\nValue: ";
      message_popup += String(message_received_from_gui.value);

    }else if(message_received_from_gui.command == 1){
      message_popup += "Value: ";
      message_popup += String(message_received_from_gui.value);
      message_popup += " write \nin Channel: ";
      message_popup += String(message_received_from_gui.channel + 1);

    }else if(message_received_from_gui.command == 2){
      message_popup += "PID mode activated";
    }

  }


  tft.drawRect(POPUP_X0-1, POPUP_Y0-1, POPUP_WIDTH+2, POPUP_HEIGHT+2, ILI9341_BLUE);
  tft.drawRect(POPUP_X0-2, POPUP_Y0-2, POPUP_WIDTH+4, POPUP_HEIGHT+4, ILI9341_BLUE);
	tft.fillRect(POPUP_X0, POPUP_Y0, POPUP_WIDTH, POPUP_HEIGHT, ILI9341_BLACK);

  submit_popup_layout.close_button = new Button(120, 190, 70, 30, "Close", to_main_page, NULL);
	submit_popup_layout.close_button->is_released(tft);

  Serial.println(message_popup);
}

void update_popup(){
  submit_popup_layout.close_button->update_state(x,y,tft);
}

void delete_submit_popup(){
  delete submit_popup_layout.close_button;
}
