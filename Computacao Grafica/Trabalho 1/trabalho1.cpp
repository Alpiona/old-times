#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include "tinyxml2.h"

#define QNT_VERTICES_CIRCULO 20

using namespace tinyxml2;
using namespace std;

int iniciou, mouseFlag[3], arrastando;
float centroX, centroY,ultimoX, ultimoY, ultimaDist;
float largura, altura, raio, corBG[3], corCirculo[3];
string titulo;

void lerXml (){
  XMLDocument config;
  XMLElement* leitor;
  string arqEntrada;
  printf("Insira a localização do arquivo 'config.xml', ou pressione 'Enter' caso esteja no mesmo diretório.\n");
  getline(cin, arqEntrada);
  if (arqEntrada == "\n"){
    arqEntrada = "config.xml";
  } else {
    arqEntrada = arqEntrada+"config.xml";
  }
  config.LoadFile(arqEntrada.c_str());

  leitor = config.FirstChildElement()->FirstChildElement("janela");
  leitor->FirstChildElement("largura")->QueryFloatText(&largura);
  leitor->FirstChildElement("altura")->QueryFloatText(&altura);
  titulo = leitor->FirstChildElement("titulo")->GetText();
  leitor = leitor->FirstChildElement("fundo");
  leitor->QueryFloatAttribute("corR", &corBG[0]);
  leitor->QueryFloatAttribute("corG", &corBG[1]);
  leitor->QueryFloatAttribute("corB", &corBG[2]);

  leitor = config.FirstChildElement()->FirstChildElement("circulo");
  leitor->QueryFloatAttribute("raio", &raio);
  leitor->QueryFloatAttribute("corR", &corCirculo[0]);
  leitor->QueryFloatAttribute("corG", &corCirculo[1]);
  leitor->QueryFloatAttribute("corB", &corCirculo[2]);
}

void init (void){
  glClearColor (corBG[0], corBG[1], corBG[2], 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, largura, 0.0, altura, -1.0, 1.0);
  glFlush();
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (corCirculo[0], corCirculo[1], corCirculo[2]);
    if (iniciou == 1){
    glBegin(GL_TRIANGLE_FAN);
  		glVertex2f(centroX, centroY);
  		for(int i = 0; i <= QNT_VERTICES_CIRCULO;i++) {
  			glVertex2f(
  		      centroX + (raio * cos(i * 2*3.14159 / QNT_VERTICES_CIRCULO)),
  			    centroY + (raio * sin(i * 2*3.14159 / QNT_VERTICES_CIRCULO))
  			);
  		}
  	glEnd();
    glFlush ();
  }
}

void mouse (int button, int state, int x, int y){
  if (iniciou == 0 && button == GLUT_LEFT_BUTTON){
    iniciou = 1;
    centroX = x;
    centroY = altura - y;
  }
    if (button == GLUT_LEFT_BUTTON && mouseFlag[button] == 0){
      mouseFlag[button] = 1;
      if (sqrt(pow(x-centroX,2)+pow(altura-y-centroY,2)) <= raio)
        arrastando = 1;
    } else if (button == GLUT_LEFT_BUTTON){
      mouseFlag[button] = 0;
      arrastando = 0;
    }
    if (button == GLUT_RIGHT_BUTTON && mouseFlag[button] == 0){
      mouseFlag[button] = 1;
      if (sqrt(pow(x-centroX,2)+pow(altura-y-centroY,2)) <= raio)
        arrastando = 1;
    } else if (button == GLUT_RIGHT_BUTTON){
      mouseFlag[button] = 0;
      arrastando = 0;
    }
    ultimaDist = sqrt(pow(x-centroX,2)+pow(y-centroY,2));
    ultimoX = x;
    ultimoY = altura - y;
    glutPostRedisplay();
}

void motion (int x, int y){
  if (arrastando == 1){
    y = altura - y;
    if (mouseFlag[GLUT_LEFT_BUTTON] ==  1){
      centroX+= x-ultimoX;
      centroY+= y-ultimoY;
    }
    if (mouseFlag[GLUT_RIGHT_BUTTON] ==  1){
      float distancia = sqrt(pow(x-centroX,2)+pow(y-centroY,2));
      if (distancia - ultimaDist < 0 && raio > 2){
        raio += distancia - ultimaDist;
      } else if (distancia - ultimaDist > 0){
        raio += distancia - ultimaDist;
      }
      ultimaDist = distancia;
    }
    ultimoY = y;
    ultimoX = x;
    glutPostRedisplay();
  }
}

int main (int argc, char** argv){
  iniciou = 0;
  lerXml();
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE |
  GLUT_RGB);
  glutInitWindowSize (largura, altura);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (titulo.c_str());
  init();
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMainLoop();
  return 0;
}
