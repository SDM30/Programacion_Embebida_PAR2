#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NORMAL_COLOR    0xF0
#define BLACK_COLOR     0x10
#define RED_COLOR       0x20
#define GREEN_COLOR     0x30
#define YELLOW_COLOR    0x40
#define BLUE_COLOR      0x50
#define MAGENTA_COLOR   0x60
#define CYAN_COLOR      0x70
#define WHITE_COLOR     0x80


#define Pause() system("pause")
#define Cls()   system("cls")

typedef unsigned char uchar;

typedef unsigned int      uint;
typedef unsigned long int uint64;

typedef struct NumS NumT;
struct NumS
{
	uint   Num1;
	uint   Num2;
	uint64 Result;
};


void BackgroundColor (uchar FontColor,uchar BgColor);
void Delay           (int   Seconds                );
int  GetRandom		 (int min, int max			   );

//Linux
void Pausar();

#endif /* UTIL_H_ */
