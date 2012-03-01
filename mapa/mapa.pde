import processing.serial.*;

int TAMX;
int TAMY;

Serial puerto;

PImage fondo;
PImage minaIMG;
PImage recorridoImg;

Recorrido recorrido;
int iniciado = 0;

void setup() {
  fondo = loadImage("desierto.jpg");
  TAMX = fondo.width;
  TAMY = fondo.height;
  size(TAMX, TAMY);
  minaIMG = loadImage("mina.png");
  recorridoImg = createImage(TAMX, TAMY, ARGB);
  
  //println(Serial.list());
  puerto = new Serial(this, "COM5", 9600);
  recorrido = new Recorrido();
  //noLoop();
}

void draw() {
  background(fondo);
  dibujarLineaRecorrido();
  dibujarMinas();
  if(iniciado == 1) {
    recorrido.recibirEventos(puerto);
    puerto.stop();
    recorrido.imprimir();
  }
  if(iniciado == 0 || iniciado == 1) iniciado++;
  
  delay(200);
}

void dibujarLineaRecorrido() {
  noFill();
  smooth();
  strokeWeight(6.0);
  strokeJoin(ROUND);
  beginShape();
    for(int i = 0; i < recorrido.filas*2; i += 2) {
      if((i/2)%2 == 0) {
        vertex((i+1)*TAMX/(recorrido.filas*2), TAMY-TAMY*0.10);
        vertex((i+1)*TAMX/(recorrido.filas*2), TAMY*0.10);
      }
      else {
        vertex((i+1)*TAMX/(recorrido.filas*2), TAMY*0.10);
        vertex((i+1)*TAMX/(recorrido.filas*2), TAMY-TAMY*0.10);
      }
    }
  endShape();
}

void dibujarMinas() {
  Mina mina;
  float longYLinea = TAMY-2*TAMY*0.10;
  int nMinas = recorrido.getNumMinas();
  imageMode(CENTER);
  for(int i = 0; i < nMinas; i++) {
    mina = recorrido.getMina(i);
    if(mina.fila%2 == 0)
      image(minaIMG, (mina.fila*2+1)*TAMX/(recorrido.filas*2), ((1-mina.pos)*longYLinea) +TAMY*0.10);
    else
      image(minaIMG, (mina.fila*2+1)*TAMX/(recorrido.filas*2), ((mina.pos)*longYLinea) +TAMY*0.10);
  }
}
