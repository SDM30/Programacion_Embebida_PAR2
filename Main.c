#include "Util.h"
#include "Maze.h"
#include "Adventurer.h"

int main() {
    printf( "PARCIAL 2 -- Grupo 2 \n");
    int opcion = 0;

    while (opcion != 2) {
        Cls();
        printf( "OPCIONES:\n"
                "1.Cargar Mapas\n"
                "2.Salir del programa\n"
                "Entrada>> " );
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            pruebaMapas();
            break;

        case 2:
            printf("Programa Finalizado\n");
            break;
        
        default:
            printf("Ingrese un valor valido\n");
            break;
        }
    }
}