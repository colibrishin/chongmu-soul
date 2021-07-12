#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cstring.h"
#include "../../afx.h"

void copyStringTXTAREA(char dst[], char src[]) {
  if (strlen(src) < TXTAREA_WIDTH) {
    memcpy(dst, src, strlen(src) * sizeof(char));
    dst[strlen(src)] = '\0';
  }
  else if (strlen(src) >= TXTAREA_WIDTH) {
    memcpy(dst, src, TXTAREA_WIDTH * sizeof(char));
    dst[TXTAREA_WIDTH - 1] = '\0';
  }
}

void printBars() {
  for (int i = 0; i < TXTAREA_WIDTH + 1; ++i) printf("-");
  printf("\n");
}

void printWithBars(const char str[]) {
  char* t_str = NULL;
  size_t len = (str == NULL ? 0 : strlen(str));

  if (str == NULL) {
    t_str = (char*)malloc(TXTAREA_WIDTH * sizeof(char));
    memset(t_str, ' ', TXTAREA_WIDTH * sizeof(char));
    t_str[TXTAREA_WIDTH - 1] = '\0';
  }
  else if (len > TXTAREA_WIDTH) {
    t_str = (char*)malloc(TXTAREA_WIDTH * sizeof(char));
    memcpy(t_str, str, TXTAREA_WIDTH * sizeof(char));
    t_str[TXTAREA_WIDTH - 1] = '\0';
  }
  else if (len < TXTAREA_WIDTH) {
    t_str = (char*)malloc(TXTAREA_WIDTH * sizeof(char));
    memset(t_str, ' ', TXTAREA_WIDTH * sizeof(char));
    memcpy(t_str + getTextPosition(len), str, len * sizeof(char));
    t_str[TXTAREA_WIDTH - 1] = '\0';
  }

  printf("|");
  printf("%s", t_str == NULL ? str : t_str);
  printf("|\n");

  if (t_str != NULL) free(t_str);
}

void printWithNumBars(int n, char str[]) {
  char* t_str = NULL;
  size_t len = (str == NULL ? 0 : strlen(str));

  // if t_n is 0 this would be broken
  int t_n = n;
  int n_digit = 1;

  while (t_n /= 10) ++n_digit;
  len += (n_digit + 2);

  if (len > TXTAREA_WIDTH) {
    t_str = (char*)malloc(TXTAREA_WIDTH * sizeof(char));
    memcpy(t_str + (n_digit + 2), str, TXTAREA_WIDTH - (n_digit + 2) * sizeof(char));
    for (int i = n_digit - 1; i >= 0; --i) {
      t_str[i] = (char)48 + (n % 10);
      n /= 10;
    }
    t_str[TXTAREA_WIDTH - 1] = '\0';
  }
  else if (len < TXTAREA_WIDTH) {
    t_str = (char*)malloc(TXTAREA_WIDTH * sizeof(char));
    memset(t_str, ' ', TXTAREA_WIDTH * sizeof(char));
    memcpy(t_str + getTextPosition(len) + (n_digit + 2), str, len - (n_digit + 2) * sizeof(char));

    for (int i = n_digit - 1; i >= 0; --i) {
      t_str[getTextPosition(len) + i] = (char)48 + (n % 10);
      n /= 10;
    }


    t_str[getTextPosition(len) + n_digit] = '.';
    t_str[getTextPosition(len) + n_digit + 1] = ' ';
    t_str[TXTAREA_WIDTH - 1] = '\0';
  }

  printf("|");
  printf("%s", t_str == NULL ? str : t_str);
  printf("|\n");

  if (t_str != NULL) free(t_str);
}

char* getIntAsString(int number) {
  int t_n = number;
  int length = 1;

  while (t_n /= 10) ++length;
  char* str = (char*)malloc(NUM_CHARS * sizeof(char));

  for (int i = 0; i < length; ++i) {
    str[length - i - 1] = 48 + (number % 10);
    number /= 10;
  }

  str[length] = '\0';
  return str;
}

size_t getBackwardTextPosition(size_t length) {
  return (BATTLESTAGE_CHARS - (length + 1));
}

size_t getTextPosition(size_t length) {
  return (((W_WIDTH - 2) / 2) - (length / 2));
}

size_t getVerticalTextPosition(size_t length) {
  return (((W_HEIGHT - 2) / 2) - (length / 2));
}