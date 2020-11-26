#include<windows.h>
#ifdef __APPLE__
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include "Construcciones.h"    //se IMPLEMENTA LA CLASE donde estan las coordenadas
#include "imageloader.h"       // Se
using namespace std;
/**
JOSE RIOS JOSE
ERIK ISAI PEREZ OLGUIN
OSWALDO HERNANDEZ ALTAMIRANO
*/
/* Variables de control para velocidad de rotation/translacion/zoom */
#define GRADOS_POR_PIXEL	0.4f
#define ZOOM_ELEMENTO		0.04f

GLuint _texturecalle, _texturepasto;     //TEXTURA PAVIMENTO

const int TAM_LINEAS = 5000;  // variable para lo largo de las lineas primitivas
Pila casal1,casal2,perso,letras,lot,esfin,casal4;   //DECLARACION DE PILAS PARA DIVERSOS ELEMENTOS DE LA ESCENA
int persovi=0;   //VARIABLE QUE CONTROLA LA VISTA 1er y 3era persona

//metodo que obtiene de construcciones las pilas llenas y las asigna a las pilas
void cargaescenario(){
    casal2=edi2();     casal1=edi1();
    if(persovi==0){                   //al iniciar siempre aparece el 3er persona
    perso=personaje();}
     letras=letrero();
    lot=llama();       esfin = pesfinge();
    casal4=edi4();
}

//se define una estructura para el estado del mouse
typedef struct {
  bool ButonIzquierda;
  bool ButonDerecha;
  int x;
  int y;
} EstadoMouse;
//variables para controlar el movimiento
int matriz[100][100];   //matriz logica para controlar las colisiones
int moverZ=3;           //movimiento en Z
int moverX=0;           //moviento en X
int moverY=1;           //moviento en Y

//este metodo ayuda a colocar valores en la matriz logica  segun el tama�o de la casa cuadrada y su posicion en x,z
void llenarMatriz(int tamanioCasa,int posx,int posy){
    int pos=80+posy;
    int posyz=20+posx;
   for(int i=pos;i>=pos-tamanioCasa;i--){
    for(int j=posyz;j<posyz+tamanioCasa;j++){
           matriz[i][j]=1;}}//DONDE ESTA LA CASA SE COLOCA UN 1
}
//este metodo ayuda a colocar valores en la matriz logica  segun el tama�o de la casa rectangular y su posicion en x,z
void llenarMatriz(int largo,int ancho,int posy,int posx){
    int pos=50+posy;
    int posyz=50+posx;
   for(int i=pos;i>=pos-largo;i--){
       for(int j=posyz;j<posyz+ancho;j++){
           matriz[i][j]=1;  //DONDE ESTA LA CASA SE COLOCA UN 1
    }}
}

EstadoMouse Estadomouse = { false, false, 0, 0 }; //se declara un estado inicial de mouse
 //variables para controlar la vista segun angulos
float xRotacion = 0;
//Arreglos de la posicion y orientacion  que se usan en el gluLookAt
GLfloat ojo[] = { 0,0, 20 };
GLfloat en[] = { 0, 0, 0 };

//metodo que genera el contorno de un cuadro segun su posicion X,Z y su tama�o  con una altura incial y una final
void plantilla(int posX,int posZ,int yi,int yf,int tamanio){
for(int t=yi;t<yf;t++){
    for(int i=posZ;i>posZ-tamanio;i--){
        for(int j=posX;j<posX+tamanio;j++) {
            if(i==posZ||i==posZ-tamanio+1) {
                glPushMatrix();
                glTranslated(j,t,i);
                glutSolidCube(1);
                glPopMatrix();
        }else{
                if(j==posX||j==(posX+tamanio)-1){
                glPushMatrix();
                glTranslated(j,t,i);
                glutSolidCube(1);
                glPopMatrix();} } } }}
}
//metodo que genera el cuadro segun su posicion X,Z y su tamaño y posicion en Y(altura)
void plantilla2(int posX,int posZ,int y,int tamanio){
 for(int i=posZ;i>posZ-tamanio;i--){
        for(int j=posX;j<posX+tamanio;j++) {
                glPushMatrix();
                glTranslated(j,y,i);
                glutSolidCube(1);
                glPopMatrix();} }
}
//metodo que recorre la Pila del edificio uno y grafica un cubo en cada coordenada segun un color especificado
void casa() {
  while(!casal1.estaVacia()){
   int * a = new int[3];
    a=casal1.pop();
  switch (a[3]){
    case 1:glColor3f(0.8,0.81,0.85);
    break;
    case 2:glColor3f(1.0,1.0,1.0);
    break;
    case 3: glColor3f(0.7, 0.13, 0.13);
    break;
    case 4:glColor3f(0.1, 0.1, 0.44);
    break;
    case 5:glColor3f(0.5, 0.5, 0.5);
    break;
    case 6:glColor3f(0.53, 0.81, 0.92);
    break;}
   glPushMatrix();
   glTranslated(a[0],a[1],a[2]);
   glRotatef(0, 0, 0.0, 0.0);
   glutSolidCube(1);
   glPopMatrix();
  }
}
//metodo que recorre la Pila del edificio dos y grafica un cubo en cada coordenada segun un color especificado
void casa2(){

 while(!casal2.estaVacia()){
   int * a = new int[3];
    a=casal2.pop();
  switch (a[3]){
    case 1:glColor3f(0.63, 0.33, 0.18);
    break;
    case 3:glColor3f(0.92,0.13,0.13);
    break;
    case 2: glColor3f(0.98,0.86,0.35);
    break;
    case 5:glColor3f(0.53, 0.81, 0.92);
    break;
    case 6:glColor3f(0.8,0.81,0.85);
    break;
  }
   glPushMatrix();
   glTranslated(a[0],a[1],a[2]);
   glRotatef(0, 0, 0.0, 0.0);
  //glutWireCube(1);
   glutSolidCube(1);
   glPopMatrix();

  }
}
//grafica la casa 3 sin pila para acelerar el proceso, un cubo en cada coordenada segun un color especificado
void casa3(){
    //cerca
    glColor3f(0.95, 0.13, 0.13);
    int temp=-42,temp2=12;
      for(int i=1;i<=6;i++){
         plantilla(temp,-12,1,3,1);
         plantilla(temp,12,1,3,1);
         plantilla(-42,temp2,1,3,1);
         plantilla(-17,temp2,1,3,1);
         temp+=5;  temp2+=-5;
      }
    plantilla(-42,12,3,4,26);
    glColor3f(0.02, 0.08, 0.2);
    for(int i=1;i<8;i++){
     plantilla2(-21,6,i,2);     plantilla2(-21,-8,i,2);}
    plantilla2(-40,6,8,16);  plantilla2(-24,6,8,5);    plantilla2(-24,1,8,5);  plantilla2(-25,-4,8,6);
    plantilla2(-42,6,14,16);   plantilla2(-26,6,14,8);  plantilla2(-26,-2,14,8);  plantilla2(-18,6,14,4);
    plantilla2(-18,2,14,4);    plantilla2(-18,-2,14,4);   plantilla2(-18,-6,14,4);
    glColor3f(0.98, 0.86, 0.85);
    for(int i=6;i>-10;i--){ plantilla(-40,i,1,8,1);}
    for(int i=28;i<41;i++){ plantilla(-i,-9,1,8,1);}
     for(int i=6;i>-5;i--){ plantilla(-29,i,1,8,1);}   plantilla(-39,6,1,8,1);  plantilla(-38,6,1,8,1);
     for(int i=29;i<35;i++){ plantilla(-i,6,1,8,1);}
     for(int i=35;i<39;i++){plantilla(-i,6,1,3,1);  plantilla(-i,6,5,8,1);}
    glColor3f(0.02, 0.08, 0.2);
     for(int i=6;i>-6;i--){  plantilla(-40,i,9,14,1);}
     for(int i=36;i<40;i++){  plantilla(-i,6,9,14,1);}  plantilla(-33,6,9,14,2); plantilla;
     for(int i=20;i<30;i++){plantilla(-i,6,9,14,1);}   plantilla(-21,5,9,14,2); plantilla(-21,1,9,14,2);
     for(int i=3;i<9;i++){ plantilla(-20,-i,9,14,1);}
     for(int i=20;i<31;i++){ plantilla(-i,-9,9,14,1);}
     glColor3f(0.99, 0.95, 0.81);
     for(int i=5;i<9;i++){ plantilla(-30,-i,9,14,1);}
      for(int i=30;i<41;i++){ plantilla(-i,-5,9,14,1);}
}
//grafica la casa 4 con una Pila de detalles para acelerar el proceso, un cubo en cada coordenada segun un color especificado
void casa4(){
    glColor3f(0.33, 0.1, 0.63);//cerca
    for(int i=25;i<48;i++){  plantilla2(-6,i,1,1);  plantilla2(23,i,1,1); }
    for(int i=-5;i<23;i++){  plantilla2(i,25,1,1);}
    glColor3f(0.78, 0.0, 0.22); //mesa
    plantilla2(-2,35,1,2);  plantilla2(-2,35,2,2);
    glColor3f(1.0, 0.34, 0.2);
    plantilla2(-3,36,3,4);//mesa
    glColor3f(0.38, 0.38, 0.38);
    plantilla(4,47,1,2,16);//casa
    for(int i=32;i<48;i++){plantilla2(4,i,2,1);  plantilla2(19,i,2,1);}
    for(int i=4;i<10;i++){plantilla2(i,32,2,1); plantilla2(i+10,32,2,1);}
    glColor3f(0.93, 0.73, 0.6);
    for(int i=2;i<8;i++){for(int j=4;j<20;j++){plantilla2(j,47,i,1);}}
    for(int i=10;i<16;i++){for(int j=4;j<20;j++){plantilla2(j,47,i,1);}}
    for(int j=3;j<8;j++){ for(int i=4;i<10;i++){plantilla2(i,32,j,1); plantilla2(i+10,32,j,1);}}
    plantilla2(4,47,7,16);          plantilla2(4,47,15,16);
    for(int j=2;j<8;j++){ for(int i=32;i<38;i++){plantilla2(4,i,j,1); plantilla2(4,i+10,j,1);
    plantilla2(19,i,j,1); plantilla2(19,i+10,j,1);}}
    for(int j=10;j<16;j++){ for(int i=32;i<38;i++){plantilla2(4,i,j,1); plantilla2(4,i+10,j,1);
    plantilla2(19,i,j,1); plantilla2(19,i+10,j,1);}}
    plantilla2(4,41,3,2);     plantilla2(18,39,3,2);   plantilla2(4,39,3,2);     plantilla2(18,41,3,2);
    plantilla2(4,41,10,2);     plantilla2(18,39,10,2);   plantilla2(4,39,10,2);     plantilla2(18,41,10,2);
    for(int j=4;j<10;j++){ for(int i=10;i<16;i++){plantilla2(j,32,i,1); plantilla2(j+10,32,i,1);}}
       plantilla2(10,33,10,2);   plantilla2(12,33,10,2);
       plantilla2(9,33,17,2);  plantilla2(9,33,18,2);  plantilla2(9,33,19,2);  plantilla2(9,33,20,2);
       plantilla2(13,33,17,2);  plantilla2(13,33,18,2);  plantilla2(13,33,19,2);  plantilla2(13,33,20,2);
       plantilla2(11,33,20,2);  plantilla2(10,33,21,2);  plantilla2(12,33,21,2); plantilla2(11,33,22,2);
    glColor3f(0.64, 0.58, 0.27);
    plantilla2(10,32,10,2);   plantilla2(12,32,10,2);    plantilla2(11,32,17,2);
    plantilla2(3,41,4,2);     plantilla2(19,39,4,2);   plantilla2(3,39,4,2);     plantilla2(19,41,4,2);
    plantilla2(3,41,11,2);     plantilla2(19,39,11,2);   plantilla2(3,39,11,2);     plantilla2(19,41,11,2);
    glColor3f(0.38, 0.38, 0.38);
    plantilla2(4,47,8,16);    plantilla2(4,47,16,16);
    glColor3f(0.78, 0.0, 0.22);
    plantilla2(4,47,9,16);
    //detalles de la casa
  while(!casal4.estaVacia()){
    int * a = new int[3];
    a=casal4.pop();
    switch (a[3]){
    case 1:glColor3f(1.0, 1.0,1.0);
    break;
    case 2:glColor3f(0.93, 0.73, 0.6);
    break;
    case 3:glColor3f(0.91, 0.99, 0.19);
    break;
    case 4:glColor3f(0.1, 0.32, 0.46);
    break;
    case 5:glColor3f(0.08, 0.26, 0.38);
    break;

    }
   glPushMatrix();
   glTranslated(a[0],a[1],a[2]);
   glutSolidCube(1);
   glPopMatrix();}

}

//grafica el arco sin pila para acelerar el proceso, un cubo en cada coordenada segun un color especificado
void arcotriunfo(){
  glColor3f(0.92, 0.6, 0.31);
  plantilla(35,26,1,3,8);    plantilla(35,45,1,3,8);  plantilla2(35,26,13,8);    plantilla2(35,45,13,8);
  plantilla2(35,26,10,8);    plantilla2(35,45,10,8);
  for(int i=19;i<27;i++){
  for(int j=3;j<9;j++){plantilla2(42,i,j,1);  plantilla2(35,i,j,1);   plantilla2(42,i+19,j,1);  plantilla2(35,i+19,j,1); }}
  for(int i=3;i<9;i++){plantilla2(41,19,i,1); plantilla2(36,19,i,1);  plantilla2(41,26,i,1); plantilla2(36,26,i,1);
  plantilla2(41,38,i,1); plantilla2(36,38,i,1);   plantilla2(41,45,i,1); plantilla2(36,45,i,1);}
  for(int i=6;i<9;i++){plantilla2(37,19,i,1); plantilla2(38,19,i,1); plantilla2(39,19,i,1); plantilla2(40,19,i,1);
  plantilla2(37,26,i,1); plantilla2(38,26,i,1); plantilla2(39,26,i,1); plantilla2(40,26,i,1);
  plantilla2(37,38,i,1); plantilla2(38,38,i,1); plantilla2(39,38,i,1); plantilla2(40,38,i,1);
  plantilla2(37,45,i,1); plantilla2(38,45,i,1); plantilla2(39,45,i,1); plantilla2(40,45,i,1);}
  for(int i=35;i<43;i++){ plantilla(i,19,10,14,1); plantilla(i,45,10,14,1);
  plantilla(i,26,10,14,1);  plantilla(i,38,10,14,1);}
  plantilla2(35,39,12,8);  plantilla2(35,31,12,8);  plantilla2(35,39,13,8);  plantilla2(35,31,13,8);
  plantilla(42,20,10,13,1);   plantilla(35,20,10,13,1);    plantilla(42,24,10,13,1);   plantilla(35,24,10,13,1);
  plantilla(42,25,10,13,1);   plantilla(35,25,10,13,1);
  plantilla(42,39,10,13,1);     plantilla(42,40,10,13,1);   plantilla(42,44,10,13,1);
  plantilla(35,39,10,13,1);     plantilla(35,40,10,13,1);   plantilla(35,44,10,13,1);
    for(int i=35;i<43;i++){ plantilla2(i,27,10,1); plantilla2(i,27,11,1); plantilla2(i,28,11,1);
    plantilla2(i,36,11,1);  plantilla2(i,37,11,1); plantilla2(i,37,10,1);}
    glColor3f(0.79, 0.81, 0.82);
    plantilla2(33,46,14,12); plantilla2(33,34,14,12);  plantilla2(33,29,14,12);
    glColor3f(0.83, 0.33, 0.0);
    plantilla(35,44,15,17,8);  plantilla(35,36,15,17,8);  plantilla(35,28,15,17,8);  plantilla(35,27,15,17,8);
    plantilla(35,44,18,19,8);  plantilla(35,36,18,19,8);  plantilla(35,28,18,19,8);  plantilla(35,27,18,19,8);
    plantilla2(36,44,18,6);  plantilla2(36,38,18,6);  plantilla2(36,32,18,6); plantilla2(36,26,18,6); plantilla2(36,25,18,6);
   glColor3f(0.9, 0.6, 0.4);

    plantilla2(36,44,17,6);  plantilla2(36,38,17,6);  plantilla2(36,32,17,6); plantilla2(36,26,17,6); plantilla2(36,25,17,6);
    glColor3f(0.98, 0.13, 0.02);
    int aux=20;
    for(int i=1;i<=13;i++){
      plantilla2(42,aux,19,1);
      plantilla2(35,aux,19,1);
      aux+=2; }
  glColor3f(0.49, 0.81, 0.63);
  plantilla2(35,26,9,8);   plantilla2(35,45,9,8);
  plantilla(34,23,9,10,2);    plantilla(40,24,9,10,4);    plantilla(37,21,9,10,4);
  plantilla2(36,25,9,6);    plantilla2(36,44,9,6);
  plantilla(34,42,9,10,2);    plantilla(40,43,9,10,4);    plantilla(37,46,9,10,4);
   aux=20;
  for(int i=1;i<=13;i++){
      plantilla2(42,aux,17,1);
      plantilla2(35,aux,17,1);
      aux+=2; }
  glColor3f(0.63, 0.25, 0.0);
  plantilla(34,23,1,4,2);    plantilla(40,24,1,2,4);    plantilla(37,21,1,2,4);
  plantilla2(36,25,1,6);    plantilla2(36,44,1,6);
  plantilla(34,42,1,4,2);    plantilla(40,43,1,2,4);    plantilla(37,46,1,2,4);
  glColor3f(0.94, 0.7, 0.48);
  plantilla2(37,36,19,4);  plantilla2(37,32,19,4);  plantilla2(37,31,19,4);
   plantilla2(38,34,20,2);  plantilla2(38,32,20,2); plantilla2(38,33,21,2);

}

//grafica el personaje segun su Pila, un cubo en cada coordenada segun un color especificado
void persona(){
   while(!perso.estaVacia()){
   int * a = new int[3];
    a=perso.pop();
   switch (a[3]){
    case 1:glColor3f(1.0,0.49,0.13);
    break;
    case 2:glColor3f(0.92,0.13,0.13);
    break;
    case 3: glColor3f(0.45, 0.35, 0.25);
    break;
    case 4:glColor3f(1.0,1.0,1.0);
    break;
    case 5:glColor3f(0.17,0.34,0.96);
    break;
    case 6:glColor3f(00.8,0.81,0.85);
    break;
    case 7:glColor3f(0,0,0);
    break;
  }
   glPushMatrix();
   glTranslatef(a[0]+moverX,a[1]+moverY,a[2]+moverZ);
   glutSolidCube(1);
   glPopMatrix();

  }

}

//grafica el edificio mas alto sin pila para acelerar el proceso, un cubo en cada coordenada segun un color especificado
void empireState(){
     glColor3f(0.71, 0.64, 0.45); //primer planta
      plantilla(-40,-28,1,5,16);   plantilla(-24,-28,1,5,8);  plantilla(-24,-36,1,5,8);
      plantilla2(-40,-28,5,16);    plantilla2(-24,-28,5,8);   plantilla2(-24,-36,5,8);
      glColor3f(0.4, 0.4, 0.4);  //segunda planta
      plantilla(-38,-30,6,10,14);  plantilla2(-38,-30,10,14);
      plantilla(-24,-30,6,10,6);   plantilla2(-24,-30,10,6);
      plantilla(-24,-36,6,10,6);   plantilla2(-24,-36,10,6);
      plantilla(-24,-42,6,10,2);   plantilla2(-24,-42,10,2);
      plantilla(-22,-42,6,10,2);   plantilla2(-22,-42,10,2);
      plantilla(-20,-42,6,10,2);   plantilla2(-20,-42,10,2);
      glColor3f(0.6, 0.6, 0.6);//tercer planta
      plantilla(-36,-32,11,13,10);  plantilla2(-36,-32,13,10);
      plantilla(-26,-32,11,13,6);  plantilla2(-26,-32,13,6);
      plantilla(-26,-36,11,13,6);  plantilla2(-26,-36,13,6);
      glColor3f(0.11, 0.17, 0.21); //cuarta planta
      plantilla(-34,-34,14,26,6);  plantilla2(-34,-34,26,6);
      plantilla(-28,-34,14,26,6);  plantilla2(-28,-34,26,6);
      glColor3f(0.73, 0.0, 0.0); // quinta planta
      plantilla(-33,-35,27,31,4);  plantilla2(-33,-35,31,4);
      plantilla(-29,-35,27,31,4);  plantilla2(-29,-35,31,4);
      plantilla(-25,-35,27,31,2);  plantilla2(-25,-35,31,2);
      plantilla(-25,-37,27,31,2);  plantilla2(-25,-37,31,2);
      glColor3f(0.12, 0.36, 0.68);//sexta planta
      plantilla2(-32,-36,32,3); plantilla2(-29,-36,32,3); plantilla2(-26,-36,32,2);
      plantilla2(-26,-38,32,1); plantilla2(-25,-38,32,1);
      plantilla2(-32,-36,33,3); plantilla2(-29,-36,33,3); plantilla2(-26,-36,33,2);
      plantilla2(-26,-38,33,1); plantilla2(-25,-38,33,1);
      glColor3f(0.86, 0.49, 0.14); //septima planta
      plantilla2(-31,-37,34,2); plantilla2(-29,-37,34,2); plantilla2(-27,-37,34,2);
      plantilla2(-29,-37,35,2); plantilla2(-29,-37,36,2); plantilla2(-29,-37,37,2);
      glColor3f(0.92, 0.91, 0.84);
      for(int i=1;i<6;i++){
       plantilla2(-36,-27,i,2); plantilla2(-34,-27,i,2);
       plantilla2(-35,-29,i+5,2); plantilla2(-33,-29,i+5,2);
       plantilla2(-24,-27,i,2); plantilla2(-22,-27,i,2);
       plantilla2(-25,-29,i+5,2); plantilla2(-23,-29,i+5,2);
      }
      for(int i=11;i<14;i++){
          plantilla2(-33,-31,i,2); plantilla2(-25,-31,i,2); }
      for(int i=14;i<27;i++){
          plantilla2(-32,-33,i,2); plantilla2(-26,-33,i,2); }
}

//grafica el letro ITO con Pila, un cubo en cada coordenada segun un color especificado
void escribeletras(){

  while(!letras.estaVacia()){
   int * a = new int[3];
    a=letras.pop();
    glColor3f(1.0, 0.5, 0.0);
   glPushMatrix();
   glTranslatef(a[0],a[1],a[2]);
   glutSolidCube(1);
   glPopMatrix();
  }

}

//metodo que grafica una cerca en todo el limite del plano
void limiteplano(){
  glColor3f(0.05, 0.05, 0.71);
  plantilla(-44,48,1,3,96);
}
//graficar una esfinge  sin pila para acelerar el proceso
void esfinge(){
  glColor3f(0.93, 0.89, 0.45);
  plantilla2(-15,-29,1,16);   plantilla2(1,-29,1,16);
  glColor3f(0.8, 0.47, 0.13);
  plantilla2(-1,-36,2,2);   plantilla2(-3,-36,2,2);
  plantilla2(1,-34,2,6);    plantilla2(1,-32,2,2);   plantilla2(3,-32,2,2);    plantilla2(1,-40,2,2);   plantilla2(3,-40,2,2);
  plantilla2(7,-34,2,4);    plantilla2(7,-38,2,2);   plantilla2(9,-38,2,2);
  plantilla2(11,-34,2,2);  plantilla2(13,-34,2,2);
  plantilla2(11,-38,2,2);  plantilla2(13,-38,2,2);
  glColor3f(0.72, 0.45, 0.2);
  plantilla2(1,-35,3,4);    plantilla2(5,-35,3,4);  plantilla2(9,-35,3,2);  plantilla2(9,-37,3,2);
  glColor3f(0.58, 0.45, 0.2);
  plantilla2(1,-36,4,2);   plantilla2(3,-36,4,2);  plantilla2(5,-36,4,2);  plantilla2(7,-36,4,2); plantilla2(9,-36,4,2);
  plantilla2(10,-34,5,2);     plantilla2(10,-36,5,2);     plantilla2(10,-38,5,2);
  plantilla2(12,-36,5,2); plantilla2(11,-36,6,2);
  glColor3f(0.58, 0.47, 0.23);
  plantilla2(10,-35,6,2);    plantilla2(10,-37,6,2);   plantilla2(10,-36,7,2);
  while(!esfin.estaVacia()){
   int * a = new int[3];
    a=esfin.pop();
   switch (a[3]){
    case 1:glColor3f(0.0, 0.57, 0.16);
    break;
    case 2:glColor3f(1.0, 0.85, 0.04);
    break;
    case 3: glColor3f(0.58, 0.53, 0.42);
    break;
    case 4:glColor3f(0.4, 0.21, 0.04);
    break;}
   glPushMatrix();
   glTranslatef(a[0],a[1],a[2]);
   glutSolidCube(1);
   glPopMatrix(); }
}

//metodo que genera un pino deacuerdo a coordenada X,Z
void creapinos(int x, int z){
   glColor3f(0.43, 0.17, 0.0);//troncos
   plantilla2(x,z,1,2);   plantilla2(x,z,2,2);   plantilla2(x,z,3,2);
   plantilla2(x,z,4,2);   plantilla2(x,z,5,2);   plantilla2(x,z,6,2);
   glColor3f(0.03, 0.31, 0.06);//ramas
   for(int i=7;i<13;i++){
   plantilla2(x-1,z+1,i,2);     plantilla2(x+1,z+1,i,2);
   plantilla2(x-1,z-1,i,2);     plantilla2(x+1,z-1,i,2);
   }
   plantilla2(x,z,13,2);

}

//metodo que genera un arbol deacuerdo a coordenada X,Z
void creaarbol(int x,int z,int c){
    glColor3f(0.43, 0.17, 0.0);//troncos
   for(int i=1;i<7;i++){  plantilla2(x,z,i,2);}
   if(c==1){glColor3f(0.13, 0.45, 0.05);}else{glColor3f(0.03, 0.31, 0.06);}
   for(int i=x-6;i<=x+6;i++){   plantilla2(i,z,7,2);}
   for(int i=z-6;i<=z+6;i++){   plantilla2(x,i,7,2);}
   for(int i=x-5;i<=x+5;i++){   plantilla2(i,z,8,2);}
   for(int i=z-5;i<=z+5;i++){   plantilla2(x,i,8,2);}
   for(int i=x-4;i<=x+4;i++){   plantilla2(i,z,9,2);}
   for(int i=z-4;i<=z+4;i++){   plantilla2(x,i,9,2);}
   for(int i=x-3;i<=x+3;i++){   plantilla2(i,z,10,2);}
   for(int i=z-3;i<=z+3;i++){   plantilla2(x,i,10,2);}
   for(int i=x-2;i<=x+2;i++){   plantilla2(i,z,11,2);}
   for(int i=z-2;i<=z+2;i++){   plantilla2(x,i,11,2);}
   for(int i=x-1;i<=x+1;i++){   plantilla2(i,z,12,2);}
   for(int i=z-1;i<=z+1;i++){   plantilla2(x,i,12,2);}
   plantilla2(x,z,13,2);
   for(int i=7;i<11;i++){plantilla2(x-1,z+1,i,2); plantilla2(x-1,z-1,i,2); plantilla2(x+1,z+1,i,2); plantilla2(x+1,z-1,i,2);}

}

//metodo que genera un arbusto deacuerdo a coordenada X,Z
void creaarbustos(int x,int z){
 glColor3f(0.8, 0.47, 0.17);
   plantilla2(x,z,1,2);
   plantilla2(x,z,2,2);
   glColor3f(0.43, 0.64, 0.19);
   plantilla2(x,z,4,2);
   plantilla2(x-1,z+1,3,2);     plantilla2(x+1,z+1,3,2);
   plantilla2(x-1,z-1,3,2);     plantilla2(x+1,z-1,3,2);

}

//metodo que genera la jardinera con 2 arbustos y 1 pino
void jardidera(){
creapinos(15,14);   creaarbustos(10,14);     creaarbustos(4,14);
 glColor3f(0.95, 0.13, 0.13);
 for(int i=2;i<19;i++){ plantilla2(i,16,1,1);  plantilla2(i,11,1,1); }
 for(int i=11;i<17;i++){ plantilla2(2,i,1,1);  plantilla2(18,i,1,1); }
}
//metodo que genera el mini bosque en la parte inferior izquierda del mapa
void bosque(){
 creaarbol(-16,43,1);   creaarbol(-20,34,2);   creaarbol(-25,27,1);   creaarbol(-32,31,2);   creaarbol(-39,24,1);
}
//metodo que recorre el arreglo de la llama para graficarla segun su color
void dillama(){
    while(!lot.estaVacia()){
   int * a = new int[3];
    a=lot.pop();
   switch (a[3]){
    case 1:glColor3f(0.07, 0.11, 0.13);
    break;
    case 2:glColor3f(0.08, 0.23, 0.44);
    break;
    case 3: glColor3f(0.31, 0.39, 0.52);
    break;
    case 4:glColor3f(0.88, 0.92, 0.91);
    break;
    case 5:glColor3f(0.9, 0.23, 0.67);
    break;
  }
   glPushMatrix();
   glTranslatef(a[0],a[1],a[2]);
   glutSolidCube(1);
   glPopMatrix();
  }
}

//metodo que genera el resto de arboles, pinos y arbustos dentro del mapa
void crearflora(){
creapinos(-41,-22);     creapinos(-41,-15);     creapinos(-42,15);    creapinos(-4,28);   creapinos(40,2);  creapinos(25,47);
creaarbustos(19,-44);     creaarbustos(48,-25);    creaarbustos(47,9);   creaarbustos(-5,45);
creaarbol(40,-38,1);        creaarbol(8,-20,1);    creaarbol(28,-42,2);
bosque();
jardidera();
}
//metodo que dibuja el conjunto de casas
void dibujacasas(){
 casa();     casa2();    casa3();     casa4();
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void Initialize() {
    //se tiene que modificar la direccion de la imagen deacuerdo a lo pc
	Image* image = loadBMP("C:\\Users\\jose_\\Downloads\\LegoParque\\bricks.bmp");
	_texturecalle = loadTexture(image);
	delete image;
	Image* image1 = loadBMP("C:\\Users\\jose_\\Downloads\\LegoParque\\grass.bmp");
	_texturepasto = loadTexture(image1);
	delete image1;
}

//metodo en el cual se dibujan las calles con texturas
void  calles(){
    glEnable(GL_TEXTURE_2D);
   glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_QUADS);
    glVertex3f(-15,0.1,2);   glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(50,0.1,2);    glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(50,0.1,9);    glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(-15,0.1,9);   glTexCoord3f(1.0,0.0,0.1);
    glEnd();
   glPopMatrix();

   glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_QUADS);
    glVertex3f(20,0.1,2); glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(20,0.1,-45);  glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(25,0.1,-45);  glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(25,0.1,2);   glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_POLYGON);
    glVertex3f(-14,0.1,2); glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(50,0.1,2);  glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(50,0.1,9);  glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(-14,0.1,9); glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_POLYGON);
    glVertex3f(25,0.1,-19);  glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(25,0.1,-25);  glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(50,0.1,-25);  glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(50,0.1,-19);  glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_POLYGON);
    glVertex3f(43,0.1,47);  glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(43,0.1,-19);  glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(50,0.1,-19);  glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(50,0.1,47);   glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_POLYGON);
    glVertex3f(25,0.1,9);  glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(25,0.1,47);  glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(33,0.1,47);  glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(33,0.1,9);   glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_POLYGON);
    glVertex3f(44,0.1,28);  glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(44,0.1,36);   glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(33,0.1,36);  glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(33,0.1,28);   glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();


    glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_POLYGON);
    glVertex3f(0,0.1,24);   glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(-15,0.1,24);  glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(-15,0.1,-27);  glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(0,0.1,-27);   glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_POLYGON);
    glVertex3f(0,0.1,18);   glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(25,0.1,18);   glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(25,0.1,24);  glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(0,0.1,24);   glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturecalle);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(0.75, 0.79, 0.79);
    glBegin(GL_POLYGON);
    glVertex3f(-1,0.1,-16);  glTexCoord3f(1.0,1.0,0.1);
    glVertex3f(-40,0.1,-16);  glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(-40,0.1,-26);   glTexCoord3f(0.0,1.0,0.1);
    glVertex3f(-1,0.1,-26);   glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();

}

//metodo que dibuja el piso con texturas
void plano(){
  glEnable(GL_TEXTURE_2D);
   glPushMatrix();
       glBindTexture(GL_TEXTURE_2D, _texturepasto);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBegin(GL_POLYGON);
    glColor3f(0.25, 0.75, 0.25);
    glVertex3f(-44,0,48);    glTexCoord3f(1.0,0.5,0.1);
    glVertex3f(52, 0,48);    glTexCoord3f(0.0,0.0,0.1);
    glVertex3f(52, 0,-48);   glTexCoord3f(0.0,0.5,0.1);
    glVertex3f(-44, 0,-48);  glTexCoord3f(1.0,0.0,0.1);
    glEnd();
    glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

//metodo en el cual se mandan a llamar todos los metodos anteriores
//se dibuja el mapa y lso edificios
//se llena la matriz logica
void dibujaCuadros(){
    cargaescenario();
    limiteplano();
    dibujacasas();
    empireState();
    crearflora();
    escribeletras();
    dillama();
    persona();
    esfinge();
    arcotriunfo();

    llenarMatriz(10,18,1,1);//casa1
    llenarMatriz(18,16,1,26);//cas2
    llenarMatriz(2,5,3,38);//carbol1
    llenarMatriz(2,8,-25,27);
    llenarMatriz(1,5,-41,26);//carbol2
    llenarMatriz(1,5,-37,38);//carbol2
    llenarMatriz(15,33,-28,-16);//esfinje-decierto
    llenarMatriz(15,27,-27,-42);//torre
    llenarMatriz(1,7,-26,-26);//torre-cuadros
    llenarMatriz(1,7,-26,-38);//torre-cuadros
    llenarMatriz(25,27,13,-43);//casa grande
    llenarMatriz(5,18,17,1);//jardinera chica
    llenarMatriz(21,31,47,-7);//jardin grande
    llenarMatriz(8,2,46,-42);//i
    llenarMatriz(0,8,38,-40);//t
    llenarMatriz(8,2,46,-37);//t
    llenarMatriz(8,8,46,-32);//0
    //*********arboles mas a la derecha
    llenarMatriz(1,5,16,-44);//arbol
    llenarMatriz(1,5,25,-41);//arbol2
    llenarMatriz(1,5,32,-34);//arbol3
    llenarMatriz(1,5,35,-22);//arbol4
    llenarMatriz(1,5,28,-27);//arbol5
    llenarMatriz(1,5,44,-18);//arbol6
    //*********arboles despues de la torre
    llenarMatriz(1,5,-21,-43);//arbol1
    llenarMatriz(1,5,-14,-43);//arbol2
    //*********arboles despues de la casi 1
    llenarMatriz(1,5,-19,6);//arbol2
    //*************arbustos
    llenarMatriz(3,5,11,45);//arbusto1
    llenarMatriz(3,5,-23,46);//arbusto2
    llenarMatriz(3,5,-42,17);//arbusto2
    llenarMatriz(7,11,27,33);//arbusto con forma2
    llenarMatriz(1,2,24,33);//arbusto con forma2
    llenarMatriz(2,1,24,43);//arbusto con forma2
    llenarMatriz(1,5,20,36);//arbusto con forma2
    llenarMatriz(7,11,46,33);//arbusto con forma1
    llenarMatriz(1,2,43,33);//arbusto con forma1
    llenarMatriz(2,1,44,43);//arbusto con forma1
    llenarMatriz(1,5,47,36);//arbusto con forma1
    llenarMatriz(1,4,48,24);//arbol8

     plano();
    calles();
}

// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
void dibuja_ejes() {
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1, 0, 0);
  glVertex3f(-TAM_LINEAS, 0, 0);
  glVertex3f(TAM_LINEAS, 0, 0);
  // eje Y, color verde
  glColor3f(0, 1, 0);
  glVertex3f(0, -TAM_LINEAS, 0);
  glVertex3f(0,TAM_LINEAS, 0);
  // eje Z, color azul
  glColor3f(0, 0, 1);
  glVertex3f(0, 1, -TAM_LINEAS);
  glVertex3f(0, 0,TAM_LINEAS);
  glEnd();
}

int ejes=1;  //variable para controlar si se muestran o no los ejes
void Display(void) {
  glDrawBuffer(GL_BACK);
  glClearColor(109,183,247,1);
  /* limpiar el display */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* posicion de la camara */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(ojo[0], ojo[2], ojo[2], en[0], en[1], en[2], 0, 2, 1);
  /* Rotacion de la escena en x direcciones */
  glRotatef(xRotacion, 0, 1, 0);
  //se comprueba el valor del angulo para que las teclas conserven su funcion ejemplo W=arriba desde el punto de vista que sea
  if(xRotacion>=360 || xRotacion<=-360){
    xRotacion=0;}
   glTranslated(-moverX,-moverY,-moverZ);
  dibujaCuadros();
  if(ejes==1){//si se quieren motrar la guia
    dibuja_ejes();}
    Initialize();
  glFlush();
  glutSwapBuffers();
}

//metodo que nos ayuda a controlar la funcion de las teclas Y A VERIFICAR NUESTRAS COLOSIONES SEGUN LA MATRIZ LOGICA
void teclado(unsigned char key, int x, int y) {
  key=tolower(key);
  if(moverZ<48&&moverZ>-45&&moverX>-44&&moverX<50){
  switch (key) {
      case 'p':
      exit(0);
      break;
      case 'o':
      ejes=1;
      break;
      case 'i':
      ejes=0;
      break;
      case 'w':
//se comprueba el valor del angulo para que las teclas conserven su funcion ejemplo W=arriba desde el punto de vista que sea
          //rotar positivo
          if(xRotacion>=0 && xRotacion<=90){ if(matriz[(moverZ+50)-1][moverX+50]==0){moverZ--;}
          }else if(xRotacion>=91 && xRotacion<=180){if(matriz[moverZ+50][(moverX+50)+1]==0){moverX++;}
          }else if(xRotacion>=181 && xRotacion<=270){if(matriz[(moverZ+50)+1][moverX+50]==0){moverZ++;}
          }else if(xRotacion>=271 && xRotacion<=359){if(matriz[moverZ+50][(moverX+50)-1]==0){moverX--;}}
           //rotar negativo
          if(xRotacion<0 && xRotacion>=-90){if(matriz[moverZ+50][(moverX+50)-1]==0){moverX--;}
          }else if(xRotacion<=-91 && xRotacion>=-180){if(matriz[(moverZ+50)+1][moverX+50]==0){moverZ++;}
          }else if(xRotacion<=-181 && xRotacion>=-270){if(matriz[moverZ+50][(moverX+50)+1]==0){moverX++;}
          }else if(xRotacion<=-271 && xRotacion>=-359){if(matriz[(moverZ+50)-1][moverX+50]==0){moverZ--;}}
      break;
      case 's':
//se comprueba el valor del angulo para que las teclas conserven su funcion ejemplo s=abajo desde el punto de vista que sea
          if(xRotacion>=0 && xRotacion<=90){ if(matriz[(moverZ+50)+1][moverX+50]==0){moverZ++;}
          }else if(xRotacion>=91 && xRotacion<=180){if(matriz[moverZ+50][(moverX+50)-1]==0){moverX--;}
          }else if(xRotacion>=181 && xRotacion<=270){if(matriz[(moverZ+50)-1][moverX+50]==0){moverZ--;}
          }else if(xRotacion>=271 && xRotacion<=359){ if(matriz[moverZ+50][(moverX+50)+1]==0){moverX++;}}
           //rotar negativo
          if(xRotacion<0 && xRotacion>=-90){ if(matriz[moverZ+50][(moverX+50)+1]==0){moverX++;}
          }else if(xRotacion<=-91 && xRotacion>=-180){if(matriz[(moverZ+50)-1][moverX+50]==0){moverZ--;}
          }else if(xRotacion<=-181 && xRotacion>=-270){if(matriz[moverZ+50][(moverX+50)-1]==0){moverX--;}
          }else if(xRotacion<=-271 && xRotacion>=-359){if(matriz[(moverZ+50)+1][moverX+50]==0){moverZ++;}}
      break;
      case 'a':
//se comprueba el valor del angulo para que las teclas conserven su funcion ejemplo a=izquierda desde el punto de vista que sea
        if(xRotacion>=0 && xRotacion<=90){ if(matriz[moverZ+50][(moverX+50)-1]==0){moverX--;}
          }else if(xRotacion>=91 && xRotacion<=180){if(matriz[(moverZ+50)-1][moverX+50]==0){moverZ--;}
          }else if(xRotacion>=181 && xRotacion<=270){ if(matriz[moverZ+50][(moverX+50)+1]==0){moverX++;}
          }else if(xRotacion>=271 && xRotacion<=359){if(matriz[(moverZ+50)+1][moverX+50]==0){moverZ++;}}

          //rotar negativo
          if(xRotacion<0 && xRotacion>=-90){ if(matriz[(moverZ+50)+1][moverX+50]==0){moverZ++;}
          }else if(xRotacion<=-91 && xRotacion>=-180){ if(matriz[moverZ+50][(moverX+50)+1]==0){moverX++;}
          }else if(xRotacion<=-181 && xRotacion>=-270){if(matriz[(moverZ+50)-1][moverX+50]==0){moverZ--;}
          }else if(xRotacion<=-271 && xRotacion>=-359){if(matriz[moverZ+50][(moverX+50)-1]==0){moverX--;}}
      break;
      case 'd':
//se comprueba el valor del angulo para que las teclas conserven su funcion ejemplo d=derecha desde el punto de vista que sea
          if(xRotacion>=0 && xRotacion<=90){ if(matriz[moverZ+50][(moverX+50)+1]==0){moverX++;}
          }else if(xRotacion>=91 && xRotacion<=180){if(matriz[(moverZ+50)+1][moverX+50]==0){moverZ++;}
          }else if(xRotacion>=181 && xRotacion<=270){if(matriz[moverZ+50][(moverX+50)-1]==0){moverX--;}
          }else if(xRotacion>=271 && xRotacion<=359){if(matriz[(moverZ+50)-1][moverX+50]==0){moverZ--;}}

          //rotar negativo
          if(xRotacion<0 && xRotacion>=-90){ if(matriz[(moverZ+50)-1][moverX+50]==0){moverZ--;}
          }else if(xRotacion<=-91 && xRotacion>=-180){if(matriz[moverZ+50][(moverX+50)-1]==0){moverX--;}
          }else if(xRotacion<=-181 && xRotacion>=-270){if(matriz[(moverZ+50)+1][moverX+50]==0){moverZ++;}
          }else if(xRotacion<=-271 && xRotacion>=-359){if(matriz[moverZ+50][(moverX+50)+1]==0){moverX++;}}
      break;
      case '1':
          persovi=1;
          en[1]=3;
              ojo[1]=15;
              ojo[2]=3;

      break;
       case '3':
          persovi=0;
            ojo[1]=0;
              ojo[2] = 20;


      break;}
  glutPostRedisplay();
   }
       else{
            if(moverZ==48)moverZ--;
            if(moverZ==-45)moverZ++;
            if(moverX==-44)moverX++;
            if(moverX==50)moverX--;
       }
}

//metodo para manejar las teclas del ZOOM
void teclasespeciales(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_END: /* zoom aleja */
      ojo[0] = (1 + ZOOM_ELEMENTO) * ojo[0] - en[0] * ZOOM_ELEMENTO;
      ojo[1] = (1 + ZOOM_ELEMENTO) * ojo[1] - en[1] * ZOOM_ELEMENTO;
      ojo[2] = (1 + ZOOM_ELEMENTO) * ojo[2] - en[2] * ZOOM_ELEMENTO;
      break;
    case GLUT_KEY_HOME: /* zoom acerca */
      ojo[0] = (1 - ZOOM_ELEMENTO) * ojo[0] + en[0] * ZOOM_ELEMENTO;
      ojo[1] = (1 - ZOOM_ELEMENTO) * ojo[1] + en[1] * ZOOM_ELEMENTO;
      ojo[2] = (1 - ZOOM_ELEMENTO) * ojo[2] + en[2] * ZOOM_ELEMENTO;
      break;}
  glutPostRedisplay();
}

//metodo para actualizar el estado del mouse
void Mouse(int button, int state, int x, int y) {
  // actualiza el estado del mouse
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN)
      Estadomouse.ButonIzquierda = true;
    else
      Estadomouse.ButonIzquierda = false;
  }
  if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN)
      Estadomouse.ButonDerecha = true;
    else
      Estadomouse.ButonDerecha = false;
  }
  Estadomouse.x = x;
  Estadomouse.y = y;
}

//metodo que detecta el movimiento del mouse
void MouseMovimiento(int x, int y) {
  /* Calcular el desplazamiento del mouse */
  int xDelta =Estadomouse.x - x;
  int yDelta =Estadomouse.y - y;
  /* Guardar la posicion del mouse */
  Estadomouse.x = x;
  Estadomouse.y = y;
  /* que se detecte el moviento del mouse mientras se mueve el personaje */
  if (Estadomouse.ButonIzquierda) {
    xRotacion -= xDelta * GRADOS_POR_PIXEL;
  }
  glutPostRedisplay();
}

//metodo donde se inicializan la camara, la proyeccion
void myInit() {
  /* Proyeccion en perspectiva*/
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(120.0f, 1.0f, 0.1f, -10.0f);
  /* Inicializacion de la camara*/
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(ojo[0], ojo[1], ojo[2], en[0], en[1], en[2], 1, 1, 0);
  glEnable(GL_DEPTH_TEST);
}

//metodo main que incializa la ventana
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(700, 500);
  glutCreateWindow("CASAS DE LEGO");

  glutDisplayFunc(Display);
  glutKeyboardFunc(teclado);
  glutSpecialFunc(teclasespeciales);
  glutMouseFunc(Mouse);
  glutMotionFunc(MouseMovimiento);
  myInit();
  glutMainLoop();
}
