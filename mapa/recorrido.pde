class Mina {
  float pos;
  int fila;
}

class Recorrido {
    class Evento {
      int objeto;
      long tiempo;
      Evento() {
        objeto = 0;
        tiempo = 0;
      }
    }
    int nEventos;
    Evento [] eventos;
    int filas;
    
    Recorrido() {
      nEventos = 0;
      filas = 0;
    }
    
    void recibirEventos(Serial puerto) {
      String inBuffer = null;
      //Indicamos que ya podemos recibir
      puerto.write('a');
      while(puerto.available() <= 0)
        ;
      delay(2000);
      
      inBuffer = puerto.readStringUntil('\n');
      nEventos = Integer.parseInt(inBuffer.substring(0, inBuffer.length()-2));
      eventos = new Evento[nEventos];
    
      for(int i = 0; i < nEventos; i++) {
        eventos[i] = new Evento();
        //Tipo
        inBuffer = puerto.readStringUntil('\n');
        eventos[i].objeto = Integer.parseInt(inBuffer.substring(0, inBuffer.length()-2));
        //Tiempo
        inBuffer = puerto.readStringUntil('\n');
        eventos[i].tiempo = Long.parseLong(inBuffer.substring(0, inBuffer.length()-2));
      }
      
      filas = getNumFilas();
    }
    
    int getNumMinas() {
      int cont = 0;
      for(int i = 0; i < nEventos; i++) {
        if(eventos[i].objeto == 1) //Si es mina
          cont++;
      }
      return cont;
    }
    
    int getNumFilas() {
      int cont = 0;
      for(int i = 0; i < nEventos; i++) {
        if(eventos[i].objeto == 2) //Si es control
          cont++;
      }
      return cont/2;
    }
    
    Mina getMina(int m) {
      Mina mina = new Mina();
      int minasEncontradas = 0;
      long controlInicio = 0, controlFin = 0, tiempoFila, tiempoMina = 0;
      int nControles = 0;
      int i;
      //Encontramos la mina y el control de su fila
      for(i = 0; i < nEventos && minasEncontradas <= m; i++) {
        if(eventos[i].objeto == 1) {
          minasEncontradas++;
          tiempoMina = eventos[i].tiempo;
        } else if(eventos[i].objeto == 2) {
          controlInicio = eventos[i].tiempo;
          nControles++;
        }
      }
      tiempoMina -= controlInicio; //Tiempo relativo en la fila
      
      //Buscamos siguiente control
      for(; i < nEventos; i++) {
        if(eventos[i].objeto == 2) {
          controlFin = eventos[i].tiempo;
          break;
        }
      }
      tiempoFila = controlFin - controlInicio;
      
      mina.pos = 1.0*((float)tiempoMina/(float)tiempoFila);
      mina.fila = nControles/2;
      
      return mina;
    }
    
    void imprimir() {
      String cadena = null;
      cadena = "Número de eventos: " + nEventos + "\n";
      for(int i = 0; i < nEventos; i++)
        cadena += "Evento: " + i + " Objeto: " + eventos[i].objeto + "  Tiempo: " + eventos[i].tiempo + "\n";
      print(cadena);
    }
}
