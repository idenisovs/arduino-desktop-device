char messages[4][20];
byte messageCounter = 0;

void message(const char * text) {
  message(text, 1);
}

void message(const char * text, byte line) {
  byte bfs = LCD_WIDTH;
  
  char buffer[bfs];

  snprintf(buffer, LCD_WIDTH, FORMATL, text);
  
  if (messageCounter < 4) {
    insertMessage(buffer);
  } else {
    appendMessage(buffer);
  }
  
  for (byte idx = 0; idx < 4; idx++) {
    lcd.setCursor(0, idx);
    lcd.print(messages[idx]);
  }
}

void insertMessage(const char * text) {
  strcpy(messages[messageCounter], text);
  messageCounter++;
}

void appendMessage(const char * text) {
  for (byte idx = 1; idx < 4; idx++) {
    memcpy(messages[idx-1], messages[idx], sizeof(messages[idx]));
  }

  memcpy(messages[3], text, 20);
}
