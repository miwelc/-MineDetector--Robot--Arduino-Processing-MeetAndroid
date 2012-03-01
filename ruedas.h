#ifndef RUEDAS_H_
#define RUEDAS_H_

#include <inttypes.h>

enum TipoMov {
  IZQUIERDA,
  DERECHA,
  ADELANTE,
  ATRAS,
  PARAR
};

class Ruedas {
  private:
    enum PINES_MOTOR {
      EA = 0, I2, I1,
      EB, I4, I3
    };
    unsigned int pines[6]; //EA, I2, I1, EB, I4, I3
    uint8_t velocidad;
  public:
    Ruedas() { velocidad = 128; }
    Ruedas(unsigned int ea, unsigned int i2, unsigned int i1,
                    unsigned int eB, unsigned int i4, unsigned int i3);
    void asociarPines(unsigned int ea, unsigned int i2, unsigned int i1,
                    unsigned int eB, unsigned int i4, unsigned int i3);
    void setVelocidad(uint8_t vel);
    void mover(int tipo);
    void girar(int sentido);
    void manejar(char orden);
};

#endif
