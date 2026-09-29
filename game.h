#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#define MAX_SCREEN_SIZE 120


// Estrutura com estado interno da aplicação
typedef struct gameData
{
    int ahrilife;
    int ahrimaxlife;
    int ahriattack;

    int ghostlife;
    int zombielife;
    int mermanlife;
    int vampirelife;
    int minotaurlife;
    int kinglife;

    int ultimaTecla;

    unsigned int tick;
    unsigned int deadTick;

    unsigned int frame_ms;

    unsigned int SAMPLE_RATE;
    unsigned int audioSampleNumber;
    double audioTone;

    char pause;

    char house1;
    char house2;
    char house3;

    char king;

} gameData;

void initGame(gameData * game, int rows, int cols);

#endif // GAME_H_INCLUDED
