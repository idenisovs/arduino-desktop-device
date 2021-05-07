#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <SD.h>

#include "messages.h"
#include "lcd_symbols.h"

#define LCD_WIDTH 20
#define LCD_HEIGHT 4
#define FORCE_RTC_ADJUST false
#define BTN_PIN 2
#define SDCARD_SS_PIN 10

#ifdef BME280_ADDRESS
    #undef BME280_ADDRESS
#endif

#define BME280_ADDRESS 0x76

LiquidCrystal_I2C lcd(0x27, LCD_WIDTH, LCD_HEIGHT);
RTC_DS1307 rtc;
Adafruit_BME280 bme;

bool setupFailed = false;

volatile unsigned int d = 0;
volatile byte h = 0;
volatile byte m = 0;
volatile byte s = 0;

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
