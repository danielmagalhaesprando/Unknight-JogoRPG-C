#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include "game.h"

//////////////////////////////////////////////////////////////////////
// Fun��es da aplica��o
//////////////////////////////////////////////////////////////////////
void initGame(gameData * game, int rows, int cols)
{
    game->ahrimaxlife = 50;
    game->ahrilife = game->ahrimaxlife;
    game->ahriattack = 10;

    game->ghostlife = 10;
    game->zombielife = 20;
    game->mermanlife = 30;
    game->vampirelife = 40;
    game->minotaurlife = 50;
    game->kinglife = 100;

    game->frame_ms = 100;

    game->pause = 0;
    game->house1 = 0;
    game->house2 = 0;
    game->house3 = 0;
    game->king = 0;

    game->SAMPLE_RATE = 44100;
    game->audioSampleNumber = 0;

    // ultimaTecla em -1 representa nenhuma tecla apertada
    game->ultimaTecla = -1;

    game->tick = 10;
    game->deadTick = 0;
}

void bestiary()
{
FILE *file = fopen("Bestiary.txt", "r");

int i,kills;
char leitor;
char num;

while(!feof(file))
{
    leitor = fgetc(file);
    if(leitor == ' ')num = num + 1;
}

fseek(file, 0, SEEK_SET);

int * bestiary = malloc(num*sizeof(int));

for(i = 0; i < num; i++)
{
    fscanf(file, "%d", &kills);
    bestiary[i] = kills;
    mvprintw(i*3+8, 5, "%d", bestiary[i]);
}

fclose(file);
free(bestiary);
}
