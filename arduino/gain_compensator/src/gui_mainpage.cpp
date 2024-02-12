#include "gui_mainpage.h"

Adafruit_FT6206 ctp = Adafruit_FT6206();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
bool read_checkbox_value;
bool write_checkbox_value;
int val_slider;
int channel_slider;

bool gui_change_triggered = false;

gui_mainpage_t mainpage;

void init_mainpage(){
	mainpage.submit_button = new Button(200, 190, 90, 30, "Submit", NULL, &gui_change_triggered);
	mainpage.submit_button->is_released(tft);

	mainpage.read_checkbox = new Checkbox(40,40,15,&read_checkbox_value,"Read", &gui_change_triggered);
	mainpage.read_checkbox->is_not_checked(tft);

	mainpage.write_checkbox = new Checkbox(180,40,15,&write_checkbox_value,"Write", &gui_change_triggered);
	mainpage.write_checkbox->is_checked(tft);

	mainpage.channel_slider = new Slider(40,100,220,5,1,8,&channel_slider,"Channel:", 15, &gui_change_triggered);
	mainpage.channel_slider->init_slider(tft);

	mainpage.value_slider = new Slider(40,160,220,5,0,100,&val_slider,"Value:", 15, &gui_change_triggered);
	mainpage.value_slider->init_slider(tft);
}


void init_tft()
{

	tft.begin();

	if (!ctp.begin(30, &Wire))
	{ // pass in 'sensitivity' coefficient and I2C bus
		while (1)
			delay(10);
	}

	tft.fillScreen(ILI9341_BLACK);
	// origin = left,top landscape
	tft.setRotation(1);

	init_mainpage();
}

void task_display(void *pvParameters)
{

	while (1)
	{

		// store current values of the checkboxes (can disable widget components)
		bool old_state_read_checkbox = read_checkbox_value;
		bool old_state_write_checkbox = write_checkbox_value;

		int x,y;
		x = 0;
		y=0;
		// Wait for a touch
		if (ctp.touched())
		{
			// Retrieve a point
			TS_Point p = ctp.getPoint();

			// flip it around to match the screen.
			p.x = map(p.x, 0, 240, 240, 0);
			p.y = map(p.y, 0, 320, 320, 0);

			y = tft.height() - p.x;
			x = p.y;
		}
		mainpage.submit_button->update_state(x,y,tft);
		mainpage.read_checkbox->update_state(x,y,tft);
		mainpage.write_checkbox->update_state(x,y,tft);
		mainpage.value_slider->update_state(x,y,tft);
		mainpage.channel_slider->update_state(x,y,tft);

		// Disable value slider according to checkboxes options
		if((read_checkbox_value != old_state_read_checkbox) || (write_checkbox_value != old_state_write_checkbox)){
			gui_change_triggered = true;
			if(read_checkbox_value){
				mainpage.value_slider->set_disabled(true);
			}
			if(write_checkbox_value){
				mainpage.value_slider->set_disabled(false);
			}
		}else{
			gui_change_triggered = false;
		}

		vTaskDelay(10/ portTICK_PERIOD_MS);
	}
}
