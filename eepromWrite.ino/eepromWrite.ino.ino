#include <EEPROM.h>

int eepromReadInt(int address) {
  int ten = EEPROM.read(address + 1);
  int one = EEPROM.read(address);
  return (one & 0xFF) + ((ten & 0xFF) << 8);
}

void eepromWriteInt(int address, int value) {
  byte one = (value & 0xFF);
  byte ten = ((value >> 8) & 0xFF);
  EEPROM.write(address + 1, ten);
  EEPROM.write(address, one);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Writing the Values");
  for (int i = 0; i < 4; ++i) {
    EEPROM.write(i, i+1);
  }
  eepromWriteInt(4, 1); // numCycles
  eepromWriteInt(6, 1); // dipTime
  eepromWriteInt(8, 1); // dipLength
  EEPROM.write(10, 0);
  EEPROM.write(11, 1);
  eepromWriteInt(12, 200); // travelSpeed
  
  Serial.println("\nReading the values");
  for (int i = 0; i < 4; ++i) {
    Serial.print(EEPROM.read(i));
    Serial.print("  ");
  }
  Serial.println();
  Serial.println(eepromReadInt(4));
  Serial.println(eepromReadInt(6));
  Serial.println(eepromReadInt(8));
  Serial.println(EEPROM.read(10));
  Serial.println(EEPROM.read(11));
  Serial.println(eepromReadInt(12));
}

void loop() {
  // put your main code here, to run repeatedly:
}
