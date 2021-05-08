#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <SD.h>

#include "config.h"
#include "messages.h"
#include "lcd_symbols.h"

LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);
RTC_DS1307 rtc;
Adafruit_BME280 bme;

typedef struct Timer {
  unsigned int d;
  byte h;
  byte m;
  byte s;
} Timer;

bool setupFailed = false;

unsigned int d = 0;
byte h = 0;
byte m = 0;
byte s = 0;

char timerRecord[LCD_WIDTH + 1];
bool timerRecordFlag = false;

byte updateTrigger = s;

void setup() { 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  setupLcd();
  setupRtc();
  setupButtonHandler();
  setupBme280();
  setupSdcard();

  if (setupFailed) {
    abort();
  }
  
  delay(1000);
  
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  if (updateTrigger != now.second()) {
    updateScreen(now);
  }

  if (timerRecordFlag) {
    writeTimerState();
  }

  delay(250);
}

void updateScreen(DateTime now) {
  updateCounters();

  printDateTime(1, now);
  printTimer(2);

  if (updateTrigger % 5 == 0) {
    printBme280(3);
  }

  updateTrigger = now.second();
}
