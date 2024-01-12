#include "display_layout.h"

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
Adafruit_FT6206 ctp = Adafruit_FT6206();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

boolean RecordOn = false;

void drawFrame()
{
    tft.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, ILI9341_BLACK);
}

void redBtn()
{ 
    tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_RED);
    tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_BLUE);
    drawFrame();
    tft.setCursor(GREENBUTTON_X + 6 , GREENBUTTON_Y + (GREENBUTTON_H/2));
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("ON");
    RecordOn = false;
}

void greenBtn()
{
    tft.fillRect(GREENBUTTON_X, GREENBUTTON_Y, GREENBUTTON_W, GREENBUTTON_H, ILI9341_GREEN);
    tft.fillRect(REDBUTTON_X, REDBUTTON_Y, REDBUTTON_W, REDBUTTON_H, ILI9341_BLUE);
    drawFrame();
    tft.setCursor(REDBUTTON_X + 6 , REDBUTTON_Y + (REDBUTTON_H/2));
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.println("OFF");
    RecordOn = true;
}

void init_tft(){

    tft.begin();

    if (! ctp.begin(40, &Wire)) {  // pass in 'sensitivity' coefficient and I2C bus   
        while (1) delay(10);
    }


    tft.fillScreen(ILI9341_BLACK);
    // origin = left,top landscape (USB left upper)
    tft.setRotation(1); 

    redBtn();

}


void task_display(void *pvParameters)
{

    while(1){
             
        // Wait for a touch
        if (ctp.touched()) { 
            // Retrieve a point  
            TS_Point p = ctp.getPoint();

    
            // flip it around to match the screen.
            p.x = map(p.x, 0, 240, 240, 0);
            p.y = map(p.y, 0, 320, 320, 0);

            int y = tft.height() - p.x;
            int x = p.y;

            if (RecordOn)
            {
                if((x > REDBUTTON_X) && (x < (REDBUTTON_X + REDBUTTON_W))) {
                    if ((y > REDBUTTON_Y) && (y <= (REDBUTTON_Y + REDBUTTON_H))) {
                    redBtn();
                    }
                }
            }
            else //Record is off (RecordOn == false)
            {
                if((x > GREENBUTTON_X) && (x < (GREENBUTTON_X + GREENBUTTON_W))) {
                    if ((y > GREENBUTTON_Y) && (y <= (GREENBUTTON_Y + GREENBUTTON_H))) {
                    greenBtn();
                    }
                }


            }  
        }

        vTaskDelay(10/portTICK_PERIOD_MS); 
    }
}

