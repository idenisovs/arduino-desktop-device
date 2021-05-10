void setupButtonHandler() {
  message(SETUP_BTN);
  pinMode(BTN_PIN, INPUT_PULLUP);
  unsigned int interrupt = digitalPinToInterrupt(BTN_PIN);
  attachInterrupt(interrupt, handleButtonPress, RISING);
}

void handleButtonPress() {
  timerResetFlag = true;
}
