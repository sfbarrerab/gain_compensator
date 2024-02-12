#include "gui_mainpage.h"

// ********************************************************
// GLOBAL VARIABLES DEFINITION

bool read_radiobox_value;
bool write_radiobox_value;
bool pid_radiobox_value;

bool old_state_read_radiobox;
bool old_state_write_radiobox;
bool old_state_pid_radiobox;

int val_slider;
int channel_slider;

bool gui_change_triggered = false;

gui_mainpage_t mainpage;

// **********************************************************

void init_mainpage(){
	
	current_screen = MAIN_PAGE;
	tft.fillScreen(ILI9341_BLACK);

	mainpage.read_radiobox = new Radio(40,40,15,&read_radiobox_value,"Read", &gui_change_triggered);
	mainpage.read_radiobox->is_not_selected(tft);

	mainpage.write_radiobox = new Radio(140,40,15,&write_radiobox_value,"Write", &gui_change_triggered);
	mainpage.write_radiobox->is_selected(tft);

	mainpage.pid_radiobox = new Radio(250,40,15,&pid_radiobox_value,"PID", &gui_change_triggered);
	mainpage.pid_radiobox->is_not_selected(tft);

	mainpage.channel_slider = new Slider(40,100,250,5,1,8,&channel_slider,"Channel:", 15, &gui_change_triggered);
	mainpage.channel_slider->init_slider(tft);

	mainpage.value_slider = new Slider(40,160,250,5,0,100,&val_slider,"Value:", 15, &gui_change_triggered);
	mainpage.value_slider->init_slider(tft);

	mainpage.submit_button = new Button(210, 190, 90, 30, "Submit", init_submit_popup, &gui_change_triggered);
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

	// while (1)
	// {

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

	// 	vTaskDelay((DEBOUNCE_TIME/4)/ portTICK_PERIOD_MS);
	// }
}

void delete_main_page(){
		delete mainpage.read_radiobox;
		delete mainpage.write_radiobox;
		delete mainpage.pid_radiobox;
		delete mainpage.value_slider;
		delete mainpage.channel_slider;
		delete mainpage.submit_button;
}
