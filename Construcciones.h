#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <math.h>
#include "Pila.h"   //se implementa la clase pila

//CLASE EN LA CUAL SE LLENAN LAS PILAS CON LAS COORDENADAS SEGUN EL DISEÑO DEL EDIFICIO, O FIGURAS DENTRO DE LA ESCENA
//CADA METODO REGRESA UNA PILA LLENA DE PUNTOS EL COLOR DE CADA UNO
//DISEÑO EDIFICIO 1
Pila edi1(){
  Pila p;
  //cerca gris
  p.push(27,1,0,1);  p.push(27,1,-2,1);  p.push(27,1,-4,1);  p.push(27,1,-6,1);  p.push(27,1,-8,1);  p.push(27,1,-10,1);
  p.push(27,1,-12,1);  p.push(27,1,-14,1);  p.push(27,1,-16,1);  p.push(27,1,-18,1);
  p.push(41,1,0,1);  p.push(41,1,-2,1);  p.push(41,1,-4,1);  p.push(41,1,-6,1);  p.push(41,1,-8,1);  p.push(41,1,-10,1);
  p.push(41,1,-12,1);  p.push(41,1,-14,1);  p.push(41,1,-16,1);  p.push(41,1,-18,1);
  p.push(29,1,0,1);  p.push(31,1,0,1);  p.push(33,1,0,1);  p.push(35,1,0,1);  p.push(37,1,0,1);  p.push(39,1,0,1);
  p.push(29,1,-18,1);  p.push(31,1,-18,1);  p.push(33,1,-18,1);  p.push(35,1,-18,1);  p.push(37,1,-18,1);  p.push(39,1,-18,1);
   //piso
  for(int i=29;i<40;i++){
        for(int j=5;j<17;j++){  p.push(i,0,-j,1);}}
  //paredes
    for(int i=5;i<17;i++){
      p.push(29,1,-i,5); p.push(29,2,-i,5); p.push(29,6,-i,3); p.push(29,7,-i,2);
      p.push(39,1,-i,5); p.push(39,2,-i,5);
      p.push(39,3,-i,2); p.push(39,4,-i,3); p.push(39,5,-i,3); p.push(39,6,-i,3); p.push(39,7,-i,2);
    }
    for(int i=1;i<8;i++){
         p.push(30,i,-5,3); p.push(31,i,-5,3); p.push(36,i,-5,3); p.push(37,i,-5,3);  p.push(38,i,-5,3);
        p.push(30,i,-16,3); p.push(31,i,-16,3); p.push(32,i,-16,3); p.push(33,i,-16,3); p.push(34,i,-16,3);
        p.push(35,i,-16,3);  p.push(36,i,-16,3); p.push(37,i,-16,3);  p.push(38,i,-16,3);
    }
     p.push(32,7,-5,3);  p.push(33,7,-5,3);   p.push(34,7,-5,3);   p.push(35,7,-5,3);
     p.push(29,3,-6,2);  p.push(29,3,-5,2);    p.push(29,3,-7,2);
     p.push(29,3,-12,2);  p.push(29,3,-13,2);    p.push(29,3,-14,2);  p.push(29,3,-15,2);    p.push(29,3,-16,2);
     p.push(29,4,-6,3);  p.push(29,4,-5,3);    p.push(29,4,-7,3);
     p.push(29,4,-12,3);  p.push(29,4,-13,3);    p.push(29,4,-14,3);  p.push(29,4,-15,3);    p.push(29,4,-16,3);
      p.push(29,5,-6,3);  p.push(29,5,-5,3);    p.push(29,5,-7,3);
     p.push(29,5,-12,3);  p.push(29,5,-13,3);    p.push(29,5,-14,3);  p.push(29,5,-15,3);    p.push(29,5,-16,3);
   //techo

   for(int i=4;i<18;i++){
        p.push(28,8,-i,4); p.push(29,8,-i,4);  p.push(29,9,-i,4); p.push(30,9,-i,4);
       p.push(30,10,-i,4); p.push(31,10,-i,4);  p.push(31,11,-i,4); p.push(32,11,-i,4);
       p.push(32,12,-i,4); p.push(33,12,-i,4);  p.push(34,12,-i,4); p.push(35,12,-i,4); p.push(36,12,-i,4);

       p.push(39,8,-i,4); p.push(40,8,-i,4);  p.push(39,9,-i,4); p.push(38,9,-i,4);
       p.push(38,10,-i,4); p.push(37,10,-i,4);  p.push(37,11,-i,4);  p.push(36,11,-i,4);
   }
   for(int i=30;i<39;i++){p.push(i,8,-5,3); p.push(i,8,-17,3);} for(int i=32;i<37;i++){p.push(i,10,-5,3); p.push(i,10,-17,3);}
   for(int i=33;i<36;i++){p.push(i,11,-5,3); p.push(i,11,-17,3);}
   p.push(31,9,-17,3); p.push(32,9,-17,3);   p.push(36,9,-17,3); p.push(37,9,-17,3);
   p.push(31,9,-5,3); p.push(32,9,-5,3);   p.push(36,9,-5,3); p.push(37,9,-5,3);
   p.push(33,9,-5,6); p.push(34,9,-5,6);   p.push(35,9,-5,6);
   p.push(33,9,-17,6); p.push(34,9,-17,6);   p.push(35,9,-17,6);

   //adornos
   p.push(29,9,-13,3); p.push(29,9,-12,3);   p.push(29,9,-11,3); p.push(29,9,-10,3);
   p.push(29,10,-13,3); p.push(29,10,-12,3);   p.push(29,10,-11,3); p.push(29,10,-10,3);
   p.push(29,11,-12,3);   p.push(29,11,-11,3);
   p.push(29,11,-14,1); p.push(29,11,-13,1);   p.push(30,11,-14,1); p.push(30,11,-13,1);
   p.push(29,11,-10,1); p.push(29,11,-9,1);   p.push(30,11,-10,1); p.push(30,11,-9,1);
   p.push(29,12,-12,1); p.push(29,12,-11,1);   p.push(30,12,-12,1); p.push(30,12,-11,1);
   p.push(31,12,-12,1); p.push(31,12,-11,1);
  p.push(32,13,-15,1); p.push(32,13,-14,1);   p.push(33,13,-14,1); p.push(33,13,-15,1);
  p.push(32,14,-15,1); p.push(32,14,-14,1);   p.push(33,14,-14,1); p.push(33,14,-15,1);
  return p;

}
//DISEÑO EDIFICIO 2
Pila edi2(){
  Pila p;
  //cerca cafe
  p.push(2,1,0,1);  p.push(2,1,-2,1);  p.push(2,1,-4,1);  p.push(2,1,-6,1);  p.push(2,1,-8,1);  p.push(2,1,-10,1);
  p.push(4,1,0,1);  p.push(4,2,0,1);  p.push(4,3,0,1);
  p.push(10,1,0,1);  p.push(12,1,0,1);  p.push(14,1,0,1);  p.push(16,1,0,1);  p.push(18,1,0,1);
  p.push(18,1,-2,1);  p.push(18,1,-4,1);  p.push(18,1,-6,1);  p.push(18,1,-8,1);  p.push(18,1,-10,1);
  p.push(4,1,-10,1);  p.push(6,1,-10,1);  p.push(8,1,-10,1);  p.push(10,1,-10,1);  p.push(12,1,-10,1);  p.push(14,1,-10,1);  p.push(16,1,-10,1);
    for(int i=4;i<16;i++){
        for(int j=1;j<9;j++){  p.push(i,0,-j,6);}}
   for(int i=1;i<9;i++){
    for(int j=1;j<7;j++){
     p.push(4,j,-i,2);  p.push(15,j,-i,2);
   }}
    for(int i=4;i<16;i++){
    for(int j=1;j<7;j++){
     p.push(i,j,-8,2);
   }}
    //pared frontal
   for(int i=1;i<7;i++){p.push(5,i,-1,2); p.push(14,i,-1,2);}
   p.push(10,1,-1,2);  p.push(11,1,-1,2);  p.push(12,1,-1,2);  p.push(13,1,-1,2);
   p.push(10,2,-1,2);  p.push(11,2,-1,2);  p.push(12,2,-1,2);  p.push(13,2,-1,2);
   p.push(10,5,-1,2);  p.push(11,5,-1,2);  p.push(12,5,-1,2);  p.push(13,5,-1,2);
   p.push(10,6,-1,2);  p.push(11,6,-1,2);  p.push(12,6,-1,2);  p.push(13,6,-1,2);
   //pared frontal parte alta
   for(int i=5;i<15;i++){p.push(i,7,-1,2); p.push(i,7,-8,2);}  for(int i=6;i<14;i++){p.push(i,8,-1,2); p.push(i,8,-8,2);}
    for(int i=8;i<12;i++){p.push(i,10,-1,2); p.push(i,10,-8,2);}  for(int i=9;i<11;i++){p.push(i,11,-1,2); p.push(i,11,-8,2);}
     p.push(7,9,-1,2);  p.push(8,9,-1,2);   p.push(11,9,-1,2);  p.push(12,9,-1,2);
     p.push(7,9,-8,2);  p.push(8,9,-8,2);   p.push(11,9,-8,2);  p.push(12,9,-8,2);
     p.push(10,9,-1,5);  p.push(10,9,-8,5);   p.push(9,9,-1,5);  p.push(9,9,-8,5);
   //techo
     for(int i=0;i<10;i++){
        p.push(3,7,-i,3);  p.push(4,7,-i,3);   p.push(4,8,-i,3);  p.push(5,8,-i,3);
        p.push(5,9,-i,3);  p.push(6,9,-i,3);   p.push(6,10,-i,3);  p.push(7,10,-i,3);
        p.push(7,11,-i,3);  p.push(8,11,-i,3);   p.push(9,12,-i,3);  p.push(10,12,-i,3);
        p.push(15,7,-i,3);  p.push(16,7,-i,3);   p.push(15,8,-i,3);  p.push(14,8,-i,3);
        p.push(14,9,-i,3);  p.push(13,9,-i,3);   p.push(13,10,-i,3);  p.push(12,10,-i,3);
        p.push(12,11,-i,3);  p.push(11,11,-i,3);}
        //chimenea
         p.push(4,9,-4,1);  p.push(4,9,-5,1);   p.push(5,10,-4,1);
         p.push(4,10,-5,1);  p.push(4,10,-4,1);   p.push(5,10,-5,1);
  return p;
}
//DISEÑO LETRERO
Pila letrero(){
   Pila p;
    for(int i=37;i<46;i++){p.push(-41,1,i,1); p.push(-36,1,i,1); p.push(-31,1,i,1); p.push(-25,1,i,1);}
    for(int i=33;i<40;i++){p.push(-i,1,37,1);}
    for(int i=25;i<31;i++){p.push(-i,1,37,1); p.push(-i,1,45,1);}
   return p;
}
//DISEÑO DE LA LLAMA
Pila llama(){
  Pila p;
  p.push(29,1,-26,1);    p.push(29,2,-26,2);   p.push(29,3,-26,3);   p.push(29,4,-26,2);  p.push(29,5,-26,2);  p.push(29,6,-26,2);
  p.push(29,7,-26,4);    p.push(29,8,-26,5);
  p.push(29,1,-28,1);    p.push(29,2,-28,2);   p.push(29,3,-28,3);   p.push(29,4,-28,2);  p.push(29,5,-28,2);  p.push(29,6,-28,2);
  p.push(29,7,-28,4);    p.push(29,8,-28,5);
  p.push(30,3,-26,3);   p.push(31,3,-26,3);     p.push(30,4,-26,4);    p.push(31,4,-26,4);
  p.push(30,3,-28,3);   p.push(31,3,-28,3);     p.push(30,4,-28,4);    p.push(31,4,-28,4);
  p.push(32,1,-26,1);   p.push(32,2,-26,2);     p.push(32,3,-26,3);    p.push(32,4,-26,2);
  p.push(32,1,-28,1);   p.push(32,2,-28,2);     p.push(32,3,-28,3);    p.push(32,4,-28,2);
  p.push(29,3,-27,3);   p.push(29,4,-27,2);    p.push(29,5,-27,2);  p.push(29,6,-27,2);  p.push(29,7,-27,2);
  p.push(27,7,-26,2);   p.push(27,7,-27,2);    p.push(27,7,-28,2); p.push(28,7,-26,2);    p.push(28,7,-27,2);   p.push(28,7,-28,2);
  p.push(30,4,-27,2);   p.push(31,4,-27,2);    p.push(32,4,-27,2);  p.push(33,4,-27,5);  p.push(33,3,-27,5);
  return p;
}
//DISEÑO PIRAMIDA ESFINGE
Pila pesfinge(){
  Pila p;
    p.push(-14,2,-30,1);  p.push(-14,3,-30,1);   p.push(-12,2,-37,1);  p.push(-10,2,-34,1);  p.push(-10,3,-34,1);
     p.push(-10,2,-41,1);  p.push(-10,3,-41,1);  p.push(-10,4,-41,1);
     p.push(-6,2,-41,1);  p.push(-6,3,-41,2);   p.push(-5,2,-30,1);  p.push(-5,3,-30,2);
  return p;
}
//DISEÑO DEL PERSONAJE DENTRO DEL MAPA
Pila personaje(){
  Pila p;
    p.push(0,0,-1,1);   p.push(1,0,-1,1);     p.push(0,1,-1,5);   p.push(1,1,-1,5);
    p.push(0,2,-1,3);   p.push(1,2,-1,3);     p.push(0,3,-1,3);   p.push(1,3,-1,3);
    p.push(-1,3,-1,1);   p.push(2,3,-1,1);
  return p;
}
//DISEÑO EDIFICIO 4
Pila edi4(){
  Pila p;
    p.push(9,1,31,1);   p.push(14,1,31,1);  p.push(9,1,28,1);   p.push(14,1,28,1);
    p.push(9,2,31,1);   p.push(9,2,30,1);  p.push(9,2,29,1);   p.push(9,2,28,1);
    p.push(14,2,31,1);   p.push(14,2,30,1);  p.push(14,2,29,1);   p.push(14,2,28,1);
    p.push(10,7,32,2);   p.push(11,7,32,2); p.push(12,7,32,2); p.push(13,7,32,2);
    p.push(16,6,31,3);   p.push(17,6,31,3);
    for(int i=3;i<9;i++){
    p.push(i,17,31,4);   p.push(i,17,32,4);  p.push(i,18,32,4);  p.push(i,18,33,4);  p.push(i,19,33,4);
    p.push(i+12,17,31,4);   p.push(i+12,17,32,4);  p.push(i+12,18,32,4);  p.push(i+12,18,33,4);  p.push(i+12,19,33,4);
    }
    for(int i=3;i<21;i++){
    p.push(i,19,34,4);
    p.push(i,20,34,4);   p.push(i,20,35,4);  p.push(i,21,35,4);  p.push(i,21,36,4);  p.push(i,22,36,4);  p.push(i,22,37,4);
    p.push(i,23,37,4);   p.push(i,23,38,4);  p.push(i,24,38,4);  p.push(i,24,39,4);  p.push(i,25,39,4);
    p.push(i,25,40,4); p.push(i,24,40,4); p.push(i,24,41,4); p.push(i,23,41,4); p.push(i,23,42,4); p.push(i,22,42,4);
    p.push(i,22,43,4);  p.push(i,21,43,4);  p.push(i,21,44,4); p.push(i,20,44,4); p.push(i,20,45,4); p.push(i,19,45,4);
    p.push(i,19,46,4);  p.push(i,18,46,4);  p.push(i,18,47,4);  p.push(i,17,47,4);   p.push(i,17,48,4);
    }
     for(int i=33;i<47;i++){p.push(4,17,i,2);  p.push(19,17,i,2);}
     for(int i=34;i<46;i++){p.push(4,18,i,2);  p.push(19,18,i,2);}
     for(int i=35;i<45;i++){p.push(4,19,i,2);  p.push(19,19,i,2);}
     for(int i=36;i<44;i++){p.push(4,20,i,2);  p.push(19,20,i,2);}
     for(int i=37;i<43;i++){p.push(4,21,i,2);  p.push(19,21,i,2);}
     for(int i=38;i<42;i++){p.push(4,22,i,2);  p.push(19,22,i,2);}
     for(int i=39;i<41;i++){p.push(4,23,i,2);  p.push(19,23,i,2);}

     for(int i=31;i<38;i++){ p.push(8,21,i,5); p.push(9,21,i,5); p.push(9,22,i,5); p.push(10,22,i,5); p.push(10,23,i,5);
     p.push(11,23,i,5);  p.push(11,24,i,5); p.push(12,23,i,5); p.push(12,24,i,5);   p.push(13,23,i,5); p.push(13,22,i,5);  p.push(14,22,i,5);
      p.push(14,21,i,5);   p.push(15,21,i,5);
     }
  return p;
}
