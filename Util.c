#include "Util.h"

void BackgroundColor (uchar FontColor, uchar BgColor)
{
	char FG;
	char BG;
	if((FontColor == NORMAL_COLOR) || (BgColor == NORMAL_COLOR))
	{
		printf("\x1b[1;97;40m");
		return;
	}
	switch (FontColor)
	{
		case BLACK_COLOR:
		{
			FG = 30;
			break;
		}
		case RED_COLOR:
		{
			FG = 31;
			break;
		}
		case GREEN_COLOR:
		{
			FG = 32;
			break;
		}
		case YELLOW_COLOR:
		{
			FG = 33;
			break;
		}
		case BLUE_COLOR:
		{
			FG = 34;
			break;
		}
		case MAGENTA_COLOR:
		{
			FG = 35;
			break;
		}
		case CYAN_COLOR:
		{
			FG = 36;
			break;
		}
		case WHITE_COLOR:
		{
			FG = 37;
			break;
		}
	}
	switch (BgColor)
	{
		case BLACK_COLOR:
		{
			BG = 40;
			break;
		}
		case RED_COLOR:
		{
			BG = 41;
			break;
		}
		case GREEN_COLOR:
		{
			BG = 42;
			break;
		}
		case YELLOW_COLOR:
		{
			BG = 43;
			break;
		}
		case BLUE_COLOR:
		{
			BG = 44;
			break;
		}
		case MAGENTA_COLOR:
		{
			BG = 45;
			break;
		}
		case CYAN_COLOR:
		{
			BG = 46;
			break;
		}
		case WHITE_COLOR:
		{
			BG = 47;
			break;
		}
	}
	printf("\x1b[%d;%dm",FG,BG);
}

void Delay (int Seconds)
{
	int ms = 1000 * Seconds;
	clock_t StartTime = clock();
	while(clock() < (StartTime + ms))
	{
	}
}

int  GetRandom (int min, int max)
{
	srand(0);
	int RandNum = rand() % (max - min + 1) + min;
	return RandNum;
}

void Pausar() {
	char a;
	printf("Ingrese un caracter para continuar...\n");
	scanf(" %c", &a);
}