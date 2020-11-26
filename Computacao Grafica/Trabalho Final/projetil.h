#ifndef Projetil_H
#define Projetil_H
#include <GL/gl.h>
#include <GL/glu.h>

class Projetil{
private:
  float cX, cY, direcaoTheta, raio, velTiro;
  bool inimigo;
public:
  Projetil(float cXp, float cYp, float direcao, float r, float velTiro){
    this->cX = cXp;
    this->cY = cYp;
    this->direcaoTheta = direcao;
    this->raio = r;
    this->velTiro = velTiro;
  }
  float getCx(){
    return cX;
  }
  float getCy(){
    return cY;
  }
  float getRaio(){
    return raio;
  }
  float getVelTiro(){
    return velTiro;
  }
  float getDirecaoTheta(){
    return direcaoTheta;
  }
  void setCx(float novoCx){
    this->cX = novoCx;
  }
  void setCy(float novoCy){
    cY = novoCy;
  }
};


#endif
