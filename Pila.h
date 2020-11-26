#include <stdio.h>
#include <iostream>
using namespace std;
//clase PILA que nos ayuda a guardar las coordenadas y el color de dicho punto
class nodo {
    public:
    nodo(int x,int y,int z,int c ,nodo *sig = NULL) {
       valorX = x;
       valorY = y;
       valorZ= z;
       color=c;
       siguiente = sig;
    }

    public:
    int valorX, valorY,valorZ,color;
    nodo *siguiente;

    friend class Pila;
};

typedef nodo *pnodo;

class Pila {
   public:
    Pila() : ultimo(NULL) {}
    ~Pila();

    void push(int x, int y,int z,int c);
    int* pop();
    bool estaVacia();
    void printPila();

   private:
    pnodo ultimo;
};
Pila::~Pila() { /*while(ultimo) pop();*/}
//metodo para agregar un nueva nodo
void Pila::push(int x, int y, int z,int c) {
   pnodo nuevo;
   nuevo = new nodo(x, y,z,c, ultimo);
   ultimo = nuevo;
}
//metodo que regresa si la pila esta vacia
bool Pila::estaVacia()
{
    return (ultimo == NULL);
}
//metodo que nos regresa los valores de el nodo en la cima
int* Pila::pop() {
   pnodo nodo;
   if(estaVacia()) {
        throw "Pila vacia, no se puede extraer.";
        return 0;
   }else{
       int * a = new int[3];
       nodo = ultimo;
       a[0] = nodo->valorX;
       a[1] = nodo->valorY;
       a[2] = nodo->valorZ;
       a[3] = nodo->color;
       ultimo = nodo->siguiente;
       return a;
   }
}
//metodo para imprimir los puntos
void Pila::printPila(){
    pnodo nodo;
    nodo = ultimo;
    while(!(nodo==NULL)){
        int x = nodo->valorX;
        int y = nodo->valorY;
        int z = nodo->valorZ;
        int c = nodo->color;
         printf("(%d,%d)\n",x,y,z,c);
         nodo = nodo -> siguiente;
    }
}
