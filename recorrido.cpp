#include "recorrido.h"
#include "Arduino.h"

Recorrido::Recorrido() {
  nEventos = 0;
}

void Recorrido::guardarEvento(int obj, unsigned long t) {
  if(nEventos == MAXEVNT)
    return;
  
  eventos[nEventos].objeto = obj;
  eventos[nEventos].tiempo = t;
  
  nEventos++;
}

void Recorrido::enviarEventos() {
  Serial.println(nEventos);
  for(int i = 0; i < nEventos; i++) {
    Serial.println(eventos[i].objeto);
    Serial.println(eventos[i].tiempo);
  }
}
