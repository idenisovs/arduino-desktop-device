void setupButtonHandler() {
  message(SETUP_BTN);
  pinMode(BTN_PIN, INPUT_PULLUP);
  unsigned int interrupt = digitalPinToInterrupt(BTN_PIN);
  attachInterrupt(interrupt, handleButtonPress, CHANGE);
}

void handleButtonPress() {
  s = 0;
  m = 0;
  h = 0;
  d = 0;
}
