#ifndef Objeto_H
#define Objeto_H
#include <GL/gl.h>
#include <GL/glu.h>

class Objeto {
private:
  float cx, cy, raio;
  int id, tipo;
public:
  Objeto(float cx, float cy, float raio, int id, int tipo){
    this->cx = cx;
    this->cy = cy;
    this->raio = raio;
    this->id = id;
    this->tipo = tipo;
  }
  float getCx(){
    return cx;
  }
  float getCy(){
    return cy;
  }
  float getRaio(){
    return raio;
  }
  int getId(){
    return id;
  }
  int getTipo(){
    return tipo;
  }
};

#endif
