#include <MeetAndroid.h>
#include "ruedas.h"
#include "barraSensora.h"
#include "recorrido.h"

#define FILASTOTALES 4
byte velocidad = 130;
byte velocidadGiro = 120;

barraSensora barra(2, 9, 10, 11, 12, 13); //7 6 5 3 2 LEDON
Recorrido recorrido;
Ruedas ruedas(3,4,5, 6,7,8);
MeetAndroid meetAndroid(error);

void error(uint8_t flag, uint8_t values){
  Serial.print("ERROR: ");
  Serial.print(flag);
}

boolean inicio = true;
int objeto;
int filas = 0;
float valoresOrientacion[3];

void orientacion(byte flag, byte numOfValues) {
  meetAndroid.getFloatValues(valoresOrientacion);
}

void giroManual() {
  while(!meetAndroid.receive())
    ;
  while(valoresOrientacion[1] < -30)
    meetAndroid.receive();
  
  ruedas.setVelocidad(velocidadGiro);
  while(valoresOrientacion[1] > -30) {
    if(valoresOrientacion[2] > 30)
      ruedas.mover(IZQUIERDA);
    else if(valoresOrientacion[2] < -30)
      ruedas.mover(DERECHA);
    else {
      ruedas.mover(PARAR);
      delay(20);
    }
    while(!meetAndroid.receive())
      ;
  }
  ruedas.setVelocidad(velocidad);
  
  ruedas.mover(PARAR);
  delay(200);
  
}

void setup() {
  Serial.begin(9600);
  barra.calibrarBlanco();
  ruedas.setVelocidad(velocidad);
  meetAndroid.registerFunction(orientacion, 'A');
}

void loop() {
  //int inByte;
  //inByte = Serial.read();
  //ruedas.manejar(inByte);
  while(!meetAndroid.receive())
            ;
  
  if(inicio) {
    giroManual();
    ruedas.mover(ADELANTE);
    recorrido.guardarEvento(CONTROL, millis());
    inicio = false;
  }
  
  if(filas < FILASTOTALES) { //Durante el recorrido
      objeto = barra.detectado();
      if(objeto == MINA) {
        Serial.println("MINA");
        recorrido.guardarEvento(MINA, millis());
      }
      else if(objeto == CONTROL) {
        Serial.println("CONTROL");
        recorrido.guardarEvento(CONTROL, millis());
        filas++;
        if(filas < FILASTOTALES) {
          ruedas.mover(ATRAS);
          delay(260);
          ruedas.mover(PARAR);
          while(!meetAndroid.receive())
            ;
          delay(100);
          giroManual();
          ruedas.mover(ADELANTE);
          
          do {
            objeto = barra.detectado();
          } while(objeto != CONTROL);
          ruedas.mover(ATRAS);
          delay(100);
          ruedas.mover(PARAR);
          while(!meetAndroid.receive())
            ;
          delay(100);
          giroManual();
          
          recorrido.guardarEvento(CONTROL, millis());
          ruedas.mover(ADELANTE);          
        }
      }
  }
  
  if(filas == FILASTOTALES) { //Fin recorrido
    ruedas.mover(PARAR);
    Serial.end();
    delay(10000);
    Serial.begin(9600);
    while(Serial.available() == 0)
      ;
    recorrido.enviarEventos();
  }
  
  delay(50);
  //barra.print();
 
}



