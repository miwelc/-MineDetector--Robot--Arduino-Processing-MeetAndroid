#include "Arduino.h"
#include "barraSensora.h"

barraSensora::barraSensora(unsigned int s1, unsigned int s2, unsigned int s3,
                    unsigned int s4, unsigned int s5, unsigned int ledon) {
  asociarPines(s1, s2, s3, s4, s5, ledon);
  umbral = 800;
  for(int i = 0; i < 5; i++)
    blanco[i] = 9999; //INICIAL
  negro = 4000;
}

void barraSensora::asociarPines(unsigned int s1, unsigned int s2, unsigned int s3,
                    unsigned int s4, unsigned int s5, unsigned int ledon) {
  pines[0] = s1; pines[1] = s2; pines[2] = s3;
  pines[3] = s4; pines[4] = s5; pines[5] = ledon;
  
  //LedOn siempre salida
  pinMode(pines[5], OUTPUT);
}

void barraSensora::calibrarBlanco() {
  read();
  for(int i = 0; i < 5; i++)
    blanco[i] = valores[i];
}

void barraSensora::read() {
  unsigned long time;
  boolean leidos[5];
  short nLeidos = 0;
  
  //Turn on IR LEDs
  digitalWrite(pines[5], HIGH);
  
  //Set the I/O line to an output and drive it high
  for(int i = 0; i < 5; i++) {
    pinMode(pines[i], OUTPUT);
    digitalWrite(pines[i], HIGH);
  }
  
  //Allow at least 10 us for the 10 nF capacitor to charge
  delayMicroseconds(10);
  
  //Make the I/O line an input (high impedance)
  for(int i = 0; i < 5; i++)
    pinMode(pines[i], INPUT);
  
  //Measure the time for the capacitor to discharge by waiting for the I/O line to go low
  time = micros();
  for(int i = 0; i < 5; i++)
    leidos[i] = false;
  while(nLeidos < 5) {
    for(int i = 0; i < 5; i++) {
      if(!leidos[i]) {
        valores[i] = micros() - time;
        if(digitalRead(pines[i]) == LOW || valores[i] > blanco[i] + umbral) {
          leidos[i] = true;
          nLeidos++;
        }
      }
    }
  }
  
  //Turn off IR LEDs
  digitalWrite(pines[5], LOW);
}

int barraSensora::detectado() {
  int count = 0;
  
  read();
  
  for(int i = 0; i < 5; i++) {
    if(valores[i] >= blanco[i] + umbral)
      count++;
  }
  
  if(count >= 2) {
    if(count == 5)
      return CONTROL;
    else
      return MINA;
  }
  else
    return NADA;
}

void barraSensora::print() {
  for(int i = 0; i < 5; i++) {
    Serial.print(" Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(valores[i]);
    Serial.print("   ");
  }
  Serial.println("");
}
