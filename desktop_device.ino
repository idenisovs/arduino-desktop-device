#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <SD.h>

#include "config.h"
#include "messages.h"
#include "lcd_symbols.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_WIDTH, LCD_HEIGHT);
RTC_DS1307 rtc;
Adafruit_BME280 bme;

typedef struct Timer {
  byte dd;
  byte hh;
  byte mm;
  byte ss;
} Timer;

Timer t1 = { 0, 0, 0, 0 };

bool setupFailed = false;
volatile bool timerResetFlag = false;
byte updateTrigger = t1.ss;

void setup() {  
  setupLcd();
  setupRtc();
  setupButtonHandler();
  setupBme280();
  setupSdcard();

  loadTimer();

  if (setupFailed) {
    abort();
  }

  message(OK);
  
  delay(1000);
  
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  if (updateTrigger != now.second()) {
    updateCounters();
    updateScreen(now);

    if (t1.ss % WRITE_INTERVAL_SEC == 0) {
      backupTimer();
    }

    updateTrigger = now.second();
  }

  if (timerResetFlag) {
    writeTimerState();
    resetTimer();
    backupTimer();
    timerResetFlag = false;
  } 

  delay(250);
}

void updateScreen(DateTime now) {
  printDateTime(1, now);
  printTimer(2);

  if (updateTrigger % 5 == 0) {
    printBme280(3);
  }
}
