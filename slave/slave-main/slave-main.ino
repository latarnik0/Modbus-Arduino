#include <ModbusRTU.h>

#define TX_DIR_PIN 2 // pin sterujący kierunkiem transmisji
#define SLAVE_ID 1


ModbusRTU m;

void setup() {
  Serial.begin(9600);

  // przypisanie portu szeregowego i pinu sterującego
  m.begin(&Serial, TX_DIR_PIN);

  // Ustawienie id na 1
  m.slave(SLAVE_ID);

  // adres i wartość rejestru. Początkowa wartość na 0
  m.addHreg(0, 0);
}

void loop() {
  // funkcja nasłuchująca zapytań od mastera 
  mb.task();
}
