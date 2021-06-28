#pragma once
#include "../../entity/enum.h"
#include "../control/cwindow.h"
#include "../control/cstring.h"

void printBars() {
  for (int i = 0; i < TXTAREA_WIDTH + 2; ++i) printf("-");
  printf("\n");
}

void printWithBars(const char str[]) {
  char* t_str = NULL;
  int len = str == NULL ? 0 : strlen(str);

  if (str == NULL) {
    t_str = (char*)malloc(TXTAREA_WIDTH + 1);
    memset(t_str, ' ', TXTAREA_WIDTH);
    t_str[TXTAREA_WIDTH] = '\0';
  }
  else if (len > TXTAREA_WIDTH) {
    t_str = (char*)malloc(TXTAREA_WIDTH + 1);
    memcpy(t_str, str, TXTAREA_WIDTH);
    t_str[TXTAREA_WIDTH] = '\0';
  }
  else if (len < TXTAREA_WIDTH) {
    t_str = (char*)malloc(TXTAREA_WIDTH + 1);
    memset(t_str, ' ', TXTAREA_WIDTH);
    memcpy(t_str + getTextPosition(len), str, len);
    t_str[TXTAREA_WIDTH] = '\0';
  }

  printf("|");
  printf("%s", t_str == NULL ? str : t_str);
  printf("|\n");

  if (t_str != NULL) free(t_str);
}

void printWithNumBars(int n, const char str[]) {
  char* t_str = NULL;
  int len = str == NULL ? 0 : strlen(str);

  // if t_n is 0 this would be broken
  int t_n = n;
  int n_digit = 1;

  while (t_n /= 10) ++n_digit;
  len += (n_digit + 2);

  if (len > TXTAREA_WIDTH) {
    t_str = (char*)malloc(TXTAREA_WIDTH + 1);
    memcpy(t_str + (n_digit + 2) , str, TXTAREA_WIDTH - (n_digit + 2));
    for (int i = n_digit - 1; i >= 0; --i) {
      t_str[i] = (char)48 + (n % 10);
      n /= 10;
    }
    t_str[TXTAREA_WIDTH - 1] = '\0';
  }
  else if (len < TXTAREA_WIDTH) {
    t_str = (char*)malloc(TXTAREA_WIDTH + 1);
    memset(t_str, ' ', TXTAREA_WIDTH);
    memcpy(t_str + getTextPosition(len) + (n_digit + 2), str, len - (n_digit + 2));

    for (int i = n_digit - 1; i >= 0; --i) {
      t_str[getTextPosition(len) + i] = (char)48 + (n % 10);
      n /= 10;
    }


    t_str[getTextPosition(len) + n_digit] = '.';
    t_str[getTextPosition(len) + n_digit + 1] = ' ';
    t_str[TXTAREA_WIDTH] = '\0';
  }

  printf("|");
  printf("%s", t_str == NULL ? str : t_str);
  printf("|\n");

  if (t_str != NULL) free(t_str);
}

int getTextPosition(int length) {
  return (((W_WIDTH - 2) / 2) - (length / 2));
}

int getVerticalTextPosition(int length) {
  return (((W_HEIGHT - 2) / 2) - (length / 2));
}