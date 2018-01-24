#include <ncurses.h>
#include <stdio.h>

void printhelp() {
  clear();
  printw("\tGracz 1:        Gracz 2:\n"
         "\t  q|w|e           u|i|p\n"
         "\t  a|s|d           j|k|l\n"
         "\t  z|x|c           m|,|.\n"
         "\tNacisnij dowolny klawisz aby wrocic");
  getch();
}

void printfield(int n, int pole[n][n]) {
  clear();
  for (int y = 0; y < n; y++) {
    for (int x = 0; x < n; x++) {
      if (pole[y][x] == 0) {
        printw(" ");
      } else if (pole[y][x] == 1) {
        printw("x");
      } else if (pole[y][x] == 2) {
        printw("O");
      }
      if (x < n-1) {
        printw("|");
      } else {
        printw("\n");
      }
    }
  }
}

void printscore(int p1score, int p2score, int pvp) {
  if (pvp == TRUE)
    printw("\n"
"Gracz 1   Gracz 2\n");
  else
    printw("\n"
"Gracz 1   Komputer\n");
  printw(
"  %d         %d\n", p1score, p2score);
}
