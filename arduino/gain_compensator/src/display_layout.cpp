#include "display_layout.h"

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int oldcolor, currentcolor;

void init_tft(){

    tft.begin();

    if (! ctp.begin(40, &Wire)) {  // pass in 'sensitivity' coefficient and I2C bus   
        while (1) delay(10);
    }

      
    tft.fillScreen(ILI9341_BLACK);
    
    // make the color selection boxes
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
    tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
    tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
    tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
    tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
    
    // select the current color 'red'
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
    currentcolor = ILI9341_RED;

}


void task_display(void *pvParameters)
{

    while(1){

      
        // Wait for a touch
        if (ctp.touched()) { 
            // Retrieve a point  
            TS_Point p = ctp.getPoint();
            
            /*
            // Print out raw data from screen touch controller
            Serial.print("X = "); Serial.print(p.x);
            Serial.print("\tY = "); Serial.print(p.y);
            Serial.print(" -> ");
            */

            // flip it around to match the screen.
            p.x = map(p.x, 0, 240, 240, 0);
            p.y = map(p.y, 0, 320, 320, 0);

            // Print out the remapped (rotated) coordinates
            // if ( xSemaphoreTake( x_serial_txrx_semaphore, SEMAPHORE_BLOCK_TIME ) == pdTRUE ){

            //     Serial.print("("); Serial.print(p.x);
            //     Serial.print(", "); Serial.print(p.y);
            //     Serial.println(")");
            //     xSemaphoreGive( x_serial_txrx_semaphore );
            // }

            if (p.y < BOXSIZE) {
                oldcolor = currentcolor;

                if (p.x < BOXSIZE) { 
                    currentcolor = ILI9341_RED; 
                    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
                } else if (p.x < BOXSIZE*2) {
                    currentcolor = ILI9341_YELLOW;
                    tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
                } else if (p.x < BOXSIZE*3) {
                    currentcolor = ILI9341_GREEN;
                    tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
                } else if (p.x < BOXSIZE*4) {
                    currentcolor = ILI9341_CYAN;
                    tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
                } else if (p.x < BOXSIZE*5) {
                    currentcolor = ILI9341_BLUE;
                    tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
                } else if (p.x <= BOXSIZE*6) {
                    currentcolor = ILI9341_MAGENTA;
                    tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_WHITE);
                }

                if (oldcolor != currentcolor) {
                    if (oldcolor == ILI9341_RED) 
                        tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9341_RED);
                    if (oldcolor == ILI9341_YELLOW) 
                        tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9341_YELLOW);
                    if (oldcolor == ILI9341_GREEN) 
                        tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, ILI9341_GREEN);
                    if (oldcolor == ILI9341_CYAN) 
                        tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, ILI9341_CYAN);
                    if (oldcolor == ILI9341_BLUE) 
                        tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ILI9341_BLUE);
                    if (oldcolor == ILI9341_MAGENTA) 
                        tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, ILI9341_MAGENTA);
                }
            }
            if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
                tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
            }
        }

        vTaskDelay(1/portTICK_PERIOD_MS); 
    }
}

