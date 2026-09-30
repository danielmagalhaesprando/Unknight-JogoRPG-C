#include <curses.h>
#include "graphics.h"

// 8 colors for standard Curses
#define PALLETE_SIZE (COLOR_WHITE - COLOR_BLACK + 1)

//////////////////////////////////////////////////////////////////////
// Fun��es auxiliares para a biblioteca Curses
//////////////////////////////////////////////////////////////////////
void initScreen()
{
#ifdef XCURSES
    Xinitscr(argc, argv);
#else
    initscr();
#endif

    if (has_colors())
    {
        int bg = 0, fg = 0;

        start_color();

        for(bg = COLOR_BLACK; bg <= COLOR_WHITE; bg++)
            for(fg = COLOR_BLACK; fg <= COLOR_WHITE; fg++)
                init_pair(bg*PALLETE_SIZE + fg + 1, fg, bg); // color 0 is system default (reserved)
    }

    // Trata a tecla Enter como \n
    //nl();
    // Teclas digitadas pelo usu�rio n�o aparecem na tela
    noecho();
    // 0 para cursor invis�vel
    curs_set(0);
    // Define getch como non-blocking de acordo com o timeout abaixo
    nodelay(stdscr, TRUE);
    // Timeout em 0 determina getch como non-blocking, n�o espera entrada do usu�rio
    timeout(0);
    // Habilita teclas de function (F1, F2, ...), flechas, etc
    keypad(stdscr, TRUE);
}

void setColor(short int fg, short int bg, chtype attr)
{
    chtype color = COLOR_PAIR(bg*PALLETE_SIZE + fg + 1);
    color |= attr;
    attrset(color);
}

int x,y,i;

void menu()
{
    //C�u
    setColor(COLOR_BLUE, COLOR_BLUE, A_BOLD);
        for(x = 0; x < 80; x++)
            for(y = 0; y < 16; y++)
                mvaddch(y, x, ACS_BLOCK);

    //Estrelas
    setColor(COLOR_WHITE, COLOR_BLUE, A_BLINK);
        mvaddch(3, 5, ACS_DIAMOND);
        mvaddch(5, 32, ACS_DIAMOND);
        mvaddch(10, 15, ACS_DIAMOND);
        mvaddch(8, 53, ACS_DIAMOND);
        mvaddch(2, 70, ACS_DIAMOND);

    //Montanhas
        setColor(COLOR_BLACK, COLOR_BLACK, 0);
        for(x = 2; x < 8; x++)
            mvaddch(10, x, ACS_BLOCK);
        for(x = 0; x < 10; x++)
            mvaddch(11, x, ACS_BLOCK);
        for(x = 0; x < 12; x++)
            mvaddch(12, x, ACS_BLOCK);
        for(x = 0; x < 14; x++)
            mvaddch(13, x, ACS_BLOCK);
        for(x = 0; x < 16; x++)
            mvaddch(14, x, ACS_BLOCK);
        for(x = 0; x < 18; x++)
            mvaddch(15, x, ACS_BLOCK);

        for(x = 68; x < 78; x++)
            mvaddch(8, x, ACS_BLOCK);
        for(x = 66; x < 80; x++)
            mvaddch(9, x, ACS_BLOCK);
        for(x = 64; x < 80; x++)
            mvaddch(10, x, ACS_BLOCK);
        for(x = 62; x < 80; x++)
            mvaddch(11, x, ACS_BLOCK);
        for(x = 60; x < 80; x++)
            mvaddch(12, x, ACS_BLOCK);
        for(x = 58; x < 80; x++)
            mvaddch(13, x, ACS_BLOCK);
        for(x = 56; x < 80; x++)
            mvaddch(14, x, ACS_BLOCK);
        for(x = 54; x < 80; x++)
            mvaddch(15, x, ACS_BLOCK);

        //Espada
        setColor(COLOR_WHITE, 0, 0);
                                  mvaddch(1, 40, ACS_BLOCK);
        mvaddch(2, 39, ACS_BLOCK);mvaddch(2, 40, ACS_BLOCK);mvaddch(2, 41, ACS_BLOCK);
        for(x = 38; x < 43; x++)
            for(y = 3; y < 12; y++)
                mvaddch(y, x, ACS_BLOCK);
        setColor(COLOR_BLACK, 0, A_BOLD);
        for(y = 3; y < 12; y++)
            mvaddch(y, 40, ACS_BLOCK);
        setColor(COLOR_YELLOW, 0, 0);
        for(y = 13; y < 16; y++)
            mvaddch(y, 40, ACS_BLOCK);
        setColor(COLOR_YELLOW, COLOR_YELLOW, A_BOLD);
        for(x = 37; x < 44; x++)mvaddch(12, x, ACS_BLOCK);
        mvaddch(16, 39, ACS_BLOCK);mvaddch(16, 40, ACS_BLOCK);mvaddch(16, 41, ACS_BLOCK);
}

void titulo()
{
    setColor(COLOR_YELLOW, 0, A_BOLD);
        mvaddch(18, 7, ACS_BLOCK);mvaddch(18, 8, ACS_BLOCK);        mvaddch(18, 11, ACS_BLOCK);mvaddch(18, 12, ACS_BLOCK);
        mvaddch(19, 7, ACS_BLOCK);mvaddch(19, 8, ACS_BLOCK);        mvaddch(19, 11, ACS_BLOCK);mvaddch(19, 12, ACS_BLOCK);
        mvaddch(20, 7, ACS_BLOCK);mvaddch(20, 8, ACS_BLOCK);        mvaddch(20, 11, ACS_BLOCK);mvaddch(20, 12, ACS_BLOCK);
        mvaddch(21, 7, ACS_BLOCK);mvaddch(21, 8, ACS_BLOCK);        mvaddch(21, 11, ACS_BLOCK);mvaddch(21, 12, ACS_BLOCK);
            mvaddch(22, 8, ACS_BLOCK);mvaddch(22, 9, ACS_BLOCK);mvaddch(22, 10, ACS_BLOCK);mvaddch(22, 11, ACS_BLOCK);

        mvaddch(18, 16, ACS_BLOCK);mvaddch(18, 17, ACS_BLOCK);
        mvaddch(19, 16, ACS_BLOCK);mvaddch(19, 17, ACS_BLOCK);
        mvaddch(20, 16, ACS_BLOCK);mvaddch(20, 17, ACS_BLOCK);
        mvaddch(21, 16, ACS_BLOCK);mvaddch(21, 17, ACS_BLOCK);
        mvaddch(22, 16, ACS_BLOCK);mvaddch(22, 17, ACS_BLOCK);
            mvaddch(19, 18, ACS_BLOCK);
            mvaddch(20, 18, ACS_BLOCK);mvaddch(20, 19, ACS_BLOCK);
            mvaddch(21, 19, ACS_BLOCK);
        mvaddch(18, 20, ACS_BLOCK);mvaddch(18, 21, ACS_BLOCK);
        mvaddch(19, 20, ACS_BLOCK);mvaddch(19, 21, ACS_BLOCK);
        mvaddch(20, 20, ACS_BLOCK);mvaddch(20, 21, ACS_BLOCK);
        mvaddch(21, 20, ACS_BLOCK);mvaddch(21, 21, ACS_BLOCK);
        mvaddch(22, 20, ACS_BLOCK);mvaddch(22, 21, ACS_BLOCK);

        mvaddch(18, 25, ACS_BLOCK);mvaddch(18, 26, ACS_BLOCK);                                                     mvaddch(18, 29, ACS_BLOCK);mvaddch(18, 30, ACS_BLOCK);
        mvaddch(19, 25, ACS_BLOCK);mvaddch(19, 26, ACS_BLOCK);                          mvaddch(19, 28, ACS_BLOCK);mvaddch(19, 29, ACS_BLOCK);
        mvaddch(20, 25, ACS_BLOCK);mvaddch(20, 26, ACS_BLOCK);mvaddch(20, 27, ACS_BLOCK);mvaddch(20, 28, ACS_BLOCK);
        mvaddch(21, 25, ACS_BLOCK);mvaddch(21, 26, ACS_BLOCK);                          mvaddch(21, 28, ACS_BLOCK);mvaddch(21, 29, ACS_BLOCK);
        mvaddch(22, 25, ACS_BLOCK);mvaddch(22, 26, ACS_BLOCK);                                                     mvaddch(22, 29, ACS_BLOCK);mvaddch(22, 30, ACS_BLOCK);

        mvaddch(18, 34, ACS_BLOCK);mvaddch(18, 35, ACS_BLOCK);
        mvaddch(19, 34, ACS_BLOCK);mvaddch(19, 35, ACS_BLOCK);
        mvaddch(20, 34, ACS_BLOCK);mvaddch(20, 35, ACS_BLOCK);
        mvaddch(21, 34, ACS_BLOCK);mvaddch(21, 35, ACS_BLOCK);
        mvaddch(22, 34, ACS_BLOCK);mvaddch(22, 35, ACS_BLOCK);
            mvaddch(19, 36, ACS_BLOCK);
            mvaddch(20, 36, ACS_BLOCK);mvaddch(20, 37, ACS_BLOCK);
            mvaddch(21, 37, ACS_BLOCK);
        mvaddch(18, 38, ACS_BLOCK);mvaddch(18, 39, ACS_BLOCK);
        mvaddch(19, 38, ACS_BLOCK);mvaddch(19, 39, ACS_BLOCK);
        mvaddch(20, 38, ACS_BLOCK);mvaddch(20, 39, ACS_BLOCK);
        mvaddch(21, 38, ACS_BLOCK);mvaddch(21, 39, ACS_BLOCK);
        mvaddch(22, 38, ACS_BLOCK);mvaddch(22, 39, ACS_BLOCK);

        mvaddch(18, 43, ACS_BLOCK);mvaddch(18, 44, ACS_BLOCK);
        mvaddch(19, 43, ACS_BLOCK);mvaddch(19, 44, ACS_BLOCK);
        mvaddch(20, 43, ACS_BLOCK);mvaddch(20, 44, ACS_BLOCK);
        mvaddch(21, 43, ACS_BLOCK);mvaddch(21, 44, ACS_BLOCK);
        mvaddch(22, 43, ACS_BLOCK);mvaddch(22, 44, ACS_BLOCK);

            mvaddch(18, 49, ACS_BLOCK);mvaddch(18, 50, ACS_BLOCK);mvaddch(18, 51, ACS_BLOCK);mvaddch(18, 52, ACS_BLOCK);mvaddch(18, 53, ACS_BLOCK);
        mvaddch(19, 48, ACS_BLOCK);mvaddch(19, 49, ACS_BLOCK);
        mvaddch(20, 48, ACS_BLOCK);mvaddch(20, 49, ACS_BLOCK);                               mvaddch(20, 52, ACS_BLOCK);mvaddch(20, 53, ACS_BLOCK);
        mvaddch(21, 48, ACS_BLOCK);mvaddch(21, 49, ACS_BLOCK);                                                          ;mvaddch(21, 53, ACS_BLOCK);
            mvaddch(22, 49, ACS_BLOCK);mvaddch(22, 50, ACS_BLOCK);mvaddch(22, 51, ACS_BLOCK);mvaddch(22, 52, ACS_BLOCK);mvaddch(22, 53, ACS_BLOCK);

        mvaddch(18, 57, ACS_BLOCK);mvaddch(18, 58, ACS_BLOCK);                                                      mvaddch(18, 61, ACS_BLOCK);mvaddch(18, 62, ACS_BLOCK);
        mvaddch(19, 57, ACS_BLOCK);mvaddch(19, 58, ACS_BLOCK);                                                      mvaddch(19, 61, ACS_BLOCK);mvaddch(19, 62, ACS_BLOCK);
        mvaddch(20, 57, ACS_BLOCK);mvaddch(20, 58, ACS_BLOCK);mvaddch(20, 59, ACS_BLOCK);mvaddch(20, 60, ACS_BLOCK);mvaddch(20, 61, ACS_BLOCK);mvaddch(20, 62, ACS_BLOCK);
        mvaddch(21, 57, ACS_BLOCK);mvaddch(21, 58, ACS_BLOCK);                                                      mvaddch(21, 61, ACS_BLOCK);mvaddch(21, 62, ACS_BLOCK);
        mvaddch(22, 57, ACS_BLOCK);mvaddch(22, 58, ACS_BLOCK);                                                      mvaddch(22, 61, ACS_BLOCK);mvaddch(22, 62, ACS_BLOCK);

        mvaddch(18, 66, ACS_BLOCK);mvaddch(18, 67, ACS_BLOCK);mvaddch(18, 68, ACS_BLOCK);mvaddch(18, 69, ACS_BLOCK);mvaddch(18, 70, ACS_BLOCK);mvaddch(18, 71, ACS_BLOCK);
                                                                mvaddch(19, 68, ACS_BLOCK);mvaddch(19, 69, ACS_BLOCK);
                                                                mvaddch(20, 68, ACS_BLOCK);mvaddch(20, 69, ACS_BLOCK);
                                                                mvaddch(21, 68, ACS_BLOCK);mvaddch(21, 69, ACS_BLOCK);
                                                                mvaddch(22, 68, ACS_BLOCK);mvaddch(22, 69, ACS_BLOCK);

        setColor(COLOR_YELLOW, 0, 0);
        mvaddch(18, 9, ACS_BLOCK);mvaddch(18, 13, ACS_BLOCK);
        mvaddch(19, 9, ACS_BLOCK);mvaddch(19, 13, ACS_BLOCK);
        mvaddch(20, 9, ACS_BLOCK);mvaddch(20, 13, ACS_BLOCK);
        mvaddch(21, 9, ACS_BLOCK);mvaddch(21, 13, ACS_BLOCK);
                        mvaddch(22, 12, ACS_BLOCK);

            mvaddch(18, 18, ACS_BLOCK);
                mvaddch(19, 19, ACS_BLOCK);
        mvaddch(21, 18, ACS_BLOCK);
        mvaddch(22, 18, ACS_BLOCK);
        mvaddch(18, 22, ACS_BLOCK);
        mvaddch(19, 22, ACS_BLOCK);
        mvaddch(20, 22, ACS_BLOCK);
        mvaddch(21, 22, ACS_BLOCK);
        mvaddch(22, 22, ACS_BLOCK);

        mvaddch(18, 27, ACS_BLOCK);                                                     mvaddch(18, 31, ACS_BLOCK);
        mvaddch(19, 27, ACS_BLOCK);                          mvaddch(19, 30, ACS_BLOCK);
                                   mvaddch(20, 29, ACS_BLOCK);
        mvaddch(21, 27, ACS_BLOCK);                          mvaddch(21, 30, ACS_BLOCK);
        mvaddch(22, 27, ACS_BLOCK);                                                     mvaddch(22, 31, ACS_BLOCK);

        mvaddch(18, 36, ACS_BLOCK);
                mvaddch(19, 37, ACS_BLOCK);
        mvaddch(21, 36, ACS_BLOCK);
        mvaddch(22, 36, ACS_BLOCK);
        mvaddch(18, 40, ACS_BLOCK);
        mvaddch(19, 40, ACS_BLOCK);
        mvaddch(20, 40, ACS_BLOCK);
        mvaddch(21, 40, ACS_BLOCK);
        mvaddch(22, 40, ACS_BLOCK);

        mvaddch(18, 45, ACS_BLOCK);
        mvaddch(19, 45, ACS_BLOCK);
        mvaddch(20, 45, ACS_BLOCK);
        mvaddch(21, 45, ACS_BLOCK);
        mvaddch(22, 45, ACS_BLOCK);

                                    mvaddch(18, 54, ACS_BLOCK);
        mvaddch(19, 50, ACS_BLOCK);
        mvaddch(20, 50, ACS_BLOCK);mvaddch(20, 54, ACS_BLOCK);
        mvaddch(21, 50, ACS_BLOCK);mvaddch(21, 54, ACS_BLOCK);
        mvaddch(22, 54, ACS_BLOCK);

        mvaddch(18, 59, ACS_BLOCK);mvaddch(18, 63, ACS_BLOCK);
        mvaddch(19, 59, ACS_BLOCK);mvaddch(19, 63, ACS_BLOCK);
                                    mvaddch(20, 63, ACS_BLOCK);
        mvaddch(21, 59, ACS_BLOCK);mvaddch(21, 63, ACS_BLOCK);
        mvaddch(22, 59, ACS_BLOCK);mvaddch(22, 63, ACS_BLOCK);

                                    mvaddch(18, 72, ACS_BLOCK);
        mvaddch(19, 70, ACS_BLOCK);
        mvaddch(20, 70, ACS_BLOCK);
        mvaddch(21, 70, ACS_BLOCK);
        mvaddch(22, 70, ACS_BLOCK);
}

void gameover()
{
    //Montanhas
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    for(x = 2; x < 8; x++)
        mvaddch(10, x, ACS_BLOCK);
    for(x = 0; x < 10; x++)
        mvaddch(11, x, ACS_BLOCK);
    for(x = 0; x < 12; x++)
        mvaddch(12, x, ACS_BLOCK);
    for(x = 0; x < 14; x++)
        mvaddch(13, x, ACS_BLOCK);
    for(x = 0; x < 16; x++)
        mvaddch(14, x, ACS_BLOCK);
    for(x = 0; x < 18; x++)
        mvaddch(15, x, ACS_BLOCK);

    for(x = 68; x < 78; x++)
        mvaddch(8, x, ACS_BLOCK);
    for(x = 66; x < 80; x++)
        mvaddch(9, x, ACS_BLOCK);
    for(x = 64; x < 80; x++)
        mvaddch(10, x, ACS_BLOCK);
    for(x = 62; x < 80; x++)
        mvaddch(11, x, ACS_BLOCK);
    for(x = 60; x < 80; x++)
        mvaddch(12, x, ACS_BLOCK);
    for(x = 58; x < 80; x++)
        mvaddch(13, x, ACS_BLOCK);
    for(x = 56; x < 80; x++)
        mvaddch(14, x, ACS_BLOCK);
    for(x = 54; x < 80; x++)
        mvaddch(15, x, ACS_BLOCK);

    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    for(x = 0; x < 80; x++)
        for(y = 16; y < 24; y++)
            mvaddch(y, x, ACS_BLOCK);

    setColor(COLOR_YELLOW, 0, A_BOLD);
        mvaddch(18, 3, ACS_BLOCK);mvaddch(18, 4, ACS_BLOCK);mvaddch(18, 5, ACS_BLOCK);mvaddch(18, 6, ACS_BLOCK);mvaddch(18, 7, ACS_BLOCK);
    mvaddch(19, 2, ACS_BLOCK);mvaddch(19, 3, ACS_BLOCK);
    mvaddch(20, 2, ACS_BLOCK);mvaddch(20, 3, ACS_BLOCK);                               mvaddch(20, 6, ACS_BLOCK);mvaddch(20, 7, ACS_BLOCK);
    mvaddch(21, 2, ACS_BLOCK);mvaddch(21, 3, ACS_BLOCK);                                                          ;mvaddch(21, 7, ACS_BLOCK);
        mvaddch(22, 3, ACS_BLOCK);mvaddch(22, 4, ACS_BLOCK);mvaddch(22, 5, ACS_BLOCK);mvaddch(22, 6, ACS_BLOCK);mvaddch(22, 7, ACS_BLOCK);

                                                        mvaddch(18, 13, ACS_BLOCK);mvaddch(18, 14, ACS_BLOCK);
                mvaddch(19, 12, ACS_BLOCK);mvaddch(19, 13, ACS_BLOCK);                            mvaddch(19, 14, ACS_BLOCK);mvaddch(19, 15, ACS_BLOCK);
    mvaddch(20, 11, ACS_BLOCK);mvaddch(20, 12, ACS_BLOCK);                                                      mvaddch(20, 15, ACS_BLOCK);mvaddch(20, 16, ACS_BLOCK);
    mvaddch(21, 11, ACS_BLOCK);mvaddch(21, 12, ACS_BLOCK);mvaddch(21, 13, ACS_BLOCK);mvaddch(21, 14, ACS_BLOCK);mvaddch(21, 15, ACS_BLOCK);mvaddch(21, 16, ACS_BLOCK);
    mvaddch(22, 11, ACS_BLOCK);mvaddch(22, 12, ACS_BLOCK);                                                      mvaddch(22, 15, ACS_BLOCK);mvaddch(22, 16, ACS_BLOCK);

    mvaddch(18, 20, ACS_BLOCK);mvaddch(18, 21, ACS_BLOCK);
    mvaddch(19, 20, ACS_BLOCK);mvaddch(19, 21, ACS_BLOCK);
    mvaddch(20, 20, ACS_BLOCK);mvaddch(20, 21, ACS_BLOCK);
    mvaddch(21, 20, ACS_BLOCK);mvaddch(21, 21, ACS_BLOCK);
    mvaddch(22, 20, ACS_BLOCK);mvaddch(22, 21, ACS_BLOCK);
                mvaddch(19, 22, ACS_BLOCK);mvaddch(20, 22, ACS_BLOCK);
                                           mvaddch(20, 23, ACS_BLOCK);mvaddch(21, 23, ACS_BLOCK);
                                           mvaddch(20, 24, ACS_BLOCK);mvaddch(21, 24, ACS_BLOCK);
                mvaddch(19, 25, ACS_BLOCK);mvaddch(20, 25, ACS_BLOCK);
    mvaddch(18, 26, ACS_BLOCK);mvaddch(18, 27, ACS_BLOCK);
    mvaddch(19, 26, ACS_BLOCK);mvaddch(19, 27, ACS_BLOCK);
    mvaddch(20, 26, ACS_BLOCK);mvaddch(20, 27, ACS_BLOCK);
    mvaddch(21, 26, ACS_BLOCK);mvaddch(21, 27, ACS_BLOCK);
    mvaddch(22, 26, ACS_BLOCK);mvaddch(22, 27, ACS_BLOCK);

    mvaddch(18, 31, ACS_BLOCK);mvaddch(18, 32, ACS_BLOCK);mvaddch(18, 33, ACS_BLOCK);mvaddch(18, 34, ACS_BLOCK);
    mvaddch(19, 31, ACS_BLOCK);mvaddch(19, 32, ACS_BLOCK);
    mvaddch(20, 31, ACS_BLOCK);mvaddch(20, 32, ACS_BLOCK);mvaddch(20, 33, ACS_BLOCK);mvaddch(20, 34, ACS_BLOCK);
    mvaddch(21, 31, ACS_BLOCK);mvaddch(21, 32, ACS_BLOCK);
    mvaddch(22, 31, ACS_BLOCK);mvaddch(22, 32, ACS_BLOCK);mvaddch(22, 33, ACS_BLOCK);mvaddch(22, 34, ACS_BLOCK);

                    mvaddch(18, 46, ACS_BLOCK);mvaddch(18, 47, ACS_BLOCK);mvaddch(18, 48, ACS_BLOCK);mvaddch(18, 49, ACS_BLOCK);
    mvaddch(19, 45, ACS_BLOCK);mvaddch(19, 46, ACS_BLOCK);                              mvaddch(19, 49, ACS_BLOCK);mvaddch(19, 50, ACS_BLOCK);
    mvaddch(20, 45, ACS_BLOCK);mvaddch(20, 46, ACS_BLOCK);                              mvaddch(20, 49, ACS_BLOCK);mvaddch(20, 50, ACS_BLOCK);
    mvaddch(21, 45, ACS_BLOCK);mvaddch(21, 46, ACS_BLOCK);                              mvaddch(21, 49, ACS_BLOCK);mvaddch(21, 50, ACS_BLOCK);
                    mvaddch(22, 46, ACS_BLOCK);mvaddch(22, 47, ACS_BLOCK);mvaddch(22, 48, ACS_BLOCK);mvaddch(22, 49, ACS_BLOCK);


    mvaddch(18, 54, ACS_BLOCK);mvaddch(18, 55, ACS_BLOCK);                          mvaddch(18, 60, ACS_BLOCK);mvaddch(18, 61, ACS_BLOCK);
    mvaddch(19, 54, ACS_BLOCK);mvaddch(19, 55, ACS_BLOCK);                          mvaddch(19, 60, ACS_BLOCK);mvaddch(19, 61, ACS_BLOCK);
    mvaddch(20, 55, ACS_BLOCK);mvaddch(20, 56, ACS_BLOCK);                          mvaddch(20, 59, ACS_BLOCK);mvaddch(20, 60, ACS_BLOCK);
    mvaddch(21, 55, ACS_BLOCK);mvaddch(21, 56, ACS_BLOCK);                          mvaddch(21, 59, ACS_BLOCK);mvaddch(21, 60, ACS_BLOCK);
                                          mvaddch(22, 57, ACS_BLOCK);mvaddch(22, 58, ACS_BLOCK);

    mvaddch(18, 65, ACS_BLOCK);mvaddch(18, 66, ACS_BLOCK);mvaddch(18, 67, ACS_BLOCK);mvaddch(18, 68, ACS_BLOCK);
    mvaddch(19, 65, ACS_BLOCK);mvaddch(19, 66, ACS_BLOCK);
    mvaddch(20, 65, ACS_BLOCK);mvaddch(20, 66, ACS_BLOCK);mvaddch(20, 67, ACS_BLOCK);mvaddch(20, 68, ACS_BLOCK);
    mvaddch(21, 65, ACS_BLOCK);mvaddch(21, 66, ACS_BLOCK);
    mvaddch(22, 65, ACS_BLOCK);mvaddch(22, 66, ACS_BLOCK);mvaddch(22, 67, ACS_BLOCK);mvaddch(22, 68, ACS_BLOCK);


    mvaddch(18, 72, ACS_BLOCK);mvaddch(18, 73, ACS_BLOCK);mvaddch(18, 74, ACS_BLOCK);mvaddch(18, 75, ACS_BLOCK);mvaddch(18, 76, ACS_BLOCK);
    mvaddch(19, 72, ACS_BLOCK);mvaddch(19, 73, ACS_BLOCK);                                                      mvaddch(19, 76, ACS_BLOCK);mvaddch(19, 77, ACS_BLOCK);
    mvaddch(20, 72, ACS_BLOCK);mvaddch(20, 73, ACS_BLOCK);mvaddch(20, 74, ACS_BLOCK);mvaddch(20, 75, ACS_BLOCK);
    mvaddch(21, 72, ACS_BLOCK);mvaddch(21, 73, ACS_BLOCK);                           mvaddch(21, 75, ACS_BLOCK);mvaddch(21, 76, ACS_BLOCK);
    mvaddch(22, 72, ACS_BLOCK);mvaddch(22, 73, ACS_BLOCK);                                                      mvaddch(22, 76, ACS_BLOCK);mvaddch(22, 77, ACS_BLOCK);


    setColor(COLOR_YELLOW, 0, 0);
                                mvaddch(18, 8, ACS_BLOCK);
    mvaddch(19, 4, ACS_BLOCK);
    mvaddch(20, 4, ACS_BLOCK);mvaddch(20, 8, ACS_BLOCK);
    mvaddch(21, 4, ACS_BLOCK);mvaddch(21, 8, ACS_BLOCK);
    mvaddch(22, 8, ACS_BLOCK);

        mvaddch(18, 15, ACS_BLOCK);
                mvaddch(19, 16, ACS_BLOCK);
    mvaddch(20, 13, ACS_BLOCK);mvaddch(20, 17, ACS_BLOCK);
                               mvaddch(21, 17, ACS_BLOCK);
    mvaddch(22, 13, ACS_BLOCK);mvaddch(22, 17, ACS_BLOCK);

    mvaddch(18, 22, ACS_BLOCK);                             mvaddch(18, 28, ACS_BLOCK);
                    mvaddch(19, 23, ACS_BLOCK);             mvaddch(19, 28, ACS_BLOCK);
                                                            mvaddch(20, 28, ACS_BLOCK);
    mvaddch(21, 22, ACS_BLOCK);mvaddch(21, 25, ACS_BLOCK);  mvaddch(21, 28, ACS_BLOCK);
    mvaddch(22, 22, ACS_BLOCK);                             mvaddch(22, 28, ACS_BLOCK);

                               mvaddch(18, 35, ACS_BLOCK);
    mvaddch(19, 33, ACS_BLOCK);
                               mvaddch(20, 35, ACS_BLOCK);
    mvaddch(21, 33, ACS_BLOCK);
                               mvaddch(22, 35, ACS_BLOCK);

                               mvaddch(18, 50, ACS_BLOCK);
    mvaddch(19, 47, ACS_BLOCK);                            mvaddch(19, 51, ACS_BLOCK);
    mvaddch(20, 47, ACS_BLOCK);                            mvaddch(20, 51, ACS_BLOCK);
    mvaddch(21, 47, ACS_BLOCK);                            mvaddch(21, 51, ACS_BLOCK);
                               mvaddch(22, 50, ACS_BLOCK);

    mvaddch(18, 56, ACS_BLOCK);          mvaddch(18, 62, ACS_BLOCK);
    mvaddch(19, 56, ACS_BLOCK);          mvaddch(19, 62, ACS_BLOCK);
    mvaddch(20, 57, ACS_BLOCK);          mvaddch(20, 61, ACS_BLOCK);
    mvaddch(21, 57, ACS_BLOCK);          mvaddch(21, 61, ACS_BLOCK);
                        mvaddch(22, 59, ACS_BLOCK);

                                mvaddch(18, 69, ACS_BLOCK);
    mvaddch(19, 67, ACS_BLOCK);
                                mvaddch(20, 69, ACS_BLOCK);
    mvaddch(21, 67, ACS_BLOCK);
                                mvaddch(22, 69, ACS_BLOCK);

                                            mvaddch(18, 77, ACS_BLOCK);
    mvaddch(19, 74, ACS_BLOCK);                           mvaddch(19, 78, ACS_BLOCK);
    mvaddch(20, 76, ACS_BLOCK);
    mvaddch(21, 74, ACS_BLOCK);                           mvaddch(21, 77, ACS_BLOCK);
    mvaddch(22, 74, ACS_BLOCK);                                          mvaddch(22, 78, ACS_BLOCK);
}

void mapa()
{
    //Desenha o campo
    setColor(COLOR_GREEN, COLOR_GREEN, A_BOLD);
    for(x = 0; x < 80; x++)
        for(y = 0; y < 25; y++)
                mvaddch(y, x, ACS_BLOCK);

    //Desenha as �rvores
    setColor(COLOR_GREEN, COLOR_GREEN, A_BLINK);
    mvaddch(14, 23, 261);
    mvaddch(21, 67, 261);
    mvaddch(3, 70, 261);

    //Desenha as casas
    setColor(COLOR_RED, COLOR_GREEN, A_BLINK);
    mvaddch(20, 20, 220);mvaddch(20, 21, ACS_BLOCK);mvaddch(20, 22, 220);
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    mvaddch(21,21, ACS_BOARD);
    setColor(COLOR_RED, COLOR_YELLOW, 0);
    mvaddch(21, 20, ACS_BOARD);                     mvaddch(21, 22, ACS_BOARD);

    setColor(COLOR_RED, COLOR_GREEN, A_BLINK);
    mvaddch(18, 50, 220);mvaddch(18, 51, ACS_BLOCK);mvaddch(18, 52, 220);
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    mvaddch(19,51, ACS_BOARD);
    setColor(COLOR_RED, COLOR_YELLOW, 0);
    mvaddch(19, 50, ACS_BOARD);                     mvaddch(19, 52, ACS_BOARD);

    setColor(COLOR_RED, COLOR_GREEN, A_BLINK);
    mvaddch(8, 66, 220);mvaddch(8, 67, ACS_BLOCK);mvaddch(8, 68, 220);
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    mvaddch(9,67, ACS_BOARD);
    setColor(COLOR_RED, COLOR_YELLOW, 0);
    mvaddch(9, 66, ACS_BOARD);                     mvaddch(9, 68, ACS_BOARD);

    //Desenha o rio
    setColor(COLOR_WHITE, COLOR_BLUE, 9);
    for(x = 3; x < 10; x++)
        for(y = 14; y < 20; y++)
            for(i = 1; i < 15; i++)
                mvaddch(y^i, x+i-3, ACS_BOARD);

    //Desenha as paredes do castelo
    setColor(COLOR_BLACK, COLOR_WHITE, A_BOLD);
    for(x = 25; x < 56; x++)
        for(y = 0; y < 11; y++)
            mvaddch(y, x, ACS_SSSS);

    //Desenha o tapete do castelo
    setColor(COLOR_RED, COLOR_RED, A_BOLD);
    mvaddch(10, 40, ACS_DIAMOND);
    for(x = 26; x < 55; x++)
        for(y = 1; y < 10; y++)
                mvaddch(y, x, ACS_DIAMOND);

    //Desenha o trono
    setColor(COLOR_YELLOW, COLOR_YELLOW, A_BOLD);
        mvaddch(0, 39, ACS_BLOCK); mvaddch(0, 41, ACS_BLOCK);
        for(x = 39; x < 42; x++)
            for(y = 1; y < 3; y++)
                mvaddch(y, x, ACS_BLOCK);
        for(x = 38; x < 43; x++)
            for(y = 3; y < 5; y++)
                mvaddch(y, x, ACS_BLOCK);
}

void ghost()
{
    //Fundo
        setColor(COLOR_BLACK, COLOR_BLACK, 0);
        for(x = 0; x < 80; x++)
            for(y = 0; y < 25; y++)
                mvaddch(y, x, ACS_BLOCK);

        //"Corpo"
        setColor(COLOR_WHITE, COLOR_WHITE, A_BOLD);
        for(x = 35; x < 45; x++)
            for(y = 4; y < 19; y++)
                mvaddch(y, x, ACS_BLOCK);
        for(x = 37; x < 43; x++)
            mvaddch(3, x, ACS_BLOCK);
        for(x = 38; x < 43; x++)
            mvaddch(2, x, ACS_BLOCK);
        mvaddch(19, 35, ACS_BLOCK);
        mvaddch(19, 39, ACS_BLOCK);
        mvaddch(19, 40, ACS_BLOCK);
        mvaddch(20, 40, ACS_BLOCK);
        mvaddch(19, 44, ACS_BLOCK);

        //Pontas
        setColor(COLOR_BLACK, COLOR_WHITE, A_BOLD);
        mvaddch(19, 36, ACS_BLOCK);
        mvaddch(19, 38, ACS_BLOCK);
        mvaddch(19, 41, ACS_BLOCK);
        mvaddch(20, 35, ACS_BLOCK);
        mvaddch(20, 39, ACS_BLOCK);
        mvaddch(21, 40, ACS_BLOCK);

        //Olhos
        setColor(COLOR_BLACK, COLOR_BLACK, 0);
        mvaddch(5, 37, ACS_BLOCK);mvaddch(5, 38, ACS_BLOCK);mvaddch(6, 36, ACS_BLOCK);mvaddch(6, 37, ACS_BLOCK);mvaddch(6, 38, ACS_BLOCK);mvaddch(7, 36, ACS_BLOCK);mvaddch(7, 37, ACS_BLOCK);mvaddch(7, 38, ACS_BLOCK);
        mvaddch(5, 41, ACS_BLOCK);mvaddch(5, 42, ACS_BLOCK);mvaddch(6, 41, ACS_BLOCK);mvaddch(6, 42, ACS_BLOCK);mvaddch(6, 43, ACS_BLOCK);mvaddch(7, 41, ACS_BLOCK);mvaddch(7, 42, ACS_BLOCK);mvaddch(7, 43, ACS_BLOCK);

        //Boca
        mvaddch(9, 39, ACS_BLOCK);mvaddch(9, 40, ACS_BLOCK);
        mvaddch(10, 38, ACS_BLOCK);mvaddch(10, 39, ACS_BLOCK);mvaddch(10, 40, ACS_BLOCK);mvaddch(10, 41, ACS_BLOCK);
        mvaddch(11, 38, ACS_BLOCK);mvaddch(11, 39, ACS_BLOCK);mvaddch(11, 40, ACS_BLOCK);mvaddch(11, 41, ACS_BLOCK);
        mvaddch(12, 38, ACS_BLOCK);mvaddch(12, 41, ACS_BLOCK);

        //Sombreado
        setColor(COLOR_WHITE, COLOR_WHITE, A_BLINK);
        mvaddch(2, 37, ACS_BLOCK);
        mvaddch(3, 36, ACS_BLOCK);
        mvaddch(3, 43, ACS_BLOCK);
        for(y = 10; y < 15; y++)mvaddch(y, 35, ACS_BLOCK);
        for(y = 8; y < 18; y++)mvaddch(y, 44, ACS_BLOCK);
}

void zombie()
{
    //Fundo
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    for(x = 0; x < 80; x++)
        for(y = 0; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Cabe�a
    setColor(COLOR_GREEN, 0, A_BOLD);
    for(x = 36; x < 44; x++)mvaddch(2, x, ACS_BLOCK);
    for(x = 35; x < 45; x++)
        for(y = 3; y < 9; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 37; x < 43; x++)mvaddch(2, x, ACS_BLOCK);
    for(x = 34; x < 46; x++)mvaddch(8, x, ACS_BLOCK);

    //Olhos
    setColor(COLOR_WHITE, 0, A_BOLD);
    mvaddch(3, 37, ACS_BLOCK);mvaddch(3, 38, ACS_BLOCK);mvaddch(4, 37, ACS_BLOCK);
    setColor(COLOR_RED, 0, A_BOLD);
    mvaddch(4, 38, ACS_BLOCK);mvaddch(4, 41, ACS_BLOCK);

    //Boca
    setColor(COLOR_BLACK, 0, 0);
    for(x = 38; x < 42; x++)
        mvaddch(6, x, ACS_BLOCK);
    mvaddch(7, 37, ACS_BLOCK);mvaddch(7, 38, ACS_BLOCK);
    setColor(COLOR_GREEN, 0, 0);
    mvaddch(7, 41, ACS_BLOCK);mvaddch(7, 42, ACS_BLOCK);mvaddch(8, 42, ACS_BLOCK);

    //Camisa
    setColor(COLOR_YELLOW, 0, 0);
    for(x = 33; x < 47; x++)
        for(y = 9; y < 14; y++)
            mvaddch(y, x, ACS_CKBOARD);
    for(x = 33; x < 40; x++)
        for(y = 14; y < 17; y++)
            mvaddch(y, x, ACS_CKBOARD);
    for(x = 33; x < 39; x++)mvaddch(y, x, ACS_CKBOARD);
    mvaddch(14, 40, ACS_CKBOARD);mvaddch(14, 41, ACS_CKBOARD);
    setColor(COLOR_GREEN, 0, A_BOLD);
    mvaddch(14, 38, ACS_BLOCK);mvaddch(10, 35, ACS_BLOCK);mvaddch(10, 36, ACS_BLOCK);mvaddch(11, 35, ACS_BLOCK);

    //Mangas
    setColor(COLOR_YELLOW, 0, 0);
    for(x = 22; x < 25; x++)mvaddch(5, x, ACS_CKBOARD);
    for(x = 26; x < 29; x++)mvaddch(5, x, ACS_CKBOARD);
    for(x = 22; x < 30; x++)mvaddch(6, x, ACS_CKBOARD);
    for(x = 24; x < 32; x++)mvaddch(7, x, ACS_CKBOARD);
    for(x = 26; x < 34; x++)mvaddch(8, x, ACS_CKBOARD);
    for(x = 26; x < 33; x++)mvaddch(9, x, ACS_CKBOARD);
    for(x = 28; x < 33; x++)mvaddch(10, x, ACS_CKBOARD);
    for(x = 30; x < 33; x++)mvaddch(11, x, ACS_CKBOARD);

    for(x = 54; x < 60; x++)mvaddch(7, x, ACS_CKBOARD);
    for(x = 46; x < 49; x++)mvaddch(8, x, ACS_CKBOARD);for(x = 52; x < 59; x++)mvaddch(8, x, ACS_CKBOARD);
    for(x = 47; x < 57; x++)mvaddch(9, x, ACS_CKBOARD);
    for(x = 47; x < 56; x++)mvaddch(10, x, ACS_CKBOARD);
    for(x = 47; x < 54; x++)mvaddch(11, x, ACS_CKBOARD);
    for(x = 49; x < 52; x++)mvaddch(12, x, ACS_CKBOARD);

    //M�os
    setColor(COLOR_GREEN, 0, A_BOLD);
    mvaddch(1, 22, ACS_BLOCK);mvaddch(1, 24, ACS_BLOCK);
    mvaddch(2, 23, ACS_BLOCK);mvaddch(2, 24, ACS_BLOCK);
    mvaddch(3, 21, ACS_BLOCK);mvaddch(3, 22, ACS_BLOCK);mvaddch(3, 23, ACS_BLOCK);mvaddch(3, 24, ACS_BLOCK);mvaddch(3, 25, ACS_BLOCK);
    mvaddch(4, 23, ACS_BLOCK);mvaddch(4, 24, ACS_BLOCK);mvaddch(4, 25, ACS_BLOCK);mvaddch(4, 26, ACS_BLOCK);
    mvaddch(5, 25, ACS_BLOCK);

    mvaddch(3, 56, ACS_BLOCK);mvaddch(3, 58, ACS_BLOCK);
    mvaddch(4, 56, ACS_BLOCK);mvaddch(4, 57, ACS_BLOCK);
    mvaddch(5, 56, ACS_BLOCK);mvaddch(5, 57, ACS_BLOCK);mvaddch(5, 58, ACS_BLOCK);mvaddch(5, 59, ACS_BLOCK);
    mvaddch(6, 55, ACS_BLOCK);mvaddch(6, 56, ACS_BLOCK);mvaddch(6, 57, ACS_BLOCK);mvaddch(6, 58, ACS_BLOCK);

    //Torax rasgado
    setColor(COLOR_GREEN, 0, A_BOLD);
    for(x = 42; x < 46; x++)mvaddch(14, x, ACS_BLOCK);
    setColor(COLOR_GREEN, 0, 0);
    for(x = 40; x < 45; x++)mvaddch(15, x, ACS_BLOCK);
    setColor(COLOR_WHITE, 0, 0);
    for(x = 40; x < 46; x++)mvaddch(16, x, ACS_BLOCK);
    setColor(COLOR_GREEN, 0, 0);
    for(x = 39; x < 45; x++)mvaddch(17, x, ACS_BLOCK);

    //Cal�a
    setColor(COLOR_BLUE, 0, 0);
    for(x = 33; x < 46; x++)mvaddch(18, x, ACS_BLOCK);
    for(x = 32; x < 46; x++)
        for(y = 19; y < 20; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 32; x < 39; x++)
        for(y = 20; y < 22; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 31; x < 38; x++)
        for(y = 22; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 40; x < 46; x++)
        for(y = 20; y < 23; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 41; x < 47; x++)
        for(y = 23; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
}

void merman()
{
    //Fundo
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    for(x = 0; x < 80; x++)
        for(y = 0; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Cabe�a
    setColor(COLOR_CYAN, 0, A_BOLD);
    for(x = 36; x < 44; x++){mvaddch(4, x, ACS_BLOCK);mvaddch(10, x, ACS_BLOCK);}
    for(x = 35; x < 45; x++)
        for(y = 5; y < 10; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 38; x < 42; x++)
        for(y = 11; y < 13; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Nadadeiras
    mvaddch(3, 31, ACS_BLOCK);                                                              mvaddch(3, 48, ACS_BLOCK);
            mvaddch(4, 32, ACS_BLOCK);                                              mvaddch(4, 47, ACS_BLOCK);
                    mvaddch(5, 33, ACS_BLOCK);                              mvaddch(5, 46, ACS_BLOCK);
                            mvaddch(6, 34, ACS_BLOCK);              mvaddch(6, 45, ACS_BLOCK);
                                    for(x = 29; x < 51; x++)mvaddch(7, x, ACS_BLOCK);
                            mvaddch(8, 34, ACS_BLOCK);              mvaddch(8, 45, ACS_BLOCK);
                    mvaddch(9, 33, ACS_BLOCK);                              mvaddch(9, 46, ACS_BLOCK);
            mvaddch(10, 32, ACS_BLOCK);                                             mvaddch(10, 47, ACS_BLOCK);
    mvaddch(11, 31, ACS_BLOCK);                                                             mvaddch(11, 48, ACS_BLOCK);

    setColor(COLOR_CYAN, 0, 0);
                                mvaddch(4, 31, ACS_BLOCK);                                                                                                                            mvaddch(4, 48, ACS_BLOCK);
                                mvaddch(5, 31, ACS_BLOCK);mvaddch(5, 32, ACS_BLOCK);                                                                        mvaddch(5, 47, ACS_BLOCK);mvaddch(5, 48, ACS_BLOCK);
    mvaddch(6, 30, ACS_BLOCK);mvaddch(6, 31, ACS_BLOCK);mvaddch(6, 32, ACS_BLOCK);mvaddch(6, 33, ACS_BLOCK);                    mvaddch(6, 46, ACS_BLOCK);mvaddch(6, 47, ACS_BLOCK);mvaddch(6, 48, ACS_BLOCK);mvaddch(6, 49, ACS_BLOCK);

    mvaddch(8, 30, ACS_BLOCK);mvaddch(8, 31, ACS_BLOCK);mvaddch(8, 32, ACS_BLOCK);mvaddch(8, 33, ACS_BLOCK);                    mvaddch(8, 46, ACS_BLOCK);mvaddch(8, 47, ACS_BLOCK);mvaddch(8, 48, ACS_BLOCK);mvaddch(8, 49, ACS_BLOCK);
                              mvaddch(9, 31, ACS_BLOCK);mvaddch(9, 32, ACS_BLOCK);                                                                        mvaddch(9, 47, ACS_BLOCK);mvaddch(9, 48, ACS_BLOCK);
                              mvaddch(10, 31, ACS_BLOCK);                                                                                                                           mvaddch(10, 48, ACS_BLOCK);

    //Olhos
    setColor(COLOR_BLUE, 0, 0);
    mvaddch(5, 36, ACS_BLOCK);mvaddch(5, 37, ACS_BLOCK);mvaddch(6, 36, ACS_BLOCK);mvaddch(6, 37, ACS_BLOCK);mvaddch(6, 38, ACS_BLOCK);
    mvaddch(5, 42, ACS_BLOCK);mvaddch(5, 43, ACS_BLOCK);mvaddch(6, 41, ACS_BLOCK);mvaddch(6, 42, ACS_BLOCK);mvaddch(6, 43, ACS_BLOCK);

    //Boca
    setColor(COLOR_BLACK, 0, 0);
    for(x = 36; x < 44; x++)
        for(y = 8; y < 10; y++)
            mvaddch(y, x, ACS_BLOCK);
    setColor(COLOR_WHITE, 0, 0);
    mvaddch(8, 37, 223);mvaddch(8, 39, 223);mvaddch(8, 41, 223);mvaddch(8, 43, 223);
    mvaddch(9, 36, 220);mvaddch(9, 38, 220);mvaddch(9, 40, 220);mvaddch(9, 42, 220);

    //Corpo
    setColor(COLOR_CYAN, 0, A_BOLD);
    for(x = 36; x < 44; x++)
        for(y = 13; y < 16; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 35; x < 45; x++)
        for(y = 16; y < 20; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Bra�os
    setColor(COLOR_CYAN, 0, A_BOLD);
    for(x = 28; x < 36; x++){mvaddch(13, x, ACS_BLOCK);mvaddch(13, x+16, ACS_BLOCK);}
    for(x = 27; x < 29; x++){mvaddch(12, x, ACS_BLOCK);mvaddch(12, x+24, ACS_BLOCK);}
    for(x = 26; x < 28; x++){mvaddch(11, x, ACS_BLOCK);mvaddch(11, x+26, ACS_BLOCK);}
    for(x = 25; x < 27; x++){mvaddch(10, x, ACS_BLOCK);mvaddch(10, x+28, ACS_BLOCK);}
    for(x = 24; x < 26; x++){mvaddch(9, x, ACS_BLOCK);mvaddch(9, x+30, ACS_BLOCK);}

    //M�os
    mvaddch(8, 20, ACS_BLOCK);mvaddch(8, 21, ACS_BLOCK);mvaddch(8, 22, ACS_BLOCK);mvaddch(8, 23, ACS_BLOCK);mvaddch(8, 24, ACS_BLOCK);
    mvaddch(9, 20, ACS_BLOCK);                          mvaddch(9, 22, ACS_BLOCK);
    mvaddch(10, 20, ACS_BLOCK);

    mvaddch(8, 56, ACS_BLOCK);mvaddch(8, 57, ACS_BLOCK);mvaddch(8, 58, ACS_BLOCK);mvaddch(8, 59, ACS_BLOCK);
                              mvaddch(9, 57, ACS_BLOCK);                                                    mvaddch(9, 60, ACS_BLOCK);
                                                        mvaddch(10, 58, ACS_BLOCK);

    //Cauda
    setColor(COLOR_CYAN, 0, 0);
    for(x = 35; x < 45; x++){mvaddch(20, x, ACS_BLOCK);mvaddch(21, x, ACS_BLOCK);mvaddch(22, x, ACS_BLOCK);}
    for(x = 35; x < 44; x++)mvaddch(23, x, ACS_BLOCK);
    for(x = 36; x < 44; x++)mvaddch(24, x, ACS_BLOCK);

    for(x = 56; x < 60; x++)mvaddch(24, x, ACS_BLOCK);
    for(x = 57; x < 59; x++){mvaddch(23, x, ACS_BLOCK);mvaddch(22, x, ACS_BLOCK);}
    for(x = 53; x < 58; x++){mvaddch(21, x, ACS_BLOCK);mvaddch(21, x+5, ACS_BLOCK);}
    for(x = 52; x < 57; x++){mvaddch(20, x, ACS_BLOCK);mvaddch(20, x+7, ACS_BLOCK);}
    for(x = 51; x < 55; x++){mvaddch(19, x, ACS_BLOCK);mvaddch(19, x+10, ACS_BLOCK);}
    for(x = 51; x < 55; x++){mvaddch(18, x, ACS_BLOCK);mvaddch(18, x+10, ACS_BLOCK);}
    for(x = 52; x < 54; x++){mvaddch(17, x, ACS_BLOCK);mvaddch(17, x+10, ACS_BLOCK);}
                    mvaddch(16, 53, ACS_BLOCK);mvaddch(16, 62, ACS_BLOCK);

    //Algas
    setColor(COLOR_GREEN, COLOR_GREEN, A_BOLD);
    mvaddch(15, 36, ACS_BOARD);
                               mvaddch(16, 37, ACS_BOARD);
                               mvaddch(17, 37, ACS_BOARD);

    mvaddch(13, 37, ACS_BOARD);mvaddch(13, 38, ACS_BOARD);                                                                                                                                                                                                                        mvaddch(13, 47, ACS_BOARD);
                                                          mvaddch(14, 39, ACS_BOARD);mvaddch(14, 40, ACS_BOARD);                                                                                                            mvaddch(14, 45, ACS_BOARD);mvaddch(14, 46, ACS_BOARD);                                                      mvaddch(14, 49, ACS_BOARD);
                                                                                                                mvaddch(15, 41, ACS_BOARD);mvaddch(15, 42, ACS_BOARD);mvaddch(15, 43, ACS_BOARD);mvaddch(15, 44, ACS_BOARD);                                                                                                            mvaddch(15, 49, ACS_BOARD);

    mvaddch(8, 23, ACS_BOARD);
    mvaddch(9, 23, ACS_BOARD);
    mvaddch(10, 23, ACS_BOARD);
    mvaddch(11, 23, ACS_BOARD);
    mvaddch(12, 23, ACS_BOARD);

    mvaddch(20, 60, ACS_BOARD);
    mvaddch(21, 60, ACS_BOARD);
    mvaddch(22, 60, ACS_BOARD);

    //Escamas
    setColor(COLOR_BLACK, COLOR_CYAN, 0);
    mvaddch(21, 36, 'V');mvaddch(21, 38, 'V');mvaddch(21, 40, 'V');mvaddch(21, 42, 'V');
                         mvaddch(23, 37, 'V');mvaddch(23, 39, 'V');mvaddch(23, 41, 'V');mvaddch(223, 43, 'V');

}

void vampire()
{
    //Fundo
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    for(x = 0; x < 80; x++)
        for(y = 0; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Cabelo
    setColor(COLOR_RED, 0, 0);
    for(x = 35; x < 45; x++)mvaddch(2, x, ACS_BLOCK);
    for(x = 34; x < 47; x++)mvaddch(3, x, ACS_BLOCK);
    for(y = 4; y < 7; y++)
        {mvaddch(y, 34, ACS_BLOCK);
         mvaddch(y, 45, ACS_BLOCK);}

    //Cabe�a
    setColor(COLOR_WHITE, 0, A_BOLD);
    for(x = 36; x < 40; x++)mvaddch(3, x, ACS_BLOCK);
    for(x = 35; x < 45; x++)
        for(y = 4; y < 8; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 36; x < 44; x++)mvaddch(8, x, ACS_BLOCK);

    //Olhos
    setColor(COLOR_BLACK, COLOR_WHITE, A_BLINK);
    mvaddch(4, 38, '\\');mvaddch(4, 41, '\/');
    setColor(COLOR_RED, 0, A_BOLD);
    mvaddch(5, 38, ACS_BLOCK);mvaddch(5, 41, ACS_BLOCK);

    //Boca
    setColor(COLOR_BLACK, COLOR_WHITE, A_BLINK);
    mvaddch(7, 36, 223);mvaddch(7, 37, ACS_BLOCK);mvaddch(7, 39, ACS_BLOCK);mvaddch(7, 40, ACS_BLOCK);mvaddch(7, 42, ACS_BLOCK);mvaddch(7, 43, 223);
    setColor(COLOR_WHITE, COLOR_BLACK, 0);
    mvaddch(7, 38, 287);mvaddch(7, 41, 287);

    //Capa
    setColor(COLOR_BLUE, 0, 0);
    for(x = 40; x < 47; x++)
        for(y = 9; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 40; x < 49; x++)
        for(y = 11; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 40; x < 50; x++)
        for(y = 13; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 30; x < 40; x++)mvaddch(9, x, ACS_BLOCK);
    for(x = 25; x < 40; x++)mvaddch(10, x, ACS_BLOCK);
    mvaddch(10, 20, ACS_BLOCK);mvaddch(10, 22, ACS_BLOCK);
    for(y = 11; y < 15; y++)mvaddch(y, 19, ACS_BLOCK);
    for(y = 14; y < 18; y++)mvaddch(y, 18, ACS_BLOCK);
    for(y = 17; y < 25; y++)mvaddch(y, 17, ACS_BLOCK);

    setColor(COLOR_RED, 0, A_BOLD);
    for(x = 20; x < 40; x++)
        for(y = 11; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 19; x < 40; x++)
        for(y = 14; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 18; x < 40; x++)
        for(y = 17; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Traje
    setColor(COLOR_RED, 0, 0);
    for(x = 25; x < 40; x++)
        for(y = 11; y < 13; y++)
            mvaddch(y, x, ACS_CKBOARD);
    for(x = 25; x < 40; x++)mvaddch(12, x, ACS_CKBOARD);
    for(x = 30; x < 40; x++)mvaddch(13, x, ACS_CKBOARD);
    for(x = 35; x < 40; x++)
        for(y = 14; y < 25; y++)
            mvaddch(y, x, ACS_CKBOARD);

    setColor(COLOR_YELLOW, 0, A_BOLD);
    for(x = 35; x < 40; x++)mvaddch(20, x, ACS_BLOCK);

    //Gema
    setColor(COLOR_YELLOW, COLOR_BLUE, A_BOLD);
                                mvaddch(9, 40, 220);
    mvaddch(10, 39, ACS_BLOCK);                     mvaddch(10, 41, ACS_BLOCK);
                                mvaddch(11, 40, 223);
                          setColor(COLOR_GREEN, 0, A_BOLD);
                             mvaddch(10, 40, ACS_BLOCK);

    //M�o
    setColor(COLOR_WHITE, COLOR_BLUE, A_BOLD);
    mvaddch(9, 21, ACS_BLOCK);mvaddch(9, 22, ACS_BLOCK);mvaddch(9, 23, ACS_BLOCK);
    mvaddch(10, 21, 223);                         mvaddch(10, 23, ACS_BLOCK);mvaddch(10, 24, ACS_BLOCK);
                              mvaddch(11, 22, ACS_BLOCK);mvaddch(11, 23, ACS_BLOCK);mvaddch(11, 24, ACS_BLOCK);

}

void minotaur()
{
    //Fundo
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    for(x = 0; x < 80; x++)
        for(y = 0; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Cabe�a
    setColor(COLOR_RED, 0, 0);
    for(x = 34; x < 46; x++)
        for(y = 5; y < 10; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 35; x < 45; x++){mvaddch(10, x, ACS_BLOCK);mvaddch(4, x, ACS_BLOCK);}
    for(x = 36; x < 44; x++){mvaddch(11, x, ACS_BLOCK);mvaddch(12, x, ACS_BLOCK);}

    //Chifres
    setColor(COLOR_WHITE, 0, 0);
    mvaddch(0, 29, ACS_BLOCK);                           mvaddch(0, 50, ACS_BLOCK);
    for(x = 28; x < 30; x++){mvaddch(1, x, ACS_BLOCK);mvaddch(1, x+22, ACS_BLOCK);}
    mvaddch(2, 28, ACS_BLOCK);                           mvaddch(2, 51, ACS_BLOCK);
    for(x = 27; x < 29; x++){mvaddch(3, x, ACS_BLOCK);mvaddch(3, x+24, ACS_BLOCK);}
    for(x = 27; x < 30; x++){mvaddch(4, x, ACS_BLOCK);mvaddch(4, x+23, ACS_BLOCK);}
    for(x = 28; x < 32; x++){mvaddch(5, x, ACS_BLOCK);mvaddch(5, x+20, ACS_BLOCK);}
    for(x = 29; x < 34; x++){mvaddch(6, x, ACS_BLOCK);mvaddch(6, x+17, ACS_BLOCK);}
    for(x = 30; x < 34; x++){mvaddch(7, x, ACS_BLOCK);mvaddch(7, x+16, ACS_BLOCK);}

    //Olhos
    setColor(COLOR_RED, COLOR_RED, A_BOLD);
    mvaddch(7, 36, ACS_BLOCK);mvaddch(8, 36, ACS_BLOCK);mvaddch(7, 37, 220);mvaddch(8, 37, ACS_BLOCK);mvaddch(8, 38, ACS_BLOCK);
    mvaddch(8, 41, ACS_BLOCK);mvaddch(8, 42, ACS_BLOCK);mvaddch(7, 42, 220);mvaddch(8, 43, ACS_BLOCK);mvaddch(7, 43, ACS_BLOCK);

    //Focinho
    setColor(COLOR_BLACK, 0, 0);
    mvaddch(11, 37, ACS_BLOCK);mvaddch(11, 42, ACS_BLOCK);


    //Anel do nariz
    setColor(COLOR_YELLOW, 0, A_BOLD);
    mvaddch(11, 41, 220);mvaddch(11, 38, 220);
    mvaddch(12, 37, ACS_BLOCK);mvaddch(12, 42, ACS_BLOCK);
    mvaddch(13, 37, ACS_BLOCK);mvaddch(13, 42, ACS_BLOCK);
    setColor(COLOR_RED, COLOR_YELLOW, A_BLINK);
    mvaddch(14, 38, 220);mvaddch(14, 41, 220);
    setColor(COLOR_YELLOW, COLOR_RED, A_BOLD);
    mvaddch(14, 39, 220);mvaddch(14, 40, 220);

    //Corpo
    setColor(COLOR_RED, 0, A_BOLD);
    mvaddch(11, 35, ACS_BLOCK);                           mvaddch(11, 44, ACS_BLOCK);
    for(x = 25; x < 36; x++){mvaddch(12, x, ACS_BLOCK);mvaddch(12, x+19, ACS_BLOCK);}
    for(x = 20; x < 37; x++)mvaddch(13, x, ACS_BLOCK);for(x = 43; x < 57; x++)mvaddch(13, x, ACS_BLOCK);
                for(x = 38; x < 42; x++)mvaddch(13, x, ACS_BLOCK);
    for(x = 30; x < 50; x++)
        for(y = 15; y < 21; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 33; x < 47; x++)
        for(y = 15; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Bra�os
    for(x = 17; x < 35; x++)mvaddch(14, x, ACS_BLOCK);
    for(x = 16; x < 35; x++)mvaddch(15, x, ACS_BLOCK);
    for(x = 16; x < 35; x++)mvaddch(16, x, ACS_BLOCK);
    for(x = 16; x < 21; x++)mvaddch(17, x, ACS_BLOCK);for(x = 27; x < 35; x++)mvaddch(17, x, ACS_BLOCK);
    setColor(COLOR_YELLOW, 0, A_BOLD);
    for(x = 16; x < 20; x++)mvaddch(18, x, ACS_BLOCK);
    for(x = 16; x < 20; x++)mvaddch(19, x, ACS_BLOCK);
    for(x = 16; x < 20; x++)mvaddch(20, x, ACS_BLOCK);
    setColor(COLOR_RED, 0, A_BOLD);
    for(x = 17; x < 22; x++)mvaddch(21, x, ACS_BLOCK);
    mvaddch(22, 17, ACS_BLOCK);mvaddch(22, 18, ACS_BLOCK);
    mvaddch(23, 18, ACS_BLOCK);mvaddch(23, 19, 220);mvaddch(23, 20, 220);mvaddch(23, 21, ACS_BLOCK);

    for(x = 46; x < 58; x++)mvaddch(14, x, ACS_BLOCK);
    for(x = 46; x < 58; x++)mvaddch(15, x, ACS_BLOCK);
    for(x = 46; x < 59; x++)mvaddch(16, x, ACS_BLOCK);
    for(x = 52; x < 59; x++)mvaddch(17, x, ACS_BLOCK);
    for(x = 53; x < 59; x++)mvaddch(18, x, ACS_BLOCK);
    for(x = 53; x < 60; x++)mvaddch(19, x, ACS_BLOCK);
    for(x = 53; x < 60; x++)mvaddch(20, x, ACS_BLOCK);
    for(x = 54; x < 60; x++)mvaddch(21, x, ACS_BLOCK);
    setColor(COLOR_YELLOW, 0, A_BOLD);
    for(x = 60; x < 64; x++)mvaddch(19, x, ACS_BLOCK);
    for(x = 60; x < 64; x++)mvaddch(20, x, ACS_BLOCK);
    for(x = 60; x < 64; x++)mvaddch(21, x, ACS_BLOCK);
    setColor(COLOR_RED, 0, A_BOLD);
    mvaddch(18, 64, ACS_BLOCK);mvaddch(18, 65, ACS_BLOCK);
                               mvaddch(19, 65, ACS_BLOCK);
    mvaddch(19, 67, ACS_BLOCK);mvaddch(20, 67, ACS_BLOCK);mvaddch(21, 67, ACS_BLOCK);
    mvaddch(21, 64, ACS_BLOCK);

    //M�sculos
    setColor(COLOR_RED, 0, 0);
    for(x = 34; x < 38; x++){mvaddch(14, x, ACS_BLOCK);mvaddch(14, x+8, ACS_BLOCK);}
    for(x = 33; x < 39; x++){mvaddch(19, x, ACS_BLOCK);mvaddch(19, x+8, ACS_BLOCK);}
                for(y = 16; y < 19; y++){mvaddch(y, 32, ACS_BLOCK);mvaddch(y, 47, ACS_BLOCK);}
    for(y = 15; y < 19; y++){mvaddch(y, 39, ACS_BLOCK);mvaddch(y, 40, ACS_BLOCK);}
                for(y = 20; y < 22; y++){mvaddch(y, 35, ACS_BLOCK);mvaddch(y, 44, ACS_BLOCK);
                                         mvaddch(y+3, 35, ACS_BLOCK);mvaddch(y+3, 44, ACS_BLOCK);}
    for(y = 20; y < 22; y++){mvaddch(y, 39, ACS_BLOCK);mvaddch(y, 40, ACS_BLOCK);}
                for(x = 36; x < 39; x++){mvaddch(22, x, ACS_BLOCK);mvaddch(22, x+5, ACS_BLOCK);}
    for(y = 23; y < 25; y++){mvaddch(y, 39, ACS_BLOCK);mvaddch(y, 40, ACS_BLOCK);}

    //Porrete
    setColor(COLOR_YELLOW, 0, 0);
    for(x = 63; x < 69; x++){mvaddch(6, x, ACS_BLOCK);mvaddch(14, x, ACS_BLOCK);}
    for(x = 62; x < 70; x++){mvaddch(7, x, ACS_BLOCK);mvaddch(8, x, ACS_BLOCK);mvaddch(12, x, ACS_BLOCK);mvaddch(13, x, ACS_BLOCK);}
    for(x = 61; x < 71; x++){mvaddch(9, x, ACS_BLOCK);mvaddch(10, x, ACS_BLOCK);mvaddch(11, x, ACS_BLOCK);}
    for(x = 64; x < 68; x++){mvaddch(15, x, ACS_BLOCK);mvaddch(16, x, ACS_BLOCK);mvaddch(17, x, ACS_BLOCK);}
    mvaddch(18, 66, ACS_BLOCK);
    mvaddch(19, 64, ACS_BLOCK);mvaddch(19, 66, ACS_BLOCK);
    mvaddch(20, 64, ACS_BLOCK);mvaddch(20, 65, ACS_BLOCK);mvaddch(20, 66, ACS_BLOCK);
                               mvaddch(21, 65, ACS_BLOCK);mvaddch(21, 66, ACS_BLOCK);
                               mvaddch(22, 65, ACS_BLOCK);mvaddch(22, 66, ACS_BLOCK);
                               mvaddch(23, 65, ACS_BLOCK);mvaddch(23, 66, ACS_BLOCK);
    setColor(COLOR_BLACK, COLOR_YELLOW, 0);
    mvaddch(7, 63, '*');mvaddch(10, 67, '*');mvaddch(12, 65, '*');mvaddch(16, 66, '*');
}

void king()
{
    //Fundo
    setColor(COLOR_BLACK, COLOR_BLACK, 0);
    for(x = 0; x < 80; x++)
        for(y = 0; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Coroa
    setColor(COLOR_YELLOW, 0, A_BOLD);
    for(x = 36; x < 45; x++)
        for(y = 3; y < 5; y++)
            mvaddch(y, x, ACS_BLOCK);
    mvaddch(2, 36, ACS_BLOCK);mvaddch(2, 37, ACS_BLOCK);mvaddch(1, 36, ACS_BLOCK);
    mvaddch(2, 39, ACS_BLOCK);mvaddch(2, 40, ACS_BLOCK);mvaddch(2, 41, ACS_BLOCK);mvaddch(1, 40, ACS_BLOCK);mvaddch(0, 40, ACS_BLOCK);
    mvaddch(2, 43, ACS_BLOCK);mvaddch(2, 44, ACS_BLOCK);mvaddch(1, 44, ACS_BLOCK);
        setColor(COLOR_CYAN, COLOR_YELLOW, A_BLINK);
        mvaddch(3, 40, ACS_DIAMOND);
        mvaddch(4, 37, ACS_DIAMOND);
        mvaddch(4, 43, ACS_DIAMOND);

    //Capa
    setColor(COLOR_RED, 0, 0);
    for(x = 33; x < 48; x++)
        for(y = 10; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 31; x < 50; x++)
        for(y = 11; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 30; x < 51; x++)
        for(y = 13; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 29; x < 52; x++)
        for(y = 16; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Cabe�a
    setColor(COLOR_YELLOW, 0, 0);
    for(x = 35; x < 46; x++)
        for(y = 5; y < 11; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Olhos
    setColor(COLOR_RED, 0, A_BOLD);
    mvaddch(6, 37, ACS_BLOCK);mvaddch(7, 37, ACS_BLOCK);mvaddch(7, 38, ACS_BLOCK);
    mvaddch(6, 43, ACS_BLOCK);mvaddch(7, 42, ACS_BLOCK);mvaddch(7, 43, ACS_BLOCK);

    //Boca
    setColor(COLOR_BLACK, 0, 0);
    mvaddch(8, 36, ACS_BLOCK);mvaddch(8, 44, ACS_BLOCK);mvaddch(9, 36, ACS_BLOCK);mvaddch(9, 44, ACS_BLOCK);
    for(x = 37; x < 44; x++)mvaddch(9, x, ACS_BLOCK);

    //Traje
    setColor(COLOR_BLUE, 0, A_BOLD);
    mvaddch(11, 40, ACS_BLOCK);
    for(x = 39; x < 42; x++)mvaddch(12, x, ACS_CKBOARD);
    for(x = 39; x < 42; x++)mvaddch(13, x, ACS_CKBOARD);
    for(x = 38; x < 43; x++)mvaddch(14, x, ACS_CKBOARD);
    for(x = 38; x < 43; x++)mvaddch(15, x, ACS_CKBOARD);
    for(x = 38; x < 43; x++)mvaddch(16, x, ACS_CKBOARD);
    for(x = 37; x < 44; x++)mvaddch(17, x, ACS_CKBOARD);
    for(x = 37; x < 44; x++)mvaddch(18, x, ACS_CKBOARD);
    for(x = 37; x < 44; x++)mvaddch(19, x, ACS_CKBOARD);
    for(x = 37; x < 44; x++)mvaddch(20, x, ACS_CKBOARD);
    for(x = 36; x < 45; x++)mvaddch(21, x, ACS_CKBOARD);
    for(x = 36; x < 45; x++)mvaddch(22, x, ACS_CKBOARD);
    for(x = 36; x < 45; x++)mvaddch(23, x, ACS_CKBOARD);
    for(x = 36; x < 45; x++)mvaddch(24, x, ACS_CKBOARD);
    setColor(COLOR_GREEN, 0, A_BOLD);
    mvaddch(12, 40, ACS_BLOCK);
    mvaddch(15, 40, ACS_BLOCK);
    mvaddch(18, 40, ACS_BLOCK);
    mvaddch(21, 40, ACS_BLOCK);
    mvaddch(24, 40, ACS_BLOCK);

    //Detalhes
    setColor(COLOR_WHITE, 0, A_BOLD);
    mvaddch(11, 40, ACS_BLOCK);
    for(y = 12; y < 14; y++){mvaddch(y, 39, ACS_BLOCK);mvaddch(y, 41, ACS_BLOCK);}
    for(y = 14; y < 17; y++){mvaddch(y, 38, ACS_BLOCK);mvaddch(y, 42, ACS_BLOCK);}
    for(y = 17; y < 21; y++){mvaddch(y, 37, ACS_BLOCK);mvaddch(y, 43, ACS_BLOCK);}
    for(y = 21; y < 26; y++){mvaddch(y, 36, ACS_BLOCK);mvaddch(y, 44, ACS_BLOCK);}
    setColor(COLOR_BLACK, 0, A_BOLD);
    mvaddch(12, 35, ACS_BLOCK);mvaddch(12, 45, ACS_BLOCK);
    mvaddch(16, 34, ACS_BLOCK);mvaddch(16, 46, ACS_BLOCK);
    mvaddch(21, 33, ACS_BLOCK);mvaddch(21, 47, ACS_BLOCK);
}

void diana()
{
    //Fundo
        setColor(COLOR_WHITE, COLOR_WHITE, 0);
        for(x = 0; x < 80; x++)
            for(y = 0; y < 25; y++)
                mvaddch(y, x, ACS_BLOCK);

        //Cabelo
        setColor(COLOR_YELLOW, 0, A_BOLD);
        for(x = 35; x < 45; x++)mvaddch(2, x, ACS_BLOCK);
        for(x = 33; x < 47; x++)
            for(y = 3; y < 18; y++)
                mvaddch(y, x, ACS_BLOCK);
        for(y = 6; y < 17; y++)
                {mvaddch(y, 32, ACS_BLOCK);
                 mvaddch(y, 47, ACS_BLOCK);
                 mvaddch(y+2, 34, ACS_BLOCK);
                 mvaddch(y+2, 45, ACS_BLOCK);}

        //Cabe�a
        setColor(5, 0, A_BOLD);
        for(x = 36; x < 44; x++)
            {mvaddch(4, x, ACS_BLOCK);
             mvaddch(9, x, ACS_BLOCK);}
        for(x = 35; x < 45; x++)
            for(y = 5; y < 9; y++)
                mvaddch(y, x, ACS_BLOCK);
        for(x = 38; x < 42; x++)mvaddch(10, x, ACS_BLOCK);
        for(x = 38; x < 42; x++)mvaddch(11, x, ACS_BLOCK);

        //Olhos
        setColor(COLOR_CYAN, 0, A_BOLD);
        mvaddch(6, 38, ACS_BLOCK);mvaddch(6, 41, ACS_BLOCK);

        //Boca
        setColor(COLOR_RED, 0, A_BOLD);
        mvaddch(8, 39, ACS_BLOCK);mvaddch(8, 40, ACS_BLOCK);

        //Vestido
        setColor(COLOR_BLUE, 0, A_BOLD);
        for(x = 35; x < 45; x++)
            for(y = 11; y < 15; y++)
                mvaddch(y, x, ACS_BLOCK);
        for(x = 36; x < 44; x++)mvaddch(15, x, ACS_BLOCK);
        for(x = 36; x < 44; x++){mvaddch(16, x, ACS_BLOCK);mvaddch(17, x, ACS_BLOCK);}
        for(x = 35; x < 45; x++){mvaddch(18, x, ACS_BLOCK);mvaddch(19, x, ACS_BLOCK);}
        for(x = 34; x < 46; x++){mvaddch(20, x, ACS_BLOCK);mvaddch(21, x, ACS_BLOCK);}
        for(x = 33; x < 47; x++){mvaddch(22, x, ACS_BLOCK);mvaddch(23, x, ACS_BLOCK);}
        for(x = 32; x < 48; x++)mvaddch(24, x, ACS_BLOCK);

        //Bra�os
        setColor(5, 0, A_BOLD);
        for(x = 33; x < 35; x++){mvaddch(12, x, ACS_BLOCK);mvaddch(12, x+12, ACS_BLOCK);}
        for(x = 32; x < 36; x++){mvaddch(13, x, ACS_BLOCK);mvaddch(13, x+12, ACS_BLOCK);}
        for(x = 33; x < 37; x++){mvaddch(14, x, ACS_BLOCK);mvaddch(14, x+10, ACS_BLOCK);}
        for(x = 34; x < 38; x++){mvaddch(15, x, ACS_BLOCK);mvaddch(15, x+8, ACS_BLOCK);}
        for(x = 35; x < 39; x++){mvaddch(16, x, ACS_BLOCK);mvaddch(16, x+6, ACS_BLOCK);}
        for(x = 36; x < 44; x++)mvaddch(17, x, ACS_BLOCK);
        for(x = 37; x < 43; x++)mvaddch(18, x, ACS_BLOCK);
        for(x = 38; x < 42; x++)mvaddch(19, x, ACS_BLOCK);
        mvaddch(20, 39, ACS_BLOCK);mvaddch(20, 40, ACS_BLOCK);
}

void julian()
{
    //Fundo
    setColor(COLOR_WHITE, COLOR_WHITE, 0);
    for(x = 0; x < 80; x++)
        for(y = 0; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Cabelo
    setColor(COLOR_RED, 0, 0);
    for(x = 35; x < 45; x++)mvaddch(2, x, ACS_BLOCK);
    for(x = 34; x < 47; x++)mvaddch(3, x, ACS_BLOCK);
    for(x = 34; x < 45; x++)mvaddch(4, x, ACS_BLOCK);
    mvaddch(4, 47, ACS_BLOCK);
    for(y = 5; y < 7; y++)
        {mvaddch(y, 34, ACS_BLOCK);
         mvaddch(y, 45, ACS_BLOCK);}

    //Cabe�a
    setColor(5, 0, A_BOLD);
    for(x = 36; x < 44; x++)
        {mvaddch(4, x, ACS_BLOCK);
         mvaddch(9, x, ACS_BLOCK);}
    for(x = 35; x < 45; x++)
        for(y = 5; y < 9; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 38; x < 42; x++)mvaddch(10, x, ACS_BLOCK);
    for(x = 38; x < 42; x++)mvaddch(11, x, ACS_BLOCK);

    //Olhos
    setColor(COLOR_BLACK, 5, A_BLINK);
    for(x = 37; x < 39; x++){mvaddch(5, x, 220);mvaddch(5, x+4, 220);}
    mvaddch(6, 38, ACS_BLOCK);mvaddch(6, 41, ACS_BLOCK);

    //Boca
    setColor(5, 5, A_BLINK);
    mvaddch(8, 39, 220);mvaddch(8, 40, 220);

    //Camisa
    setColor(COLOR_YELLOW, 0, A_BOLD);
    for(x = 37; x < 43; x++)mvaddch(11, x, ACS_BLOCK);
    for(x = 34; x < 46; x++)
        for(y = 13; y < 20; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 31; x < 49; x++)mvaddch(12, x, ACS_BLOCK);
    for(x = 30; x < 50; x++)mvaddch(13, x, ACS_BLOCK);
    for(x = 30; x < 34; x++)mvaddch(14, x, ACS_BLOCK);for(x = 46; x < 51; x++)mvaddch(14, x, ACS_BLOCK);
                                                      for(x = 47; x < 52; x++)mvaddch(15, x, ACS_BLOCK);

    //Cal�a
    setColor(COLOR_BLUE, 0, 0);
    for(y = 12; y < 20; y++)
        mvaddch(y, 43, ACS_BLOCK);
    for(x = 34; x < 46; x++)
        for(y = 20; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);
    setColor(COLOR_YELLOW, 0, 0);
    mvaddch(20, 43, ACS_BLOCK);

    //Bra�os
    setColor(5, 0, A_BOLD);
    for(x = 30; x < 34; x++)
        for(y = 15; y < 21; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 31; x < 34; x++)
        for(y = 21; y < 23; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 48; x < 53; x++)mvaddch(16, x, ACS_BLOCK);
    for(x = 49; x < 54; x++)mvaddch(17, x, ACS_BLOCK);
    for(x = 48; x < 53; x++)mvaddch(18, x, ACS_BLOCK);
    for(x = 47; x < 52; x++)mvaddch(19, x, ACS_BLOCK);
    for(x = 46; x < 51; x++)mvaddch(20, x, ACS_BLOCK);
    for(x = 46; x < 49; x++){mvaddch(21, x, ACS_BLOCK);mvaddch(22, x, ACS_BLOCK);}
}

void aura()
{
    //Fundo
    setColor(COLOR_WHITE, COLOR_WHITE, 0);
    for(x = 0; x < 80; x++)
        for(y = 0; y < 25; y++)
            mvaddch(y, x, ACS_BLOCK);

    //Cabelo
    setColor(COLOR_BLACK, 0, 0);
    for(x = 35; x < 45; x++)mvaddch(2, x, ACS_BLOCK);
    for(x = 34; x < 46; x++)mvaddch(3, x, ACS_BLOCK);
    for(x = 33; x < 47; x++)
        for(y = 4; y < 8; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 34; x < 46; x++)mvaddch(8, x, ACS_BLOCK);
    mvaddch(0, 31, ACS_BLOCK);mvaddch(0, 32, ACS_BLOCK);mvaddch(0, 33, ACS_BLOCK);
    mvaddch(1, 30, ACS_BLOCK);mvaddch(1, 31, ACS_BLOCK);mvaddch(1, 32, ACS_BLOCK);mvaddch(1, 33, ACS_BLOCK);mvaddch(1, 34, ACS_BLOCK);
    mvaddch(2, 30, ACS_BLOCK);mvaddch(2, 31, ACS_BLOCK);mvaddch(2, 32, ACS_BLOCK);
    mvaddch(3, 30, ACS_BLOCK);mvaddch(3, 31, ACS_BLOCK);
    mvaddch(4, 31, ACS_BLOCK);

    setColor(COLOR_RED, 0, A_BOLD);
    mvaddch(2, 33, ACS_BLOCK);mvaddch(2, 34, ACS_BLOCK);
    mvaddch(3, 32, ACS_BLOCK);mvaddch(3, 33, ACS_BLOCK);

    //Cabe�a
    setColor(5, 0, A_BOLD);
    for(x = 36; x < 44; x++)
        {mvaddch(4, x, ACS_BLOCK);
         mvaddch(9, x, ACS_BLOCK);}
    for(x = 35; x < 45; x++)
        for(y = 5; y < 9; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 38; x < 42; x++)mvaddch(10, x, ACS_BLOCK);
    for(x = 38; x < 42; x++)mvaddch(11, x, ACS_BLOCK);

    //Olhos
    setColor(COLOR_BLACK, 5, A_BLINK);
    for(x = 37; x < 39; x++){mvaddch(4, x, 220);mvaddch(4, x+4, 220);}
    setColor(COLOR_GREEN, 0, A_BOLD);
    mvaddch(6, 38, ACS_BLOCK);mvaddch(6, 41, ACS_BLOCK);

    //Boca
    setColor(COLOR_RED, 0, A_BOLD);
    mvaddch(8, 39, ACS_BLOCK);mvaddch(8, 40, ACS_BLOCK);

    //Vestido
    setColor(COLOR_CYAN, 0, A_BOLD);
    for(x = 38; x < 42; x++)mvaddch(11, x, ACS_BLOCK);
    for(x = 35; x < 45; x++)
        for(y = 12; y < 15; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 37; x < 43; x++)
        for(y = 15; y < 17; y++)
            mvaddch(y, x, ACS_BLOCK);
    for(x = 35; x < 45; x++){mvaddch(18, x, ACS_BLOCK);mvaddch(19, x, ACS_BLOCK);}
    for(x = 34; x < 46; x++){mvaddch(20, x, ACS_BLOCK);mvaddch(21, x, ACS_BLOCK);}
    for(x = 33; x < 47; x++){mvaddch(22, x, ACS_BLOCK);mvaddch(23, x, ACS_BLOCK);mvaddch(24, x, ACS_BLOCK);}
    setColor(COLOR_WHITE, 0, A_BOLD);
    for(x = 37; x < 43; x++)mvaddch(17, x, ACS_BLOCK);
    for(y = 18; y < 25; y++){mvaddch(y, 39, ACS_BLOCK);mvaddch(y, 40, ACS_BLOCK);}

    //Bra�os
    setColor(5, 0, A_BOLD);
    for(x = 45; x < 47; x++){mvaddch(12, x, ACS_BLOCK);mvaddch(17, x, ACS_BLOCK);}
    for(x = 45; x < 48; x++)mvaddch(13, x, ACS_BLOCK);
    for(x = 46; x < 49; x++){mvaddch(14, x, ACS_BLOCK);mvaddch(16, x, ACS_BLOCK);}
    for(x = 47; x < 50; x++)mvaddch(15, x, ACS_BLOCK);
    mvaddch(18, 45, ACS_BLOCK);
    mvaddch(19, 46, ACS_BLOCK);

    for(x = 24; x < 28; x++)mvaddch(11, x, ACS_BLOCK);
    for(x = 27; x < 29; x++){mvaddch(12, x, ACS_BLOCK);mvaddch(12, x+6, ACS_BLOCK);}
    for(x = 28; x < 30; x++){mvaddch(13, x, ACS_BLOCK);mvaddch(13, x+4, ACS_BLOCK);}mvaddch(13, 34, ACS_BLOCK);
    for(x = 29; x < 33; x++)mvaddch(14, x, ACS_BLOCK);
    for(x = 30; x < 32; x++)mvaddch(15, x, ACS_BLOCK);
}

