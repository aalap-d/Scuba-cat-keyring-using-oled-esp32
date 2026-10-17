#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "video_frames.h"

#define OLED_SDA 6
#define OLED_SCL 7

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SH1106G display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1
);

void setup() {
  Serial.begin(115200);

  Wire.begin(OLED_SDA, OLED_SCL);
  Wire.setClock(100000);

  if (!display.begin(OLED_ADDRESS, true)) {
    Serial.println("OLED initialization failed!");
    while (true) {
      delay(1000);
    }
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  for (uint16_t frame = 0;
       frame < VIDEO_FRAME_COUNT;
       frame++) {

    display.clearDisplay();

    display.drawBitmap(
      0, 0,
      videoFrames[frame],
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SH110X_WHITE
    );

    display.display();
    delay(VIDEO_FRAME_DELAY_MS);
  }
}