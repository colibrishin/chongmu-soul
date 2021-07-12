#include <string.h>
#include <stdlib.h>
#include "menus.h"
#include "../../afx.h"
#include "../control/cstring.h"

void centerAlignMenu(int y, char** str, char waitstr[]) {
  system("cls");
  for (int i = 0; i < getVerticalTextPosition(y); ++i) printWithBars(NULL);
  for (int i = 0; i < y; ++i) printWithNumBars(i + 1, str[i]);
  for (int i = 0; i < getVerticalTextPosition(y); ++i) printWithBars(NULL);
  printBars();
  printWithBars(waitstr);
}

void centerAlignScreen(int y, char** str, char waitstr[]) {
  system("cls");
  for (int i = 0; i < getVerticalTextPosition(y); ++i) printWithBars(NULL);
  for (int i = 0; i < y; ++i) printWithBars(str[i]);
  for (int i = 0; i < getVerticalTextPosition(y); ++i) printWithBars(NULL);
  printBars();
  printWithBars(waitstr);
}

void characterPOVScreen(char** str, char helpstr[]) {
  system("cls");
  for (int i = 0; i < getVerticalTextPosition(POV_LINES); ++i) printWithBars(NULL);
  for (int i = 0; i < POV_LINES; ++i) printWithBars(str[i]);
  for (int i = 0; i < getVerticalTextPosition(POV_LINES); ++i) printWithBars(NULL);
  printBars();
  printWithBars(helpstr);

  for (int i = 0; i < POV_LINES; ++i) free(str[i]);
}

void battleScreen(char** str, char helpstr[]) {
  system("cls");
  for (int i = 0; i < getVerticalTextPosition(BATTLESTAGE_LINES); ++i) printWithBars(NULL);
  for (int i = 0; i < BATTLESTAGE_LINES; ++i) printWithBars(str[i]);
  for (int i = 0; i < getVerticalTextPosition(BATTLESTAGE_LINES); ++i) printWithBars(NULL);
  printBars();
  printWithBars(helpstr);

  for (int i = 0; i < BATTLESTAGE_LINES; ++i) free(str[i]);
}

void loadingScreen(char str[]) {
  system("cls");
  for (int i = 0; i < W_HEIGHT - 2; ++i) printWithBars(NULL);
  printBars();
  printWithBars(str);
}