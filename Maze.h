#ifndef MAZE_H_
#define MAZE_H_
#include "Util.h"
#include "Adventurer.h"
#define MAXADV 6

typedef struct Maze MazeT;
struct Maze
{
    char mapa[40][40];
    char desc[50];
    int numAventureros;
};

void ReadMatrix(int Rows, int Cols, char Matrix[Rows][Cols], char Verbose, char fileName[], char desc[]);
void imprMapa(int Filas, int Colums, char Mapa[Filas][Colums]);
MazeT selMapa();

#endif