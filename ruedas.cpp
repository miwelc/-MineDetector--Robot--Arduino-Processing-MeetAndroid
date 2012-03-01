//#include "WProgram.h"
#include "Arduino.h"
#include "ruedas.h"

Ruedas::Ruedas(unsigned int ea, unsigned int i2, unsigned int i1,
                    unsigned int eB, unsigned int i4, unsigned int i3) {
  velocidad = 128;
  asociarPines(ea, i2, i1, eB, i4, i3);
}

void Ruedas::asociarPines(unsigned int ea, unsigned int i2, unsigned int i1,
                    unsigned int eb, unsigned int i4, unsigned int i3) {
  pines[EA] = ea; pines[I2] = i2; pines[I1] = i1;
  pines[EB] = eb; pines[I4] = i4; pines[I3] = i3;
  
  //Velocidad
  analogWrite(pines[EA], velocidad);
  analogWrite(pines[EB], velocidad);
  
  //Izq
  pinMode(pines[EA], OUTPUT);
  pinMode(pines[I2], OUTPUT);
  pinMode(pines[I1], OUTPUT);
  
  //Dech
  pinMode(pines[EB], OUTPUT);
  pinMode(pines[I4], OUTPUT);
  pinMode(pines[I3], OUTPUT);
}

void Ruedas::setVelocidad(uint8_t vel) {
  velocidad = vel;
  analogWrite(pines[EA], vel*0.9);
  analogWrite(pines[EB], vel+vel*0.1);
}

void Ruedas::mover(int tipo) {
  switch(tipo) {
    case ATRAS:
      digitalWrite(pines[I2], HIGH);
      digitalWrite(pines[I1], LOW); 
      digitalWrite(pines[I4], HIGH);
      digitalWrite(pines[I3], LOW); 
      break;
    case ADELANTE:
      digitalWrite(pines[I2], LOW);
      digitalWrite(pines[I1], HIGH); 
      digitalWrite(pines[I4], LOW);
      digitalWrite(pines[I3], HIGH); 
      break;
      
    case IZQUIERDA:
      digitalWrite(pines[I2], HIGH);
      digitalWrite(pines[I1], LOW); 
      digitalWrite(pines[I4], LOW);
      digitalWrite(pines[I3], HIGH); 
      break;
    case DERECHA:
      digitalWrite(pines[I2], LOW);
      digitalWrite(pines[I1], HIGH); 
      digitalWrite(pines[I4], HIGH);
      digitalWrite(pines[I3], LOW); 
      break;
    case PARAR:
      digitalWrite(pines[I2], LOW);
      digitalWrite(pines[I1], LOW); 
      digitalWrite(pines[I4], LOW);
      digitalWrite(pines[I3], LOW); 
      break;
  }
}

void Ruedas::girar(int sentido) {
  unsigned long time;
  uint8_t velTmp = velocidad;
  
  setVelocidad(140);
  
  time = millis();
  switch(sentido) {
    case IZQUIERDA:
      digitalWrite(pines[I2], HIGH);
      digitalWrite(pines[I1], LOW); 
      digitalWrite(pines[I4], LOW);
      digitalWrite(pines[I3], HIGH); 
      break;
    case DERECHA:
      digitalWrite(pines[I2], LOW);
      digitalWrite(pines[I1], HIGH); 
      digitalWrite(pines[I4], HIGH);
      digitalWrite(pines[I3], LOW); 
      break;
  }
  while(millis() - time < 1322)
    ;
  
  setVelocidad(velTmp);
  mover(PARAR);
}

void Ruedas::manejar(char orden) {
  switch(orden) {
    case 'a':
      mover(IZQUIERDA);
    break;
    case 'd':
      mover(DERECHA);
    break;
    case 'w':
      mover(ADELANTE);
    break;
    case 's':
      mover(ATRAS);
    break;
    case ' ':
      mover(PARAR);
    break;
    case 'j':
      girar(IZQUIERDA);
    break;
    case 'k':
      girar(DERECHA);
    break;
  }
}
