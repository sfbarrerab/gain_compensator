#include "gui_mainpage.h"

// ********************************************************
// GLOBAL VARIABLES DEFINITION

bool read_radiobox_value = false;
bool write_radiobox_value = true;
bool pid_radiobox_value = false;

bool old_state_read_radiobox;
bool old_state_write_radiobox;
bool old_state_pid_radiobox;

int val_slider;
int channel_slider;

bool gui_change_triggered = false;

gui_mainpage_t mainpage;

// **********************************************************

void to_popup_page(){
	
	command_t config_message_from_gui;	
	String command_from_gui;
	if(read_radiobox_value){
		config_message_from_gui.command = 0;
	}else if(write_radiobox_value){
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

void init_mainpage(){

	tft.fillScreen(ILI9341_BLACK);

	mainpage.read_radiobox = new Radio(40,40,15,&read_radiobox_value,"Read", &gui_change_triggered);
	mainpage.read_radiobox->init_radiobox(tft);

	mainpage.write_radiobox = new Radio(140,40,15,&write_radiobox_value,"Write", &gui_change_triggered);
	mainpage.write_radiobox->init_radiobox(tft);

	mainpage.pid_radiobox = new Radio(250,40,15,&pid_radiobox_value,"PID", &gui_change_triggered);
	mainpage.pid_radiobox->init_radiobox(tft);

	mainpage.channel_slider = new Slider(40,100,230,5,1,8,&channel_slider,"Channel:", 15, &gui_change_triggered);
	mainpage.channel_slider->init_slider(tft);

	mainpage.value_slider = new Slider(40,160,230,5,0,100,&val_slider,"Value:", 15, &gui_change_triggered);
	mainpage.value_slider->init_slider(tft);

	mainpage.submit_button = new Button(210, 190, 90, 30, "Submit", to_popup_page, &gui_change_triggered);
	mainpage.submit_button->is_released(tft);
}

void handle_radioboxes(){
	if(read_radiobox_value != old_state_read_radiobox){
		if(read_radiobox_value){
			write_radiobox_value = false;
			pid_radiobox_value  = false;
			mainpage.value_slider->set_disabled(true);
			mainpage.channel_slider->set_disabled(false);
		}
		gui_change_triggered = true;

	}else if(write_radiobox_value != old_state_write_radiobox){
		if(write_radiobox_value){
			read_radiobox_value = false;
			pid_radiobox_value = false;
			mainpage.value_slider->set_disabled(false);
			mainpage.channel_slider->set_disabled(false);
		}
		gui_change_triggered = true;

	}else if(pid_radiobox_value != old_state_pid_radiobox){
		if(pid_radiobox_value){
			write_radiobox_value = false;
			read_radiobox_value = false;
			mainpage.value_slider->set_disabled(true);
			mainpage.channel_slider->set_disabled(true);
		}
		gui_change_triggered = true;
	}else{
		gui_change_triggered = false;
	}

}

void update_gui_mainpage()
{
	// store current values of the radioboxes
	old_state_read_radiobox = read_radiobox_value;
	old_state_write_radiobox = write_radiobox_value;
	old_state_pid_radiobox = pid_radiobox_value;

	mainpage.read_radiobox->update_state(x,y,tft);
	mainpage.write_radiobox->update_state(x,y,tft);
	mainpage.pid_radiobox->update_state(x,y,tft);
	mainpage.value_slider->update_state(x,y,tft);
	mainpage.channel_slider->update_state(x,y,tft);
	mainpage.submit_button->update_state(x,y,tft);

	// Disable value slider according to radioboxes options
	handle_radioboxes();
}

void delete_main_page(){
	delete mainpage.read_radiobox;
	delete mainpage.write_radiobox;
	delete mainpage.pid_radiobox;
	delete mainpage.value_slider;
	delete mainpage.channel_slider;
	delete mainpage.submit_button;
}
