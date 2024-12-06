#include <Adafruit_NeoPixel.h>
#include "led_config.h"
#ifdef _AVR_
#include <avr/power.h>
#endif
#define PIN 8
#define NUMPIXELS 8
# include <IRremote.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
const int RECEIVER_PIN=11;
const int STRIP_PIN=8;

int currentBrightness = 255;
boolean executeMode = false;
int lastPressedButton;
int lastSelectedMode;

const int BRIGHTNESS_UP_BUTTON = 70;
const int BRIGHTNESS_DOWN_BUTTON = 21;
const int OFF_BUTTON = 69;
const int ON_BUTTON=71;

const int MAX_BRIGHTNESS = 255;
const int MIN_BRIGHTNESS = 55;
const int BRIGTHNESS_LEVEL= 40;

const int MODE_1 = 7;
const int MODE_2 = 22;
const int MODE_3 = 25;
const int MODE_4 = 13;
const int MODE_5 = 12;
const int MODE_6 = 24;
const int MODE_7 = 94;
const int MODE_8 = 8;
const int MODE_9 = 28;
const int MODE_10 = 90;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECEIVER_PIN);
  pixels.begin();
}

void loop() {
  if (IrReceiver.decode()) {
    delay(200);
    IrReceiver.resume();
    lastPressedButton = IrReceiver.decodedIRData.command;
    switch(lastPressedButton) {
      case OFF_BUTTON:
        turnAllOff();
        executeMode = false;
        Serial.println("Off button pressed");
        break;
      case ON_BUTTON:
        executeMode = true;
        Serial.println("On button pressed");
        break;
      case BRIGHTNESS_UP_BUTTON:
        if (executeMode) {
          brightnessUp();
          Serial.println("Brighness up");
        }
        break;
      case BRIGHTNESS_DOWN_BUTTON:
        if (executeMode) {
          brightnessDown();
          Serial.println("Brightness down");
        }
        break;
    }
  } else if (executeMode) {
    switch (lastPressedButton) {
      case MODE_1:
        lastSelectedMode = MODE_1;
        Serial.println("mode 1");
        chasePattern();
        break;
      case MODE_2:
        lastSelectedMode = MODE_2;
        Serial.println("mode 2");
        streetPattern();
        break;
      case MODE_3:
        lastSelectedMode = MODE_3;
        Serial.println("mode 3");
        blinkPattern();
        break;
      case MODE_4:
        lastSelectedMode = MODE_4;
        Serial.println("mode 4");
        unfoldPattern();
        break;
      case MODE_5:
        lastSelectedMode = MODE_5;
        Serial.println("mode 5");
        fadePattern();
        break;
      case MODE_6:
        lastSelectedMode = MODE_6;
        Serial.println("mode 6");
        randomPattern();
        break;
      case MODE_7:
        lastSelectedMode = MODE_7;
        Serial.println("mode 7");
        lightedStreetPattern();
        break;
      case MODE_8:
        lastSelectedMode = MODE_8;
        Serial.println("mode 8");
        clashPattern();
        break;
      case MODE_9:
        lastSelectedMode = MODE_9;
        Serial.println("mode 9");
        break;
      case MODE_10:
        lastSelectedMode = MODE_10;
        Serial.println("mode 10");
        break;
      case ON_BUTTON:
        lastPressedButton = lastSelectedMode;
        break;
      case BRIGHTNESS_DOWN_BUTTON:
        lastPressedButton = lastSelectedMode;
        break;
      case BRIGHTNESS_UP_BUTTON:
        lastPressedButton = lastSelectedMode;
        break;
    }
  }
}

void clashPattern() {
  
  for (int k = 0 ; k < 4 ; ++k) {
    turnAllOff();
    pixels.setPixelColor(0 + k, pixels.Color(0, 10, 10));
    pixels.setPixelColor(7 - k, pixels.Color(0, 10, 10));
    pixels.show();
    delay(50);
  }

  for (int k = 0 ; k < 4 ; ++k) {
    turnAllOff();
    pixels.setPixelColor(3 - k, pixels.Color(0, 10, 10));
    pixels.setPixelColor(4 + k, pixels.Color(0, 10, 10));
    pixels.show();
    delay(50);
  }
}

void lightedStreetPattern() {
  for (int k = 0 ; k < 8 ; ++k) {
    pixels.setPixelColor(0, pixels.Color(10, 10, 10));
    pixels.setPixelColor(1, pixels.Color(0, 0, 10));
    pixels.setPixelColor(2, pixels.Color(0, 10, 0));
    pixels.setPixelColor(3, pixels.Color(0, 10, 10));
    pixels.setPixelColor(4, pixels.Color(10, 0, 0));
    pixels.setPixelColor(5, pixels.Color(10, 0, 10));
    pixels.setPixelColor(6, pixels.Color(10, 10, 0));
    pixels.setPixelColor(7, pixels.Color(10, 10, 10));
    pixels.setPixelColor(k, pixels.Color(0, 0, 0));
    pixels.show();
    delay(100);

  }
}

void randomPattern() {
    pixels.setPixelColor(0, pixels.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    pixels.setPixelColor(1, pixels.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    pixels.setPixelColor(2, pixels.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    pixels.setPixelColor(3, pixels.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    pixels.setPixelColor(4, pixels.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    pixels.setPixelColor(5, pixels.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    pixels.setPixelColor(6, pixels.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    pixels.setPixelColor(7, pixels.Color(getRandomNumberForColor(), getRandomNumberForColor(), getRandomNumberForColor()));
    pixels.show();
    delay(100);
}

void fadePattern() {
  for (int k = 10 ; k > 0 ; --k) {
    pixels.setPixelColor(0, pixels.Color(0, 0, k));
    pixels.setPixelColor(1, pixels.Color(0, 0, k));
    pixels.setPixelColor(2, pixels.Color(0, 0, k));
    pixels.setPixelColor(3, pixels.Color(0, 0, k));
    pixels.setPixelColor(4, pixels.Color(0, 0, k));
    pixels.setPixelColor(5, pixels.Color(0, 0, k));
    pixels.setPixelColor(6, pixels.Color(0, 0, k));
    pixels.setPixelColor(7, pixels.Color(0, 0, k));
    pixels.show();
    delay(100);
  }
  

  for (int i = 0 ; i < 10 ; ++i) {
    pixels.setPixelColor(0, pixels.Color(0, 0, i));
    pixels.setPixelColor(1, pixels.Color(0, 0, i));
    pixels.setPixelColor(2, pixels.Color(0, 0, i));
    pixels.setPixelColor(3, pixels.Color(0, 0, i));
    pixels.setPixelColor(4, pixels.Color(0, 0, i));
    pixels.setPixelColor(5, pixels.Color(0, 0, i));
    pixels.setPixelColor(6, pixels.Color(0, 0, i));
    pixels.setPixelColor(7, pixels.Color(0, 0, i));
    pixels.show();
    delay(100);
  }
}

void unfoldPattern() {
  turnAllOff();
  pixels.show();
  delay(100);

  greenLED(3);
  greenLED(4);
  pixels.show();
  delay(100);

  redLED(2);
  redLED(5);
  pixels.show();
  delay(100);

  blueLED(1);
  blueLED(6);
  pixels.show();
  delay(100);

  whiteLED(0);
  whiteLED(7);
  pixels.show();
  delay(100);

  turnOffLED(0);
  turnOffLED(7);
  pixels.show();
  delay(100);

  turnOffLED(1);
  turnOffLED(6);
  pixels.show();
  delay(100);

  turnOffLED(2);
  turnOffLED(5);
  pixels.show();
  delay(100);

  turnOffLED(3);
  turnOffLED(4);
  pixels.show();
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
  pixels.show();
  delay(200);

  blueLED(0);
  turnOffLED(1);
  blueLED(2);
  turnOffLED(3);
  blueLED(4);
  turnOffLED(5);
  blueLED(6);
  turnOffLED(7);
  pixels.show();
  delay(200);
  
  turnOffLED(0);
  whiteLED(1);
  turnOffLED(2);
  whiteLED(3);
  turnOffLED(4);
  whiteLED(5);
  turnOffLED(6);
  whiteLED(7);
  pixels.show();
  delay(200);
  
  greenLED(0);
  turnOffLED(1);
  greenLED(2);
  turnOffLED(3);
  greenLED(4);
  turnOffLED(5);
  greenLED(6);
  turnOffLED(7);
  pixels.show();
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
    pixels.show();
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
  pixels.show();
  delay(100);

  // second
  turnAllOff();
  greenLED(1);
  pixels.show();
  delay(100);

  // third
  turnAllOff();
  blueLED(2);
  pixels.show();
  delay(100);

  // fourth
  turnAllOff();
  whiteLED(3);
  pixels.show();
  delay(100);

  // fith
  turnAllOff();
  whiteLED(4);
  pixels.show();
  delay(100);

  // sixth
  turnAllOff();
  blueLED(5);
  pixels.show();
  delay(100);

  // seventh
  turnAllOff();
  greenLED(6);
  pixels.show();
  delay(100);

  // eight
  turnAllOff();
  redLED(7);
  pixels.show();
  delay(100);
}

void whiteLED(int ledNr) {
  pixels.setPixelColor(ledNr, pixels.Color(10, 10, 10));
}

void redLED(int ledNr) {
  pixels.setPixelColor(ledNr, pixels.Color(10, 0, 0));
}

void greenLED(int ledNr) {
  pixels.setPixelColor(ledNr, pixels.Color(0, 10, 0));
}

void blueLED(int ledNr) {
  pixels.setPixelColor(ledNr, pixels.Color(0, 0, 10));
}

void turnAllOff() {
  for (int i = 0 ; i < 8 ; i++) {
    turnOffLED(i);
  }
  pixels.show();
}

void turnOffLED(int ledNr) {
  pixels.setPixelColor(ledNr, pixels.Color(0, 0, 0));
}

void brightnessUp() {
  int newBrightness = currentBrightness + BRIGTHNESS_LEVEL;
  if (newBrightness <= MAX_BRIGHTNESS) {
    pixels.setBrightness(newBrightness);
    pixels.show();
    currentBrightness = newBrightness;
  }
}

void brightnessDown() {
  int newBrightness = currentBrightness - BRIGTHNESS_LEVEL;
  Serial.println("current brightness: ");
  Serial.println(currentBrightness);
  Serial.println(newBrightness);
  if (newBrightness >= MIN_BRIGHTNESS) {
    pixels.setBrightness(newBrightness);
    pixels.show();
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
