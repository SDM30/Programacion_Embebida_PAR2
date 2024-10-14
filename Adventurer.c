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
        if (orientacion == 1) {
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
    aventurero->numGiros++;
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
    aventurero->numGiros+= 2;
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
    aventurero->numPasos++;
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

void backtrace(AdventurerT* aventurero, int memRuta[], char mapa[][40]) {
    CoordenadaT adelante, atras, izq, der;
    obtenerCasillas(aventurero, mapa);
    adelante = libreAdelante(aventurero, mapa);
    atras = libreAtras(aventurero, mapa);
    izq = libreIzq(aventurero, mapa);
    der = libreDer(aventurero, mapa);

    //printf("CASILLAS PARA BACKTRACE\n");
    //Recordar las rutas ya tomadas, no pueden ser muros
    if ( (der.posX != -1 && der.posY != -1) ) {
        memRuta[0] = aventurero->ruta[der.posY][der.posX];    // E
        //printf("Coordenada libre Derecha = (%d, %d)\n", der.posX, der.posY);
        //printf("Valor Derecha = %d\n",memRuta[0]);
    } else {
        memRuta[0] = -1;
    }

    if (adelante.posX != -1 && adelante.posY != -1) {
        memRuta[1] = aventurero->ruta[adelante.posY][adelante.posX];    // N
        //printf("Coordenada libre Adelante = (%d, %d)\n", adelante.posX, adelante.posY);
        //printf("Valor Adelante = %d\n",memRuta[1]);
    } else {
        memRuta[1] = -1;
    }

    if (izq.posX != -1 && izq.posY != -1) {
        memRuta[2] = aventurero->ruta[izq.posY][izq.posX];      // W
        //printf("Coordenada libre Izquierda = (%d, %d)\n", izq.posX, izq.posY);
        //printf("Valor Izquierda = %d\n",memRuta[2]);
    } else {
        memRuta[2] = -1;
    }


    if (atras.posX != -1 && atras.posY != -1) {
        memRuta[3] = aventurero->ruta[atras.posY][atras.posX];      // S
        //printf("Coordenada libre Atras = (%d, %d)\n", atras.posX, atras.posY);
        //printf("Valor Atras = %d\n",memRuta[3]);
    } else {
        memRuta[3] = -1;        
    }

}

CoordenadaT libreAdelante(AdventurerT* aventurero, char mapa[][40]) {
    // Verifica si hay camino libre hacia adelante basado en la dirección actual
    CoordenadaT libre = {-1,-1};
    int posX = aventurero->posicion.posX;
    int posY = aventurero->posicion.posY;

    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[0] == ' ') {
                libre.posX = posX;
                libre.posY = posY - 1;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[1] == ' ') {
                libre.posX = posX;
                libre.posY = posY + 1;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[2] == ' ') {
                libre.posX = posX - 1;
                libre.posY = posY;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[3] == ' ') {
                libre.posX = posX + 1;
                libre.posY = posY;
            }
            break;  
    }

    //printf("Coordenada libre Adelante = (%d, %d)\n", libre.posX, libre.posY);

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
    int posX = aventurero->posicion.posX;
    int posY = aventurero->posicion.posY;

    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[3] == ' ') {
                libre.posX = posX + 1;
                libre.posY = posY;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[2] == ' ') {
                libre.posX = posX - 1;
                libre.posY = posY;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[0] == ' ') {
                libre.posX = posX;
                libre.posY = posY - 1;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[1] == ' ') {
                libre.posX = posX;
                libre.posY = posY + 1;
            } 
            break; 
    }

    //printf("Coordenada libre Der = (%d, %d)\n", libre.posX, libre.posY);

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
    int posX = aventurero->posicion.posX;
    int posY = aventurero->posicion.posY;

    switch (aventurero->caracter) {
        case '^': //NORTE
            if (aventurero->casillas[2] == ' ') {
                libre.posX = posX - 1;
                libre.posY = posY;
            }
            break;  
        case 'v': //SUR
            if (aventurero->casillas[3] == ' ') {
                libre.posX = posX + 1;
                libre.posY = posY;
            }
            break;
        case '<': //W = Izq
            if (aventurero->casillas[1] == ' ') {
                libre.posX = posX;
                libre.posY = posY + 1;
            }
            break;
        case '>': // E = Der
            if (aventurero->casillas[0] == ' ') {
                libre.posX = posX;
                libre.posY = posY - 1;
            } 
            break; 
    }

    //printf("Coordenada libre Izq = (%d, %d)\n", libre.posX, libre.posY);
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
    //printf("Coordenada libre Atras = (%d, %d)\n", libre.posX, libre.posY);
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

void manoDerecha(AdventurerT* aventurero, char mapa[][40], int verbose) {
    
    CoordenadaT adelante, atras, izq, der;
    int extAdelante, extIzq, extDer, extDetras;
    int Limite = 2;
    for (int i = 0; i < Limite; i++) {
        int memRuta[4];
        //Casillas jugador
        obtenerCasillas(aventurero, mapa);
        adelante = libreAdelante(aventurero, mapa);
        atras = libreAtras(aventurero, mapa);
        izq = libreIzq(aventurero, mapa);
        der = libreDer(aventurero, mapa);
        //Revisar si hay salida
        extAdelante = salidaAdelante(aventurero, mapa);
        extIzq = salidaIzq(aventurero, mapa);
        extDer = salidaDer(aventurero, mapa);
        extDetras = salidaAtras(aventurero, mapa);

        //Priorizar casilla 
        backtrace(aventurero, memRuta, mapa);
        uint minVal = memRuta[0];
        for (int i = 0; i < 4; i++) {
            if ((memRuta[i] != -1) && (memRuta[i] <= minVal)) {
                minVal = memRuta[i];
            }
        }

        switch (aventurero->estadoAdv)
        {
            case Espera:
                if (verbose) {
                    printf("Tomando decisión...\n");
                }
                //Priorizar casilla 
                backtrace(aventurero, memRuta, mapa);
                if (verbose) {
                   printf("VALORES BACKTRACE\n"); 
                }

                for (int i = 0; i < 4; i++) {
                    if (verbose) {
                        printf("%d\n", memRuta[i]);
                    }
                    if ((memRuta[i] != -1) && (memRuta[i] <= minVal)) {
                        minVal = memRuta[i];
                    }
                }

                if (verbose) {
                    printf("MinVal Encontrado = %d\n",minVal);
                }

                // Verificar si alguna de las casillas es la salida
                if (extAdelante == 1) {
                    aventurero->estadoAdv = Moverse;
                    break;
                } else if (extIzq == 1) {
                    aventurero->estadoAdv = Girar;
                    break;
                } else if (extDer == 1) {
                    aventurero->estadoAdv = Girar;
                    break;
                } else if (extDetras == 1) {
                    aventurero->estadoAdv = Girar;
                    break;
                }
                //la derecha está libre, girar a la derecha
                if ( (der.posX != -1 && der.posY != -1) && (minVal == memRuta[0]) ) {
                    if (verbose) {
                        printf("Voy a la derecha\n");
                        printf("\tMemRuta = %d\n", memRuta[0]);
                    }
                    aventurero->estadoAdv = Girar;
                }
                // Si adelante está libre, avanzar
                else if ( (adelante.posX != -1 && adelante.posY != -1) && (minVal == memRuta[1]) ) {
                    if (verbose) {
                        printf("Voy a la adelante\n");
                        printf("\tMemRuta = %d\n", memRuta[1]);
                    }
                    aventurero->estadoAdv = Moverse;
                }
                // Si la izquierda está libre, girar a la izquierda
                else if ((izq.posX != -1 && izq.posY != -1) && (minVal == memRuta[2]) ) {
                    if (verbose) {
                        printf("Voy a la izquierda\n");
                        printf("\tMemRuta = %d\n", memRuta[2]);
                    }
                    aventurero->estadoAdv = Girar;
                }
                // Si atrás está libre, retroceder
                else if ( (atras.posX != -1 && atras.posY != -1) && (minVal == memRuta[3]) ) {
                    if (verbose) {
                        printf("Voy a la atras\n");
                        printf("\tMemRuta = %d\n", memRuta[3]);
                    }
                    aventurero->estadoAdv = Girar;
                }
                else {
                    if (verbose) {
                        printf("No se que hacer, voy a esperar...\n");
                    }
                    return;
                }
                break;
            
            case Moverse:
                extAdelante = salidaAdelante(aventurero, mapa);
                if (verbose) {
                    printf("Salida Adelante = %d\n", extAdelante);
                    printf("Me muevo...\n");
                }

                if (adelante.posX != -1 && adelante.posY != -1) {
                    // Actualizar la posición y la ruta
                    moverse(aventurero, mapa);
                    aventurero->estadoAdv = Espera;

                } else {
                    aventurero->estadoAdv = Girar;
                }

                if (extAdelante == 1) {
                    aventurero->estadoAdv = Salida;
                }
                break;
            
            case Girar:
                if (verbose) {
                printf("Debo girar...\n");
                }

                //Girar a la Salida
                if (extIzq == 1) {
                    if (verbose) {
                        printf("Salida a la izquierda\n");
                    }

                    girar90(aventurero, mapa, 1);
                    aventurero->estadoAdv = Moverse;
                    break;
                } else if (extDer == 1) {
                    if (verbose) {
                        printf("Salida a la Derecha\n");
                    }

                    girar90(aventurero, mapa, 0);
                    aventurero->estadoAdv = Moverse;
                    break;
                } else if (extDetras == 1) {
                    if (verbose) {
                        printf("Salida Detras\n");
                    }
                    
                    girar180(aventurero, mapa, 0);
                    aventurero->estadoAdv = Moverse;
                    break;
                }

                if ( (der.posX != -1 && der.posY != -1) && (minVal == memRuta[0]) ) {
                    if (verbose) {
                        printf("Hacia la derecha...\n");
                    }
                    // Si la derecha está libre, girar hacia la derecha
                    girar90(aventurero, mapa, 0);
                    aventurero->estadoAdv = Moverse;

                } else if ( (izq.posX != -1 && izq.posY != -1) && (minVal == memRuta[2]) ) {
                    if (verbose) {
                        printf("Hacia la izquierda...\n");
                    }
                    // Si la izquierda está libre, girar a la izquierda
                    girar90(aventurero, mapa, 1);
                    aventurero->estadoAdv = Moverse;

                } else if ((adelante.posX != -1 && adelante.posY != -1) && (minVal == memRuta[1]) ) {
                    aventurero->estadoAdv = Moverse; 

                } else if ((atras.posX != -1 && atras.posY != -1) && (minVal == memRuta[3])) {
                    if (verbose) {
                        printf("180...\n");
                    }
                    //Si atras esta libre, girar
                    girar180(aventurero, mapa, 0);
                    aventurero->estadoAdv = Moverse;
                }     
                break;   

            case Salida:
                printf("\n\nSaliendo del laberinto...\n");
                mapa[aventurero->posicion.posY][aventurero->posicion.posX] = ' ';
                return; 
        }
             
    }
 
}

void inicializarAventurero(char mapa[][40], int* numeroAven, AdventurerT aventureros[]) {
    //MANEJAR VARIOS AVENTUREROS
    int numAdv = 0, turno = 1;

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++){
            if (mapa[i][j] == 'N' || mapa[i][j] == 'S' || 
                mapa[i][j] == 'E' || mapa[i][j] == 'W') {

                AdventurerT adv1; 
            
                adv1.posicion.posX = j;
                adv1.posicion.posY = i;
                adv1.turno = turno;
                adv1.estadoAdv = Espera;
                adv1.numGiros = 0;
                adv1.numPasos = 0;

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

                //Inicializar miniMapa Aventurero
                for (int i = 0; i < 40; i++){
                    for (int j = 0; j < 40; j++) {
                        adv1.ruta[i][j] = 0;
                    }
                }
                aventureros[numAdv] = adv1;
                //Cambiar mapa general
                actualizarMapaChar(&adv1, mapa);
                //Aumentar numero de aventureros
                numAdv ++;
                turno ++;
                *numeroAven = numAdv;
            }  
        }
    }
}

void pruebaMapas() {
    MazeT Mapa = selMapa();
    //Si no se lee ningun mapa
    if (Mapa.numAventureros == 7) {return;}
    Mapa.numAventureros = 0;
    AdventurerT Aventurero[MAXADV];

    inicializarAventurero(Mapa.mapa,&Mapa.numAventureros, Aventurero);

    int salidas[Mapa.numAventureros];
    //Revisar estatus aventureros
    printf("Numero de aventureros leidos = %d \n",Mapa.numAventureros);
    for (int i = 0; i < Mapa.numAventureros; i++) {
        salidas[i] = 0;
        printf( "Aventurero con turno = %d \n"
                "Posicion = (%d,%d) \n", Aventurero[i].turno, Aventurero[i].posicion.posX, Aventurero[i].posicion.posY);
    }

    int turnoMapa = 0, todosSalieron = 0;

    while (todosSalieron == 0)
    {
        //Si el aventurero ya salio
        if (Aventurero[turnoMapa].estadoAdv == Salida) {
            salidas[turnoMapa] = 1;
        } else {
            Cls();
            printf("TURNO %d\n", Aventurero[turnoMapa].turno);
            manoDerecha(&Aventurero[turnoMapa], Mapa.mapa, 0);
            imprMapa(40, 40,Mapa.mapa);
        }
        manoDerecha(&Aventurero[turnoMapa], Mapa.mapa, 0);
        turnoMapa ++;
        turnoMapa = turnoMapa % Mapa.numAventureros;

        //todos los aventureros ya salieron
        int sum = 0;
        for (int i = 0; i < Mapa.numAventureros; i++) {
            sum += salidas[i];
        }
        if (sum == Mapa.numAventureros) {
            todosSalieron = 1;
            break;
        }
    }

    if (todosSalieron) {
        for (int i = 0; i < Mapa.numAventureros; i++) {
            printf( "Turno aventurero = %d \n"
                    "Numero de acciones = %d \n"
                    "Numero de Pasos Final = %d\n"
                    "Numero de Giros Final = %d\n"
                    "\n RUTA TOMADA POR AVENTURERO \n", 
                    Aventurero[i].turno, 
                    (Aventurero[i].numPasos + Aventurero[i].numGiros),
                    Aventurero[i].numPasos,
                    Aventurero[i].numGiros );

            for (int j = 0; j < 40; j++){
                for (int k = 0; k < 40; k++) {
                        if (Aventurero[i].ruta[j][k] != 0){
                        printf("%d",Aventurero[i].ruta[j][k]);
                    }else {
                        printf(" ");
                    }
                }
                printf("\n");
            }  
        }
    }
    Pausar();    
}
