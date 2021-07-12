#pragma once
#include <stdio.h>
#include <Windows.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../stage/stage.h"
#include "../entity/entity.h"

char* getFileName(Entity* e) {
  char* str = (char*)malloc(TXTAREA_WIDTH * sizeof(char));
  for (int i = 0; i < TXTAREA_WIDTH; ++i) {
    str[i] = e->name[i];
    if (str[i] == ' ') str[i] = '_';
    if (str[i] == '\0') break;
  }

  return str;
}

int saveItemtoFile(Entity* e) {
  if (getEntityType(e) != NULL) return -1;
  struct stat st = { 0 };
  if (stat(".\\data", &st) == -1) {
    CreateDirectory(".\\", NULL);
  }
  else {

  }
}

Stage* loadCharacterfromFile(char name[]) {

}