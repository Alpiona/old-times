#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <math.h>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include "tinyxml2.h"
#include "personagem.h"
#include "objeto.h"
#include "projetil.h"

#define QNT_VERTICES_CIRCULOS 200

#define VELOCIDADE 0.1

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

int keyFlags[256], moveFlag[4], atirarFlag;
float tamanhoTela[4], altura, ultimoX, velPersonagem, velTiroPersonagem, freqTiroInimigo, velInimigo, velTiroInimigo;
string nome, tipo, caminho, caminhoInteiro;
vector<Objeto*> objetos;
vector<Projetil*> projeteis;
vector<Personagem*> inimigos;
Personagem* player;


void novoObjeto( XMLElement* child){
  float cx, cy, r;
  int id;
  child->QueryFloatAttribute("cx", &cx);
  child->QueryFloatAttribute("cy", &cy);
  child->QueryFloatAttribute("r", &r);
  child->QueryIntAttribute("id", &id);
  string cor = child->Attribute("fill");
  if (cor.compare("blue") != 0){
    cy = tamanhoTela[2]+tamanhoTela[3]-cy;
  }

  if (cor.compare("green") == 0){
    player = new Personagem(cx, cy, r, id, velPersonagem, velTiroPersonagem);
  }
  else if (cor.compare("black") == 0){
    Objeto* novoObjeto = new Objeto(cx, cy, r, id, OBSTACULO_PULAVEL);
    objetos.push_back(novoObjeto);
  }
  else if (cor.compare("red") == 0){
    Personagem* novoInimigo = new Personagem(cx,cy,r,id,velInimigo, velTiroInimigo);
    inimigos.push_back(novoInimigo);
  }
  else if (cor.compare("white") == 0){
    Objeto* novoObjeto = new Objeto(cx, cy, r, id, LIMITE_INTERNO_ARENA);
    objetos.push_back(novoObjeto);
  }

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
  if (config.LoadFile( arqEntrada.c_str()) == 0) {
    leitor = config.FirstChildElement()->FirstChildElement("arquivoDaArena");
    nome = leitor->Attribute("nome");
    tipo = leitor->Attribute("tipo");
    caminho = leitor->Attribute("caminho");
    leitor = config.FirstChildElement()->FirstChildElement("jogador");
    leitor->QueryFloatAttribute("vel", &velPersonagem);
    leitor->QueryFloatAttribute("velTiro", &velTiroPersonagem);
    leitor = config.FirstChildElement()->FirstChildElement("inimigo");
    leitor->QueryFloatAttribute("vel", &velInimigo);
    leitor->QueryFloatAttribute("velTiro", &velTiroInimigo);
    leitor->QueryFloatAttribute("freqTiro", &freqTiroInimigo);
    leitor = config.FirstChildElement()->FirstChildElement("obstaculo");
    leitor->QueryFloatAttribute("altura", &altura);
  }else{
    cout<<"Não foi possível encontrar o arquivo config.xml em "<<argv<<endl;
    exit(0);
  }
}

void lerSvg(char* argv){
  XMLDocument svg;
  XMLElement* leitor;
  string arqEntrada= caminho+nome+"."+tipo;

  if (svg.LoadFile(arqEntrada.c_str()) == 0) {
    leitor = svg.FirstChildElement("svg");
    string cor;
    for (XMLElement* child = leitor->FirstChildElement("circle"); child != NULL; child = child->NextSiblingElement()){
      novoObjeto(child);
    }
  } else {
    cout<<"Não foi possível encontrar o arquivo "<<nome<<"."<<tipo<<" em ."<<argv<<caminho<<endl;
    exit(0);
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

void desenhaCirculo(GLfloat cX, GLfloat cY, GLfloat raio){
  glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glVertex2f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS))
      );
    }
  glEnd();
}

void desenhaParedeCircular(GLfloat cX, GLfloat cY, GLfloat raio){
  glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         0
      );
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         raio*5
      );
    }
  glEnd();
}

void display(void){
  glClear (GL_COLOR_BUFFER_BIT);

  for (Objeto* obj : objetos){

      if (obj->getTipo() == LIMITE_EXTERNO_ARENA){
        glColor3fv(azul);
        desenhaCirculo(obj->getCx(), obj->getCy(), obj->getRaio());
        desenhaParedeCircular(obj->getCx(), obj->getCy(), obj->getRaio());
      }

      else if(obj->getTipo() == OBSTACULO_PULAVEL){
        glColor3fv(preto);
        desenhaCirculo(obj->getCx(), obj->getCy(), obj->getRaio());
      }

      else if (obj->getTipo() == LIMITE_INTERNO_ARENA){
        glColor3fv(branco);
        desenhaCirculo(obj->getCx(), obj->getCy(), obj->getRaio());
      }

  }
  // desenhaProjeteis();
  glColor3fv(vermelho);
  for (Projetil* proj : projeteis){
    glBegin(GL_TRIANGLE_FAN);
      for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
        glVertex2f(
           proj->getCx() + (proj->getRaio() * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
           proj->getCy() + (proj->getRaio() * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS))
        );
      }
    glEnd();
  }
  for (Personagem* inimigo : inimigos){
    inimigo->desenharPersonagem(QNT_VERTICES_CIRCULOS, 255, 0, 0);
  }
  player->desenharPersonagem(QNT_VERTICES_CIRCULOS, 0, 255, 0);
  glutSwapBuffers();
}

void checaProjeteis(GLfloat valor){
  vector<Projetil*> aux;
  bool del = false;
  for (Projetil* proj : projeteis){
    for (Objeto* obj : objetos){
      if ((obj->getTipo() == OBSTACULO_PULAVEL || obj->getTipo() == LIMITE_INTERNO_ARENA)
      && proj->getRaio()+obj->getRaio() >= sqrt(pow(proj->getCx()-obj->getCx(),2)+pow(proj->getCy()-obj->getCy(),2))){
        del = true;
      }
      else if (obj->getTipo() == LIMITE_EXTERNO_ARENA
      && obj->getRaio()-proj->getRaio() <= sqrt(pow(obj->getCx()-proj->getCx(), 2)+pow(obj->getCy()-proj->getCy(),2))){
        del = true;
      }
      else{
      }
    }
    if (del == false){
      proj->setCx(proj->getCx()-valor*sin(proj->getDirecaoTheta()*0.0174533));
      proj->setCy(proj->getCy()+valor*cos(proj->getDirecaoTheta()*0.0174533));
      aux.push_back(proj);
    }
    del = false;
  }
  projeteis = aux;
}

void atualizaDirecao(Personagem* inimigo){
  GLfloat novoAngulo = atan2(player->getCy() - inimigo->getCy(), player->getCx() - inimigo->getCx());
  inimigo->setThetaPersonagem(novoAngulo);
}

void movimentaInimigo(GLdouble velocidade, Personagem* inimigo){
  atualizaDirecao(inimigo);
  GLint moveInimigoFlag = 0, pulo = 0;
  GLfloat thetaInicial = inimigo->getThetaPersonagem();
  GLfloat i=0;
  while (moveInimigoFlag == 0){
    moveInimigoFlag = 1;
    float cosSqrPlayer = pow(player->getCx()-inimigo->getCx()-(velocidade*1.01* cos ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2);
    float senSqrPlayer = pow(player->getCy()-inimigo->getCy()-(velocidade*1.01* sin ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2);
    float distPlayer = sqrt(cosSqrPlayer+senSqrPlayer);

    if (inimigo->getRaioInicial()+player->getRaioInicial() > distPlayer){
      moveInimigoFlag = 0;
    }

    for (Objeto* obj : objetos){
      float cosSqrObjeto = pow(obj->getCx()-inimigo->getCx()-(velocidade*1.01* cos ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2);
      float senSqrObjeto = pow(obj->getCy()-inimigo->getCy()-(velocidade*1.01* sin ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2);
      float distObjeto = sqrt(cosSqrObjeto+senSqrObjeto);

      if (obj->getTipo() == LIMITE_EXTERNO_ARENA && obj->getRaio() - inimigo->getRaioInicial() < distObjeto){
        moveInimigoFlag = 0;
      }

      else if (obj->getTipo() != LIMITE_EXTERNO_ARENA && obj->getTipo() != OBSTACULO_PULAVEL && inimigo->getRaioInicial()+obj->getRaio() > distObjeto){
        moveInimigoFlag = 0;
      }

      else if (obj->getTipo() == OBSTACULO_PULAVEL && inimigo->getRaioInicial()+obj->getRaio() > distObjeto && moveInimigoFlag == 1){
        if (inimigo->getAltura()==0){
          // inimigo->pulou();
          // glutTimerFunc(100, pular, inimigo->getId());
          moveInimigoFlag = 0;
        } else if (inimigo->getAltura()<altura/10) {
          moveInimigoFlag=0;
        }
      }
    }

    if (moveInimigoFlag == 0 ){
      if (i>0){
        i=-(i);
      } else if(i<0){
        i=1-i;
      } else {
        i++;
      }
    } else {
      inimigo->rotacionar(i*velocidade);
      inimigo->movimentar(velocidade);
    }
  }
}

void idle(){
  static GLdouble previousTime = 0;
  GLdouble currentTime, timeDifference;

  currentTime = glutGet(GLUT_ELAPSED_TIME);
  timeDifference = currentTime - previousTime;
  previousTime = currentTime;
  player->calcularDisparoPos();

  for (Personagem* inimigo: inimigos){
    movimentaInimigo(inimigo->getVel()*timeDifference, inimigo);
  }
  checaProjeteis(player->getVelTiro()*timeDifference);

  if (keyFlags['w'] == 1){
    moveFlag[0] = 1;
    for (Objeto* obj : objetos){
      float cosSqr = pow(obj->getCx()-player->getCx()-(player->getVel() * timeDifference* cos ((player->getThetaPersonagem()+90)*0.0174533)),2);
      float senSqr = pow(obj->getCy()-player->getCy()-(player->getVel() * timeDifference* sin ((player->getThetaPersonagem()+90)*0.0174533)),2);
      float dist = sqrt(cosSqr+senSqr);
      if (obj->getTipo() == LIMITE_EXTERNO_ARENA && obj->getRaio() - player->getRaio() < dist){
        moveFlag[0] = 0;
      }

      else if (obj->getTipo() != LIMITE_EXTERNO_ARENA && obj->getTipo() != OBSTACULO_PULAVEL && player->getRaio()+obj->getRaio() > dist){
        moveFlag[0] = 0;
      }

      else if (obj->getTipo() == OBSTACULO_PULAVEL  && player->getAltura() < (altura/10) && player->getRaio()+obj->getRaio() > dist){
        moveFlag[0] = 0;
      }

    }
    for (Personagem* inimigo : inimigos){
      float cosSqr = pow(inimigo->getCx()-player->getCx()-(player->getVel() * timeDifference* cos ((player->getThetaPersonagem()+90)*0.0174533)),2);
      float senSqr = pow(inimigo->getCy()-player->getCy()-(player->getVel() * timeDifference* sin ((player->getThetaPersonagem()+90)*0.0174533)),2);
      float dist = sqrt(cosSqr+senSqr);
      if (inimigo->getRaio()+player->getRaio() > dist){
        moveFlag[0] = 0;
      }
    }
    if (moveFlag[0] == 1){
      player->movimentar(player->getVel()*timeDifference);
    }
  }

  if (keyFlags['a'] == 1){
      player->rotacionar(player->getVel()*timeDifference);
  }

  if (keyFlags['s'] == 1){
    moveFlag[2] = 1;
    for (Objeto* obj : objetos){
      float cosSqr = pow(obj->getCx()-player->getCx()+(player->getVel() *timeDifference* cos ((player->getThetaPersonagem()+90)*0.0174533)),2);
      float senSqr = pow(obj->getCy()-player->getCy()+(player->getVel() *timeDifference* sin ((player->getThetaPersonagem()+90)*0.0174533)),2);
      float dist = sqrt(cosSqr + senSqr);

      if (obj->getTipo() == LIMITE_EXTERNO_ARENA && obj->getRaio() - player->getRaio() < dist){
        moveFlag[2] = 0;
      }

      else if (obj->getTipo() != LIMITE_EXTERNO_ARENA && obj->getTipo() != OBSTACULO_PULAVEL && player->getRaio()+obj->getRaio() > dist){
        moveFlag[2] = 0;
      }

      else if (obj->getTipo() == OBSTACULO_PULAVEL && player->getAltura() < (altura/10) && player->getRaio()+obj->getRaio() > dist){
        moveFlag[2] = 0;
      }
    }

    for (Personagem* inimigo : inimigos){
      float cosSqr = pow(inimigo->getCx()-player->getCx()+(player->getVel() *timeDifference* cos ((player->getThetaPersonagem()+90)*0.0174533)),2);
      float senSqr = pow(inimigo->getCy()-player->getCy()+(player->getVel() *timeDifference* sin ((player->getThetaPersonagem()+90)*0.0174533)),2);
      float dist = sqrt(cosSqr+senSqr);
      if (inimigo->getRaio()+player->getRaio() > dist){
        moveFlag[2] = 0;
      }
    }

    if (moveFlag[2] == 1){
      player->movimentar(-player->getVel()*timeDifference);
    }

  }

  if (keyFlags['d'] == 1){
    player->rotacionar(-player->getVel()*timeDifference);
  }
  glutPostRedisplay();
}

void keyUp (unsigned char key, int x, int y){
  keyFlags[key] = 0;
}

void keyPress (unsigned char key, int x, int y){
  keyFlags[key] = 1;
}

void criaProjetil(){
  float cXp = player->getDisparoCx();
  float cYp = player->getDisparoCy();
  float direcao = player->getDisparoTheta();
  float raio = 1;
  Projetil* novoProjetil = new Projetil(cXp, cYp, direcao, raio, player->getVelTiro());
  projeteis.push_back(novoProjetil);
}

void mouse (int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON && player->getAltura() == 0 && atirarFlag==0){
    atirarFlag=1;
    criaProjetil();
  } else if (atirarFlag==0){
    atirarFlag=1;
  } else {
    atirarFlag=0;
  }
}

void motion (int x, int y){
  GLfloat valor = x-ultimoX;
  player->rotacionaBraco(valor);
  ultimoX = x;
  glutPostRedisplay();
}

int main (int argc, char* argv[]){
  ultimoX = (tamanhoTela[1]-tamanhoTela[0])/2;
  atirarFlag = 0;
  if (argc < 2) {
    string aux = "\n";
    lerConfig(const_cast<char*>(aux.c_str()));
    lerSvg(const_cast<char*>(aux.c_str()));
  } else{
    lerConfig(argv[1]);
    lerSvg(argv[1]);
  }
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (tamanhoTela[1]-tamanhoTela[0], tamanhoTela[3]-tamanhoTela[2]);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("arena");
  init();
  glutKeyboardFunc(keyPress);
  glutKeyboardUpFunc(keyUp);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(motion);
  glutMainLoop();
  return 0;
}
