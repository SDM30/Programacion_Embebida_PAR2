#include "Adventurer.h"
#include <unistd.h> // LINUX DELAY

void actualizarMapaChar(AdventurerT* aventurero, char mapa[][40]) {
    int posX = aventurero->posicion.posX;
    int posY = aventurero->posicion.posY;
    mapa[posY][posX] = aventurero->caracter;
}

void actualizarMapaPos(AdventurerT* aventurero, char mapa[][40], int posXnueva, int posYnueva){
    int posXprev = aventurero->posicion.posX;
    int posYprev = aventurero->posicion.posY;
    //Reemplazar posicion anterior con un espacio
    mapa[posYprev][posXprev] = ' ';
    //aumentar valor de casilla en ruta
    aventurero->ruta[posYprev][posXprev] ++;
    //colocar adv en nueva posicion
    aventurero->posicion.posX = posXnueva;
    aventurero->posicion.posY = posYnueva;
    actualizarMapaChar(aventurero, mapa);
}

void girar90(AdventurerT* aventurero, char mapa[][40], int orientacion) {
    
    switch (aventurero->caracter) {
    case '^':
        if (orientacion == 1) {
            aventurero->caracter = '<';
        } else if (orientacion == 0) {
            aventurero->caracter = '>';
        }
        break;

    case '<':
        if (orientacion) {
            aventurero->caracter = 'v';
        } else if (orientacion == 0) {
            aventurero->caracter = '^';
        }
        break;

    case 'v':
        if (orientacion == 1) {
            aventurero->caracter = '>';
        } else if (orientacion == 0) {
            aventurero->caracter = '<';
        }
        break;

    case '>':
        if (orientacion) {
            aventurero->caracter = '^';
        } else if (orientacion == 0) {
            aventurero->caracter = 'v';
        }
        break;    
    }
    actualizarMapaChar(aventurero, mapa);
}

void girar180(AdventurerT* aventurero, char mapa[][40], int orientacion) {
    if (orientacion == 1) {
        girar90(aventurero, mapa, 1);
        girar90(aventurero, mapa, 1);
    } else if (orientacion == 0) {
        girar90(aventurero, mapa, 0);
        girar90(aventurero, mapa, 0);
    }
}

void moverse(AdventurerT* aventurero, char mapa[][40]) {

    int nuevaY = aventurero->posicion.posY;
    int nuevaX = aventurero->posicion.posX;

    switch (aventurero->caracter) {
    case '^':
        //Norte
        nuevaY --;
        break;

    case '<':
        //Occidente
        nuevaX --;
        break;

    case 'v':
        //Sur
        nuevaY ++;
        break;

    case '>':
        //Oriente
        nuevaX ++;
        break;    
    }

    actualizarMapaPos(aventurero, mapa, nuevaX, nuevaY);
}

void obtenerCasillas(AdventurerT* aventurero, char mapa[][40]) {
    int posX = aventurero->posicion.posX;
    int posY = aventurero->posicion.posY;
    //Actualizar casillas
    aventurero->casillas[0] = mapa[posY - 1][posX];//N
    aventurero->casillas[1] = mapa[posY + 1][posX];//S
    aventurero->casillas[2] = mapa[posY][posX - 1];//W = izq
    aventurero->casillas[3] = mapa[posY][posX + 1];//E = der    
}

CoordenadaT libreAdelante(AdventurerT* aventurero, char mapa[][40]) {
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    CoordenadaT libre = {-1,-1};
    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[0] == ' ') {
                libre = aventurero->posicion;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[1] == ' ') {
                libre = aventurero->posicion;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[2] == ' ') {
                libre = aventurero->posicion;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[3] == ' ') {
                libre = aventurero->posicion;
            }
            break;  
    }

    return libre;
}

int salidaAdelante(AdventurerT* aventurero, char mapa[][40]) {
    int haySalida = 0;
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[0] == 'O') {
                haySalida = 1;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[1] == 'O') {
                haySalida = 1;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[2] == 'O') {
                haySalida = 1;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[3] == 'O') {
                haySalida = 1;
            }
            break;  
    }

    return haySalida;
}

CoordenadaT libreDer(AdventurerT* aventurero, char mapa[][40]) {
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    CoordenadaT libre = {-1,-1};
    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[3] == ' ') {
                libre = aventurero->posicion;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[2] == ' ') {
                libre = aventurero->posicion;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[0] == ' ') {
                libre = aventurero->posicion;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[1] == ' ') {
                libre = aventurero->posicion;
            } 
            break; 
    }

    return libre;
}

int salidaDer(AdventurerT* aventurero, char mapa[][40]) {
    int haySalida = 0;
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[3] == 'O') {
                haySalida = 1;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[2] == 'O') {
                haySalida = 1;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[0] == 'O') {
                haySalida = 1;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[1] == 'O') {
                haySalida = 1;
            } 
            break; 
    }

    return haySalida;
}

CoordenadaT libreIzq(AdventurerT* aventurero, char mapa[][40]) {
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    CoordenadaT libre = {-1,-1};
    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[2] == ' ') {
                libre = aventurero->posicion;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[3] == ' ') {
                libre = aventurero->posicion;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[1] == ' ') {
                libre = aventurero->posicion;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[0] == ' ') {
                libre = aventurero->posicion;
            } 
            break; 
    }

    return libre;
}

int salidaIzq(AdventurerT* aventurero, char mapa[][40]) {
    int haySalida = 0;
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[2] == 'O') {
                haySalida = 1;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[3] == 'O') {
                haySalida = 1;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[1] == 'O') {
                haySalida = 1;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[0] == 'O') {
                haySalida = 1;
            } 
            break; 
    }

    return haySalida;
}

CoordenadaT libreAtras(AdventurerT* aventurero, char mapa[][40]) {
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    CoordenadaT libre = {-1,-1};
    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[1] == ' ') {
                libre = aventurero->posicion;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[0] == ' ') {
                libre = aventurero->posicion;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[3] == ' ') {
                libre = aventurero->posicion;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[2] == ' ') {
                libre = aventurero->posicion;
            } 
            break;
    }

    return libre;
}

int salidaAtras(AdventurerT* aventurero, char mapa[][40]) {
    int haySalida = 0;
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    switch (aventurero->caracter) {
        case '^': //NORTE
            if ( aventurero->casillas[1] == 'O') {
                haySalida = 1;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[0] == 'O') {
                haySalida = 1;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[3] == 'O') {
                haySalida = 1;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[2] == 'O') {
                haySalida = 1;
            } 
            break; 
    }

    return haySalida;    
}

void manoDerecha(AdventurerT* aventurero, char mapa[][40]) {
    static FSMadv Estado = Espera;
    CoordenadaT adelante, atras, izq, der;
    int extAdelante, extIzq, extDer, extDetras;
    while (1) {
        //Casillas jugador
        obtenerCasillas(aventurero, mapa);
        adelante = libreAdelante(aventurero, mapa);
        atras = libreAtras(aventurero, mapa);
        izq = libreIzq(aventurero, mapa);
        der = libreDer(aventurero, mapa);
        //Revisar si hay salida
        extAdelante = salidaAdelante(aventurero, mapa);
        printf("Salida Adelante = %d\n", extAdelante);
        extIzq = salidaIzq(aventurero, mapa);
        printf("Salida Izquierda = %d\n", extIzq);
        extDer = salidaDer(aventurero, mapa);
        printf("Salida Derecha = %d\n", extDer);
        extDetras = salidaAtras(aventurero, mapa);
        printf("Salida Atras = %d\n", extDetras);
        //Priorizar casilla 

        switch (Estado)
        {
            case Espera:
                printf("Tomando decisión...\n");

                // Verificar si alguna de las casillas es la salida
                //Cambiar a logica para salir
                // Verificar si alguna de las casillas es la salida
                if (extAdelante == 1) {
                    Estado = Moverse;
                    break;
                } else if (extIzq == 1) {
                    Estado = Girar;
                    break;
                } else if (extDer == 1) {
                    Estado = Girar;
                    break;
                } else if (extDetras == 1) {
                    Estado = Girar;
                    break;
                }

                //la derecha está libre, girar a la derecha
                if (der.posX != -1 && der.posY != -1) {
                    Estado = Girar;
                }
                // Si adelante está libre, avanzar
                else if (adelante.posX != -1 && adelante.posY != -1) {
                    Estado = Moverse;
                }
                // Si la izquierda está libre, girar a la izquierda
                else if (izq.posX != -1 && izq.posY != -1) {
                    Estado = Girar;
                }
                // Si atrás está libre, retroceder
                else if (atras.posX != -1 && atras.posY != -1) {
                    Estado = Moverse;
                }
                else {
                    Estado = Salida; // Salir si no hay opciones
                }
                break;
            
            case Moverse:
                extAdelante = salidaAdelante(aventurero, mapa);
                printf("Salida Adelante = %d\n", extAdelante);
                printf("Me muevo...\n");
                if (adelante.posX != -1 && adelante.posY != -1) {
                    // Actualizar la posición y la ruta
                    moverse(aventurero, mapa);
                    Estado = Espera;

                } else {
                    Estado = Girar;
                }

                if (extAdelante == 1) {
                    Estado = Salida;
                }
                break;
            
            case Girar:

                //Girar a la Salida
                if (extIzq == 1) {
                    girar90(aventurero, mapa, 0);
                    Estado = Moverse;
                    break;
                } else if (extDer == 1) {
                    girar90(aventurero, mapa, 1);
                    Estado = Moverse;
                    break;
                } else if (extDetras == 1) {
                    girar180(aventurero, mapa, 0);
                    Estado = Moverse;
                    break;
                }

                printf("Debo girar...");
                if (der.posX != -1 && der.posY != -1) {
                    printf("Hacia la derecha...\n");
                    // Si la derecha está libre, girar hacia la derecha
                    girar90(aventurero, mapa, 0);
                    Estado = Moverse;

                } else if (izq.posX != -1 && izq.posY != -1) {
                    printf("Hacia la izquierda...\n");
                    // Si la izquierda está libre, girar a la izquierda
                    girar90(aventurero, mapa, 1);
                    Estado = Moverse;

                } else if (adelante.posX != -1 && adelante.posY != -1) {
                    Estado = Moverse; 

                } else if (atras.posX != -1 && atras.posY != -1) {
                    printf("180...\n");
                    girar180(aventurero, mapa, 0);
                    Estado = Moverse;
                }     
                break;   

            case Salida:
                printf("Saliendo del laberinto...\n");
                mapa[aventurero->posicion.posY][aventurero->posicion.posX] = ' ';
                return; 
        }
        //Delay(3);
        sleep(0.5);
        imprMapa(40, 40,mapa);
        Cls();

        //Inicializar miniMapa Aventurero
        /*
        for (int i = 0; i < 40; i++){
            for (int j = 0; j < 40; j++) {
                printf("%d",aventurero->ruta[i][j]);
            }
            printf("\n");
        }  
        */      
    }
 
}

AdventurerT inicializarAventurero(char mapa[][40]) {
    //MANEJAR VARIOS AVENTUREROS
    AdventurerT adv1;

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++){
            if (mapa[i][j] == 'N' || mapa[i][j] == 'S' || 
                mapa[i][j] == 'E' || mapa[i][j] == 'W') { 
            
                adv1.posicion.posX = j;
                adv1.posicion.posY = i;
                adv1.turno = 1;

                //Inicializar casillas
                adv1.casillas[0] = mapa[i - 1][j];//N
                adv1.casillas[1] = mapa[i + 1][j];//S
                adv1.casillas[2] = mapa[i][j - 1];//W = izq
                adv1.casillas[3] = mapa[i][j + 1];//E = der

                switch (mapa[i][j])
                {
                    case 'N':
                        adv1.caracter = '^';
                        break;
                    
                    case 'S':
                        adv1.caracter = 'v';
                        break;
                    
                    case 'W':
                        adv1.caracter = '<';
                        break;

                    case 'E':
                        adv1.caracter = '>';
                        break;

                    default:
                        break;
                }

                //Cambiar mapa general
                actualizarMapaChar(&adv1, mapa);
            }  
        }
    }

    //Inicializar miniMapa Aventurero
    for (int i = 0; i < 40; i++){
        for (int j = 0; j < 40; j++) {
            adv1.ruta[i][j] = 0;
        }
    }

    return adv1;
}

void pruebaMapas() {
    MazeT Mapa = selMapa();
    AdventurerT Aventurero[6];
    //for() 
    //{
                // i
        Aventurero[0] = inicializarAventurero(Mapa.mapa);
        Aventurero->turno = 0;
        //Aventurero[], pasar indice a funcion para inicializar cada aventurero
    //}
    manoDerecha(&Aventurero[0], Mapa.mapa);        
    if (Aventurero[0].posicion.posX >= 40 || Aventurero[0].posicion.posY >= 40) {
        return;
    }
}
