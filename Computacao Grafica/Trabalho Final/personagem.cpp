#include "personagem.h"
#include <math.h>
#include <string>
#include <iostream>

Personagem::Personagem(GLfloat X, GLfloat Y, GLfloat r, GLfloat id, GLfloat vel, GLfloat velTiro){
  cX = X;
  cY = Y;
  cZ = 0;
  raio = r;
  raioInicial = r;
  subindo = false;
  descendo = false;
  this->id = id;
  this->vel = vel;
  this->velTiro = velTiro;
  altura = 0;
  podePular = true;
  movPernas = 0;
  sentPernasFlag = 1;
  gThetaBraco = 0;
  gThetaPersonagem = 0;
}

void Personagem::estaSubindo(){
  this->cZ+= 5;
  altura+= 5;
}

void Personagem::estaDescendo(){
  this->cZ-= 5;
  altura-= 5;
}

bool Personagem::isSubindo (){
  return subindo;
}

bool Personagem::isDescendo (){
  return descendo;
}

void Personagem::setSubindo(bool valor){
  subindo = valor;
}

void Personagem::setDescendo(bool valor){
  descendo = valor;
}

bool Personagem::estaPulando(){
  return podePular;
}

GLfloat Personagem::getMovPernas(){
  return movPernas/4;
}

GLfloat Personagem::getCx(){
  return cX;
}

GLfloat Personagem::getCy(){
  return cY;
}

GLfloat Personagem::getCz(){
  return cZ;
}

GLfloat Personagem::getThetaBraco(){
  return gThetaBraco;
}

GLfloat Personagem::getThetaPersonagem(){
  return gThetaPersonagem;
}

void Personagem::setThetaPersonagem(GLfloat valor){
  gThetaPersonagem = (valor*57.2958)-90;
}

GLfloat Personagem::getRaio(){
  return raio;
}

void Personagem::setRaio(GLfloat valor){
  raio = valor;
}

GLfloat Personagem::getRaioInicial(){
  return raioInicial;
}

GLfloat Personagem::getId(){
  return id;
}

GLfloat Personagem::getVel(){
  return vel;
}

GLfloat Personagem::getVelTiro(){
  return velTiro;
}

GLfloat Personagem::getDisparoCy(){
  return disparoCy;
}

GLfloat Personagem::getDisparoCx(){
  return disparoCx;
}

GLfloat Personagem::getDisparoTheta(){
  return disparoTheta;
}

GLfloat Personagem::getAltura(){
  return altura;
}

void Personagem::movimentar(GLfloat valor){
  cX+= valor * cos ((gThetaPersonagem+90)*0.0174533);
  cY+= valor * sin ((gThetaPersonagem+90)*0.0174533);
      if (movPernas+(valor*sentPernasFlag) > 16){
        sentPernasFlag = -sentPernasFlag;
        movPernas = 15;
      } else if (movPernas+(valor*sentPernasFlag) < 0){
        sentPernasFlag = -sentPernasFlag;
        movPernas = 0;
      } else {
        movPernas = movPernas + (valor*sentPernasFlag);
      }

}

void Personagem::calcularDisparoPos(){
  disparoCx = cX+(raio/2)*cos(gThetaPersonagem*0.0174533)-(raio*2/3)*sin((gThetaBraco+gThetaPersonagem)*0.0174533);
  disparoCy = cY+(raio/2)*sin(gThetaPersonagem*0.0174533)+(raio*2/3)*cos((gThetaBraco+gThetaPersonagem)*0.0174533);
  disparoTheta = gThetaPersonagem+gThetaBraco;
}

void Personagem::rotacionar(GLfloat sentido){
  gThetaPersonagem += sentido;
}

void Personagem::rotacionaBraco(GLfloat valor){
  if (gThetaBraco-valor <= -45){
    gThetaBraco = -45;
  } else if (gThetaBraco-valor >= 45){
    gThetaBraco = 45;
  } else {
    gThetaBraco-=valor;
  }
}

void Personagem::desenharCirculo(GLint vertices, GLfloat raio){

  //PINTAR CENTRO DO CIRUCLO
  glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i <= vertices;i++) {
      glVertex2f(
         raio * cos(i * 2*3.14159 / vertices),
         raio * sin(i * 2*3.14159 / vertices)
      );
    }
  glEnd();

  //FAZER A BORDA DO CÍRCULO
  glColor3f(0,0,0);
  glBegin(GL_LINES);
    for(int i = 0; i <= vertices;i++) {
      glVertex2f(
         raio * cos(i * 2*3.14159 / vertices),
         raio * sin(i * 2*3.14159 / vertices)
      );
    }
  glEnd();
}

void Personagem::desenharRetangulo(GLfloat altura, GLfloat largura){
  glBegin(GL_QUADS);
    glVertex2f(-largura/2.0, 0.0);
    glVertex2f(+largura/2.0, 0.0);
    glVertex2f(+largura/2.0, altura);
    glVertex2f(-largura/2.0, altura);
  glEnd();
  glColor3f(0,0,0);
  glBegin(GL_LINES);
    glVertex2f(-largura/2.0, 0.0);
    glVertex2f(+largura/2.0, 0.0);
    glVertex2f(+largura/2.0, altura);
    glVertex2f(-largura/2.0, altura);
  glEnd();
}

void Personagem::desenharPersonagem(GLint vertices, GLfloat R, GLfloat G, GLfloat B){
  glPushMatrix();
    glTranslatef(cX, cY, 0);
    glRotatef(gThetaPersonagem, 0.0, 0.0, 1.0);

    //PERNAS
    glPushMatrix();
      glTranslatef(raio * 1/6, movPernas, 0);
      glColor3f(0,0,0);
      desenharRetangulo((raio * 2/3), (raio * 1/6));
    glPopMatrix();
    glPushMatrix();
      glTranslatef((-raio) * 1/6, -(raio * 2/3) - movPernas, 0);
      glColor3f(0,0,0);
      desenharRetangulo((raio * 2/3), (raio * 1/6));
    glPopMatrix();

    //TODO:BRAÇO
    glPushMatrix();
      glTranslatef(raio/2, 0, 0);
      glRotatef(gThetaBraco, 0.0, 0.0, 1.0);
      glColor3f(R,G,B);
      desenharRetangulo((raio * 2/3), (raio * 1/6));
    glPopMatrix();

    //PINTAR O CORPO
    glColor3f(R,G,B);
    glBegin(GL_TRIANGLE_FAN);
      for(int i = 0; i <= vertices;i++) {
        glVertex2f(
           raio * 2/3 * cos(i * 2*3.14159 / vertices),
           raio * 1/6 * sin(i * 2*3.14159 / vertices)
        );
      }
    glEnd();

    //FAZER BORDA DO CORPO
    glColor3f(0,0,0);
    glBegin(GL_LINES);
      for(int i = 0; i <= vertices;i++) {
        glVertex2f(
           raio * 2/3 * cos(i * 2*3.14159 / vertices),
           raio * 1/6 * sin(i * 2*3.14159 / vertices)
        );
      }
    glEnd();

    //FAZER A CABEÇA
    glColor3f(R,G,B);
    desenharCirculo(vertices, raio*1/3);

    //LIMITE DO PERSONAGEM (RAIO DO SVG)
    glColor3f(R,G,B);
    glBegin(GL_LINES);
      for(int i = 0; i <= vertices;i++) {
        glVertex2f(
           raio * cos(i * 2*3.14159 / vertices),
           raio * sin(i * 2*3.14159 / vertices)
        );
      }
    glEnd();
  glPopMatrix();

}
