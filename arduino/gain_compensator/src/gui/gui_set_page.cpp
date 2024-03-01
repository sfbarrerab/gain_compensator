#include "gui_set_page.h"

// ********************************************************
// GLOBAL VARIABLES DEFINITION

bool attenuation_radiobox_value = true;
bool pid_radiobox_value = false;

bool old_state_attenuation_radiobox;
bool old_state_pid_radiobox;

int val_slider = MIN_VALUE_SLIDER;
int channel_slider = MIN_CHANNEL_SLIDER;

bool gui_change_triggered = false;

gui_set_page_t set_page;

// **********************************************************

void to_popup_page(){
	
	command_t config_message_from_gui;	
	String command_from_gui;
	if(attenuation_radiobox_value){
		config_message_from_gui.command = 1;
	}else{
		config_message_from_gui.command = 2;
	}
	config_message_from_gui.channel = channel_slider - 1;
	config_message_from_gui.value = val_slider;
	
	if(x_received_commands_queue != NULL){
		xQueueSend(x_received_commands_queue,(void *)&config_message_from_gui, QUEUE_SEND_BLOCK_TIME);
	}

	current_screen = POPUP;
}

void init_set_page(){

	tft.fillRect(MENU_BTN_WIDTH,0,SCREEN_WIDTH-MENU_BTN_WIDTH,SCREEN_HEIGHT,ILI9341_BLACK);

	set_page.attenuation_radiobox = new Radio(MENU_BTN_WIDTH + PADDING,40,RADIOBOX_RADIUS,&attenuation_radiobox_value,"Atten.", &gui_change_triggered);
	set_page.pid_radiobox = new Radio(225,40,RADIOBOX_RADIUS,&pid_radiobox_value,"Power", &gui_change_triggered);
	set_page.channel_slider = new Slider(MENU_BTN_WIDTH + PADDING,100,SLIDER_WIDTH,5, MIN_CHANNEL_SLIDER, MAX_NUMBER_OF_CHANNELS,&channel_slider,"Channel:", 15, &gui_change_triggered);
	set_page.value_slider = new Slider(MENU_BTN_WIDTH + PADDING,160,SLIDER_WIDTH,5, MIN_VALUE_SLIDER, 255, &val_slider,"Atten. (dB):", 15, &gui_change_triggered);
	set_page.submit_button = new Button(210, 190, 90, 30, "Submit", to_popup_page, &gui_change_triggered);

	set_page.attenuation_radiobox->init_radiobox(tft);
	set_page.pid_radiobox->init_radiobox(tft);
	set_page.channel_slider->init_slider(tft);
	set_page.value_slider->init_slider(tft);
	set_page.submit_button->is_released(tft);
}

void handle_radioboxes(){
	if(attenuation_radiobox_value != old_state_attenuation_radiobox){
		if(attenuation_radiobox_value){
			pid_radiobox_value = false;
			set_page.value_slider->change_label("Atten. (dB):");
		}
		gui_change_triggered = true;

	}else if(pid_radiobox_value != old_state_pid_radiobox){
		if(pid_radiobox_value){
			attenuation_radiobox_value = false;
			set_page.value_slider->change_label("Power (dB):");
		}
		gui_change_triggered = true;
	}else{
		gui_change_triggered = false;
	}

}

void update_gui_set_page()
{
	// store current values of the radioboxes
	old_state_attenuation_radiobox = attenuation_radiobox_value;
	old_state_pid_radiobox = pid_radiobox_value;

	set_page.attenuation_radiobox->update_state(x,y,tft);
	set_page.pid_radiobox->update_state(x,y,tft);
	set_page.value_slider->update_state(x,y,tft);
	set_page.channel_slider->update_state(x,y,tft);
	set_page.submit_button->update_state(x,y,tft);

	// Disable value slider according to radioboxes options
	handle_radioboxes();
}

void delete_set_page(){
	delete set_page.attenuation_radiobox;
	delete set_page.pid_radiobox;
	delete set_page.value_slider;
	delete set_page.channel_slider;
	delete set_page.submit_button;
}
