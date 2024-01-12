#include <Adafruit_GFX.h>    // Core graphics library

#define BUTTON_RADIOUS 10

void initButton(int16_t ButtonX, int16_t ButtonY, uint8_t ButtonWidth, uint8_t ButtonHeight,
		uint16_t OutlineColor, uint16_t ButtonColor, uint16_t TextColor, uint16_t BackgroundColor,
		const char *ButtonText, int16_t TextOffsetX, int16_t TextOffsetY);