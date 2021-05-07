void setupRtc() {
  message(SETUP_RTC);

  if (!rtc.begin()) {
    message(RTC_FAILED);
    setupFailed = true;
    return;
  }

  if (!rtc.isrunning() || FORCE_RTC_ADJUST) {
    message(RTC_LOST_POWER);
    message(RTC_TIME_ADJUST);
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    message(DONE);
    delay(3000);
    lcd.clear();
  }
}

DateTime printDateTime(byte line) {
  DateTime now = rtc.now();

  char output[LCD_WIDTH + 1];

  snprintf(output, sizeof(output), "%02u.%02u.%u. %02u:%02u:%02u", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());

  lcd.setCursor(0, line - 1);
  lcd.print(output);

  return now;
}

void updateCounters() {
  s++;

  if (s >= 60) {
    s = 0;
    m++;
  }

  if (m >= 60) {
    m = 0;
    h++;
  }

  if (h >= 24) {
    h = 0;
    d++;
  }
}

void printTimer(byte line) {
  char output[LCD_WIDTH + 1];

  snprintf(output, sizeof(output), "%u:%02u:%02u:%02u", d, h, m, s);

  lcd.setCursor(0, line - 1);
  lcd.print(output);
}
