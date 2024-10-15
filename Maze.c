#include "Maze.h"

void ReadMatrix(int Rows, int Cols, char Matrix[Rows][Cols], char Verbose, char fileName[], char desc[])
{
    char C;
    int i = 0;
    int j = 0;
    int k = 0;

    FILE *TextFile;
    TextFile = fopen(fileName, "r");
    if(NULL == TextFile) {
        printf("No se logro abrir el archivo \n");
        return;
    }
    if (Verbose == 1) {
        printf("El contenido del archivo es :-: \n");
    }
    while ((C = fgetc(TextFile)) != EOF) {
        if (C == 0x0A) {
            i++;
            j = 0;
            if (i >= Rows) {
                break;
            } 
            if (Verbose == 1) {
                printf("\n");
            }

        } else {

            if (j < Cols) {
                Matrix[i][j] = C;
                if (Verbose == 1) {
                    printf("%c", C);
                }
                j++;
            }
        }
    }

    if (Verbose == 1) {
        printf("\n");
    }

    // Leer la descripción
    while ((C = fgetc(TextFile)) != EOF && k < 50) {
        desc[k++] = C;
        if (Verbose == 1) {
            printf("%c", C);
        }
    }
    desc[k] = '\0';

    if (Verbose == 1) {
        printf("\n");
    }
    fclose(TextFile);
}

void imprMapa(int Filas, int Colums, char Mapa[Filas][Colums]) {
    for (int i = 0; i < Filas; i++) {
        for (int j = 0; j < Colums; j++) {
            if (Mapa[i][j] == '*') {
                BackgroundColor(RED_COLOR,RED_COLOR);
                printf("%c%c",Mapa[i][j],Mapa[i][j]);
            }else if (Mapa[i][j] == ' ') {
                BackgroundColor(BLACK_COLOR,BLACK_COLOR);
                printf("%c%c",Mapa[i][j],Mapa[i][j]);                
            }else if (Mapa[i][j] == 'O') {
                BackgroundColor(GREEN_COLOR,GREEN_COLOR);
                printf("%c%c",Mapa[i][j],Mapa[i][j]);
            }else if (Mapa[i][j] == 'O') {
                BackgroundColor(GREEN_COLOR,GREEN_COLOR);
                printf("%c%c",Mapa[i][j],Mapa[i][j]);
            }else if (Mapa[i][j] == 'N' || Mapa[i][j] == 'S' || 
                      Mapa[i][j] == 'E' || Mapa[i][j] == 'W') {
                BackgroundColor(CYAN_COLOR,BLACK_COLOR);
                printf("%c%c",Mapa[i][j],Mapa[i][j]);
            } else if (Mapa[i][j] == '^' || Mapa[i][j] == 'v' ||
                       Mapa[i][j] == '<' || Mapa[i][j] == '>') {
                BackgroundColor(WHITE_COLOR,BLACK_COLOR);
                printf("%c%c",Mapa[i][j],Mapa[i][j]);
            }
        }
        BackgroundColor(WHITE_COLOR,BLACK_COLOR);
        printf("\n");
    }
    printf("\n");

}


MazeT selMapa() {

    MazeT Mapa1, Mapa2, Mapa3, Mapa4, MapaSel;
    ReadMatrix(40, 40, Mapa1.mapa, 0, "Map1.txt", Mapa1.desc);
    ReadMatrix(40, 40, Mapa2.mapa, 0, "Map2.txt", Mapa2.desc);
    ReadMatrix(40, 40, Mapa3.mapa, 0, "Map3.txt", Mapa3.desc);
    ReadMatrix(40, 40, Mapa4.mapa, 0, "Map4.txt", Mapa4.desc);

    MapaSel.numAventureros = 7;

    int opcion = -1;
    while (opcion != 0) {
        printf("1. Mapa 1: %s\n"
               "2. Mapa 2: %s\n"
               "3. Mapa 3: %s\n"
               "4. Mapa 4: %s\n"
               "0. Salir\n"
               "Opcion Usuario>>", Mapa1.desc, Mapa2.desc, Mapa3.desc, Mapa4.desc);
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            imprMapa(40,40, Mapa1.mapa);
            MapaSel = Mapa1;
            break;

        case 2:
            imprMapa(40,40, Mapa2.mapa);
            MapaSel = Mapa2;
            break;
        
        case 3:
            imprMapa(40,40, Mapa3.mapa);
            MapaSel = Mapa3;
            break;
        
        case 4:
            imprMapa(40,40, Mapa4.mapa);
            MapaSel = Mapa4;
            break;

        case 0:
            printf("PARCIAL FINALIZADO\n");
            break;

        default:
            printf("INGRESE UNA OPCION VALIDA\n");
            break;
        }
        return MapaSel;
    }
    return MapaSel;
}