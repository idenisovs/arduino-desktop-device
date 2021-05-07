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

void printDateTime(byte line) {
  printDateTime(line, rtc.now());
}

void printDateTime(byte line, DateTime datetime) {
  char output[LCD_WIDTH + 1];

  snprintf(output, sizeof(output), "%02u.%02u.%u. %02u:%02u:%02u", datetime.day(), datetime.month(), datetime.year(), datetime.hour(), datetime.minute(), datetime.second());

  lcd.setCursor(0, line - 1);
  lcd.print(output);
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
