#include "gui_mainpage.h"

Adafruit_FT6206 ctp = Adafruit_FT6206();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
bool read_function_checkbox = true;
bool write_function_checkbox = false;
int val_slider = 0;
int channel_slider = 1;

gui_mainpage_t mainpage;

void init_mainpage(){
	mainpage.submit_button = new Button(200, 190, 90, 30, "Submit", NULL);
	mainpage.submit_button->is_released(tft);

	mainpage.read_checkbox = new Checkbox(40,40,15,&read_function_checkbox,"Read");
	mainpage.read_checkbox->is_checked(tft);

	mainpage.write_checkbox = new Checkbox(180,40,15,&write_function_checkbox,"Write");
	mainpage.write_checkbox->is_not_checked(tft);

	mainpage.value_slider = new Slider(40,100,220,5,0,100,&val_slider,"Value:",15);
	mainpage.value_slider->init_slider(tft);

	mainpage.channel_slider = new Slider(40,160,220,5,1,8,&channel_slider,"Channel:",15);
	mainpage.channel_slider->init_slider(tft);
}


void init_tft()
{

	tft.begin();

	if (!ctp.begin(40, &Wire))
	{ // pass in 'sensitivity' coefficient and I2C bus
		while (1)
			delay(10);
	}

	tft.fillScreen(ILI9341_BLACK);
	// origin = left,top landscape (USB left upper)
	tft.setRotation(1);

	init_mainpage();
}

void task_display(void *pvParameters)
{

	while (1)
	{
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
		vTaskDelay(1/ portTICK_PERIOD_MS);
	}
}
