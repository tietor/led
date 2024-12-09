#include <Adafruit_NeoPixel.h>
#include "led_config.h"
#ifdef _AVR_
#include <avr/power.h>
#endif
#define PIN STRIP_PIN
#define NUMPIXELS STRIP_PIN
#include <IRremote.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int currentBrightness = 255;
boolean executeMode = false;
int lastPressedButton;
int lastSelectedMode;

const int MAX_BRIGHTNESS = 255;
const int MIN_BRIGHTNESS = 55;
const int BRIGTHNESS_LEVEL= 40;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECEIVER_PIN);
  strip.begin();
}

void loop() {
  handleButtonClick();
  handleModeExecution();
}

void handleButtonClick() {
  if (IrReceiver.decode()) {
    delay(200);
    IrReceiver.resume();
    lastPressedButton = IrReceiver.decodedIRData.command;
    switch(lastPressedButton) {
      case OFF_BUTTON:
        turnAllOff();
        executeMode = false;
        break;
      case ON_BUTTON:
        lastPressedButton = lastSelectedMode;
        executeMode = true;
        break;
      case BRIGHTNESS_UP_BUTTON:
        if (executeMode) {
          brightnessUp();
          lastPressedButton = lastSelectedMode;
        }
        break;
      case BRIGHTNESS_DOWN_BUTTON:
        if (executeMode) {
          brightnessDown();
          lastPressedButton = lastSelectedMode;
        }
        break;
    }
  }
}

void handleModeExecution() {
  if (executeMode) {
    switch (lastPressedButton) {
      case MODE_1:
        lastSelectedMode = MODE_1;
        chasePattern();
        break;
      case MODE_2:
        lastSelectedMode = MODE_2;
        streetPattern();
        break;
      case MODE_3:
        lastSelectedMode = MODE_3;
        blinkPattern();
        break;
      case MODE_4:
        lastSelectedMode = MODE_4;
        unfoldPattern();
        break;
      case MODE_5:
        lastSelectedMode = MODE_5;
        fadePattern();
        break;
      case MODE_6:
        lastSelectedMode = MODE_6;
        randomPattern();
        break;
      case MODE_7:
        lastSelectedMode = MODE_7;
        lightedStreetPattern();
        break;
      case MODE_8:
        lastSelectedMode = MODE_8;
        clashPattern();
        break;
      case MODE_9:
        lastSelectedMode = MODE_9;
        break;
      case MODE_10:
        lastSelectedMode = MODE_10;
        break;
    }
  }
}

void clashPattern() {
  
  for (int k = 0 ; k < 4 ; ++k) {
    turnAllOff();
    strip.setPixelColor(0 + k, strip.Color(0, 10, 10));
    strip.setPixelColor(7 - k, strip.Color(0, 10, 10));
    strip.show();
    delay(50);
  }

  for (int k = 0 ; k < 4 ; ++k) {
    turnAllOff();
    strip.setPixelColor(3 - k, strip.Color(0, 10, 10));
    strip.setPixelColor(4 + k, strip.Color(0, 10, 10));
    strip.show();
    delay(50);
  }
}

void lightedStreetPattern() {
  for (int k = 0 ; k < 8 ; ++k) {
    strip.setPixelColor(0, strip.Color(10, 10, 10));
    strip.setPixelColor(1, strip.Color(0, 0, 10));
    strip.setPixelColor(2, strip.Color(0, 10, 0));
    strip.setPixelColor(3, strip.Color(0, 10, 10));
    strip.setPixelColor(4, strip.Color(10, 0, 0));
    strip.setPixelColor(5, strip.Color(10, 0, 10));
    strip.setPixelColor(6, strip.Color(10, 10, 0));
    strip.setPixelColor(7, strip.Color(10, 10, 10));
    strip.setPixelColor(k, strip.Color(0, 0, 0));
    strip.show();
    delay(100);

  }
}

void randomPattern() {
    strip.setPixelColor(0, strip.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    strip.setPixelColor(1, strip.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    strip.setPixelColor(2, strip.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    strip.setPixelColor(3, strip.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    strip.setPixelColor(4, strip.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    strip.setPixelColor(5, strip.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    strip.setPixelColor(6, strip.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    strip.setPixelColor(7, strip.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    strip.show();
    delay(100);
}

void fadePattern() {
  for (int k = 10 ; k > 0 ; --k) {
    strip.setPixelColor(0, strip.Color(0, 0, k));
    strip.setPixelColor(1, strip.Color(0, 0, k));
    strip.setPixelColor(2, strip.Color(0, 0, k));
    strip.setPixelColor(3, strip.Color(0, 0, k));
    strip.setPixelColor(4, strip.Color(0, 0, k));
    strip.setPixelColor(5, strip.Color(0, 0, k));
    strip.setPixelColor(6, strip.Color(0, 0, k));
    strip.setPixelColor(7, strip.Color(0, 0, k));
    strip.show();
    delay(100);
  }
  

  for (int i = 0 ; i < 10 ; ++i) {
    strip.setPixelColor(0, strip.Color(0, 0, i));
    strip.setPixelColor(1, strip.Color(0, 0, i));
    strip.setPixelColor(2, strip.Color(0, 0, i));
    strip.setPixelColor(3, strip.Color(0, 0, i));
    strip.setPixelColor(4, strip.Color(0, 0, i));
    strip.setPixelColor(5, strip.Color(0, 0, i));
    strip.setPixelColor(6, strip.Color(0, 0, i));
    strip.setPixelColor(7, strip.Color(0, 0, i));
    strip.show();
    delay(100);
  }
}

void unfoldPattern() {
  turnAllOff();
  strip.show();
  delay(100);

  greenLED(3);
  greenLED(4);
  strip.show();
  delay(100);

  redLED(2);
  redLED(5);
  strip.show();
  delay(100);

  blueLED(1);
  blueLED(6);
  strip.show();
  delay(100);

  whiteLED(0);
  whiteLED(7);
  strip.show();
  delay(100);

  turnOffLED(0);
  turnOffLED(7);
  strip.show();
  delay(100);

  turnOffLED(1);
  turnOffLED(6);
  strip.show();
  delay(100);

  turnOffLED(2);
  turnOffLED(5);
  strip.show();
  delay(100);

  turnOffLED(3);
  turnOffLED(4);
  strip.show();
  delay(300);
}

void blinkPattern() {
  turnOffLED(0);
  redLED(1);
  turnOffLED(2);
  redLED(3);
  turnOffLED(4);
  redLED(5);
  turnOffLED(6);
  redLED(7);
  strip.show();
  delay(200);

  blueLED(0);
  turnOffLED(1);
  blueLED(2);
  turnOffLED(3);
  blueLED(4);
  turnOffLED(5);
  blueLED(6);
  turnOffLED(7);
  strip.show();
  delay(200);
  
  turnOffLED(0);
  whiteLED(1);
  turnOffLED(2);
  whiteLED(3);
  turnOffLED(4);
  whiteLED(5);
  turnOffLED(6);
  whiteLED(7);
  strip.show();
  delay(200);
  
  greenLED(0);
  turnOffLED(1);
  greenLED(2);
  turnOffLED(3);
  greenLED(4);
  turnOffLED(5);
  greenLED(6);
  turnOffLED(7);
  strip.show();
  delay(200);
}

void chasePattern() {
  int chase_1[] = {0, 1};
  int chase_2[] = {4, 5};
 
  for (int i = 0 ; i < 5 ; ++i) {
    turnAllOff();
    greenLED(chase_1[0]);
    greenLED(chase_1[1]);
    greenLED(chase_2[0]);
    greenLED(chase_2[1]);
    chase_1[0] = increment(chase_1[0]);
    chase_1[1] = increment(chase_1[1]);
    chase_2[0] = increment(chase_2[0]);
    chase_2[1] = increment(chase_2[1]);
    strip.show();
    delay(200);
  }
}
 
int increment(int ledNumber) {
  if (ledNumber == 7) {
    return 0;
  }
 
  return ++ledNumber;
}

void streetPattern() {
  int ledsToTurnOff[] = {0, 1, 2, 3, 4, 5, 6, 7};

  // first
  turnAllOff();
  redLED(0);
  strip.show();
  delay(100);

  // second
  turnAllOff();
  greenLED(1);
  strip.show();
  delay(100);

  // third
  turnAllOff();
  blueLED(2);
  strip.show();
  delay(100);

  // fourth
  turnAllOff();
  whiteLED(3);
  strip.show();
  delay(100);

  // fith
  turnAllOff();
  whiteLED(4);
  strip.show();
  delay(100);

  // sixth
  turnAllOff();
  blueLED(5);
  strip.show();
  delay(100);

  // seventh
  turnAllOff();
  greenLED(6);
  strip.show();
  delay(100);

  // eight
  turnAllOff();
  redLED(7);
  strip.show();
  delay(100);
}

void whiteLED(int ledNr) {
  strip.setPixelColor(ledNr, strip.Color(10, 10, 10));
}

void redLED(int ledNr) {
  strip.setPixelColor(ledNr, strip.Color(10, 0, 0));
}

void greenLED(int ledNr) {
  strip.setPixelColor(ledNr, strip.Color(0, 10, 0));
}

void blueLED(int ledNr) {
  strip.setPixelColor(ledNr, strip.Color(0, 0, 10));
}

void turnAllOff() {
  for (int i = 0 ; i < 8 ; i++) {
    turnOffLED(i);
  }
  strip.show();
}

void turnOffLED(int ledNr) {
  strip.setPixelColor(ledNr, strip.Color(0, 0, 0));
}

void brightnessUp() {
  int newBrightness = currentBrightness + BRIGTHNESS_LEVEL;
  if (newBrightness <= MAX_BRIGHTNESS) {
    strip.setBrightness(newBrightness);
    currentBrightness = newBrightness;
  }
}

void brightnessDown() {
  int newBrightness = currentBrightness - BRIGTHNESS_LEVEL;
  if (newBrightness >= MIN_BRIGHTNESS) {
    strip.setBrightness(newBrightness);
    currentBrightness = newBrightness;
  }
}

int getRandomNumberForColor() {
  int number = random(0, 2);
  if (number == 1) {
    return 10;
  }
  return 0;
}
