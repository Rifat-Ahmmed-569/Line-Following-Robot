void recording() {
  for (byte i = 0;; i++) {
    EEPROM.write(i + 30, path[i]); delay(10);
    if (path[i] == 5) return;
  }
}