#pragma once
#include <string.h>
#include <stdlib.h>
#include "../../entity/enum.h"
#include "../control/cstring.h"
#include "../control/cwindow.h"

typedef struct {
  char up[4];
  char upmidline[7];
  char mident[6];
  char downmidline[7];
  char down[4];
} ExploreMap;

ExploreMap* InitExploreMap() {
  ExploreMap* em = (ExploreMap*)malloc(sizeof(ExploreMap));
  memcpy(em->up, "| |", sizeof(em->up));
  memcpy(em->upmidline, "-------", sizeof(em->upmidline));
  memcpy(em->mident, "     ", sizeof(em->mident));
  memcpy(em->downmidline, "-------", sizeof(em->downmidline));
  memcpy(em->down, "| |", sizeof(em->down));
}

ExploreMap* getStageExploreMap(ExploreMap* em, Stage* s) {
  Entity* e = 
}

void deleteExploreMap(ExploreMap* em) {
  free(em);
}

void centerAlignMenu(int y, char str[][110], char waitstr[]) {
  for (int i = 0; i < getVerticalTextPosition(y); ++i) printWithBars(NULL);
  for (int i = 0; i < y; ++i) printWithNumBars(i + 1, str[i]);
  for (int i = 0; i < getVerticalTextPosition(y); ++i) printWithBars(NULL);
  printBars();
  printWithBars(waitstr);
}

void centerAlignScreen(int y, char str[][110], char waitstr[]) {
  for (int i = 0; i < getVerticalTextPosition(y); ++i) printWithBars(NULL);
  for (int i = 0; i < y; ++i) printWithBars(str[i]);
  for (int i = 0; i < getVerticalTextPosition(y); ++i) printWithBars(NULL);
  printBars();
  printWithBars(waitstr);
}

void loadingMenu(char str[]) {
  for (int i = 0; i < W_HEIGHT - 2; ++i) printWithBars(NULL);
  printBars();
  printWithBars(str);
}