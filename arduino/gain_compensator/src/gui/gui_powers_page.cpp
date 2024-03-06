#include "gui_powers_page.h"

gui_powers_page_t powers_page;
TickType_t previous_tick_count;
TickType_t current_tick_count;
  
command_t powers_message_values_request;
command_t message_received;  

void init_powers_page(){
  String label_channel_power = "";
  String const_mini_label = "";
  powers_message_values_request.command = 0;

  tft.fillRect(MENU_BTN_WIDTH,0,SCREEN_WIDTH-MENU_BTN_WIDTH,SCREEN_HEIGHT,ILI9341_BLACK);
  previous_tick_count = xTaskGetTickCount();
  for(int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    powers_message_values_request.channel = i;

    if(x_received_commands_queue != NULL){
      xQueueSend(x_received_commands_queue,(void *)&powers_message_values_request, QUEUE_SEND_BLOCK_TIME);
    }

    const_mini_label = "Ch ";
    const_mini_label += String(i+1);
    const_mini_label += ": ";

    if(x_messages_to_send_to_gui_queue != NULL && (xQueueReceive(x_messages_to_send_to_gui_queue, (void *)&message_received, QUEUE_RECEIVE_BLOCK_TIME) == pdTRUE))
    {
      label_channel_power = String(message_received.value);  
      label_channel_power += " dB";
      powers_page.channels_power[i] = new Textbox(TEXTBOX_X0,2*PADDING+((i%4)*SCREEN_HEIGHT/4),50,8,label_channel_power.c_str(),NULL,ILI9341_BLACK, ILI9341_WHITE,1,const_mini_label.c_str());
    }

    powers_page.channels_power[i]->init_label(tft);
  }
}

void update_gui_powers_page(){
  String new_power = "";
  current_tick_count = xTaskGetTickCount();
  int delta = (current_tick_count - previous_tick_count);
  
  if(delta > REFRESHING_POWER_VALUES_PERIOD){
    for(int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
      powers_message_values_request.channel = i;

      if(x_received_commands_queue != NULL){
        xQueueSend(x_received_commands_queue,(void *)&powers_message_values_request, QUEUE_RECEIVE_BLOCK_TIME);
      }

      if(x_messages_to_send_to_gui_queue != NULL && (xQueueReceive(x_messages_to_send_to_gui_queue, (void *)&message_received, QUEUE_SEND_BLOCK_TIME) == pdTRUE))
      {
        new_power = String(message_received.value);  
        new_power += " dB";
        powers_page.channels_power[i]->update_label(tft, new_power.c_str());
      }
    }
    previous_tick_count = xTaskGetTickCount();
  }

}

void delete_powers_page(){
  for(int i = 0; i < MAX_NUMBER_OF_CHANNELS; i++){
    delete powers_page.channels_power[i];
  }
}