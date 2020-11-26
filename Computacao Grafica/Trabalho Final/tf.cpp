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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "objloader.h"

#define QNT_VERTICES_CIRCULOS 200

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

mesh meshModelPlayer[5];
mesh meshModelEnemy[5];
mesh meshWeaponPlayer;
mesh meshWeaponEnemy;

using namespace tinyxml2;
using namespace std;

int keyFlags[256], moveFlag[4], atirarFlag, movPlayer;
float tamanhoTela[4], altura, ultimoX, velPersonagem, velTiroPersonagem, freqTiroInimigo, velInimigo, velTiroInimigo, sentMovPlayer;
string nome, tipo, caminho, caminhoInteiro;
vector<Objeto*> objetos;
vector<Projetil*> projeteis;
vector<Personagem*> inimigos;
Personagem* player;

double camDist=50;
double camXYAngle=-180, weaponXYAngle = 0;
double camYZAngle=0, weaponYZAngle = 0;
int toggleCam = 1;
int camAngle = 60;
int lastX = 0;
int lastY = 0;
int buttonRightDown=0;

GLuint textureWall;
GLuint textureGround;
GLuint textureSky;
GLuint textureRock;
GLuint texturePlayer;
GLuint textureEnemy;
GLuint textureWeapon;

GLuint LoadTextureRAW( const char * filename ){

  GLuint texture;
  int x,y,n;
  unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
  // Image* image = loadBMP(filename);

  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    delete data;

    return texture;
}

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
  movPlayer = 1;
  sentMovPlayer = 1;
  glShadeModel(GL_SMOOTH);
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  // GLfloat lmodel_ambient[] = {player->getCx(),player->getCy() , 100, 1.0 };
  // glLightfv(GL_LIGHT0, GL_POSITION, lmodel_ambient);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  // glMatrixMode (GL_PROJECTION);
  // glLoadIdentity();
  // gluPerspective(45, 1, 5, 10);
  // glOrtho(tamanhoTela[0], tamanhoTela[1], tamanhoTela[2], tamanhoTela[3], -5.0, 5.0);
  // glFlush();
  textureWall = LoadTextureRAW("wall.jpeg");
  textureGround = LoadTextureRAW("ground.jpg");
  textureSky = LoadTextureRAW("sky.jpg");
  textureRock = LoadTextureRAW("rock.jpg");
  texturePlayer = LoadTextureRAW("player.jpeg");
  textureEnemy = LoadTextureRAW("enemy.jpg");
  meshWeaponPlayer.loadMesh("arma.obj");
  meshWeaponPlayer.loadMeshTex(texturePlayer);
  meshWeaponEnemy.loadMesh("arma.obj");
  meshWeaponEnemy.loadMeshTex(textureEnemy);
  meshModelPlayer[0].loadMesh("model1.obj");
  meshModelPlayer[1].loadMesh("model2.obj");
  meshModelPlayer[2].loadMesh("model3.obj");
  meshModelPlayer[3].loadMesh("model4.obj");
  meshModelPlayer[4].loadMesh("model5.obj");
  meshModelEnemy[0].loadMesh("model1.obj");
  meshModelEnemy[1].loadMesh("model2.obj");
  meshModelEnemy[2].loadMesh("model3.obj");
  meshModelEnemy[3].loadMesh("model4.obj");
  meshModelEnemy[4].loadMesh("model5.obj");
  for (int i =0; i<5; i++){
    meshModelPlayer[i].loadMeshTex(texturePlayer);
    meshModelEnemy[i].loadMeshTex(textureEnemy);
  }
}

void atualizaDirecao(Personagem* inimigo){
  GLfloat novoAngulo = atan2(player->getCy() - inimigo->getCy(), player->getCx() - inimigo->getCx());
  inimigo->setThetaPersonagem(novoAngulo);
}

void movimentaInimigo(GLdouble velocidade, Personagem* inimigo){
  atualizaDirecao(inimigo);
  GLint moveInimigoFlag = 0;
  GLfloat i=0;
  while (moveInimigoFlag == 0){
    moveInimigoFlag = 1;

    if (inimigo->getRaioInicial()+player->getRaioInicial() > sqrt(
      pow(player->getCx()-inimigo->getCx()-(velocidade*1.1* cos ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2)+
      pow(player->getCy()-inimigo->getCy()-(velocidade*1.1* sin ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2))){
      moveInimigoFlag = 0;
    }

    for (Objeto* obj : objetos){
      if (obj->getTipo() == LIMITE_EXTERNO_ARENA &&
      obj->getRaio() - inimigo->getRaioInicial() < sqrt(
        pow(obj->getCx()-inimigo->getCx()-(velocidade*1.1* cos ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2)+
        pow(obj->getCy()-inimigo->getCy()-(velocidade*1.1*sin ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2))){
        moveInimigoFlag = 0;
      }

      else if (obj->getTipo() != LIMITE_EXTERNO_ARENA && obj->getTipo() != OBSTACULO_PULAVEL &&
      inimigo->getRaioInicial()+obj->getRaio() > sqrt(
        pow(obj->getCx()-inimigo->getCx()-(velocidade*1.1* cos ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2)+
        pow(obj->getCy()-inimigo->getCy()-(velocidade*1.1* sin ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2))){
        moveInimigoFlag = 0;
      }

      else if (obj->getTipo() == OBSTACULO_PULAVEL &&
      inimigo->getRaioInicial()+obj->getRaio() > sqrt(
        pow(obj->getCx()-inimigo->getCx()-(velocidade *1.1* cos ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2)+
        pow(obj->getCy()-inimigo->getCy()-(velocidade *1.1* sin ((inimigo->getThetaPersonagem()+i+90)*0.0174533)),2))){
        moveInimigoFlag=0;
      }
    }
    if (moveInimigoFlag == 0){
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

void desenhaObstaculo(GLfloat cX, GLfloat cY, GLfloat raio){
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

  GLfloat materialEmission[] = { 0.10, 0.10, 0.10, 1};
  GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
  GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_shininess[] = { 100.0 };
  glColor3f(1,1,1);

  glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glBindTexture (GL_TEXTURE_2D, textureRock);
  double textures = 0, inc = (double) 1/QNT_VERTICES_CIRCULOS;
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0,0,1);
    glTexCoord2f(0.5,0.5);
    glVertex3f(cX, cY, 35);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glNormal3f(0,0,-1);
      glTexCoord2f((cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)+1)/2, (sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)+1)/2);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         35
      );
    }
  glEnd();
  textures = 0;
  glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glNormal3f(-(cos(i*2*3.14159/QNT_VERTICES_CIRCULOS)),-(sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),0);
      glTexCoord2f(textures*5, 0);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         0
      );
      glNormal3f(-(cos(i*2*3.14159/QNT_VERTICES_CIRCULOS)),-(sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),0);
      glTexCoord2f(textures*5,1);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         35
      );
      textures += inc;
    }
  glEnd();
}

void desenharLimiteExterno(GLfloat cX, GLfloat cY, GLfloat raio){
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

  GLfloat materialEmission[] = { 0.10, 0.10, 0.10, 1};
  GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
  GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_shininess[] = { 100.0 };
  glColor3f(1,1,1);

  glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glBindTexture (GL_TEXTURE_2D, textureWall);
  double textures = 0, inc = (double) 1/QNT_VERTICES_CIRCULOS;
  glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glNormal3f(-(cos(i*2*3.14159/QNT_VERTICES_CIRCULOS)),-(sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),0);
      glTexCoord2f(textures*5, 0);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         0
      );
      glNormal3f(-(cos(i*2*3.14159/QNT_VERTICES_CIRCULOS)),-(sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),0);
      glTexCoord2f(textures*5,1);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         160
      );
      textures += inc;
    }
  glEnd();
}

void desenharLimiteInterno(GLfloat cX, GLfloat cY, GLfloat raio){
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

  GLfloat materialEmission[] = { 0.10, 0.10, 0.10, 1};
GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
GLfloat mat_shininess[] = { 100.0 };
glColor3f(1,1,1);

glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glBindTexture (GL_TEXTURE_2D, textureWall);
  double textures = 0, inc = (double) 1/QNT_VERTICES_CIRCULOS;
  glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glNormal3f(sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS),cos(i*2*3.14159/QNT_VERTICES_CIRCULOS),0);
      glTexCoord2f(textures*3.5, 0);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         0
      );
      glNormal3f(sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS),cos(i*2*3.14159/QNT_VERTICES_CIRCULOS),0);
      glTexCoord2f(textures*3.5,1);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         160
      );
      textures += inc;
    }
  glEnd();
}

void desenharChao(GLfloat cX, GLfloat cY, GLfloat raio){
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

  GLfloat materialEmission[] = { 0.10, 0.10, 0.10, 1};
  GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
  GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_shininess[] = { 100.0 };
  glColor3f(1,1,1);

  glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glBindTexture (GL_TEXTURE_2D, textureGround);
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0,0,1);
    glTexCoord3f(0.5,0.5, 0);
    glVertex3f(cX, cY, 0);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glNormal3f(0,0,1);
      glTexCoord3f((cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)+1)/2, (sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)+1)/2, raio/3);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         0
      );
    }
  glEnd();
}

void desenharCeu(GLfloat cX, GLfloat cY, GLfloat raio){
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );

  GLfloat materialEmission[] = { 0.10, 0.10, 0.10, 1};
  GLfloat materialColorA[] = { 0.2, 0.2, 0.2, 1};
  GLfloat materialColorD[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1};
  GLfloat mat_shininess[] = { 100.0 };
  glColor3f(1,1,1);

  glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
  glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glBindTexture (GL_TEXTURE_2D, textureSky);
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0,0,-1);
    glTexCoord3f(0.5,0.5, raio/3);
    glVertex3f(cX, cY, raio/3);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glNormal3f(0,0,-1);
      glTexCoord3f((cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)+1)/2, (sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)+1)/2, raio/3);
      glVertex3f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         raio/3
      );
    }
  glEnd();
}

void desenhaCirculoVazio(GLfloat cX, GLfloat cY, GLfloat raio){
  glBegin(GL_LINES);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glVertex2f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS))
      );
    }
  glEnd();
}

void desenhaCirculoCheio(GLfloat cX, GLfloat cY, GLfloat raio){
  glBegin(GL_TRIANGLE_FAN);
    for(int i = 0; i <= QNT_VERTICES_CIRCULOS;i++) {
      glVertex2f(
         cX+ (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULOS)),
         cY+ (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULOS))
      );
    }
  glEnd();
}

void desenhaMapa(){
  for (Objeto* obj : objetos){

    if (obj->getTipo() == LIMITE_EXTERNO_ARENA){
      glColor3fv(azul);
      desenhaCirculoVazio(obj->getCx(), obj->getCy(), obj->getRaio());
    }

    else {
      if (obj->getTipo() == OBSTACULO_PULAVEL){
        glColor3fv(preto);
        desenhaCirculoCheio(obj->getCx(), obj->getCy(), obj->getRaio());
      }
      else if (obj->getTipo() == LIMITE_INTERNO_ARENA){
        glColor3fv(preto);
        desenhaCirculoVazio(obj->getCx(), obj->getCy(), obj->getRaio());
      }
      // desenhaCirculo(obj->getCx(), obj->getCy(), obj->getRaio());
    }
  }
  for (Personagem* inimigo : inimigos){
    glColor3fv(vermelho);
    desenhaCirculoCheio(inimigo->getCx(), inimigo->getCy(), inimigo->getRaio());
  }
  glColor3fv(verde);
  desenhaCirculoCheio(player->getCx(), player->getCy(), player->getRaio());
}

void display(void){
  glClearColor (1.0, 1.0, 1.0, 0.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  // GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
  // glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  for (int i =0; i<2;i++){
    if (i == 0){
      // if (toggleCam == 1)
      glViewport(0,0,500,200);
      glLoadIdentity();
      gluPerspective (60, (GLfloat)500 / (GLfloat)200, 1, 1000.0);
      gluLookAt(player->getCx()+2*sin(-player->getThetaPersonagem()*0.0174533),player->getCy()+2*cos(player->getThetaPersonagem()*0.0174533),35+player->getCz(),
              100000*(-sin(player->getThetaPersonagem()*0.0174533)),100000*(cos(player->getThetaPersonagem()*0.0174533)),5+player->getCz(),
              0,0,1);
    }
    else {
      glViewport(0,200,500,700);
      glLoadIdentity();
      gluPerspective (60, (GLfloat)500 / (GLfloat)500, 1, 1000.0);
      if (toggleCam == 2){
        double Xpos = player->getCx()+camDist*cos((+90-camXYAngle+player->getThetaPersonagem())*0.0174533);
        double Ypos = player->getCy()+camDist*sin((+90-camXYAngle+player->getThetaPersonagem())*0.0174533);
        gluLookAt(Xpos,Ypos, 27+player->getCz()+(camDist*cos((90-camYZAngle)*0.0174533)),
                  player->getCx(), player->getCy(), 27+player->getCz(),
                  0, 0, 1);
      }
      else if (toggleCam == 1) {
        gluLookAt(player->getCx()+5*cos((player->getThetaPersonagem())*0.0174533)-10*sin(player->getThetaPersonagem()*0.0174533),
                player->getCy()+5*sin(player->getThetaPersonagem()*0.0174533)+10*cos(player->getThetaPersonagem()*0.0174533),
                32.5+player->getCz(),
                player->getCx()+5*cos((player->getThetaPersonagem())*0.0174533)-10*sin(player->getThetaPersonagem()*0.0174533)+2*-sin((player->getThetaPersonagem()-weaponXYAngle)*0.0174533),
                player->getCy()+5*sin(player->getThetaPersonagem()*0.0174533)+10*cos(player->getThetaPersonagem()*0.0174533)+2*cos((player->getThetaPersonagem()-weaponXYAngle)*0.0174533),
                32.5-2.5*sin(weaponYZAngle*0.0174533)+player->getCz(),
                0,0,1);
      }
    }
    for (Objeto* obj : objetos){
      if (obj->getTipo() == LIMITE_EXTERNO_ARENA){
        desenharChao(obj->getCx(), obj->getCy(), obj->getRaio());
        desenharLimiteExterno(obj->getCx(), obj->getCy(), obj->getRaio());
        desenharCeu(obj->getCx(), obj->getCy(), obj->getRaio());
      }
      else if(obj->getTipo() == OBSTACULO_PULAVEL){
        glColor3fv(preto);
        desenhaObstaculo(obj->getCx(), obj->getCy(), obj->getRaio());
      }
      else if (obj->getTipo() == LIMITE_INTERNO_ARENA){
        glColor3fv(branco);
        desenharLimiteInterno(obj->getCx(), obj->getCy(), obj->getRaio());
      }
    }
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
      glPushMatrix();
        glTranslatef(inimigo->getCx()+12*cos((inimigo->getThetaPersonagem()+65)*0.0174533), inimigo->getCy()+(12*sin((inimigo->getThetaPersonagem()+65)*0.0174533)), 29.5);
        glRotatef(90,1,0,0);
        glRotatef(90,0,1,0);
        glRotatef(inimigo->getThetaPersonagem()+180,0,1,0);
        glScalef(3.5,3.5,3.5);
        meshWeaponEnemy.draw();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(inimigo->getCx(), inimigo->getCy(), 0);
        glRotatef(90,1,0,0);
        glRotatef(inimigo->getThetaPersonagem()+180,0,1,0);
        glScalef(13,13,13);
        meshModelEnemy[(int)inimigo->getMovPernas()].draw();
      glPopMatrix();
    }
    glShadeModel(GL_FLAT);
    glPushMatrix();
      glTranslatef(
                  // player->getCx()+12*cos((player->getThetaPersonagem()+65)*0.0174533),
                  // player->getCy()+(12*sin((player->getThetaPersonagem()+65)*0.0174533)),
                  player->getCx()+5*cos((player->getThetaPersonagem())*0.0174533)-10*sin(player->getThetaPersonagem()*0.0174533),
                  player->getCy()+5*sin(player->getThetaPersonagem()*0.0174533)+10*cos(player->getThetaPersonagem()*0.0174533),
                  player->getCz()+29.5);
      glRotatef(90,1,0,0);
      glRotatef(90,0,1,0);
      glRotatef(player->getThetaPersonagem()+180,0,1,0);
      glRotatef(-weaponXYAngle,0,1,0);
      glRotatef(weaponYZAngle,0,0,1);
      glScalef(3.5,3.5,3.5);
      meshWeaponPlayer.draw();
    glPopMatrix();
    glPushMatrix();
      glTranslatef(player->getCx(), player->getCy(), player->getCz());
      glRotatef(90,1,0,0);
      glRotatef(player->getThetaPersonagem()+180,0,1,0);
      glScalef(13,13,13);
      meshModelPlayer[(int)player->getMovPernas()].draw();
    glPopMatrix();
    glLoadIdentity();
    if (i != 0){
      glViewport(0,200,500,500);
      // gluPerspective(45, 1, 5, 10);
      // glOrtho(-1500, tamanhoTela[1], tamanhoTela[2], 2300, -5.0, 5.0);
      glOrtho(tamanhoTela[0]-(tamanhoTela[1]-tamanhoTela[0])*3,tamanhoTela[1],tamanhoTela[2],tamanhoTela[3]+(tamanhoTela[3]-tamanhoTela[2])*3,-1, 1);
      // glOrtho(0, 100, 0, 100,-1,1);
      desenhaMapa();
    }
  }
  glutSwapBuffers();
}

void pular (int value){
  if (value > 0){
    value--;
    player->estaSubindo();
    glutTimerFunc(100, pular, value);
  } else if (player->getCz() == 35){
    for (Objeto* obj :objetos){
      if (obj->getTipo() == OBSTACULO_PULAVEL &&
      player->getRaioInicial()+obj->getRaio() >= sqrt (pow(player->getCx()-obj->getCx(),2)+pow(player->getCy()-obj->getCy(),2))){
        player->setSubindo(false);
        player->setDescendo(false);
        glutTimerFunc(100, pular, 0);
        return;
      }
    }
    player->estaDescendo();
    player->setSubindo(false);
    player->setDescendo(false);
    glutTimerFunc(100, pular, 0);
  } else {
    if (player->getCz() > 0){
      player->setSubindo(false);
      player->setDescendo(true);
      player->estaDescendo();
      glutTimerFunc(100, pular, 0);
    } else {
      player->setSubindo(false);
      player->setDescendo(false);
    }
  }
}

GLdouble currentTime, timeDifference;

void idle(){
  static GLdouble previousTime = 0;

  currentTime = glutGet(GLUT_ELAPSED_TIME);
  timeDifference = currentTime - previousTime;
  previousTime = currentTime;
  player->calcularDisparoPos();


  // for (Personagem* inimigo: inimigos){
  //   movimentaInimigo(inimigo->getVel()*timeDifference, inimigo);
  // }
  // checaProjeteis(player->getVelTiro()*timeDifference);

  if (keyFlags['p'] == 1 && player->isSubindo() == player->isDescendo()){
    player->setSubindo(true);
    player->setDescendo(false);
    glutTimerFunc(100, pular, 10);
  }

  if (keyFlags['1'] == 1){
    toggleCam = 1;
  }

  if (keyFlags['2'] == 1){
    toggleCam = 2;
  }

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

      else if (obj->getTipo() == OBSTACULO_PULAVEL  && player->getCz() < 35 && player->getRaio()+obj->getRaio() > dist){
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
      // if (sentMovPlayer == 1){
      //   if (movPlayer+1 > 16){
      //     sentMovPlayer = 0;
      //     movPlayer = 15;
      //   } else {
      //     movPlayer++;
      //   }
      // } else {
      //   if (movPlayer-1 <0){
      //     sentMovPlayer = 1;
      //     movPlayer = 1;
      //   } else {
      //     movPlayer--;
      //   }
      // }
      player->movimentar(player->getVel()*timeDifference);
    }
    // if (moveFlag[0] == 1){
    //   if(movPlayer != 16 && movPlayer != 0 )
    //     movPlayer= movPlayer + (1*sentMovPlayer);
    //   else{
    //     sentMovPlayer = sentMovPlayer * (-1);
    //     movPlayer= movPlayer + (1*sentMovPlayer);
    //   }
    // player->movimentar(player->getVel()*timeDifference);
    // }
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

    // if (moveFlag[2] == 1){
    //   if(movPlayer != 16 && movPlayer != 0 )
    //     movPlayer= movPlayer - (1*sentMovPlayer);
    //   else{
    //     sentMovPlayer = sentMovPlayer * (-1);
    //     movPlayer= movPlayer - (1*sentMovPlayer);
    //   }
    //   player->movimentar(-player->getVel()*timeDifference);
    // }

    // if (moveFlag[2] == 1){
    //   if (sentMovPlayer == 1){
    //     if (movPlayer-1 < 0){
    //       sentMovPlayer = 0;
    //       movPlayer = 1;
    //     } else {
    //       movPlayer--;
    //     }
    //   } else {
    //     if (movPlayer+1 >16){
    //       sentMovPlayer = 1;
    //       movPlayer = 15;
    //     } else {
    //       movPlayer++;
    //     }
    //   }
    //   player->movimentar(-player->getVel()*timeDifference);
    // }

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

void reshape (int w, int h) {

    // glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    // gluPerspective (60, (GLfloat)w / (GLfloat)h, 1, 1000.0);
    glMatrixMode (GL_MODELVIEW);
}

void mouse_callback(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        lastX = x;
        lastY = y;
        buttonRightDown = 1;
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
      buttonRightDown = 0;
    }
}

void mouse_motion(int x, int y)
{
  if (toggleCam == 2){
    if(buttonRightDown == 1 && camXYAngle + x-lastX > -360 && camXYAngle + x-lastX <=0 )
      camXYAngle += x - lastX;
    if(buttonRightDown == 1 && camYZAngle + y - lastY <= 90 && camYZAngle + y - lastY >= -90)
      camYZAngle += y - lastY;

    camXYAngle = (int)camXYAngle % 360;
    camYZAngle = (int)camYZAngle % 360;
  }

    lastX = x;
    lastY = y;
}

void mouse_passivemotion(int x, int y){
  if (toggleCam == 1){
    if(weaponXYAngle + x-lastX > -45 && weaponXYAngle + x-lastX <=45 )
      weaponXYAngle += x - lastX;
    if(weaponYZAngle + y - lastY > -45 && weaponYZAngle + y - lastY <= 45)
      weaponYZAngle += y - lastY;

    weaponXYAngle = (int)weaponXYAngle % 360;
    weaponYZAngle = (int)weaponYZAngle % 360;
  }

  lastX = x;
  lastY = y;

}

int main (int argc, char* argv[]){
  // ultimoX = (tamanhoTela[1]-tamanhoTela[0])/2;
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
  glutInitWindowSize (500, 700);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("arena");
  init();

  glutKeyboardFunc(keyPress);
  glutKeyboardUpFunc(keyUp);
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMouseFunc(mouse_callback);
  glutPassiveMotionFunc(mouse_passivemotion);
  glutMotionFunc(mouse_motion);
  glutReshapeFunc (reshape);
  glutMainLoop();
  return 0;
}
