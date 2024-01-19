#include "gui_mainpage.h"

Adafruit_FT6206 ctp = Adafruit_FT6206();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

gui_mainpage_t mainpage;

void init_mainpage(){
	mainpage.my_button = new Button(200, 170, 90, 30, "Submit", NULL);
	mainpage.my_button->is_released(tft);
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
		mainpage.my_button->update_button_state(x,y,tft);
		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
}
