#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

// https://pubs.opengroup.org/onlinepubs/7908799/xcurses/curses.h.html
#include <curses.h> // chtype in setColor

void initScreen();
void setColor(short int fg, short int bg, chtype attr);

void menu();
void titulo();
void mapa();
void gameover();

void ghost();
void zombie();
void merman();
void vampire();
void minotaur();
void king();

void diana();
void julian();
void aura();

#endif // GRAPHICS_H_INCLUDED
