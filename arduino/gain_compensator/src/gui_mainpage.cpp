#include "gui_mainpage.h"

Adafruit_FT6206 ctp = Adafruit_FT6206();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

gui_mainpage_t mainpage;

void init_mainpage(){
    mainpage.myButton = new Button(10, 20, 50, 30, "ON", NULL);
    mainpage.myButton->draw_widget(tft);
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

		// Wait for a touch
		if (ctp.touched())
		{
			// Retrieve a point
			TS_Point p = ctp.getPoint();

			// flip it around to match the screen.
			p.x = map(p.x, 0, 240, 240, 0);
			p.y = map(p.y, 0, 320, 320, 0);

			int y = tft.height() - p.x;
			int x = p.y;

            if ((x > REDBUTTON_X) && (x < (REDBUTTON_X + REDBUTTON_W)))
            {
                if ((y > REDBUTTON_Y) && (y <= (REDBUTTON_Y + REDBUTTON_H)))
                {
                    mainpage.myButton->onTouch();
                    mainpage.myButton->draw_widget(tft);
                }
            }
			
		}

		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}
