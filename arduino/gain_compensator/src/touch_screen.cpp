#include "touch_screen.h"

Adafruit_FT6206 ctp = Adafruit_FT6206();

int x,y;

void init_touch_screen(){
	if (!ctp.begin(30, &Wire))
	{ // pass in 'sensitivity' coefficient and I2C bus
		while (1)
			vTaskDelay(10/ portTICK_PERIOD_MS);
	}
}

void task_touch_screen(void *pvParameters)
{
  while(1){
    x = 0;
    y=0;
    // Wait for a touch
    if (ctp.touched())
    {
      // Retrieve a point
      TS_Point p = ctp.getPoint();

      // flip it around to match the screen.
      p.x = map(p.x, 0, DISPLAY_PIXEL_HEIGHT, DISPLAY_PIXEL_HEIGHT, 0);
      p.y = map(p.y, 0, DISPLAY_PIXEL_WIDTH, DISPLAY_PIXEL_WIDTH, 0);

      y = DISPLAY_PIXEL_HEIGHT - p.x;
      x = p.y;
    }

    vTaskDelay(2/ portTICK_PERIOD_MS);
  }
}