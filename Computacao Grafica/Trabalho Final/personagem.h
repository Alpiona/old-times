#ifndef Personagem_H
#define Personagem_H
#include <GL/gl.h>
#include <GL/glu.h>

class Personagem {
  private:
    GLfloat cX;
    GLfloat cY;
    GLfloat cZ;
    GLfloat gThetaBraco;
    GLfloat gThetaPersonagem;
    GLfloat disparoCx;
    GLfloat disparoCy;
    GLfloat disparoTheta;
    GLfloat movPernas;
    GLfloat sentPernasFlag;
    GLfloat raio, raioInicial;
    bool subindo, descendo;
    GLfloat vel, velTiro;
    GLfloat id;
    GLfloat altura;
    bool podePular;

  public:
    Personagem(GLfloat cX, GLfloat cY, GLfloat raio, GLfloat id, GLfloat vel, GLfloat velTiro);
    void estaSubindo();
    void estaDescendo();
    bool isSubindo();
    bool isDescendo();
    void setSubindo(bool valor);
    void setDescendo(bool valor);
    bool estaPulando();
    GLfloat getMovPernas();
    GLfloat getCx();
    GLfloat getCy();
    GLfloat getCz();
    GLfloat getThetaBraco();
    GLfloat getThetaPersonagem();
    void setThetaPersonagem(GLfloat valor);
    GLfloat getRaio();
    void setRaio(GLfloat valor);
    GLfloat getRaioInicial();
    GLfloat getId();
    GLfloat getVel();
    GLfloat getVelTiro();
    GLfloat getDisparoCx();
    GLfloat getDisparoCy();
    GLfloat getDisparoTheta();
    GLfloat getAltura();
    void desceu();
    void movimentar(GLfloat valor);
    void calcularDisparoPos();
    void rotacionar (GLfloat direcao);
    void rotacionaBraco (GLfloat valor);
    void desenharCirculo(GLint vertices, GLfloat raio);
    void desenharRetangulo(GLfloat altura, GLfloat largura);
    void desenharPersonagem(GLint vertices, GLfloat R, GLfloat G, GLfloat B);

};

#endif
