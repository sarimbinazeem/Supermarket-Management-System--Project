#ifndef SCREEN_H
#define SCREEN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
static inline void pauseScreen()
{
    printf("\nPress any key to continue...");
    getch();
}
#endif
