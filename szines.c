#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "szines.h"
// Ez a forr�sk�d: https://stackoverflow.com/questions/29574849/how-to-change-text-color-and-console-color-in-codeblocks oldalr�l sz�rmazik.

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}