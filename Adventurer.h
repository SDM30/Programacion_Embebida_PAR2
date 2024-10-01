#ifndef ADVENTURER_H_
#define ADVENTURER_H_
#include "Util.h"
#include "Maze.h"

typedef enum{
    Espera,
    Girar,
    Moverse,
    Salida
}FSMadv;

typedef struct  Coordenada CoordenadaT;
struct Coordenada
{
    int posX;
    int posY;
};

typedef struct  Adventurer AdventurerT;
struct Adventurer
{
    char caracter; //^,v,<,>
    CoordenadaT posicion;
    uint numPasos;
    uint numGiros;
    char casillas[4]; //entorno del aventurero
    uint turno;
    int ruta[40][40];
};
void actualizarMapaChar(AdventurerT* aventurero, char mapa[][40]);
void actualizarMapaPos(AdventurerT* aventurero, char mapa[][40], int posXnueva, int posYnueva);
// 1 izquierda(W), 0 derecha(E)
void girar90(AdventurerT* aventurero, char mapa[][40], int orientacion);
void girar180(AdventurerT* aventurero, char mapa[][40], int orientacion);
void moverse(AdventurerT* aventurero, char mapa[][40]);
void obtenerCasillas(AdventurerT* aventurero, char mapa[][40]);

//AGREGAR FUNCION DE BACKTRACKING

//Revisar camino
CoordenadaT libreAdelante(AdventurerT* aventurero, char mapa[][40]);
int salidaAdelante(AdventurerT* aventurero, char mapa[][40]);
CoordenadaT libreDer(AdventurerT* aventurero, char mapa[][40]);
int salidaDer(AdventurerT* aventurero, char mapa[][40]);
CoordenadaT libreIzq(AdventurerT* aventurero, char mapa[][40]);
int salidaIzq(AdventurerT* aventurero, char mapa[][40]);
CoordenadaT libreAtras(AdventurerT* aventurero, char mapa[][40]);
int salidaAtras(AdventurerT* aventurero, char mapa[][40]);

//Cerebro Aventurero
void manoDerecha(AdventurerT* aventurero, char mapa[][40]);


void numeroAventureros(char mapa[][40]);
AdventurerT inicializarAventurero(char mapa[][40]);
void pruebaMapas();


#endif