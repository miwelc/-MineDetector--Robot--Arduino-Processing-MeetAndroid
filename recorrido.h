#ifndef __RECORRIDO_H__
#define __RECORRIDO_H__

#define MAXEVNT 50

class Recorrido {
  private:
  public:
    struct Evento {
      int objeto;
      unsigned long tiempo;
    } eventos[MAXEVNT];
    int nEventos;
    Recorrido();
    void guardarEvento(int obj, unsigned long t);
    void enviarEventos();
};

#endif
