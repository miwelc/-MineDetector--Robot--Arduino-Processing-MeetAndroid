#ifndef BARRA_H_
#define BARRA_H_

#include <inttypes.h>

enum {
  NADA,
  MINA,
  CONTROL
};

class barraSensora {
  private:
    unsigned int pines[6]; //5 sens. + LEDON
    unsigned long valores[5];
    unsigned int umbral;
    unsigned int blanco[5];
    unsigned int negro;
  public:
    barraSensora(unsigned int s1, unsigned int s2, unsigned int s3,
                    unsigned int s4, unsigned int s5, unsigned int ledon);
    void asociarPines(unsigned int s1, unsigned int s2, unsigned int s3,
                    unsigned int s4, unsigned int s5, unsigned int ledon);
    void calibrarBlanco();
    void read();
    int detectado();
    void print();
};

#endif
