void setupButtonHandler() {
  message(SETUP_BTN);
  pinMode(BTN_PIN, INPUT_PULLUP);
  unsigned int interrupt = digitalPinToInterrupt(BTN_PIN);
  attachInterrupt(interrupt, handleButtonPress, RISING);
}

void handleButtonPress() {
  saveTimerRecord();
  resetCounters();
}

void saveTimerRecord() {
  snprintf(timerRecord, sizeof(timerRecord), "%u:%02u:%02u:%02u", d, h, m, s);
  timerRecordFlag = true;
}

void resetCounters() {
  s = 0;
  m = 0;
  h = 0;
  d = 0;
}
