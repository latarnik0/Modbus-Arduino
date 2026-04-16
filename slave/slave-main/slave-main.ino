#include <ModbusRTU.h>

//KONFIGURACJA MODBUS
#define SLAVE_ID 1        
#define TXEN_PIN 2        // pin sterujący nadawaniem/odbiorem

ModbusRTU mb;

//PINY SPRZĘTOWE
#define LED_PIN 13        // Pin diody LED do sterowania przez Mastera
#define SENSOR_PIN A0     // Analogowy pin dla przykładowego czujnika

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);

  mb.begin(&Serial, TXEN_PIN);  
  mb.slave(SLAVE_ID);          

  // REJESTRACJA REJESTRÓW
  mb.addHreg(0, 0); // Rejestr 0: Czujnik analogowy 
  mb.addHreg(1, 0); // Rejestr 1: Uptime 
  mb.addHreg(2, 0); // Rejestr 2: Sterowanie LED 
}

void loop() {
  //OBSŁUGA KOMUNIKACJI
  mb.task();

  // zapis wartości do wewnętrznych rejestrów Modbus
  mb.Hreg(0, analogRead(SENSOR_PIN));
  mb.Hreg(1, millis() / 1000);

  // REAKCJA NA KOMENDY
  if (mb.Hreg(2) > 0) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
