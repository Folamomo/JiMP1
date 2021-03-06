#include <ncurses.h> // sudo apt-get install libncurses5-dev
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "keyinputs.h"
#include "ai.h"
#include "printing.h"

void init() {
  initscr();
  noecho();
  cbreak();
  srand(time(NULL));
}

void initfield(int n, int field[n][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      field[i][j] = 0;
  }
}

int checkwin(int field[3][3]) {
  for (int i = 0; i < 3; i++) { 
    if (field[0][i] != 0) {
      if (field[0][i] == field[1][i] && field[0][i] == field[2][i]) {
        return field[0][i];
      }
    }
    if (field[i][0] != 0) {
      if (field[i][0] == field[i][1] && field[i][0] == field[i][2]) {
        return field[i][0];
      }
    }
  }

  if (field[1][1] != 0) {
    if (field[0][0] == field[1][1] && field[1][1] == field[2][2]) {
      return field[1][1];
    }
    if (field[2][0] == field[1][1] && field[1][1] == field[0][2]) {
      return field[1][1];
    }
  }
  return 0;
}

int playOneRound(int startsfirst, int p1score, int p2score, int pvp) {
  int field[3][3];
  initfield(3, field);
  int movecounter = 0;
  printfield(3, field);
  printscore(p1score, p2score, pvp);
  
  while (checkwin(field) == 0 && movecounter < 9) {
    if ((movecounter + startsfirst) % 2)
      p1move(field);
    else if (pvp == TRUE)
      p2move(field);
    else
      CPmove(field);
    printfield(3, field);
    printscore(p1score, p2score, pvp);
    movecounter++;
  }
  
  getch();
  return checkwin(field);
}

void game(int pvp) {
  int startsfirst = 1;
  int p1score = 0;
  int p2score = 0;
  
  while (p1score < 4 && p2score < 4) {
    int winner = playOneRound(startsfirst, p1score, p2score, pvp);
    if (winner == 1) {
      p1score++;
      startsfirst = 0;
    } else if (winner == 2) {
      p2score++;
      startsfirst = 1;
    } else
      startsfirst = (startsfirst + 1) % 2;
  }

  if (p1score > p2score)
    printw("Wygrywa gracz 1!\n");
  else if (pvp == TRUE)
    printw("Wygrywa gracz 2!\n");
  else
    printw("Wygrywa Komputer!\n");
  printw("Nacisnij dowolny klawisz, aby wrocic do menu\n");
  getch();
  return;
}

void run(int mode) {
  switch (mode) {
  case 1:
    game(TRUE);
    break;
  case 2:
    game(FALSE);
    break;
  case 3:
    printhelp();
  }
}

int menu() {
  clear();
  printw("1. Zagraj z innym graczem\n"
         "2. Zagraj z komputerem\n"
         "3. Sterowanie\n"
         "4. Wyjscie\n");
  const char c = getch();
  switch (c) {
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 0;
  }
  return -1;
}

int main() {
  init();
  int choice = 1;
  while (choice) {
    choice = menu();
    run(choice);
  }
  endwin();
  return 0;
}
