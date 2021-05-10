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
  char output[LCD_WIDTH];

  sprintf(output, "%02u.%02u.%u. %02u:%02u:%02u", datetime.day(), datetime.month(), datetime.year(), datetime.hour(), datetime.minute(), datetime.second());

  lcd.setCursor(0, line - 1);
  lcd.print(output);
}

void updateCounters() {
  t1.ss++;

  if (t1.ss >= 60) {
    t1.ss = 0;
    t1.mm++;
  }

  if (t1.mm >= 60) {
    t1.mm = 0;
    t1.hh++;
  }

  if (t1.hh >= 24) {
    t1.hh = 0;
    t1.dd++;
  }
}

void printTimer(byte line) {
  char output[LCD_WIDTH];

  sprintf(output, "%u:%02u:%02u:%02u ", t1.dd, t1.hh, t1.mm, t1.ss);

  lcd.setCursor(0, line - 1);
  lcd.print(output);
}
