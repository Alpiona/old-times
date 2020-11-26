#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <math.h>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include "tinyxml2.h"

#define VELOCIDADE 0.5
#define QNT_VERTICES_CIRCULOS 100

#define PLAYER 1
#define OBSTACULO_PULAVEL 2
#define OBSTACULO_NAO_PULAVEL 3
#define LIMITE_INTERNO_ARENA 4
#define LIMITE_EXTERNO_ARENA 5

const float azul[] = {0,0,255};
const float verde[] = {0,255,0};
const float vermelho[] = {255,0,0};
const float preto[] = {0,0,0};
const float branco[] = {255,255,255};

using namespace tinyxml2;
using namespace std;

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

int keyFlags[256], moveFlag[4], idPlayer, playerNoAlto, subiu;
float tamanhoTela[4], centroXPlayer, centroYPlayer, raioPlayer, raioExtraPlayer;
string nome, tipo, caminho, caminhoInteiro;
vector<Objeto*> objetos;

void novoObjeto( XMLElement* child){
  float cx, cy, r;
  int id;
  child->QueryFloatAttribute("cx", &cx);
  child->QueryFloatAttribute("cy", &cy);
  child->QueryFloatAttribute("r", &r);
  child->QueryIntAttribute("id", &id);
  string cor = child->Attribute("fill");

  if (cor.compare("green") == 0){
    centroXPlayer=cx;
    centroYPlayer=cy;
    raioPlayer = r;
    idPlayer = id;
  }
  else if (cor.compare("black") == 0){
    Objeto* novoObjeto = new Objeto(cx, cy, r, id, OBSTACULO_PULAVEL);
    objetos.push_back(novoObjeto);
  }
  else if (cor.compare("red") == 0){
    Objeto* novoObjeto = new Objeto(cx, cy, r, id, OBSTACULO_NAO_PULAVEL);
    objetos.push_back(novoObjeto);
  }
  else if (cor.compare("white") == 0){
    Objeto* novoObjeto = new Objeto(cx, cy, r, id, LIMITE_INTERNO_ARENA);
    objetos.push_back(novoObjeto);
  }

  //Caso seja o limite exterior, é feito os calculos para Ortho e tamanho de janela
  else if (cor.compare("blue") == 0){
    Objeto* novoObjeto = new Objeto(cx, cy, r, id, LIMITE_EXTERNO_ARENA);
    tamanhoTela[0] = cx-r;
    tamanhoTela[1] = cx+r;
    tamanhoTela[2] = cy-r;
    tamanhoTela[3] = cy+r;
    objetos.push_back(novoObjeto);
  }
}

void lerConfig(char* argv){
  XMLDocument config;
  XMLElement* leitor;
  string arqEntrada = argv;
  if (arqEntrada == "\n"){
    arqEntrada = "config.xml";
  } else {
    arqEntrada = arqEntrada+"config.xml";
  }
  config.LoadFile(arqEntrada.c_str());

  leitor = config.FirstChildElement()->FirstChildElement("arquivoDaArena");
  nome = leitor->Attribute("nome");
  tipo = leitor->Attribute("tipo");
  caminho = leitor->Attribute("caminho");
}

void lerSvg(){
  XMLDocument svg;
  XMLElement* leitor;
  string arqEntrada = caminho+nome+"."+tipo;

  svg.LoadFile(arqEntrada.c_str());

  leitor = svg.FirstChildElement("svg");
  string cor;
  for (XMLElement* child = leitor->FirstChildElement("circle"); child != NULL; child = child->NextSiblingElement()){
    novoObjeto(child);
  }
}

void init (void){
  glClearColor (1.0, 1.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(tamanhoTela[0], tamanhoTela[1], tamanhoTela[2], tamanhoTela[3], -5.0, 5.0);
  glFlush();
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT);

  for (Objeto* obj : objetos){

      if (obj->getTipo() == LIMITE_EXTERNO_ARENA){
        glColor3fv(azul);
        glBegin(GL_TRIANGLE_FAN);
          glVertex2f(obj->getCx(), obj->getCy());
          for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
            glVertex2f(
               obj->getCx()+ (obj->getRaio() * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
               obj->getCy()+ (obj->getRaio() * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS))
            );
          }
        glEnd();
      }

      else {
        if (obj->getTipo() == OBSTACULO_PULAVEL){
          glColor3fv(preto);
        }
        else if (obj->getTipo() == OBSTACULO_NAO_PULAVEL){
          glColor3fv(vermelho);
        }
        else if (obj->getTipo() == LIMITE_INTERNO_ARENA){
          glColor3fv(branco);
        }
        glBegin(GL_TRIANGLE_FAN);
          glVertex2f(obj->getCx(), obj->getCy());
          for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
            glVertex2f(
               obj->getCx()+ (obj->getRaio() * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
               obj->getCy()+ (obj->getRaio() * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS))
            );
          }

        glEnd();
      }

  }

  glColor3fv(verde);
  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centroXPlayer, centroYPlayer);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glVertex2f(
         centroXPlayer+ ((raioPlayer+raioExtraPlayer) * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         centroYPlayer+ ((raioPlayer+raioExtraPlayer) * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS))
      );
    }
  glEnd();

  glFlush ();
}

void timer (int value){
  if (value <=10){
    raioExtraPlayer += raioPlayer*0.075;
    glutTimerFunc(100, timer, value+1);
  } else if (value == 20){
    subiu = 0;
    for (Objeto* obj : objetos){
      if (obj->getTipo() == OBSTACULO_PULAVEL &&
      raioPlayer+obj->getRaio() >= sqrt(pow(obj->getCx()-centroXPlayer,2)+pow(obj->getCy()-centroYPlayer,2))){
        subiu =1;
      }
    }
    if (subiu == 0){
      playerNoAlto = 0;
    }
    raioExtraPlayer = 0;
  } else if (value < 20){
    raioExtraPlayer -= raioPlayer*0.075;
    glutTimerFunc(100, timer, value+1);
  }
}

void idle(){
  if (keyFlags[' '] == 1){
    if (playerNoAlto==0){
      playerNoAlto = 1;
      glutTimerFunc(100, timer, 1);
    }
  }
  if (subiu == 1){
    subiu = 0;
    for (Objeto* obj : objetos){
      if (obj->getTipo() == OBSTACULO_PULAVEL &&
      raioPlayer+obj->getRaio() >= sqrt(pow(obj->getCx()-centroXPlayer,2)+pow(obj->getCy()-centroYPlayer,2))){
        subiu = 1;
      }
    }
    if (subiu == 0 ){
      playerNoAlto = 0;
    }
  }

  if (keyFlags['w'] == 1){
    moveFlag[0] = 1;
    for (Objeto* obj : objetos){

      if (obj->getTipo() == LIMITE_EXTERNO_ARENA &&
      obj->getRaio() - raioPlayer < sqrt(pow(obj->getCx()-centroXPlayer,2)+pow(obj->getCy()-centroYPlayer-VELOCIDADE,2))){
        moveFlag[0] = 0;
      }

      else if (obj->getTipo() != LIMITE_EXTERNO_ARENA && obj->getTipo() != OBSTACULO_PULAVEL &&
      raioPlayer+obj->getRaio() > sqrt(pow(obj->getCx()-centroXPlayer,2)+pow(obj->getCy()-centroYPlayer-VELOCIDADE,2))){
        moveFlag[0] = 0;
      }

      else if (obj->getTipo() == OBSTACULO_PULAVEL && playerNoAlto == 0 &&
      raioPlayer+obj->getRaio() > sqrt(pow(obj->getCx()-centroXPlayer,2)+pow(obj->getCy()-centroYPlayer-VELOCIDADE,2))){
        moveFlag[0] = 0;
      }

    }
    if (moveFlag[0] == 1){
      centroYPlayer += VELOCIDADE;
    }
  }

  if (keyFlags['a'] == 1){
    moveFlag[1] = 1;
    for (Objeto* obj : objetos){

      if (obj->getTipo() == LIMITE_EXTERNO_ARENA &&
      obj->getRaio() - raioPlayer < sqrt(pow(obj->getCx()-centroXPlayer+VELOCIDADE,2)+pow(obj->getCy()-centroYPlayer,2))){
        moveFlag[1] = 0;
      }

      else if (obj->getTipo() != LIMITE_EXTERNO_ARENA && obj->getTipo() != OBSTACULO_PULAVEL &&
      raioPlayer+obj->getRaio() > sqrt(pow(obj->getCx()-centroXPlayer+VELOCIDADE,2)+pow(obj->getCy()-centroYPlayer,2))){
        moveFlag[1] = 0;
      }

      else if (obj->getTipo() == OBSTACULO_PULAVEL && playerNoAlto == 0 &&
      raioPlayer+obj->getRaio() > sqrt(pow(obj->getCx()-centroXPlayer+VELOCIDADE,2)+pow(obj->getCy()-centroYPlayer,2))){
        moveFlag[1] = 0;
      }

    }
    if (moveFlag[1] == 1){
      centroXPlayer -= VELOCIDADE;
    }

  }

  if (keyFlags['s'] == 1){
    moveFlag[2] = 1;
    for (Objeto* obj : objetos){

      if (obj->getTipo() == LIMITE_EXTERNO_ARENA &&
      obj->getRaio() - raioPlayer < sqrt(pow(obj->getCx()-centroXPlayer,2)+pow(obj->getCy()-centroYPlayer+VELOCIDADE,2))){
        moveFlag[2] = 0;
      }

      else if (obj->getTipo() != LIMITE_EXTERNO_ARENA && obj->getTipo() != OBSTACULO_PULAVEL &&
      raioPlayer+obj->getRaio() > sqrt(pow(obj->getCx()-centroXPlayer,2)+pow(obj->getCy()-centroYPlayer+VELOCIDADE,2))){
        moveFlag[2] = 0;
      }

      else if (obj->getTipo() == OBSTACULO_PULAVEL && playerNoAlto == 0 &&
      raioPlayer+obj->getRaio() > sqrt(pow(obj->getCx()-centroXPlayer,2)+pow(obj->getCy()-centroYPlayer+VELOCIDADE,2))){
        moveFlag[2] = 0;
      }

    }
    if (moveFlag[2] == 1){
      centroYPlayer -= VELOCIDADE;
    }
  }

  if (keyFlags['d'] == 1){
    moveFlag[3] = 1;
    for (Objeto* obj : objetos){

      if (obj->getTipo() == LIMITE_EXTERNO_ARENA &&
      obj->getRaio() - raioPlayer < sqrt(pow(obj->getCx()-centroXPlayer-VELOCIDADE,2)+pow(obj->getCy()-centroYPlayer,2))){
        moveFlag[3] = 0;
      }

      else if (obj->getTipo() != LIMITE_EXTERNO_ARENA && obj->getTipo() != OBSTACULO_PULAVEL &&
      raioPlayer+obj->getRaio() > sqrt(pow(obj->getCx()-centroXPlayer-VELOCIDADE,2)+pow(obj->getCy()-centroYPlayer,2))){
        moveFlag[3] = 0;
      }

      else if (obj->getTipo() == OBSTACULO_PULAVEL && playerNoAlto == 0 &&
      raioPlayer+obj->getRaio() > sqrt(pow(obj->getCx()-centroXPlayer-VELOCIDADE,2)+pow(obj->getCy()-centroYPlayer,2))){
        moveFlag[3] = 0;
      }

    }
    if (moveFlag[3] == 1){
      centroXPlayer += VELOCIDADE;
    }
  }
  glutPostRedisplay();
}

void keyUp (unsigned char key, int x, int y){
  keyFlags[key] = 0;
}

void keyPress (unsigned char key, int x, int y){
  keyFlags[key] = 1;
}

int main (int argc, char* argv[]){
  raioExtraPlayer = 0;
  if (argc < 2) {
    string aux = "\n";
    lerConfig(const_cast<char*>(aux.c_str()));
  } else{
    lerConfig(argv[1]);
  }
  lerSvg();
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE |  GLUT_RGB);
  glutInitWindowSize (tamanhoTela[1]-tamanhoTela[0], tamanhoTela[3]-tamanhoTela[2]);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("arena");
  init();
  glutKeyboardFunc(keyPress);
  glutKeyboardUpFunc(keyUp);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
