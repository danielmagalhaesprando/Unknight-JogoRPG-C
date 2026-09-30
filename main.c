#include <math.h>
#include "graphics.h"
#include "game.h"
#include "sound.h"
#include <time.h>
#include <stdlib.h>

int tela = 4;

int x,y,i;

int gho = '0';
int zom = '0';
int mer = '0';
int vam = '0';
int min = '0';

int posicaox = 40;
int posicaoy = 20;

int level = 1;

int random_event = 0;
int randomattack = 0;
int randomloot = 0;
int action = 0;

int entrada = -1;

// Gerencia entradas do usu�rio e controla o estado interno em game
void handleInputs(gameData * game)
{
    srand((unsigned)time(NULL));

    while((entrada = getch()) != -1)
    {
        game->ultimaTecla = entrada;

        switch(entrada)
        {
            case 32:
                if(tela != 0)
                tela = tela - 1;
                break;

            case 10:
            case 459:
                if(tela != 0)
                tela = 0;
                break;

            case 'q':
            case 'Q':
                curs_set(1);
                endwin();
                exit(EXIT_SUCCESS);
                break;

            case 'p':
            case 'P':
                if(tela == 0 && random_event != 9 && random_event != 19 && (random_event != 29 || posicaox > 20) && (random_event != 39 || level < 2) && (random_event != 49 || level < 2) && game->king != 1)
                game->pause ^= 1;
                break;

            case 'e':
            case 'E':
                if(game->pause != 1)
                {
                    if((posicaox == 38 && posicaoy == 1) || (posicaox == 42 && posicaoy == 1) || (posicaox == 37 && posicaoy == 2) || (posicaox == 38 && posicaoy == 2) || (posicaox == 42 && posicaoy == 2) || (posicaox == 43 && posicaoy == 2) || (posicaox == 37 && posicaoy == 3) || (posicaox == 43 && posicaoy == 3) || (posicaox == 37 && posicaoy == 4) || (posicaox == 43 && posicaoy == 4) || (posicaox == 37 && posicaoy == 5) || (posicaox == 38 && posicaoy == 5) || (posicaox == 39 && posicaoy == 5) || (posicaox == 40 && posicaoy == 5) || (posicaox == 41 && posicaoy == 5) || (posicaox == 42 && posicaoy == 5) || (posicaox == 43 && posicaoy == 5))
                        if(game->king != 1)
                        {
                            game->king = 1;
                            game->tick = 10;
                            action = 0;
                        }
                    if(posicaox == 21 && posicaoy == 21)
                    {
                        game->ahrilife = game->ahrimaxlife;
                        game->tick = 10;
                        game->house1 ^= 1;
                    }
                    if(posicaox == 51 && posicaoy == 19)
                    {
                        game->ahrilife = game->ahrimaxlife;
                        game->tick = 10;
                        game->house2 ^= 1;
                    }
                    if(posicaox == 67 && posicaoy == 9)
                    {
                        game->ahrilife = game->ahrimaxlife;
                        game->tick = 10;
                        game->house3 ^= 1;
                    }
                }
                break;

            case 'r':
            case 'R':
                if(game->ahrilife < 1 || game->kinglife < 1)
                {
                    tela = 0;
                    game->tick = 10;
                    game->pause = 0;

                    posicaox = 40;
                    posicaoy = 20;

                    random_event = 0;
                    randomloot = 0;

                    level = 1;

                    game->house1 = 0;
                    game->house2 = 0;
                    game->house3 = 0;

                    game->ahrilife = 50;
                    game->ahrimaxlife = 50;
                    game->ahriattack = 10;
                    game->ghostlife = 10;
                    game->zombielife = 20;
                    game->mermanlife = 30;
                    game->vampirelife = 40;
                    game->minotaurlife = 50;
                    game->kinglife = 100;

                    game->king = 0;
                    action = 0;
                }
                break;

            case 'a':
            case 'A':
                if(tela == 0 && game->ahrilife > 0 && game->pause != 1)
                {
                    if(random_event == 9)
                    {
                        action = rand() % 5;

                        if(action != 1)
                            game->ghostlife = game->ghostlife - (game->ahriattack / 2);

                        if(action == 1)
                        {
                            game->ahrilife = game->ahrilife - 10;
                            game->ghostlife = game->ghostlife - game->ahriattack;
                        }
                    }

                    if(random_event == 19)
                    {
                        action = rand() %3;

                        if(action != 1)
                            game->zombielife = game->zombielife - (game->ahriattack / 2);

                        if(action == 1)
                        {
                            game->ahrilife = game->ahrilife - 10;
                            game->zombielife = game->zombielife - game->ahriattack;
                        }
                    }
                    if(random_event == 29)
                    {
                        action = rand() %5;

                        if(action != 1)
                            game->mermanlife = game->mermanlife - (game->ahriattack / 2);

                        if(action == 1)
                        {
                            game->ahrilife = game->ahrilife - 10;
                            game->mermanlife = game->mermanlife - game->ahriattack;
                        }
                    }
                    if(random_event == 39 && level == 2)
                    {
                        action = rand() %3;

                        if(action != 1)
                            game->vampirelife = game->vampirelife - (game->ahriattack / 2);

                        if(action == 1)
                        {
                            game->ahrilife = game->ahrilife - 20;
                            game->vampirelife = game->vampirelife - game->ahriattack;
                        }
                    }
                    if(random_event == 49 && level == 2)
                    {
                        action = rand() %5;

                        if(action != 1)
                            game->minotaurlife = game->minotaurlife - (game->ahriattack / 2);

                        if(action == 1)
                        {
                            game->ahrilife = game->ahrilife - 20;
                            game->minotaurlife = game->minotaurlife - game->ahriattack;
                        }
                    }
                    if(game->king == 1)
                    {
                        action = rand() %2;

                        if(action != 1)
                            game->kinglife = game->kinglife - (game->ahriattack / 2);

                        if(action == 1)
                        {
                            game->ahrilife = game->ahrilife - 30;
                            game->kinglife = game->kinglife - game->ahriattack;
                        }

                    }
                }
                break;

            case 'd':
            case 'D':
                if(tela == 0 && game->ahrilife > 0 && game->pause != 1)
                {
                    if(random_event == 9)
                    {
                        action = rand() % 5;

                        if(action == 1)
                            game->ahrilife = game->ahrilife - 5;
                    }

                    if(random_event == 19)
                    {
                        action = rand() %3;

                        if(action == 1)
                            game->ahrilife = game->ahrilife - 5;
                    }
                    if(random_event == 29)
                    {
                        action = rand() %5;

                        if(action == 1)
                            game->ahrilife = game->ahrilife - 5;
                    }
                    if(random_event == 39 && level == 2)
                    {
                        action = rand() %3;

                        if(action == 1)
                            game->ahrilife = game->ahrilife - 10;
                    }
                    if(random_event == 49 && level > 1)
                    {
                        action = rand() %5;

                        if(action == 1)
                            game->ahrilife = game->ahrilife - 10;

                    }
                    if(game->king == 1)
                    {
                        action = rand() %2;

                        if(action == 1)
                            game->ahrilife = game->ahrilife - 15;
                    }
                }
                break;

            case KEY_LEFT:
                if(game->pause == 0 && game->king == 0 && tela == 0)
                    if(random_event != 9 && random_event != 19 && (random_event != 29 || posicaox > 20) && (random_event != 39 || level < 2) && (random_event != 49 || level < 2) && game->house1 != 1 && game->house2 != 1 && game->house3 != 1 && (posicaox != 23 || posicaoy != 20) && (posicaox != 23 || posicaoy != 21) && (posicaox != 53 || posicaoy != 18) && (posicaox != 53 || posicaoy != 19) && (posicaox != 69 || posicaoy != 8) && (posicaox != 69 || posicaoy != 9) && (posicaox != 21 || posicaoy != 21) && (posicaox != 51 || posicaoy != 19) && (posicaox != 67 || posicaoy != 9) && (posicaox != 21 || posicaoy != 0) && (posicaox != 21 || posicaoy != 1) && (posicaox != 20 || posicaoy != 2) && (posicaox != 20 || posicaoy != 3) && (posicaox != 18 || posicaoy != 4) && (posicaox != 18 || posicaoy != 5) && (posicaox != 16 || posicaoy != 6) && (posicaox != 16 || posicaoy != 7) && (posicaox != 14 || posicaoy != 8) && (posicaox != 14 || posicaoy != 9) && (posicaox != 12 || posicaoy != 10) && (posicaox != 12 || posicaoy != 11) && (posicaox != 10 || posicaoy != 12) && (posicaox != 10 || posicaoy != 13) && (posicaox != 8 || posicaoy != 14) && (posicaox != 8 || posicaoy != 15) && (posicaox != 10 || posicaoy != 16) && (posicaox != 10 || posicaoy != 17) && (posicaox != 10 || posicaoy != 18) && (posicaox != 10 || posicaoy != 19) && (posicaox != 14 || posicaoy != 20) && (posicaox != 14 || posicaoy != 21) && (posicaox != 14 || posicaoy != 22) && (posicaox != 14 || posicaoy != 23) && (posicaox != 18 || posicaoy != 24) && (posicaox != 26 || posicaoy != 1) && (posicaox != 42 || posicaoy != 1) && (posicaox != 42 || posicaoy != 2) && (posicaox != 43 || posicaoy != 3) && (posicaox != 43 || posicaoy != 4) && (posicaox != 26 || posicaoy != 2) && (posicaox != 26 || posicaoy != 3) && (posicaox != 26 || posicaoy != 4) && (posicaox != 26 || posicaoy != 5) && (posicaox != 26 || posicaoy != 6) && (posicaox != 26 || posicaoy != 7) && (posicaox != 26 || posicaoy != 8) && (posicaox != 26 || posicaoy != 9) && (posicaox != 40 || posicaoy != 10) && (posicaox != 56 || posicaoy != 0) && (posicaox != 56 || posicaoy != 1) && (posicaox != 56 || posicaoy != 2) && (posicaox != 56 || posicaoy != 3) && (posicaox != 56 || posicaoy != 4) && (posicaox != 56 || posicaoy != 5) && (posicaox != 56 || posicaoy != 6) && (posicaox != 56 || posicaoy != 7) && (posicaox != 56 || posicaoy != 8) && (posicaox != 56 || posicaoy != 9) && (posicaox != 56 || posicaoy != 10))
                    {
                        game->tick = 1;

                        posicaox = posicaox - 1;

                        if((posicaox != 26 || posicaoy!= 1) && (posicaox != 27 || posicaoy!= 1) && (posicaox != 28 || posicaoy!= 1) && (posicaox != 29 || posicaoy!= 1) && (posicaox != 30 || posicaoy!= 1) && (posicaox != 31 || posicaoy!= 1) && (posicaox != 32 || posicaoy!= 1) && (posicaox != 33 || posicaoy!= 1) && (posicaox != 34 || posicaoy!= 1) && (posicaox != 35 || posicaoy!= 1) && (posicaox != 36 || posicaoy!= 1) && (posicaox != 37 || posicaoy!= 1) && (posicaox != 38 || posicaoy!= 1) && (posicaox != 42 || posicaoy!= 1) && (posicaox != 43 || posicaoy!= 1) && (posicaox != 44 || posicaoy!= 1) && (posicaox != 45 || posicaoy!= 1) && (posicaox != 46 || posicaoy!= 1) && (posicaox != 47 || posicaoy!= 1) && (posicaox != 48 || posicaoy!= 1) && (posicaox != 49 || posicaoy!= 1) && (posicaox != 50 || posicaoy!= 1) && (posicaox != 51 || posicaoy!= 1) && (posicaox != 52 || posicaoy!= 1) && (posicaox != 53 || posicaoy!= 1) && (posicaox != 54 || posicaoy!= 1) && (posicaox != 26 || posicaoy!= 2) && (posicaox != 27 || posicaoy!= 2) && (posicaox != 28 || posicaoy!= 2) && (posicaox != 29 || posicaoy!= 2) && (posicaox != 30 || posicaoy!= 2) && (posicaox != 31 || posicaoy!= 2) && (posicaox != 32 || posicaoy!= 2) && (posicaox != 33 || posicaoy!= 2) && (posicaox != 34 || posicaoy!= 2) && (posicaox != 35 || posicaoy!= 2) && (posicaox != 36 || posicaoy!= 2) && (posicaox != 37 || posicaoy!= 2) && (posicaox != 38 || posicaoy!= 2) && (posicaox != 42 || posicaoy!= 2) && (posicaox != 43 || posicaoy!= 2) && (posicaox != 44 || posicaoy!= 2) && (posicaox != 45 || posicaoy!= 2) && (posicaox != 46 || posicaoy!= 2) && (posicaox != 47 || posicaoy!= 2) && (posicaox != 48 || posicaoy!= 2) && (posicaox != 49 || posicaoy!= 2) && (posicaox != 50 || posicaoy!= 2) && (posicaox != 51 || posicaoy!= 2) && (posicaox != 52 || posicaoy!= 2) && (posicaox != 53 || posicaoy!= 2) && (posicaox != 54 || posicaoy!= 2) && (posicaox != 26 || posicaoy!= 3) && (posicaox != 27 || posicaoy!= 3) && (posicaox != 28 || posicaoy!= 3) && (posicaox != 29 || posicaoy!= 3) && (posicaox != 30 || posicaoy!= 3) && (posicaox != 31 || posicaoy!= 3) && (posicaox != 32 || posicaoy!= 3) && (posicaox != 33 || posicaoy!= 3) && (posicaox != 34 || posicaoy!= 3) && (posicaox != 35 || posicaoy!= 3) && (posicaox != 36 || posicaoy!= 3) && (posicaox != 37 || posicaoy!= 3) && (posicaox != 43 || posicaoy!= 3) && (posicaox != 44 || posicaoy!= 3) && (posicaox != 45 || posicaoy!= 3) && (posicaox != 46 || posicaoy!= 3) && (posicaox != 47 || posicaoy!= 3) && (posicaox != 48 || posicaoy!= 3) && (posicaox != 49 || posicaoy!= 3) && (posicaox != 50 || posicaoy!= 3) && (posicaox != 51 || posicaoy!= 3) && (posicaox != 52 || posicaoy!= 3) && (posicaox != 53 || posicaoy!= 3) && (posicaox != 54 || posicaoy!= 3) && (posicaox != 26 || posicaoy!= 4) && (posicaox != 27 || posicaoy!= 4) && (posicaox != 28 || posicaoy!= 4) && (posicaox != 29 || posicaoy!= 4) && (posicaox != 30 || posicaoy!= 4) && (posicaox != 31 || posicaoy!= 4) && (posicaox != 32 || posicaoy!= 4) && (posicaox != 33 || posicaoy!= 4) && (posicaox != 34 || posicaoy!= 4) && (posicaox != 35 || posicaoy!= 4) && (posicaox != 36 || posicaoy!= 4) && (posicaox != 37 || posicaoy!= 4) && (posicaox != 43 || posicaoy!= 4) && (posicaox != 44 || posicaoy!= 4) && (posicaox != 45 || posicaoy!= 4) && (posicaox != 46 || posicaoy!= 4) && (posicaox != 47 || posicaoy!= 4) && (posicaox != 48 || posicaoy!= 4) && (posicaox != 49 || posicaoy!= 4) && (posicaox != 50 || posicaoy!= 4) && (posicaox != 51 || posicaoy!= 4) && (posicaox != 52 || posicaoy!= 4) && (posicaox != 53 || posicaoy!= 4) && (posicaox != 54 || posicaoy!= 4) && (posicaox != 26 || posicaoy!= 5) && (posicaox != 27 || posicaoy!= 5) && (posicaox != 28 || posicaoy!= 5) && (posicaox != 29 || posicaoy!= 5) && (posicaox != 30 || posicaoy!= 5) && (posicaox != 31 || posicaoy!= 5) && (posicaox != 32 || posicaoy!= 5) && (posicaox != 33 || posicaoy!= 5) && (posicaox != 34 || posicaoy!= 5) && (posicaox != 35 || posicaoy!= 5) && (posicaox != 36 || posicaoy!= 5) && (posicaox != 37 || posicaoy!= 5) && (posicaox != 38 || posicaoy!= 5) && (posicaox != 39 || posicaoy != 5) && (posicaox != 40 || posicaoy != 5) && (posicaox != 41 || posicaoy != 5) && (posicaox != 42 || posicaoy!= 5) && (posicaox != 43 || posicaoy!= 5) && (posicaox != 44 || posicaoy!= 5) && (posicaox != 45 || posicaoy!= 5) && (posicaox != 46 || posicaoy!= 5) && (posicaox != 47 || posicaoy!= 5) && (posicaox != 48 || posicaoy!= 5) && (posicaox != 49 || posicaoy!= 5) && (posicaox != 50 || posicaoy!= 5) && (posicaox != 51 || posicaoy!= 5) && (posicaox != 52 || posicaoy!= 5) && (posicaox != 53 || posicaoy!= 5) && (posicaox != 54 || posicaoy!= 5) && (posicaox != 26 || posicaoy!= 6) && (posicaox != 27 || posicaoy!= 6) && (posicaox != 28 || posicaoy!= 6) && (posicaox != 29 || posicaoy!= 6) && (posicaox != 30 || posicaoy!= 6) && (posicaox != 31 || posicaoy!= 6) && (posicaox != 32 || posicaoy!= 6) && (posicaox != 33 || posicaoy!= 6) && (posicaox != 34 || posicaoy!= 6) && (posicaox != 35 || posicaoy!= 6) && (posicaox != 36 || posicaoy!= 6) && (posicaox != 37 || posicaoy!= 6) && (posicaox != 38 || posicaoy!= 6) && (posicaox != 39 || posicaoy != 6) && (posicaox != 40 || posicaoy != 6) && (posicaox != 41 || posicaoy != 6) && (posicaox != 42 || posicaoy!= 6) && (posicaox != 43 || posicaoy!= 6) && (posicaox != 44 || posicaoy!= 6) && (posicaox != 45 || posicaoy!= 6) && (posicaox != 46 || posicaoy!= 6) && (posicaox != 47 || posicaoy!= 6) && (posicaox != 48 || posicaoy!= 6) && (posicaox != 49 || posicaoy!= 6) && (posicaox != 50 || posicaoy!= 6) && (posicaox != 51 || posicaoy!= 6) && (posicaox != 52 || posicaoy!= 6) && (posicaox != 53 || posicaoy!= 6) && (posicaox != 54 || posicaoy!= 6) && (posicaox != 26 || posicaoy!= 7) && (posicaox != 27 || posicaoy!= 7) && (posicaox != 28 || posicaoy!= 7) && (posicaox != 29 || posicaoy!= 7) && (posicaox != 30 || posicaoy!= 7) && (posicaox != 31 || posicaoy!= 7) && (posicaox != 32 || posicaoy!= 7) && (posicaox != 33 || posicaoy!= 7) && (posicaox != 34 || posicaoy!= 7) && (posicaox != 35 || posicaoy!= 7) && (posicaox != 36 || posicaoy!= 7) && (posicaox != 37 || posicaoy!= 7) && (posicaox != 38 || posicaoy!= 7) && (posicaox != 39 || posicaoy != 7) && (posicaox != 40 || posicaoy != 7) && (posicaox != 41 || posicaoy != 7) && (posicaox != 42 || posicaoy!= 7) && (posicaox != 43 || posicaoy!= 7) && (posicaox != 44 || posicaoy!= 7) && (posicaox != 45 || posicaoy!= 7) && (posicaox != 46 || posicaoy!= 7) && (posicaox != 47 || posicaoy!= 7) && (posicaox != 48 || posicaoy!= 7) && (posicaox != 49 || posicaoy!= 7) && (posicaox != 50 || posicaoy!= 7) && (posicaox != 51 || posicaoy!= 7) && (posicaox != 52 || posicaoy!= 7) && (posicaox != 53 || posicaoy!= 7) && (posicaox != 54 || posicaoy!= 7) && (posicaox != 26 || posicaoy!= 8) && (posicaox != 27 || posicaoy!= 8) && (posicaox != 28 || posicaoy!= 8) && (posicaox != 29 || posicaoy!= 8) && (posicaox != 30 || posicaoy!= 8) && (posicaox != 31 || posicaoy!= 8) && (posicaox != 32 || posicaoy!= 8) && (posicaox != 33 || posicaoy!= 8) && (posicaox != 34 || posicaoy!= 8) && (posicaox != 35 || posicaoy!= 8) && (posicaox != 36 || posicaoy!= 8) && (posicaox != 37 || posicaoy!= 8) && (posicaox != 38 || posicaoy!= 8) && (posicaox != 39 || posicaoy != 8) && (posicaox != 40 || posicaoy != 8) && (posicaox != 41 || posicaoy != 8) && (posicaox != 42 || posicaoy!= 8) && (posicaox != 43 || posicaoy!= 8) && (posicaox != 44 || posicaoy!= 8) && (posicaox != 45 || posicaoy!= 8) && (posicaox != 46 || posicaoy!= 8) && (posicaox != 47 || posicaoy!= 8) && (posicaox != 48 || posicaoy!= 8) && (posicaox != 49 || posicaoy!= 8) && (posicaox != 50 || posicaoy!= 8) && (posicaox != 51 || posicaoy!= 8) && (posicaox != 52 || posicaoy!= 8) && (posicaox != 53 || posicaoy!= 8) && (posicaox != 54 || posicaoy!= 8) && (posicaox != 26 || posicaoy!= 9) && (posicaox != 27 || posicaoy!= 9) && (posicaox != 28 || posicaoy!= 9) && (posicaox != 29 || posicaoy!= 9) && (posicaox != 30 || posicaoy!= 9) && (posicaox != 31 || posicaoy!= 9) && (posicaox != 32 || posicaoy!= 9) && (posicaox != 33 || posicaoy!= 9) && (posicaox != 34 || posicaoy!= 9) && (posicaox != 35 || posicaoy!= 9) && (posicaox != 36 || posicaoy!= 9) && (posicaox != 37 || posicaoy!= 9) && (posicaox != 38 || posicaoy!= 9) && (posicaox != 39 || posicaoy != 9) && (posicaox != 40 || posicaoy != 9) && (posicaox != 41 || posicaoy != 9) && (posicaox != 42 || posicaoy!= 9) && (posicaox != 43 || posicaoy!= 9) && (posicaox != 44 || posicaoy!= 9) && (posicaox != 45 || posicaoy!= 9) && (posicaox != 46 || posicaoy!= 9) && (posicaox != 47 || posicaoy!= 9) && (posicaox != 48 || posicaoy!= 9) && (posicaox != 49 || posicaoy!= 9) && (posicaox != 50 || posicaoy!= 9) && (posicaox != 51 || posicaoy!= 9) && (posicaox != 52 || posicaoy!= 9) && (posicaox != 53 || posicaoy!= 9) && (posicaox != 54 || posicaoy!= 9) && (posicaox != 40 || posicaoy != 10))
                            random_event = rand() %50;
                    }
                break;

            case KEY_RIGHT:
                if(game->pause == 0 && game->king == 0 && tela == 0)
                    if(random_event != 9 && random_event != 19 && (random_event != 29 || posicaox > 20) && (random_event != 39 || level < 2) && (random_event != 49 || level < 2) && game->house1 != 1 && game->house2 != 1 && game->house3 != 1 && posicaox != 79 && (posicaox != 19 || posicaoy != 20) && (posicaox != 19 || posicaoy != 21) && (posicaox != 49 || posicaoy != 18) && (posicaox != 49 || posicaoy != 19) && (posicaox != 65 || posicaoy != 8) && (posicaox != 65 || posicaoy != 9) && (posicaox != 21 || posicaoy != 21) && (posicaox != 51 || posicaoy != 19) && (posicaox != 67 || posicaoy != 9) && (posicaox != 38 || posicaoy != 1) && (posicaox != 38 || posicaoy != 2) && (posicaox != 37 || posicaoy != 3) && (posicaox != 37 || posicaoy != 4) && (posicaox != 54 || posicaoy != 1) && (posicaox != 54 || posicaoy != 2) && (posicaox != 54 || posicaoy != 3) && (posicaox != 54 || posicaoy != 4) && (posicaox != 54 || posicaoy != 5) && (posicaox != 54 || posicaoy != 6) && (posicaox != 54 || posicaoy != 7) && (posicaox != 54 || posicaoy != 8) && (posicaox != 54 || posicaoy != 9) && (posicaox != 40 || posicaoy != 10) && (posicaox != 24 || posicaoy != 0)&&(posicaox != 24 || posicaoy != 1)&&(posicaox != 24 || posicaoy != 2)&&(posicaox != 24 || posicaoy != 3)&&(posicaox != 24 || posicaoy != 4)&&(posicaox != 24 || posicaoy != 5)&&(posicaox != 24 || posicaoy != 6)&&(posicaox != 24 || posicaoy != 7)&&(posicaox != 24 || posicaoy != 8)&&(posicaox != 24 || posicaoy != 9)&&(posicaox != 24 || posicaoy != 10))
                    {
                        game->tick = 1;

                        posicaox = posicaox + 1;

                        if((posicaox != 26 || posicaoy!= 1) && (posicaox != 27 || posicaoy!= 1) && (posicaox != 28 || posicaoy!= 1) && (posicaox != 29 || posicaoy!= 1) && (posicaox != 30 || posicaoy!= 1) && (posicaox != 31 || posicaoy!= 1) && (posicaox != 32 || posicaoy!= 1) && (posicaox != 33 || posicaoy!= 1) && (posicaox != 34 || posicaoy!= 1) && (posicaox != 35 || posicaoy!= 1) && (posicaox != 36 || posicaoy!= 1) && (posicaox != 37 || posicaoy!= 1) && (posicaox != 38 || posicaoy!= 1) && (posicaox != 42 || posicaoy!= 1) && (posicaox != 43 || posicaoy!= 1) && (posicaox != 44 || posicaoy!= 1) && (posicaox != 45 || posicaoy!= 1) && (posicaox != 46 || posicaoy!= 1) && (posicaox != 47 || posicaoy!= 1) && (posicaox != 48 || posicaoy!= 1) && (posicaox != 49 || posicaoy!= 1) && (posicaox != 50 || posicaoy!= 1) && (posicaox != 51 || posicaoy!= 1) && (posicaox != 52 || posicaoy!= 1) && (posicaox != 53 || posicaoy!= 1) && (posicaox != 54 || posicaoy!= 1) && (posicaox != 26 || posicaoy!= 2) && (posicaox != 27 || posicaoy!= 2) && (posicaox != 28 || posicaoy!= 2) && (posicaox != 29 || posicaoy!= 2) && (posicaox != 30 || posicaoy!= 2) && (posicaox != 31 || posicaoy!= 2) && (posicaox != 32 || posicaoy!= 2) && (posicaox != 33 || posicaoy!= 2) && (posicaox != 34 || posicaoy!= 2) && (posicaox != 35 || posicaoy!= 2) && (posicaox != 36 || posicaoy!= 2) && (posicaox != 37 || posicaoy!= 2) && (posicaox != 38 || posicaoy!= 2) && (posicaox != 42 || posicaoy!= 2) && (posicaox != 43 || posicaoy!= 2) && (posicaox != 44 || posicaoy!= 2) && (posicaox != 45 || posicaoy!= 2) && (posicaox != 46 || posicaoy!= 2) && (posicaox != 47 || posicaoy!= 2) && (posicaox != 48 || posicaoy!= 2) && (posicaox != 49 || posicaoy!= 2) && (posicaox != 50 || posicaoy!= 2) && (posicaox != 51 || posicaoy!= 2) && (posicaox != 52 || posicaoy!= 2) && (posicaox != 53 || posicaoy!= 2) && (posicaox != 54 || posicaoy!= 2) && (posicaox != 26 || posicaoy!= 3) && (posicaox != 27 || posicaoy!= 3) && (posicaox != 28 || posicaoy!= 3) && (posicaox != 29 || posicaoy!= 3) && (posicaox != 30 || posicaoy!= 3) && (posicaox != 31 || posicaoy!= 3) && (posicaox != 32 || posicaoy!= 3) && (posicaox != 33 || posicaoy!= 3) && (posicaox != 34 || posicaoy!= 3) && (posicaox != 35 || posicaoy!= 3) && (posicaox != 36 || posicaoy!= 3) && (posicaox != 37 || posicaoy!= 3) && (posicaox != 43 || posicaoy!= 3) && (posicaox != 44 || posicaoy!= 3) && (posicaox != 45 || posicaoy!= 3) && (posicaox != 46 || posicaoy!= 3) && (posicaox != 47 || posicaoy!= 3) && (posicaox != 48 || posicaoy!= 3) && (posicaox != 49 || posicaoy!= 3) && (posicaox != 50 || posicaoy!= 3) && (posicaox != 51 || posicaoy!= 3) && (posicaox != 52 || posicaoy!= 3) && (posicaox != 53 || posicaoy!= 3) && (posicaox != 54 || posicaoy!= 3) && (posicaox != 26 || posicaoy!= 4) && (posicaox != 27 || posicaoy!= 4) && (posicaox != 28 || posicaoy!= 4) && (posicaox != 29 || posicaoy!= 4) && (posicaox != 30 || posicaoy!= 4) && (posicaox != 31 || posicaoy!= 4) && (posicaox != 32 || posicaoy!= 4) && (posicaox != 33 || posicaoy!= 4) && (posicaox != 34 || posicaoy!= 4) && (posicaox != 35 || posicaoy!= 4) && (posicaox != 36 || posicaoy!= 4) && (posicaox != 37 || posicaoy!= 4) && (posicaox != 43 || posicaoy!= 4) && (posicaox != 44 || posicaoy!= 4) && (posicaox != 45 || posicaoy!= 4) && (posicaox != 46 || posicaoy!= 4) && (posicaox != 47 || posicaoy!= 4) && (posicaox != 48 || posicaoy!= 4) && (posicaox != 49 || posicaoy!= 4) && (posicaox != 50 || posicaoy!= 4) && (posicaox != 51 || posicaoy!= 4) && (posicaox != 52 || posicaoy!= 4) && (posicaox != 53 || posicaoy!= 4) && (posicaox != 54 || posicaoy!= 4) && (posicaox != 26 || posicaoy!= 5) && (posicaox != 27 || posicaoy!= 5) && (posicaox != 28 || posicaoy!= 5) && (posicaox != 29 || posicaoy!= 5) && (posicaox != 30 || posicaoy!= 5) && (posicaox != 31 || posicaoy!= 5) && (posicaox != 32 || posicaoy!= 5) && (posicaox != 33 || posicaoy!= 5) && (posicaox != 34 || posicaoy!= 5) && (posicaox != 35 || posicaoy!= 5) && (posicaox != 36 || posicaoy!= 5) && (posicaox != 37 || posicaoy!= 5) && (posicaox != 38 || posicaoy!= 5) && (posicaox != 39 || posicaoy != 5) && (posicaox != 40 || posicaoy != 5) && (posicaox != 41 || posicaoy != 5) && (posicaox != 42 || posicaoy!= 5) && (posicaox != 43 || posicaoy!= 5) && (posicaox != 44 || posicaoy!= 5) && (posicaox != 45 || posicaoy!= 5) && (posicaox != 46 || posicaoy!= 5) && (posicaox != 47 || posicaoy!= 5) && (posicaox != 48 || posicaoy!= 5) && (posicaox != 49 || posicaoy!= 5) && (posicaox != 50 || posicaoy!= 5) && (posicaox != 51 || posicaoy!= 5) && (posicaox != 52 || posicaoy!= 5) && (posicaox != 53 || posicaoy!= 5) && (posicaox != 54 || posicaoy!= 5) && (posicaox != 26 || posicaoy!= 6) && (posicaox != 27 || posicaoy!= 6) && (posicaox != 28 || posicaoy!= 6) && (posicaox != 29 || posicaoy!= 6) && (posicaox != 30 || posicaoy!= 6) && (posicaox != 31 || posicaoy!= 6) && (posicaox != 32 || posicaoy!= 6) && (posicaox != 33 || posicaoy!= 6) && (posicaox != 34 || posicaoy!= 6) && (posicaox != 35 || posicaoy!= 6) && (posicaox != 36 || posicaoy!= 6) && (posicaox != 37 || posicaoy!= 6) && (posicaox != 38 || posicaoy!= 6) && (posicaox != 39 || posicaoy != 6) && (posicaox != 40 || posicaoy != 6) && (posicaox != 41 || posicaoy != 6) && (posicaox != 42 || posicaoy!= 6) && (posicaox != 43 || posicaoy!= 6) && (posicaox != 44 || posicaoy!= 6) && (posicaox != 45 || posicaoy!= 6) && (posicaox != 46 || posicaoy!= 6) && (posicaox != 47 || posicaoy!= 6) && (posicaox != 48 || posicaoy!= 6) && (posicaox != 49 || posicaoy!= 6) && (posicaox != 50 || posicaoy!= 6) && (posicaox != 51 || posicaoy!= 6) && (posicaox != 52 || posicaoy!= 6) && (posicaox != 53 || posicaoy!= 6) && (posicaox != 54 || posicaoy!= 6) && (posicaox != 26 || posicaoy!= 7) && (posicaox != 27 || posicaoy!= 7) && (posicaox != 28 || posicaoy!= 7) && (posicaox != 29 || posicaoy!= 7) && (posicaox != 30 || posicaoy!= 7) && (posicaox != 31 || posicaoy!= 7) && (posicaox != 32 || posicaoy!= 7) && (posicaox != 33 || posicaoy!= 7) && (posicaox != 34 || posicaoy!= 7) && (posicaox != 35 || posicaoy!= 7) && (posicaox != 36 || posicaoy!= 7) && (posicaox != 37 || posicaoy!= 7) && (posicaox != 38 || posicaoy!= 7) && (posicaox != 39 || posicaoy != 7) && (posicaox != 40 || posicaoy != 7) && (posicaox != 41 || posicaoy != 7) && (posicaox != 42 || posicaoy!= 7) && (posicaox != 43 || posicaoy!= 7) && (posicaox != 44 || posicaoy!= 7) && (posicaox != 45 || posicaoy!= 7) && (posicaox != 46 || posicaoy!= 7) && (posicaox != 47 || posicaoy!= 7) && (posicaox != 48 || posicaoy!= 7) && (posicaox != 49 || posicaoy!= 7) && (posicaox != 50 || posicaoy!= 7) && (posicaox != 51 || posicaoy!= 7) && (posicaox != 52 || posicaoy!= 7) && (posicaox != 53 || posicaoy!= 7) && (posicaox != 54 || posicaoy!= 7) && (posicaox != 26 || posicaoy!= 8) && (posicaox != 27 || posicaoy!= 8) && (posicaox != 28 || posicaoy!= 8) && (posicaox != 29 || posicaoy!= 8) && (posicaox != 30 || posicaoy!= 8) && (posicaox != 31 || posicaoy!= 8) && (posicaox != 32 || posicaoy!= 8) && (posicaox != 33 || posicaoy!= 8) && (posicaox != 34 || posicaoy!= 8) && (posicaox != 35 || posicaoy!= 8) && (posicaox != 36 || posicaoy!= 8) && (posicaox != 37 || posicaoy!= 8) && (posicaox != 38 || posicaoy!= 8) && (posicaox != 39 || posicaoy != 8) && (posicaox != 40 || posicaoy != 8) && (posicaox != 41 || posicaoy != 8) && (posicaox != 42 || posicaoy!= 8) && (posicaox != 43 || posicaoy!= 8) && (posicaox != 44 || posicaoy!= 8) && (posicaox != 45 || posicaoy!= 8) && (posicaox != 46 || posicaoy!= 8) && (posicaox != 47 || posicaoy!= 8) && (posicaox != 48 || posicaoy!= 8) && (posicaox != 49 || posicaoy!= 8) && (posicaox != 50 || posicaoy!= 8) && (posicaox != 51 || posicaoy!= 8) && (posicaox != 52 || posicaoy!= 8) && (posicaox != 53 || posicaoy!= 8) && (posicaox != 54 || posicaoy!= 8) && (posicaox != 26 || posicaoy!= 9) && (posicaox != 27 || posicaoy!= 9) && (posicaox != 28 || posicaoy!= 9) && (posicaox != 29 || posicaoy!= 9) && (posicaox != 30 || posicaoy!= 9) && (posicaox != 31 || posicaoy!= 9) && (posicaox != 32 || posicaoy!= 9) && (posicaox != 33 || posicaoy!= 9) && (posicaox != 34 || posicaoy!= 9) && (posicaox != 35 || posicaoy!= 9) && (posicaox != 36 || posicaoy!= 9) && (posicaox != 37 || posicaoy!= 9) && (posicaox != 38 || posicaoy!= 9) && (posicaox != 39 || posicaoy != 9) && (posicaox != 40 || posicaoy != 9) && (posicaox != 41 || posicaoy != 9) && (posicaox != 42 || posicaoy!= 9) && (posicaox != 43 || posicaoy!= 9) && (posicaox != 44 || posicaoy!= 9) && (posicaox != 45 || posicaoy!= 9) && (posicaox != 46 || posicaoy!= 9) && (posicaox != 47 || posicaoy!= 9) && (posicaox != 48 || posicaoy!= 9) && (posicaox != 49 || posicaoy!= 9) && (posicaox != 50 || posicaoy!= 9) && (posicaox != 51 || posicaoy!= 9) && (posicaox != 52 || posicaoy!= 9) && (posicaox != 53 || posicaoy!= 9) && (posicaox != 54 || posicaoy!= 9) && (posicaox != 40 || posicaoy != 10))
                            random_event = rand() %50;
                    }
                break;

            case KEY_DOWN:
                if(game->pause == 0 && game->king == 0 && tela == 0)
                    if(random_event != 9 && random_event != 19 && (random_event != 29 || posicaox > 20) && (random_event != 39 || level < 2) && (random_event != 49 || level < 2) && game->house1 != 1 && game->house2 != 1 && game->house3 != 1 && posicaoy != 24 && (posicaox != 20 || posicaoy != 19) && (posicaox != 21 || posicaoy != 19) && (posicaox != 22 || posicaoy != 19) && (posicaox != 50 || posicaoy != 17) && (posicaox != 51 || posicaoy != 17) && (posicaox != 52 || posicaoy != 17) && (posicaox != 66 || posicaoy != 7) && (posicaox != 67 || posicaoy != 7) && (posicaox != 68 || posicaoy != 7) && (posicaox != 8 || posicaoy != 15) && (posicaox != 9 || posicaoy != 15) && (posicaox != 10 || posicaoy != 19) && (posicaox != 11 || posicaoy != 19) && (posicaox != 12 || posicaoy != 19) && (posicaox != 13 || posicaoy != 19) && (posicaox != 14 || posicaoy != 23) && (posicaox != 15 || posicaoy != 23) && (posicaox != 16 || posicaoy != 23) && (posicaox != 17 || posicaoy != 23) && (posicaox != 26 || posicaoy != 9) && (posicaox != 27 || posicaoy != 9) && (posicaox != 28 || posicaoy != 9) && (posicaox != 29 || posicaoy != 9) && (posicaox != 30 || posicaoy != 9) && (posicaox != 31 || posicaoy != 9) && (posicaox != 32 || posicaoy != 9) && (posicaox != 33 || posicaoy != 9) && (posicaox != 34 || posicaoy != 9) && (posicaox != 35 || posicaoy != 9) && (posicaox != 36 || posicaoy != 9) && (posicaox != 37 || posicaoy != 9) && (posicaox != 38 || posicaoy != 9) && (posicaox != 39 || posicaoy != 9) && (posicaox != 38 || posicaoy != 2) && (posicaox != 42 || posicaoy != 2) && (posicaox != 41 || posicaoy != 9) && (posicaox != 42 || posicaoy != 9) && (posicaox != 43 || posicaoy != 9) && (posicaox != 44 || posicaoy != 9) && (posicaox != 45 || posicaoy != 9) && (posicaox != 46 || posicaoy != 9) && (posicaox != 47 || posicaoy != 9) && (posicaox != 48 || posicaoy != 9) && (posicaox != 49 || posicaoy != 9) && (posicaox != 50 || posicaoy != 9) && (posicaox != 51 || posicaoy != 9) && (posicaox != 52 || posicaoy != 9) && (posicaox != 53 || posicaoy != 9) && (posicaox != 54 || posicaoy != 9))
                    {
                        game->tick = 1;

                        posicaoy = posicaoy + 1;

                        if((posicaox != 26 || posicaoy!= 1) && (posicaox != 27 || posicaoy!= 1) && (posicaox != 28 || posicaoy!= 1) && (posicaox != 29 || posicaoy!= 1) && (posicaox != 30 || posicaoy!= 1) && (posicaox != 31 || posicaoy!= 1) && (posicaox != 32 || posicaoy!= 1) && (posicaox != 33 || posicaoy!= 1) && (posicaox != 34 || posicaoy!= 1) && (posicaox != 35 || posicaoy!= 1) && (posicaox != 36 || posicaoy!= 1) && (posicaox != 37 || posicaoy!= 1) && (posicaox != 38 || posicaoy!= 1) && (posicaox != 42 || posicaoy!= 1) && (posicaox != 43 || posicaoy!= 1) && (posicaox != 44 || posicaoy!= 1) && (posicaox != 45 || posicaoy!= 1) && (posicaox != 46 || posicaoy!= 1) && (posicaox != 47 || posicaoy!= 1) && (posicaox != 48 || posicaoy!= 1) && (posicaox != 49 || posicaoy!= 1) && (posicaox != 50 || posicaoy!= 1) && (posicaox != 51 || posicaoy!= 1) && (posicaox != 52 || posicaoy!= 1) && (posicaox != 53 || posicaoy!= 1) && (posicaox != 54 || posicaoy!= 1) && (posicaox != 26 || posicaoy!= 2) && (posicaox != 27 || posicaoy!= 2) && (posicaox != 28 || posicaoy!= 2) && (posicaox != 29 || posicaoy!= 2) && (posicaox != 30 || posicaoy!= 2) && (posicaox != 31 || posicaoy!= 2) && (posicaox != 32 || posicaoy!= 2) && (posicaox != 33 || posicaoy!= 2) && (posicaox != 34 || posicaoy!= 2) && (posicaox != 35 || posicaoy!= 2) && (posicaox != 36 || posicaoy!= 2) && (posicaox != 37 || posicaoy!= 2) && (posicaox != 38 || posicaoy!= 2) && (posicaox != 42 || posicaoy!= 2) && (posicaox != 43 || posicaoy!= 2) && (posicaox != 44 || posicaoy!= 2) && (posicaox != 45 || posicaoy!= 2) && (posicaox != 46 || posicaoy!= 2) && (posicaox != 47 || posicaoy!= 2) && (posicaox != 48 || posicaoy!= 2) && (posicaox != 49 || posicaoy!= 2) && (posicaox != 50 || posicaoy!= 2) && (posicaox != 51 || posicaoy!= 2) && (posicaox != 52 || posicaoy!= 2) && (posicaox != 53 || posicaoy!= 2) && (posicaox != 54 || posicaoy!= 2) && (posicaox != 26 || posicaoy!= 3) && (posicaox != 27 || posicaoy!= 3) && (posicaox != 28 || posicaoy!= 3) && (posicaox != 29 || posicaoy!= 3) && (posicaox != 30 || posicaoy!= 3) && (posicaox != 31 || posicaoy!= 3) && (posicaox != 32 || posicaoy!= 3) && (posicaox != 33 || posicaoy!= 3) && (posicaox != 34 || posicaoy!= 3) && (posicaox != 35 || posicaoy!= 3) && (posicaox != 36 || posicaoy!= 3) && (posicaox != 37 || posicaoy!= 3) && (posicaox != 43 || posicaoy!= 3) && (posicaox != 44 || posicaoy!= 3) && (posicaox != 45 || posicaoy!= 3) && (posicaox != 46 || posicaoy!= 3) && (posicaox != 47 || posicaoy!= 3) && (posicaox != 48 || posicaoy!= 3) && (posicaox != 49 || posicaoy!= 3) && (posicaox != 50 || posicaoy!= 3) && (posicaox != 51 || posicaoy!= 3) && (posicaox != 52 || posicaoy!= 3) && (posicaox != 53 || posicaoy!= 3) && (posicaox != 54 || posicaoy!= 3) && (posicaox != 26 || posicaoy!= 4) && (posicaox != 27 || posicaoy!= 4) && (posicaox != 28 || posicaoy!= 4) && (posicaox != 29 || posicaoy!= 4) && (posicaox != 30 || posicaoy!= 4) && (posicaox != 31 || posicaoy!= 4) && (posicaox != 32 || posicaoy!= 4) && (posicaox != 33 || posicaoy!= 4) && (posicaox != 34 || posicaoy!= 4) && (posicaox != 35 || posicaoy!= 4) && (posicaox != 36 || posicaoy!= 4) && (posicaox != 37 || posicaoy!= 4) && (posicaox != 43 || posicaoy!= 4) && (posicaox != 44 || posicaoy!= 4) && (posicaox != 45 || posicaoy!= 4) && (posicaox != 46 || posicaoy!= 4) && (posicaox != 47 || posicaoy!= 4) && (posicaox != 48 || posicaoy!= 4) && (posicaox != 49 || posicaoy!= 4) && (posicaox != 50 || posicaoy!= 4) && (posicaox != 51 || posicaoy!= 4) && (posicaox != 52 || posicaoy!= 4) && (posicaox != 53 || posicaoy!= 4) && (posicaox != 54 || posicaoy!= 4) && (posicaox != 26 || posicaoy!= 5) && (posicaox != 27 || posicaoy!= 5) && (posicaox != 28 || posicaoy!= 5) && (posicaox != 29 || posicaoy!= 5) && (posicaox != 30 || posicaoy!= 5) && (posicaox != 31 || posicaoy!= 5) && (posicaox != 32 || posicaoy!= 5) && (posicaox != 33 || posicaoy!= 5) && (posicaox != 34 || posicaoy!= 5) && (posicaox != 35 || posicaoy!= 5) && (posicaox != 36 || posicaoy!= 5) && (posicaox != 37 || posicaoy!= 5) && (posicaox != 38 || posicaoy!= 5) && (posicaox != 39 || posicaoy != 5) && (posicaox != 40 || posicaoy != 5) && (posicaox != 41 || posicaoy != 5) && (posicaox != 42 || posicaoy!= 5) && (posicaox != 43 || posicaoy!= 5) && (posicaox != 44 || posicaoy!= 5) && (posicaox != 45 || posicaoy!= 5) && (posicaox != 46 || posicaoy!= 5) && (posicaox != 47 || posicaoy!= 5) && (posicaox != 48 || posicaoy!= 5) && (posicaox != 49 || posicaoy!= 5) && (posicaox != 50 || posicaoy!= 5) && (posicaox != 51 || posicaoy!= 5) && (posicaox != 52 || posicaoy!= 5) && (posicaox != 53 || posicaoy!= 5) && (posicaox != 54 || posicaoy!= 5) && (posicaox != 26 || posicaoy!= 6) && (posicaox != 27 || posicaoy!= 6) && (posicaox != 28 || posicaoy!= 6) && (posicaox != 29 || posicaoy!= 6) && (posicaox != 30 || posicaoy!= 6) && (posicaox != 31 || posicaoy!= 6) && (posicaox != 32 || posicaoy!= 6) && (posicaox != 33 || posicaoy!= 6) && (posicaox != 34 || posicaoy!= 6) && (posicaox != 35 || posicaoy!= 6) && (posicaox != 36 || posicaoy!= 6) && (posicaox != 37 || posicaoy!= 6) && (posicaox != 38 || posicaoy!= 6) && (posicaox != 39 || posicaoy != 6) && (posicaox != 40 || posicaoy != 6) && (posicaox != 41 || posicaoy != 6) && (posicaox != 42 || posicaoy!= 6) && (posicaox != 43 || posicaoy!= 6) && (posicaox != 44 || posicaoy!= 6) && (posicaox != 45 || posicaoy!= 6) && (posicaox != 46 || posicaoy!= 6) && (posicaox != 47 || posicaoy!= 6) && (posicaox != 48 || posicaoy!= 6) && (posicaox != 49 || posicaoy!= 6) && (posicaox != 50 || posicaoy!= 6) && (posicaox != 51 || posicaoy!= 6) && (posicaox != 52 || posicaoy!= 6) && (posicaox != 53 || posicaoy!= 6) && (posicaox != 54 || posicaoy!= 6) && (posicaox != 26 || posicaoy!= 7) && (posicaox != 27 || posicaoy!= 7) && (posicaox != 28 || posicaoy!= 7) && (posicaox != 29 || posicaoy!= 7) && (posicaox != 30 || posicaoy!= 7) && (posicaox != 31 || posicaoy!= 7) && (posicaox != 32 || posicaoy!= 7) && (posicaox != 33 || posicaoy!= 7) && (posicaox != 34 || posicaoy!= 7) && (posicaox != 35 || posicaoy!= 7) && (posicaox != 36 || posicaoy!= 7) && (posicaox != 37 || posicaoy!= 7) && (posicaox != 38 || posicaoy!= 7) && (posicaox != 39 || posicaoy != 7) && (posicaox != 40 || posicaoy != 7) && (posicaox != 41 || posicaoy != 7) && (posicaox != 42 || posicaoy!= 7) && (posicaox != 43 || posicaoy!= 7) && (posicaox != 44 || posicaoy!= 7) && (posicaox != 45 || posicaoy!= 7) && (posicaox != 46 || posicaoy!= 7) && (posicaox != 47 || posicaoy!= 7) && (posicaox != 48 || posicaoy!= 7) && (posicaox != 49 || posicaoy!= 7) && (posicaox != 50 || posicaoy!= 7) && (posicaox != 51 || posicaoy!= 7) && (posicaox != 52 || posicaoy!= 7) && (posicaox != 53 || posicaoy!= 7) && (posicaox != 54 || posicaoy!= 7) && (posicaox != 26 || posicaoy!= 8) && (posicaox != 27 || posicaoy!= 8) && (posicaox != 28 || posicaoy!= 8) && (posicaox != 29 || posicaoy!= 8) && (posicaox != 30 || posicaoy!= 8) && (posicaox != 31 || posicaoy!= 8) && (posicaox != 32 || posicaoy!= 8) && (posicaox != 33 || posicaoy!= 8) && (posicaox != 34 || posicaoy!= 8) && (posicaox != 35 || posicaoy!= 8) && (posicaox != 36 || posicaoy!= 8) && (posicaox != 37 || posicaoy!= 8) && (posicaox != 38 || posicaoy!= 8) && (posicaox != 39 || posicaoy != 8) && (posicaox != 40 || posicaoy != 8) && (posicaox != 41 || posicaoy != 8) && (posicaox != 42 || posicaoy!= 8) && (posicaox != 43 || posicaoy!= 8) && (posicaox != 44 || posicaoy!= 8) && (posicaox != 45 || posicaoy!= 8) && (posicaox != 46 || posicaoy!= 8) && (posicaox != 47 || posicaoy!= 8) && (posicaox != 48 || posicaoy!= 8) && (posicaox != 49 || posicaoy!= 8) && (posicaox != 50 || posicaoy!= 8) && (posicaox != 51 || posicaoy!= 8) && (posicaox != 52 || posicaoy!= 8) && (posicaox != 53 || posicaoy!= 8) && (posicaox != 54 || posicaoy!= 8) && (posicaox != 26 || posicaoy!= 9) && (posicaox != 27 || posicaoy!= 9) && (posicaox != 28 || posicaoy!= 9) && (posicaox != 29 || posicaoy!= 9) && (posicaox != 30 || posicaoy!= 9) && (posicaox != 31 || posicaoy!= 9) && (posicaox != 32 || posicaoy!= 9) && (posicaox != 33 || posicaoy!= 9) && (posicaox != 34 || posicaoy!= 9) && (posicaox != 35 || posicaoy!= 9) && (posicaox != 36 || posicaoy!= 9) && (posicaox != 37 || posicaoy!= 9) && (posicaox != 38 || posicaoy!= 9) && (posicaox != 39 || posicaoy != 9) && (posicaox != 40 || posicaoy != 9) && (posicaox != 41 || posicaoy != 9) && (posicaox != 42 || posicaoy!= 9) && (posicaox != 43 || posicaoy!= 9) && (posicaox != 44 || posicaoy!= 9) && (posicaox != 45 || posicaoy!= 9) && (posicaox != 46 || posicaoy!= 9) && (posicaox != 47 || posicaoy!= 9) && (posicaox != 48 || posicaoy!= 9) && (posicaox != 49 || posicaoy!= 9) && (posicaox != 50 || posicaoy!= 9) && (posicaox != 51 || posicaoy!= 9) && (posicaox != 52 || posicaoy!= 9) && (posicaox != 53 || posicaoy!= 9) && (posicaox != 54 || posicaoy!= 9) && (posicaox != 40 || posicaoy != 10))
                            random_event = rand() %50;
                    }
                break;

            case KEY_UP:
                if(game->pause == 0 == game->king == 0 && tela == 0)
                    if(random_event != 9 && random_event != 19 && (random_event != 29 || posicaox > 20) && (random_event != 39 || level < 2) && (random_event != 49 || level < 2) && game->house1 != 1 && game->house2 != 1 && game->house3 != 1 && posicaoy != 0 && (posicaox != 20 || posicaoy != 22) && (posicaox != 21 || posicaoy != 21) && (posicaox != 22 || posicaoy != 22) && (posicaox != 50 || posicaoy != 20) && (posicaox != 51 || posicaoy != 19) && (posicaox != 52 || posicaoy != 20) && (posicaox != 66 || posicaoy != 10) && (posicaox != 67 || posicaoy != 9) && (posicaox != 68 || posicaoy != 10) && (posicaox != 20 || posicaoy != 2) && (posicaox != 18 || posicaoy != 4) && (posicaox != 19 || posicaoy != 4) && (posicaox != 16 || posicaoy != 6) && (posicaox != 17 || posicaoy != 6) && (posicaox != 14 || posicaoy != 8) && (posicaox != 15 || posicaoy != 8) && (posicaox != 12 || posicaoy != 10) && (posicaox != 13 || posicaoy != 10) && (posicaox != 10 || posicaoy != 12) && (posicaox != 11 || posicaoy != 12) && (posicaox != 8 || posicaoy != 14) && (posicaox != 9 || posicaoy != 14) && (posicaox != 26 || posicaoy != 1) && (posicaox != 27 || posicaoy != 1) && (posicaox != 28 || posicaoy != 1) && (posicaox != 29 || posicaoy != 1) && (posicaox != 30 || posicaoy != 1) && (posicaox != 31 || posicaoy != 1) && (posicaox != 32 || posicaoy != 1) && (posicaox != 33 || posicaoy != 1) && (posicaox != 34 || posicaoy != 1) && (posicaox != 35 || posicaoy != 1) && (posicaox != 36 || posicaoy != 1) && (posicaox != 37 || posicaoy != 1) && (posicaox != 38 || posicaoy != 1) && (posicaox != 42 || posicaoy != 1) && (posicaox != 43 || posicaoy != 1) && (posicaox != 44 || posicaoy != 1) && (posicaox != 45 || posicaoy != 1) && (posicaox != 46 || posicaoy != 1) && (posicaox != 47 || posicaoy != 1) && (posicaox != 48 || posicaoy != 1) && (posicaox != 49 || posicaoy != 1) && (posicaox != 50 || posicaoy != 1) && (posicaox != 51 || posicaoy != 1) && (posicaox != 52 || posicaoy != 1) && (posicaox != 53 || posicaoy != 1) && (posicaox != 54 || posicaoy != 1) && (posicaox != 38 || posicaoy != 5) && (posicaox != 39 || posicaoy != 5) && (posicaox != 40 || posicaoy != 5) && (posicaox != 41 || posicaoy != 5) && (posicaox != 42 || posicaoy != 5) && (posicaox != 25 || posicaoy != 11) && (posicaox != 26 || posicaoy != 11) && (posicaox != 27 || posicaoy != 11) && (posicaox != 28 || posicaoy != 11) && (posicaox != 29 || posicaoy != 11) && (posicaox != 30 || posicaoy != 11) && (posicaox != 31 || posicaoy != 11) && (posicaox != 32 || posicaoy != 11) && (posicaox != 33 || posicaoy != 11) && (posicaox != 34 || posicaoy != 11) && (posicaox != 35 || posicaoy != 11) && (posicaox != 36 || posicaoy != 11) && (posicaox != 37 || posicaoy != 11) && (posicaox != 38 || posicaoy != 11) && (posicaox != 39 || posicaoy != 11) && (posicaox != 41 || posicaoy != 11) && (posicaox != 42 || posicaoy != 11) && (posicaox != 43 || posicaoy != 11) && (posicaox != 44 || posicaoy != 11) && (posicaox != 45 || posicaoy != 11) && (posicaox != 46 || posicaoy != 11) && (posicaox != 47 || posicaoy != 11) && (posicaox != 48 || posicaoy != 11) && (posicaox != 49 || posicaoy != 11) && (posicaox != 50 || posicaoy != 11) && (posicaox != 51 || posicaoy != 11) && (posicaox != 52 || posicaoy != 11) && (posicaox != 53 || posicaoy != 11) && (posicaox != 54 || posicaoy != 11) && (posicaox != 55 || posicaoy != 11))
                    {
                        game->tick = 1;

                        posicaoy = posicaoy - 1;

                        if((posicaox != 26 || posicaoy!= 1) && (posicaox != 27 || posicaoy!= 1) && (posicaox != 28 || posicaoy!= 1) && (posicaox != 29 || posicaoy!= 1) && (posicaox != 30 || posicaoy!= 1) && (posicaox != 31 || posicaoy!= 1) && (posicaox != 32 || posicaoy!= 1) && (posicaox != 33 || posicaoy!= 1) && (posicaox != 34 || posicaoy!= 1) && (posicaox != 35 || posicaoy!= 1) && (posicaox != 36 || posicaoy!= 1) && (posicaox != 37 || posicaoy!= 1) && (posicaox != 38 || posicaoy!= 1) && (posicaox != 42 || posicaoy!= 1) && (posicaox != 43 || posicaoy!= 1) && (posicaox != 44 || posicaoy!= 1) && (posicaox != 45 || posicaoy!= 1) && (posicaox != 46 || posicaoy!= 1) && (posicaox != 47 || posicaoy!= 1) && (posicaox != 48 || posicaoy!= 1) && (posicaox != 49 || posicaoy!= 1) && (posicaox != 50 || posicaoy!= 1) && (posicaox != 51 || posicaoy!= 1) && (posicaox != 52 || posicaoy!= 1) && (posicaox != 53 || posicaoy!= 1) && (posicaox != 54 || posicaoy!= 1) && (posicaox != 26 || posicaoy!= 2) && (posicaox != 27 || posicaoy!= 2) && (posicaox != 28 || posicaoy!= 2) && (posicaox != 29 || posicaoy!= 2) && (posicaox != 30 || posicaoy!= 2) && (posicaox != 31 || posicaoy!= 2) && (posicaox != 32 || posicaoy!= 2) && (posicaox != 33 || posicaoy!= 2) && (posicaox != 34 || posicaoy!= 2) && (posicaox != 35 || posicaoy!= 2) && (posicaox != 36 || posicaoy!= 2) && (posicaox != 37 || posicaoy!= 2) && (posicaox != 38 || posicaoy!= 2) && (posicaox != 42 || posicaoy!= 2) && (posicaox != 43 || posicaoy!= 2) && (posicaox != 44 || posicaoy!= 2) && (posicaox != 45 || posicaoy!= 2) && (posicaox != 46 || posicaoy!= 2) && (posicaox != 47 || posicaoy!= 2) && (posicaox != 48 || posicaoy!= 2) && (posicaox != 49 || posicaoy!= 2) && (posicaox != 50 || posicaoy!= 2) && (posicaox != 51 || posicaoy!= 2) && (posicaox != 52 || posicaoy!= 2) && (posicaox != 53 || posicaoy!= 2) && (posicaox != 54 || posicaoy!= 2) && (posicaox != 26 || posicaoy!= 3) && (posicaox != 27 || posicaoy!= 3) && (posicaox != 28 || posicaoy!= 3) && (posicaox != 29 || posicaoy!= 3) && (posicaox != 30 || posicaoy!= 3) && (posicaox != 31 || posicaoy!= 3) && (posicaox != 32 || posicaoy!= 3) && (posicaox != 33 || posicaoy!= 3) && (posicaox != 34 || posicaoy!= 3) && (posicaox != 35 || posicaoy!= 3) && (posicaox != 36 || posicaoy!= 3) && (posicaox != 37 || posicaoy!= 3) && (posicaox != 43 || posicaoy!= 3) && (posicaox != 44 || posicaoy!= 3) && (posicaox != 45 || posicaoy!= 3) && (posicaox != 46 || posicaoy!= 3) && (posicaox != 47 || posicaoy!= 3) && (posicaox != 48 || posicaoy!= 3) && (posicaox != 49 || posicaoy!= 3) && (posicaox != 50 || posicaoy!= 3) && (posicaox != 51 || posicaoy!= 3) && (posicaox != 52 || posicaoy!= 3) && (posicaox != 53 || posicaoy!= 3) && (posicaox != 54 || posicaoy!= 3) && (posicaox != 26 || posicaoy!= 4) && (posicaox != 27 || posicaoy!= 4) && (posicaox != 28 || posicaoy!= 4) && (posicaox != 29 || posicaoy!= 4) && (posicaox != 30 || posicaoy!= 4) && (posicaox != 31 || posicaoy!= 4) && (posicaox != 32 || posicaoy!= 4) && (posicaox != 33 || posicaoy!= 4) && (posicaox != 34 || posicaoy!= 4) && (posicaox != 35 || posicaoy!= 4) && (posicaox != 36 || posicaoy!= 4) && (posicaox != 37 || posicaoy!= 4) && (posicaox != 43 || posicaoy!= 4) && (posicaox != 44 || posicaoy!= 4) && (posicaox != 45 || posicaoy!= 4) && (posicaox != 46 || posicaoy!= 4) && (posicaox != 47 || posicaoy!= 4) && (posicaox != 48 || posicaoy!= 4) && (posicaox != 49 || posicaoy!= 4) && (posicaox != 50 || posicaoy!= 4) && (posicaox != 51 || posicaoy!= 4) && (posicaox != 52 || posicaoy!= 4) && (posicaox != 53 || posicaoy!= 4) && (posicaox != 54 || posicaoy!= 4) && (posicaox != 26 || posicaoy!= 5) && (posicaox != 27 || posicaoy!= 5) && (posicaox != 28 || posicaoy!= 5) && (posicaox != 29 || posicaoy!= 5) && (posicaox != 30 || posicaoy!= 5) && (posicaox != 31 || posicaoy!= 5) && (posicaox != 32 || posicaoy!= 5) && (posicaox != 33 || posicaoy!= 5) && (posicaox != 34 || posicaoy!= 5) && (posicaox != 35 || posicaoy!= 5) && (posicaox != 36 || posicaoy!= 5) && (posicaox != 37 || posicaoy!= 5) && (posicaox != 38 || posicaoy!= 5) && (posicaox != 39 || posicaoy != 5) && (posicaox != 40 || posicaoy != 5) && (posicaox != 41 || posicaoy != 5) && (posicaox != 42 || posicaoy!= 5) && (posicaox != 43 || posicaoy!= 5) && (posicaox != 44 || posicaoy!= 5) && (posicaox != 45 || posicaoy!= 5) && (posicaox != 46 || posicaoy!= 5) && (posicaox != 47 || posicaoy!= 5) && (posicaox != 48 || posicaoy!= 5) && (posicaox != 49 || posicaoy!= 5) && (posicaox != 50 || posicaoy!= 5) && (posicaox != 51 || posicaoy!= 5) && (posicaox != 52 || posicaoy!= 5) && (posicaox != 53 || posicaoy!= 5) && (posicaox != 54 || posicaoy!= 5) && (posicaox != 26 || posicaoy!= 6) && (posicaox != 27 || posicaoy!= 6) && (posicaox != 28 || posicaoy!= 6) && (posicaox != 29 || posicaoy!= 6) && (posicaox != 30 || posicaoy!= 6) && (posicaox != 31 || posicaoy!= 6) && (posicaox != 32 || posicaoy!= 6) && (posicaox != 33 || posicaoy!= 6) && (posicaox != 34 || posicaoy!= 6) && (posicaox != 35 || posicaoy!= 6) && (posicaox != 36 || posicaoy!= 6) && (posicaox != 37 || posicaoy!= 6) && (posicaox != 38 || posicaoy!= 6) && (posicaox != 39 || posicaoy != 6) && (posicaox != 40 || posicaoy != 6) && (posicaox != 41 || posicaoy != 6) && (posicaox != 42 || posicaoy!= 6) && (posicaox != 43 || posicaoy!= 6) && (posicaox != 44 || posicaoy!= 6) && (posicaox != 45 || posicaoy!= 6) && (posicaox != 46 || posicaoy!= 6) && (posicaox != 47 || posicaoy!= 6) && (posicaox != 48 || posicaoy!= 6) && (posicaox != 49 || posicaoy!= 6) && (posicaox != 50 || posicaoy!= 6) && (posicaox != 51 || posicaoy!= 6) && (posicaox != 52 || posicaoy!= 6) && (posicaox != 53 || posicaoy!= 6) && (posicaox != 54 || posicaoy!= 6) && (posicaox != 26 || posicaoy!= 7) && (posicaox != 27 || posicaoy!= 7) && (posicaox != 28 || posicaoy!= 7) && (posicaox != 29 || posicaoy!= 7) && (posicaox != 30 || posicaoy!= 7) && (posicaox != 31 || posicaoy!= 7) && (posicaox != 32 || posicaoy!= 7) && (posicaox != 33 || posicaoy!= 7) && (posicaox != 34 || posicaoy!= 7) && (posicaox != 35 || posicaoy!= 7) && (posicaox != 36 || posicaoy!= 7) && (posicaox != 37 || posicaoy!= 7) && (posicaox != 38 || posicaoy!= 7) && (posicaox != 39 || posicaoy != 7) && (posicaox != 40 || posicaoy != 7) && (posicaox != 41 || posicaoy != 7) && (posicaox != 42 || posicaoy!= 7) && (posicaox != 43 || posicaoy!= 7) && (posicaox != 44 || posicaoy!= 7) && (posicaox != 45 || posicaoy!= 7) && (posicaox != 46 || posicaoy!= 7) && (posicaox != 47 || posicaoy!= 7) && (posicaox != 48 || posicaoy!= 7) && (posicaox != 49 || posicaoy!= 7) && (posicaox != 50 || posicaoy!= 7) && (posicaox != 51 || posicaoy!= 7) && (posicaox != 52 || posicaoy!= 7) && (posicaox != 53 || posicaoy!= 7) && (posicaox != 54 || posicaoy!= 7) && (posicaox != 26 || posicaoy!= 8) && (posicaox != 27 || posicaoy!= 8) && (posicaox != 28 || posicaoy!= 8) && (posicaox != 29 || posicaoy!= 8) && (posicaox != 30 || posicaoy!= 8) && (posicaox != 31 || posicaoy!= 8) && (posicaox != 32 || posicaoy!= 8) && (posicaox != 33 || posicaoy!= 8) && (posicaox != 34 || posicaoy!= 8) && (posicaox != 35 || posicaoy!= 8) && (posicaox != 36 || posicaoy!= 8) && (posicaox != 37 || posicaoy!= 8) && (posicaox != 38 || posicaoy!= 8) && (posicaox != 39 || posicaoy != 8) && (posicaox != 40 || posicaoy != 8) && (posicaox != 41 || posicaoy != 8) && (posicaox != 42 || posicaoy!= 8) && (posicaox != 43 || posicaoy!= 8) && (posicaox != 44 || posicaoy!= 8) && (posicaox != 45 || posicaoy!= 8) && (posicaox != 46 || posicaoy!= 8) && (posicaox != 47 || posicaoy!= 8) && (posicaox != 48 || posicaoy!= 8) && (posicaox != 49 || posicaoy!= 8) && (posicaox != 50 || posicaoy!= 8) && (posicaox != 51 || posicaoy!= 8) && (posicaox != 52 || posicaoy!= 8) && (posicaox != 53 || posicaoy!= 8) && (posicaox != 54 || posicaoy!= 8) && (posicaox != 26 || posicaoy!= 9) && (posicaox != 27 || posicaoy!= 9) && (posicaox != 28 || posicaoy!= 9) && (posicaox != 29 || posicaoy!= 9) && (posicaox != 30 || posicaoy!= 9) && (posicaox != 31 || posicaoy!= 9) && (posicaox != 32 || posicaoy!= 9) && (posicaox != 33 || posicaoy!= 9) && (posicaox != 34 || posicaoy!= 9) && (posicaox != 35 || posicaoy!= 9) && (posicaox != 36 || posicaoy!= 9) && (posicaox != 37 || posicaoy!= 9) && (posicaox != 38 || posicaoy!= 9) && (posicaox != 39 || posicaoy != 9) && (posicaox != 40 || posicaoy != 9) && (posicaox != 41 || posicaoy != 9) && (posicaox != 42 || posicaoy!= 9) && (posicaox != 43 || posicaoy!= 9) && (posicaox != 44 || posicaoy!= 9) && (posicaox != 45 || posicaoy!= 9) && (posicaox != 46 || posicaoy!= 9) && (posicaox != 47 || posicaoy!= 9) && (posicaox != 48 || posicaoy!= 9) && (posicaox != 49 || posicaoy!= 9) && (posicaox != 50 || posicaoy!= 9) && (posicaox != 51 || posicaoy!= 9) && (posicaox != 52 || posicaoy!= 9) && (posicaox != 53 || posicaoy!= 9) && (posicaox != 54 || posicaoy!= 9) && (posicaox != 40 || posicaoy != 10))
                            random_event = rand()%50;
                    }
                break;

            case KEY_RESIZE:
                // Finaliza a tela atual e cria uma nova
                endwin();
                initScreen();

                clear();
                refresh();

                break;
        }
    }
}

void doUpdate(gameData * game)
{
    if(game->tick == 100)
        game->tick = 10;
    if(game->tick == 5)
        game->tick = 10;

    game->tick++;
}

void drawScreen(gameData * game)
{
    clear();

    //Tela inicial
    if(tela != 0)
    {
        menu();

        //Brilho da espada
        setColor(COLOR_WHITE, COLOR_WHITE, A_BOLD);
        if(game->tick > 30 && game->tick < 34){mvaddch(1, 40, ACS_BLOCK);mvaddch(2, 41, ACS_BLOCK);mvaddch(3, 42, ACS_BLOCK);}
        if(game->tick > 32 && game->tick < 36){mvaddch(2, 40, ACS_BLOCK);mvaddch(3, 41, ACS_BLOCK);mvaddch(4, 42, ACS_BLOCK);}
        if(game->tick > 34 && game->tick < 38){mvaddch(2, 39, ACS_BLOCK);mvaddch(3, 40, ACS_BLOCK);mvaddch(4, 41, ACS_BLOCK);mvaddch(5, 42, ACS_BLOCK);}
        if(game->tick > 36 && game->tick < 40){mvaddch(3, 39, ACS_BLOCK);mvaddch(4, 40, ACS_BLOCK);mvaddch(5, 41, ACS_BLOCK);mvaddch(6, 42, ACS_BLOCK);}
        if(game->tick > 38 && game->tick < 42){mvaddch(3, 38, ACS_BLOCK);mvaddch(4, 39, ACS_BLOCK);mvaddch(5, 40, ACS_BLOCK);mvaddch(6, 41, ACS_BLOCK);mvaddch(7, 42, ACS_BLOCK);}
        if(game->tick > 40 && game->tick < 44){mvaddch(4, 38, ACS_BLOCK);mvaddch(5, 39, ACS_BLOCK);mvaddch(6, 40, ACS_BLOCK);mvaddch(7, 41, ACS_BLOCK);mvaddch(8, 42, ACS_BLOCK);}
        if(game->tick > 42 && game->tick < 46){mvaddch(5, 38, ACS_BLOCK);mvaddch(6, 39, ACS_BLOCK);mvaddch(7, 40, ACS_BLOCK);mvaddch(8, 41, ACS_BLOCK);mvaddch(9, 42, ACS_BLOCK);}
        if(game->tick > 44 && game->tick < 48){mvaddch(6, 38, ACS_BLOCK);mvaddch(7, 39, ACS_BLOCK);mvaddch(8, 40, ACS_BLOCK);mvaddch(9, 41, ACS_BLOCK);mvaddch(10, 42, ACS_BLOCK);}
        if(game->tick > 46 && game->tick < 50){mvaddch(7, 38, ACS_BLOCK);mvaddch(8, 39, ACS_BLOCK);mvaddch(9, 40, ACS_BLOCK);mvaddch(10, 41, ACS_BLOCK);mvaddch(11, 42, ACS_BLOCK);}
        if(game->tick > 48 && game->tick < 52){mvaddch(8, 38, ACS_BLOCK);mvaddch(9, 39, ACS_BLOCK);mvaddch(10, 40, ACS_BLOCK);mvaddch(11, 41, ACS_BLOCK);}
        if(game->tick > 50 && game->tick < 54){mvaddch(9, 38, ACS_BLOCK);mvaddch(10, 39, ACS_BLOCK);mvaddch(11, 40, ACS_BLOCK);}
        if(game->tick > 52 && game->tick < 56){mvaddch(10, 38, ACS_BLOCK);mvaddch(11, 39, ACS_BLOCK);}
        if(game->tick > 54 && game->tick < 58)mvaddch(11, 38, ACS_BLOCK);

        //Jogar
        setColor(COLOR_BLACK, COLOR_BLACK, A_BOLD);
        mvprintw(0, 0, "Daniel Magalhaes Prando");mvprintw(0, 54, "Fundamentos de Programacao");
        mvprintw(24, 0, "Press SPACE to continue");mvprintw(24, 55, "Press ENTER to skip story.");
    }

    //T�tulo
    if(tela == 4)
        titulo();

    //Historia
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if(tela == 3)mvprintw(18, 0, "Once upon a time, there was a hero named Ahri.\n\nHe was the most loyal knight of the kingdom of Albendia.\n\nThe kingdom was peaceful and prosper.");
    if(tela == 2)mvprintw(18, 0, "One day, came an army of monsters, ruled by an Evil King.\n\nThey attacked Albendia in an attempt to rule all of the land.");
    if(tela == 1)mvprintw(18, 0, "The soldiers of Albendia fought back, but they were at a major disadvantage.\n\nAs the battle continued, it seemed all was lost.\n\nBut the bravest of the knights, Ahri, refused to give up hope!");

//Jogo
if(tela == 0)
{
mapa();

//Desenha o Personagem
setColor(COLOR_WHITE, COLOR_WHITE, A_BOLD);
mvaddch(posicaoy, posicaox, ACS_BLOCK);

    //Fantasma
    if(random_event == 9 && game->ghostlife > 0)
    {
    ghost();

    //Status da luta
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if(game->ghostlife == 10 && game->ultimaTecla != 'a' && game->ultimaTecla != 'A' && game->ultimaTecla != 'd' && game->ultimaTecla != 'D')mvprintw(24, 0, "A ghost finds you!");

    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action != 1){mvprintw(23, 0, "You attacked the ghost!");mvprintw(24, 0, "The ghost didn't attack you.");}
    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action == 1){mvprintw(23, 0, "You attacked the ghost!");mvprintw(24, 0, "The ghost hit you back.");}

    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action != 1){mvprintw(23, 0, "You didn't attack!");mvprintw(24, 0, "The ghost didn't attack you either.");}
    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action == 1){mvprintw(23, 0, "You defended!");mvprintw(24, 0, "The ghost's attack was less effective.");}

    //Status do fantasma
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(4, 59, ACS_SSBB);mvaddch(4, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(4, x, ACS_BSBS);}
    for(y = 1; y < 4; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Name: Ghost        ");mvprintw(2,60,"Life: %d           ",game->ghostlife);mvprintw(3,60,"Attack: 10         ");
    }

    //Quando Fantasma morrer, pode spawnar de novo, e pode dropar upgrade
    if(game->ghostlife < 1)
    {
        gho = gho + 1;
        random_event = 0;
        game->ghostlife = 10;
        randomloot = rand() %5;

        game->tick = 10;
    }

    //Zumbi
    if(random_event == 19 && game->zombielife > 0)
    {
    zombie();

    //Status da luta
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if(game->zombielife == 20 && game->ultimaTecla != 'a' && game->ultimaTecla != 'A' && game->ultimaTecla != 'd' && game->ultimaTecla != 'D')mvprintw(24, 0, "A zombie ambushes you!");

    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action != 1){mvprintw(23, 0, "You hit the zombie!");mvprintw(24, 0, "He guarded the attack.");}
    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action == 1){mvprintw(23, 0, "You hit the zombie!");mvprintw(24, 0, "He gnawed you in return.");}

    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action != 1){mvprintw(23, 0, "You defended!");mvprintw(24, 0, "But the zombie didn't attack.");}
    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action == 1){mvprintw(23, 0, "You defended!");mvprintw(24, 0, "The zombie almost got to you.");}

    //Status do zumbi
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(4, 59, ACS_SSBB);mvaddch(4, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(4, x, ACS_BSBS);}
    for(y = 1; y < 4; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Name: Zombie       ");mvprintw(2,60,"Life: %d           ",game->zombielife);mvprintw(3,60,"Attack: 10         ");
    }

    //Quando Zumbi morrer, pode spawnar de novo, e pode dropar upgrade
    if(game->zombielife < 1)
    {
        zom = zom + 1;
        random_event = 0;
        game->zombielife = 20;
        randomloot = rand() %5;

        game->tick = 10;
    }

    //Trit�o
    if(random_event == 29 && game->mermanlife > 0 && posicaox < 20)
    {
    merman();

    //Status da luta
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if(game->mermanlife == 30 && game->ultimaTecla != 'a' && game->ultimaTecla != 'A' && game->ultimaTecla != 'd' && game->ultimaTecla != 'D')mvprintw(24, 0, "A merman creeps out from the river!");

    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action != 1){mvprintw(23, 0, "You cutted the merman!");mvprintw(24, 0, "He tried to avoid you sword.");}
    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action == 1){mvprintw(23, 0, "You cutted the merman!");mvprintw(24, 0, "He scratched your legs.");}

    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action != 1){mvprintw(23, 0, "You guarded against the merman's attacks!");mvprintw(24, 0, "But he didn't attack.");}
    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action == 1){mvprintw(23, 0, "You defended!");mvprintw(24, 0, "The merman's claws almost pierced you.");}

    //Status do trit�o
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(4, 59, ACS_SSBB);mvaddch(4, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(4, x, ACS_BSBS);}
    for(y = 1; y < 4; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Name: Merman       ");mvprintw(2,60,"Life: %d           ",game->mermanlife);mvprintw(3,60,"Attack: 10         ");
    }

    //Quando Trit�o morrer, pode spawnar de novo, e pode dropar upgrade
    if(game->mermanlife < 1)
    {
        mer = mer + 1;
        random_event = 0;
        game->mermanlife = 30;
        randomloot = rand() %5;

        game->tick = 10;
    }

    //Vampiro
    if(random_event == 39 && game->vampirelife > 0 && level > 1)
    {
    vampire();

    //Status da luta
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if(game->vampirelife == 40 && game->ultimaTecla != 'a' && game->ultimaTecla != 'A' && game->ultimaTecla != 'd' && game->ultimaTecla != 'D')mvprintw(24, 0, "A dangerous vampire gazes at your soul!");

    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action != 1){mvprintw(23, 0, "You attacked the vampire!");mvprintw(24, 0, "He tried to dodge your attack.");}
    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action == 1){mvprintw(23, 0, "You attacked the vampire!");mvprintw(24, 0, "He bit you with his big tusks.");}

    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action != 1){mvprintw(23, 0, "You raised your shield up!");mvprintw(24, 0, "He stood there gazing at you.");}
    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action == 1){mvprintw(23, 0, "You raised your shield up!");mvprintw(24, 0, "The vampire's attack was still fierce.");}

    //Status do vampiro
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(4, 59, ACS_SSBB);mvaddch(4, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(4, x, ACS_BSBS);}
    for(y = 1; y < 4; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Name: Vampire      ");mvprintw(2,60,"Life: %d           ",game->vampirelife);mvprintw(3,60,"Attack: 20         ");
    }

    //Quando Vampiro morrer, pode spawnar de novo, e pode dropar upgrade
    if(game->vampirelife < 1)
    {
        vam = vam + 1;
        random_event = 0;
        game->vampirelife = 50;
        randomloot = rand() %5;

        game->tick = 10;
    }

    //Minotauro
    if(random_event == 49 && game->minotaurlife > 0 && level > 1)
    {
    minotaur();

    //Status da luta
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if(game->minotaurlife == 50 && game->ultimaTecla != 'a' && game->ultimaTecla != 'A' && game->ultimaTecla != 'd' && game->ultimaTecla != 'D')mvprintw(24, 0, "A foul minotaur comes to stomp you flat!");

    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action != 1){mvprintw(23, 0, "You slashed the minotaur!");mvprintw(24, 0, "But his skin is too thick.");}
    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action == 1){mvprintw(23, 0, "You slashed the minotaur!");mvprintw(24, 0, "His big horns punctured you.");}

    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action != 1){mvprintw(23, 0, "You raised your shield up!");mvprintw(24, 0, "But the minotaur is too slow.");}
    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action == 1){mvprintw(23, 0, "You defend!");mvprintw(24, 0, "The minotaur's club smashed your shield.");}

    //Status do minotauro
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(4, 59, ACS_SSBB);mvaddch(4, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(4, x, ACS_BSBS);}
    for(y = 1; y < 4; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Name: Minotaur     ");mvprintw(2,60,"Life: %d           ",game->minotaurlife);mvprintw(3,60,"Attack: 20         ");
    }

    //Quando Minotauro morrer, pode spawnar de novo, e pode dropar upgrade
    if(game->minotaurlife < 1)
    {
        min = min + 1;
        random_event = 0;
        game->minotaurlife = 50;
        randomloot = rand() %5;

        game->tick = 10;
    }

    //Rei
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if((posicaox == 26 && posicaoy == 1) || (posicaox == 27 && posicaoy == 1) || (posicaox == 28 && posicaoy == 1) || (posicaox == 29 && posicaoy == 1) || (posicaox == 30 && posicaoy == 1) || (posicaox == 31 && posicaoy == 1) || (posicaox == 32 && posicaoy == 1) || (posicaox == 33 && posicaoy == 1) || (posicaox == 34 && posicaoy == 1) || (posicaox == 35 && posicaoy == 1) || (posicaox == 36 && posicaoy == 1) || (posicaox == 37 && posicaoy == 1) || (posicaox == 38 && posicaoy == 1) || (posicaox == 42 && posicaoy == 1) || (posicaox == 43 && posicaoy == 1) || (posicaox == 44 && posicaoy == 1) || (posicaox == 45 && posicaoy == 1) || (posicaox == 46 && posicaoy == 1) || (posicaox == 47 && posicaoy == 1) || (posicaox == 48 && posicaoy == 1) || (posicaox == 49 && posicaoy == 1) || (posicaox == 50 && posicaoy == 1) || (posicaox == 51 && posicaoy == 1) || (posicaox == 52 && posicaoy == 1) || (posicaox == 53 && posicaoy == 1) || (posicaox == 54 && posicaoy == 1) || (posicaox == 26 && posicaoy == 2) || (posicaox == 27 && posicaoy == 2) || (posicaox == 28 && posicaoy == 2) || (posicaox == 29 && posicaoy == 2) || (posicaox == 30 && posicaoy == 2) || (posicaox == 31 && posicaoy == 2) || (posicaox == 32 && posicaoy == 2) || (posicaox == 33 && posicaoy == 2) || (posicaox == 34 && posicaoy == 2) || (posicaox == 35 && posicaoy == 2) || (posicaox == 36 && posicaoy == 2) || (posicaox == 37 && posicaoy == 2) || (posicaox == 38 && posicaoy == 2) || (posicaox == 42 && posicaoy == 2) || (posicaox == 43 && posicaoy == 2) || (posicaox == 44 && posicaoy == 2) || (posicaox == 45 && posicaoy == 2) || (posicaox == 46 && posicaoy == 2) || (posicaox == 47 && posicaoy == 2) || (posicaox == 48 && posicaoy == 2) || (posicaox == 49 && posicaoy == 2) || (posicaox == 50 && posicaoy == 2) || (posicaox == 51 && posicaoy == 2) || (posicaox == 52 && posicaoy == 2) || (posicaox == 53 && posicaoy == 2) || (posicaox == 54 && posicaoy == 2) || (posicaox == 26 && posicaoy == 3) || (posicaox == 27 && posicaoy == 3) || (posicaox == 28 && posicaoy == 3) || (posicaox == 29 && posicaoy == 3) || (posicaox == 30 && posicaoy == 3) || (posicaox == 31 && posicaoy == 3) || (posicaox == 32 && posicaoy == 3) || (posicaox == 33 && posicaoy == 3) || (posicaox == 34 && posicaoy == 3) || (posicaox == 35 && posicaoy == 3) || (posicaox == 36 && posicaoy == 3) || (posicaox == 37 && posicaoy == 3) || (posicaox == 43 && posicaoy == 3) || (posicaox == 44 && posicaoy == 3) || (posicaox == 45 && posicaoy == 3) || (posicaox == 46 && posicaoy == 3) || (posicaox == 47 && posicaoy == 3) || (posicaox == 48 && posicaoy == 3) || (posicaox == 49 && posicaoy == 3) || (posicaox == 50 && posicaoy == 3) || (posicaox == 51 && posicaoy == 3) || (posicaox == 52 && posicaoy == 3) || (posicaox == 53 && posicaoy == 3) || (posicaox == 54 && posicaoy == 3) || (posicaox == 26 && posicaoy == 4) || (posicaox == 27 && posicaoy == 4) || (posicaox == 28 && posicaoy == 4) || (posicaox == 29 && posicaoy == 4) || (posicaox == 30 && posicaoy == 4) || (posicaox == 31 && posicaoy == 4) || (posicaox == 32 && posicaoy == 4) || (posicaox == 33 && posicaoy == 4) || (posicaox == 34 && posicaoy == 4) || (posicaox == 35 && posicaoy == 4) || (posicaox == 36 && posicaoy == 4) || (posicaox == 37 && posicaoy == 4) || (posicaox == 43 && posicaoy == 4) || (posicaox == 44 && posicaoy == 4) || (posicaox == 45 && posicaoy == 4) || (posicaox == 46 && posicaoy == 4) || (posicaox == 47 && posicaoy == 4) || (posicaox == 48 && posicaoy == 4) || (posicaox == 49 && posicaoy == 4) || (posicaox == 50 && posicaoy == 4) || (posicaox == 51 && posicaoy == 4) || (posicaox == 52 && posicaoy == 4) || (posicaox == 53 && posicaoy == 4) || (posicaox == 54 && posicaoy == 4) || (posicaox == 26 && posicaoy == 5) || (posicaox == 27 && posicaoy == 5) || (posicaox == 28 && posicaoy == 5) || (posicaox == 29 && posicaoy == 5) || (posicaox == 30 && posicaoy == 5) || (posicaox == 31 && posicaoy == 5) || (posicaox == 32 && posicaoy == 5) || (posicaox == 33 && posicaoy == 5) || (posicaox == 34 && posicaoy == 5) || (posicaox == 35 && posicaoy == 5) || (posicaox == 36 && posicaoy == 5) || (posicaox == 37 && posicaoy == 5) || (posicaox == 38 && posicaoy == 5) || (posicaox == 39 && posicaoy == 5) || (posicaox == 40 && posicaoy == 5) || (posicaox == 41 && posicaoy == 5) || (posicaox == 42 && posicaoy == 5) || (posicaox == 43 && posicaoy == 5) || (posicaox == 44 && posicaoy == 5) || (posicaox == 45 && posicaoy == 5) || (posicaox == 46 && posicaoy == 5) || (posicaox == 47 && posicaoy == 5) || (posicaox == 48 && posicaoy == 5) || (posicaox == 49 && posicaoy == 5) || (posicaox == 50 && posicaoy == 5) || (posicaox == 51 && posicaoy == 5) || (posicaox == 52 && posicaoy == 5) || (posicaox == 53 && posicaoy == 5) || (posicaox == 54 && posicaoy == 5) || (posicaox == 26 && posicaoy == 6) || (posicaox == 27 && posicaoy == 6) || (posicaox == 28 && posicaoy == 6) || (posicaox == 29 && posicaoy == 6) || (posicaox == 30 && posicaoy == 6) || (posicaox == 31 && posicaoy == 6) || (posicaox == 32 && posicaoy == 6) || (posicaox == 33 && posicaoy == 6) || (posicaox == 34 && posicaoy == 6) || (posicaox == 35 && posicaoy == 6) || (posicaox == 36 && posicaoy == 6) || (posicaox == 37 && posicaoy == 6) || (posicaox == 38 && posicaoy == 6) || (posicaox == 39 && posicaoy == 6) || (posicaox == 40 && posicaoy == 6) || (posicaox == 41 && posicaoy == 6) || (posicaox == 42 && posicaoy == 6) || (posicaox == 43 && posicaoy == 6) || (posicaox == 44 && posicaoy == 6) || (posicaox == 45 && posicaoy == 6) || (posicaox == 46 && posicaoy == 6) || (posicaox == 47 && posicaoy == 6) || (posicaox == 48 && posicaoy == 6) || (posicaox == 49 && posicaoy == 6) || (posicaox == 50 && posicaoy == 6) || (posicaox == 51 && posicaoy == 6) || (posicaox == 52 && posicaoy == 6) || (posicaox == 53 && posicaoy == 6) || (posicaox == 54 && posicaoy == 6) || (posicaox == 26 && posicaoy == 7) || (posicaox == 27 && posicaoy == 7) || (posicaox == 28 && posicaoy == 7) || (posicaox == 29 && posicaoy == 7) || (posicaox == 30 && posicaoy == 7) || (posicaox == 31 && posicaoy == 7) || (posicaox == 32 && posicaoy == 7) || (posicaox == 33 && posicaoy == 7) || (posicaox == 34 && posicaoy == 7) || (posicaox == 35 && posicaoy == 7) || (posicaox == 36 && posicaoy == 7) || (posicaox == 37 && posicaoy == 7) || (posicaox == 38 && posicaoy == 7) || (posicaox == 39 && posicaoy == 7) || (posicaox == 40 && posicaoy == 7) || (posicaox == 41 && posicaoy == 7) || (posicaox == 42 && posicaoy == 7) || (posicaox == 43 && posicaoy == 7) || (posicaox == 44 && posicaoy == 7) || (posicaox == 45 && posicaoy == 7) || (posicaox == 46 && posicaoy == 7) || (posicaox == 47 && posicaoy == 7) || (posicaox == 48 && posicaoy == 7) || (posicaox == 49 && posicaoy == 7) || (posicaox == 50 && posicaoy == 7) || (posicaox == 51 && posicaoy == 7) || (posicaox == 52 && posicaoy == 7) || (posicaox == 53 && posicaoy == 7) || (posicaox == 54 && posicaoy == 7) || (posicaox == 26 && posicaoy == 8) || (posicaox == 27 && posicaoy == 8) || (posicaox == 28 && posicaoy == 8) || (posicaox == 29 && posicaoy == 8) || (posicaox == 30 && posicaoy == 8) || (posicaox == 31 && posicaoy == 8) || (posicaox == 32 && posicaoy == 8) || (posicaox == 33 && posicaoy == 8) || (posicaox == 34 && posicaoy == 8) || (posicaox == 35 && posicaoy == 8) || (posicaox == 36 && posicaoy == 8) || (posicaox == 37 && posicaoy == 8) || (posicaox == 38 && posicaoy == 8) || (posicaox == 39 && posicaoy == 8) || (posicaox == 40 && posicaoy == 8) || (posicaox == 41 && posicaoy == 8) || (posicaox == 42 && posicaoy == 8) || (posicaox == 43 && posicaoy == 8) || (posicaox == 44 && posicaoy == 8) || (posicaox == 45 && posicaoy == 8) || (posicaox == 46 && posicaoy == 8) || (posicaox == 47 && posicaoy == 8) || (posicaox == 48 && posicaoy == 8) || (posicaox == 49 && posicaoy == 8) || (posicaox == 50 && posicaoy == 8) || (posicaox == 51 && posicaoy == 8) || (posicaox == 52 && posicaoy == 8) || (posicaox == 53 && posicaoy == 8) || (posicaox == 54 && posicaoy == 8) || (posicaox == 26 && posicaoy == 9) || (posicaox == 27 && posicaoy == 9) || (posicaox == 28 && posicaoy == 9) || (posicaox == 29 && posicaoy == 9) || (posicaox == 30 && posicaoy == 9) || (posicaox == 31 && posicaoy == 9) || (posicaox == 32 && posicaoy == 9) || (posicaox == 33 && posicaoy == 9) || (posicaox == 34 && posicaoy == 9) || (posicaox == 35 && posicaoy == 9) || (posicaox == 36 && posicaoy == 9) || (posicaox == 37 && posicaoy == 9) || (posicaox == 38 && posicaoy == 9) || (posicaox == 39 && posicaoy == 9) || (posicaox == 40 && posicaoy == 9) || (posicaox == 41 && posicaoy == 9) || (posicaox == 42 && posicaoy == 9) || (posicaox == 43 && posicaoy == 9) || (posicaox == 44 && posicaoy == 9) || (posicaox == 45 && posicaoy == 9) || (posicaox == 46 && posicaoy == 9) || (posicaox == 47 && posicaoy == 9) || (posicaox == 48 && posicaoy == 9) || (posicaox == 49 && posicaoy == 9) || (posicaox == 50 && posicaoy == 9) || (posicaox == 51 && posicaoy == 9) || (posicaox == 52 && posicaoy == 9) || (posicaox == 53 && posicaoy == 9) || (posicaox == 54 && posicaoy == 9) || (posicaox == 40 && posicaoy == 10))
        {mvprintw(22, 0, "You feel an ominous presence...");mvprintw(23, 0, "The Evil King must be nearby!");}
    if((posicaox == 38 && posicaoy == 1) || (posicaox == 42 && posicaoy == 1) || (posicaox == 37 && posicaoy == 2) || (posicaox == 38 && posicaoy == 2) || (posicaox == 42 && posicaoy == 2) || (posicaox == 43 && posicaoy == 2) || (posicaox == 37 && posicaoy == 3) || (posicaox == 43 && posicaoy == 3) || (posicaox == 37 && posicaoy == 4) || (posicaox == 43 && posicaoy == 4) || (posicaox == 37 && posicaoy == 5) || (posicaox == 38 && posicaoy == 5) || (posicaox == 39 && posicaoy == 5) || (posicaox == 40 && posicaoy == 5) || (posicaox == 41 && posicaoy == 5) || (posicaox == 42 && posicaoy == 5) || (posicaox == 43 && posicaoy == 5))
        mvprintw(24, 0, "Press E to touch the throne");

    if(game->king == 1)
    {
    king();

    //Status da luta
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if(game->kinglife == 100){mvprintw(24, 0, "You engage the Evil King! Showdown time!");}

    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action != 1){mvprintw(23, 0, "You attacked the Evil King!");mvprintw(24, 0, "He stood guard!");}
    if((game->ultimaTecla == 'a' || game->ultimaTecla == 'A') && action == 1){mvprintw(23, 0, "You attacked the Evil King!");mvprintw(24, 0, "He retaliated!");}

    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action != 1){mvprintw(23, 0, "You defended!");mvprintw(24, 0, "The Evil King also defended!");}
    if((game->ultimaTecla == 'd' || game->ultimaTecla == 'D') && action == 1){mvprintw(23, 0, "You defended!");mvprintw(24, 0, "The Evil King's attack still hit you!");}

    //Status do Rei
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(4, 59, ACS_SSBB);mvaddch(4, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(4, x, ACS_BSBS);}
    for(y = 1; y < 4; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Name: Evil King    ");mvprintw(2,60,"Life: %d          ",game->kinglife);mvprintw(3,60,"Attack: 30         ");
    }

    //Alde�es
    if((game->house1 == 0 && posicaox == 21 && posicaoy == 21) || (game->house2 == 0 && posicaox == 51 && posicaoy == 19) || (game->house3 == 0 && posicaox == 67 && posicaoy == 9))
        mvprintw(24, 0, "Press E to enter and talk");

    if(game->house1 == 1)
    {
    diana();

    //Dialogo
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(14, 59, ACS_SSBB);mvaddch(14, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(14, x, ACS_BSBS);}
    for(y = 1; y < 14; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Diana:             ");mvprintw(2,60,"                   ");mvprintw(3,60,"Finally, the       ");mvprintw(4,60,"royal soldiers     ");mvprintw(5,60,"came to rescue us. ");mvprintw(6,60,"                   ");mvprintw(7,60,"When the monsters  ");mvprintw(8,60,"stormed the city,  ");mvprintw(9,60,"I thought we were  ");mvprintw(10,60,"already done for.  ");mvprintw(11,60,"                   ");mvprintw(12,60,"Please, rest here  ");mvprintw(13,60,"before continuing. ");

    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(23, 0, "Your life was refilled!");
    mvprintw(24, 0, "Press E to leave");
    }

    if(game->house2 == 1)
    {
    julian();

    //Dialogo
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(14, 59, ACS_SSBB);mvaddch(14, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(14, x, ACS_BSBS);}
    for(y = 1; y < 14; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Julian:            ");mvprintw(2,60,"                   ");mvprintw(3,60,"GAH! A monster!... ");mvprintw(4,60,"                   ");mvprintw(5,60,"Oh, it's a guard.  ");mvprintw(6,60,"Phew, close call.  ");mvprintw(7,60,"                   ");mvprintw(8,60,"Here, buddy.       ");mvprintw(9,60,"Rest a little.     ");mvprintw(10,60,"                   ");mvprintw(11,60,"The fields are     ");mvprintw(12,60,"crawling with      ");mvprintw(13,60,"those beasts.      ");

    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(23, 0, "Your life was refilled!");
    mvprintw(24, 0, "Press E to leave");
    }

    if(game->house3 == 1)
    {
    aura();

    //Dialogo
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(0, 59, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);mvaddch(14, 59, ACS_SSBB);mvaddch(14, 79, ACS_SBBS);
    for(x = 60; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(14, x, ACS_BSBS);}
    for(y = 1; y < 14; y++)
    {   mvaddch(y, 59, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    mvprintw(1,60,"Aura:              ");mvprintw(2,60,"                   ");mvprintw(3, 60,"Welcome, sir!      ");mvprintw(4, 60, "                   ");mvprintw(5, 60, "Have you come to   ");mvprintw(6, 60, "rid us of those    ");mvprintw(7, 60, "monstrosities?     ");mvprintw(8, 60, "                   ");mvprintw(9,60,"There's a swarm    ");mvprintw(10,60,"of them outside!   ");mvprintw(11,60,"                   ");mvprintw(12,60,"You better rest    ");mvprintw(13,60,"before going out.  ");

    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(23, 0, "Your life was refilled!");
    mvprintw(24, 0, "Press E to leave");
    }

//Status do personagem
setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
mvaddch(0, 0, ACS_BSSB);mvaddch(0, 20, ACS_BBSS);mvaddch(4, 0, ACS_SSBB);mvaddch(4, 20, ACS_SBBS);
for(x = 1; x < 20; x++)
{   mvaddch(0, x, ACS_BSBS);
    mvaddch(4, x, ACS_BSBS);}
for(y = 1; y < 4; y++)
{   mvaddch(y, 0, ACS_SBSB);
    mvaddch(y, 20, ACS_SBSB);}
mvprintw(1,1,"Name: Ahri         ");mvprintw(2,1,"Life: %d / %d      ",game->ahrilife, game->ahrimaxlife);mvprintw(3,1,"Attack:  %d        ", game->ahriattack);

    //Life upgrade
    if(randomloot == 1)
    {
        game->ahrimaxlife = game->ahrimaxlife + 10;
        game->tick = 6;
        randomloot = 0;
    }

    //Attack upgrade
    if(randomloot == 2)
    {
        game->ahriattack = game->ahriattack + 10;
        game->tick = 6;
        randomloot = 0;
    }

    setColor(COLOR_RED, 0, A_BOLD);
    if(game->ahrimaxlife > 50)
        mvaddch(2, 18, 259);
    setColor(COLOR_GREEN, 0, A_BOLD);
    if(game->ahriattack > 10)
        mvaddch(3, 18, ACS_UARROW);

    //Level upgrade
    if(game->ahrimaxlife > 69 || game->ahriattack > 29)
        level = 2;

//Besti�rio
if(game->pause == 1)
{
    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvaddch(0, 0, ACS_BSSB);mvaddch(0, 79, ACS_BBSS);
    mvaddch(4, 0, ACS_SSSB);mvaddch(4, 79, ACS_SBSS);
    mvaddch(24, 0, ACS_SSBB);mvaddch(24, 79, ACS_SBBS);
    for(x = 1; x < 79; x++)
    {   mvaddch(0, x, ACS_BSBS);
        mvaddch(24, x, ACS_BSBS);
        mvaddch(4, x, ACS_BSBS);}
    for(y = 1; y < 4; y++)
    {   mvaddch(y, 0, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    for(y = 5; y < 24; y++)
    {   mvaddch(y, 0, ACS_SBSB);
        mvaddch(y, 79, ACS_SBSB);}
    setColor(COLOR_BLACK, 0, 0);
    for(x = 1; x < 79; x++)
        for(y = 1; y < 4; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 1; x < 79; x++)
        for(y = 5; y < 24; y++)
            mvaddch(y, x, ACS_BLOCK);

    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    mvprintw(2, 2, "BESTIARY");

    FILE *fp = fopen("Bestiary.txt", "w");

    fseek(fp,0,SEEK_SET);fputc(gho,fp);fputc(' ',fp);mvprintw(8, 10, "Ghost(s) killed");
    fseek(fp,2,SEEK_SET);fputc(zom,fp);fputc(' ',fp);mvprintw(11, 10, "Zombie(s) killed");
    fseek(fp,4,SEEK_SET);fputc(mer,fp);fputc(' ',fp);mvprintw(14, 10, "Merman(s) killed");
    fseek(fp,6,SEEK_SET);fputc(vam,fp);fputc(' ',fp);mvprintw(17, 10, "Vampire(s) killed");
    fseek(fp,8,SEEK_SET);fputc(min,fp);fputc(' ',fp);mvprintw(20, 10, "Minotaur(s) killed");

    fclose(fp);

    bestiary();
}

//Game Over
if(game->ahrilife < 1 || game->kinglife < 1)
{
    if(game->ahrilife < 1)
    {
        //C�u vermelho
        setColor(COLOR_RED, COLOR_RED, A_BOLD);
        for(x = 0; x < 80; x++)
            for(y = 0; y < 16; y++)
                mvaddch(y, x, ACS_BLOCK);

        //Lua
        setColor(COLOR_RED, COLOR_RED, 0);
        for(x = 36; x < 44; x++){mvaddch(3, x, ACS_BLOCK);mvaddch(12, x, ACS_BLOCK);}
        for(x = 34; x < 46; x++){mvaddch(4, x, ACS_BLOCK);mvaddch(11, x, ACS_BLOCK);}
        for(x = 41; x < 48; x++){mvaddch(5, x, ACS_BLOCK);mvaddch(10, x, ACS_BLOCK);}for(x = 33; x < 37; x++){mvaddch(5, x, ACS_BLOCK);mvaddch(10, x, ACS_BLOCK);}
        for(x = 43; x < 49; x++){mvaddch(6, x, ACS_BLOCK);mvaddch(9, x, ACS_BLOCK);}for(x = 33; x < 35; x++){mvaddch(6, x, ACS_BLOCK);mvaddch(9, x, ACS_BLOCK);}
        for(x = 44; x < 49; x++){mvaddch(7, x, ACS_BLOCK);mvaddch(8, x, ACS_BLOCK);}
    }

    if(game->kinglife < 1 && game->ahrilife > 0)
    {
        //C�u claro
        setColor(COLOR_CYAN, COLOR_CYAN, A_BOLD);
        for(x = 0; x < 80; x++)
            for(y = 0; y < 16; y++)
                mvaddch(y, x, ACS_BLOCK);

        //Sol
        setColor(COLOR_YELLOW, COLOR_YELLOW, A_BOLD);

        for(y = 3; y < 9; y++)mvaddch(y, 40, ACS_BLOCK);

        mvaddch(5, 26, ACS_BLOCK);mvaddch(5,54, ACS_BLOCK);
        mvaddch(6, 27, ACS_BLOCK);mvaddch(6,53, ACS_BLOCK);
        mvaddch(7, 28, ACS_BLOCK);mvaddch(7,52, ACS_BLOCK);
        mvaddch(8, 29, ACS_BLOCK);mvaddch(8,51, ACS_BLOCK);
        mvaddch(9, 30, ACS_BLOCK);mvaddch(9,50, ACS_BLOCK);

        mvaddch(10, 21, ACS_BLOCK);mvaddch(10, 22, ACS_BLOCK);mvaddch(10,58, ACS_BLOCK);mvaddch(10,59, ACS_BLOCK);
        mvaddch(11, 23, ACS_BLOCK);mvaddch(11, 24, ACS_BLOCK);mvaddch(11,56, ACS_BLOCK);mvaddch(11,57, ACS_BLOCK);
        mvaddch(12, 25, ACS_BLOCK);mvaddch(12, 26, ACS_BLOCK);mvaddch(12,54, ACS_BLOCK);mvaddch(12,55, ACS_BLOCK);

        for(x = 34; x < 46; x++)mvaddch(10, x, ACS_BLOCK);
        for(x = 31; x < 49; x++)mvaddch(11, x, ACS_BLOCK);
        for(x = 29; x < 51; x++)mvaddch(12, x, ACS_BLOCK);
        for(x = 28; x < 52; x++)mvaddch(13, x, ACS_BLOCK);
        for(x = 28; x < 52; x++)mvaddch(14, x, ACS_BLOCK);
        for(x = 27; x < 53; x++)mvaddch(15, x, ACS_BLOCK);
    }

    gameover();

    setColor(COLOR_WHITE, COLOR_BLACK, A_BOLD);
    if(game->kinglife < 1 && game->ahrilife > 0)mvprintw(0, 0, "Our hero was victorious against the evil army!\nAlbendia will see the sun rise once again over its beautiful mountains...       ");
    if(game->ahrilife < 1)mvprintw(0, 0, "Our hero fell to to the forces of evil.\nAlbendia saw the bright sun set over its hills for the last time...             ");

    setColor(COLOR_BLACK, COLOR_BLACK, A_BOLD);
    mvprintw(24, 0, "Press Q -> Quit                                                Press R -> Replay");
}

    // Exibe o conte�do na tela (stdscr), getch() tamb�m ativa um refresh
    refresh();
}
}

void playAudio(gameData * game)
{
    if(tela == 4 || tela == 3 || tela == 2 || tela == 1)
    {
        //Tilintar da espada
        game->audioTone = 0;
        if((game->tick > 30 && game->tick < 33) || (game->tick > 36 && game->tick < 39) || (game->tick > 42 && game->tick < 45) || (game->tick > 48 && game->tick < 51) || (game->tick > 54 && game->tick < 57))game->audioTone = 980;
        if((game->tick > 33 && game->tick < 36) || (game->tick > 39 && game->tick < 42) || (game->tick > 45 && game->tick < 48) || (game->tick > 51 && game->tick < 54) || (game->tick > 57 && game->tick < 61))game->audioTone = 1050;
    }

    if(tela == 0)
    {
        //Som dos passos
        game->audioTone = 0;
        if(game->tick < 3)game->audioTone = 4;

        //M�sica de batalha
        if((random_event == 9 || random_event == 19 || (random_event == 29 && posicaox < 20) || (random_event == 39 && level > 1) || (random_event == 49 && level > 1)))
        {
            game->audioTone = 0;
            game->audioTone = 10;
        }

        //M�sica do boss
        if(game->king == 1)
        {
            game->audioTone = 0;
            if((game->tick > 0 && game->tick < 25) || (game->tick > 50 && game->tick < 75))game->audioTone = 20;
            if((game->tick > 25 && game->tick < 50) || (game->tick > 75 && game->tick < 100))game->audioTone = 50;
        }

        //M�sica das casinhas
        if(game->house1 == 1 || game->house2 == 1 || game->house3 == 1)
        {
            game->audioTone = 0;
            if((game->tick > 10 && game->tick < 20) || (game->tick > 30 && game->tick < 40) || (game->tick > 50 && game->tick < 60) || (game->tick > 70 && game->tick < 80) || (game->tick > 90 && game->tick < 100))game->audioTone = 900;
            if((game->tick > 20 && game->tick < 30) || (game->tick > 40 && game->tick < 50) || (game->tick > 60 && game->tick < 70) || (game->tick > 80 && game->tick < 90))game->audioTone = 1050;
        }

        //Som dos upgrades
        if(game->tick > 5 && game->tick < 10)
        {
            game->audioTone = 0;
            if(game->tick > 5 && game->tick < 8)
            game->audioTone = 700;
            if(game->tick > 8 && game->tick < 10)
            game->audioTone = 900;
        }
    }

    //M�sica da vit�ria
    if(game->kinglife < 1 && game->ahrilife > 0)
    {
        game->audioTone = 0;
        if(game->tick > 50 && game->tick < 80)game->audioTone = 2100;
        if(game->tick > 20 && game->tick < 50)game->audioTone = 1050;
    }

    //M�sica da derrota
    if(game->ahrilife < 1)
    {
        game->audioTone = 0;
        game->audioTone = (game->tick / 9) * 300;
    }
}

int main(int argc, char *argv[])
{
    int cols = 0, rows = 0;

    // estrutura com dados internos da aplica��o
    gameData game;

    // inicializa a tela pelo Curses e o estado inicial da aplica��o
    initScreen();
    // pega as dimens�es da tela do terminal e utiliza para montar o tabuleiro
    getmaxyx(stdscr, rows, cols);

    // precisa vir depois do initScreen, pega o tamanho da tela pra gerar o mapa
    initGame(&game, rows, cols);

    // precisa vir depois da game pra pegar o tom da onda
    initAudio(&game);


    // La�o principal sem retorno, pode ser removido para exibi��o direta de informa��o na tela
	while(1)
    {
        // Gerencia entradas do usu�rio pelo teclado
        handleInputs(&game);

        // Gerencia l�gica da aplica��o
        doUpdate(&game);

        // Atualiza a tela
        drawScreen(&game);

        // Controla o �udio
        playAudio(&game);

        // Controla o FPS da aplica��o
        napms(game.frame_ms);
    }

    // Encerra a tela inicializada em initScreen
    endwin();

    // Encerra o �udio
    SDL_PauseAudio(1);
    SDL_CloseAudio();

	return 0;
}
