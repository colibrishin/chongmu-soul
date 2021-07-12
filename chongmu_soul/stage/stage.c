#include "../stage/stage.h"
#include "../entity/entity.h"
#include "../ui/control/cstring.h"
#include "../entity/place/afxplace.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Entity*** createEmptyEntityMap(int x, int y) {
  Entity*** e = (Entity***)malloc(y * sizeof(Entity**));
  for (int i = 0; i < y; ++i) {
    e[i] = (Entity**)malloc(x * sizeof(Entity*));
    memset(e[i], NULL, x * sizeof(Entity*));
  }

  return e;
}

Stage* createStageEmpty(int x, int y) {
  Stage* s = (Stage*)malloc(sizeof(Stage));
  copyStringTXTAREA(s->name, " ");

  s->pos_x = 0;
  s->pos_y = 0;
  s->size_x = x;
  s->size_y = y;

  s->replaceEntity = NULL;
  s->map = createEmptyEntityMap(x, y);
  for (int i = 0; i < y; ++i) {
    for (int j = 0; j < x; ++j) {
      s->map[i][j] = NULL;
    }
  }

  return s;
}

Stage* createStageWFillmap(char name[], int x, int y, Entity* replaceEntity, Entity * lists[], unsigned int * fillmap){
  Stage* s = (Stage*)malloc(sizeof(Stage));

  copyStringTXTAREA(s->name, name);

  s->pos_x = 0;
  s->pos_y = 0;
  s->size_x = x;
  s->size_y = y;

  s->replaceEntity = replaceEntity;
  s->map = createEmptyEntityMap(x, y);
  for (int i = 0; i < y; ++i) {
    for (int j = 0; j < x; ++j) {
      s->map[i][j] = lists[*((fillmap + i * x) + j)];
    }
  }

  return s;
}

void copyStage(Stage* dst, Stage* src, unsigned char copyPos){
  memcpy(dst->name, src->name, sizeof(src->name));
  if (copyPos == 1) {
    dst->pos_x = src->pos_x;
    dst->pos_y = src->pos_y;
  }
  else {
    dst->pos_x = 0;
    dst->pos_y = 0;
  }

  dst->size_x = src->size_x;
  dst->size_y = src->size_y;

  dst->replaceEntity = src->replaceEntity;

  for (int i = 0; i < dst->size_y; ++i) {
    for (int j = 0; j < dst->size_x; ++j) {
      dst->map[i][j] = src->map[i][j];
    }
  }
}

int checkOOB(Stage * s, int x, int y) {
  if (x < 0 || y < 0) return 1;
  return (s->size_x > x && s->size_y > y) ? 0 : 1;
}

int checkOOBWMoveType(Stage * s, int x, int y, MoveType type) {
  int move_x = 0;
  int move_y = 0;

  switch (type) {
  case -1:
    return checkOOB(s, s->pos_x + x, s->pos_y + y);
  case UP:
    move_y += -1;
    break;
  case LEFT:
    move_x += -1;
    break;
  case RIGHT:
    move_x += 1;
    break;
  case DOWN:
    move_y += 1;
    break;
  }
  return checkOOBWMoveType(s, move_x, move_y, -1);
}

Entity* getPositionEntity(Stage * s, int x, int y) {
  if (checkOOB(s, x, y) == 1) return NULL;
  else return s->map[y][x];
}

EntityType getPositionEntityType(Stage * s, int x, int y) {
  if (checkOOB(s, x, y) == 1) return -1;
  else return getEntityType(getPositionEntity(s, x, y));
}

PlaceType getPositionPlaceType(Stage * s, int x, int y) {
  if (checkOOB(s, x, y) == 1) return -1;
  else {
    switch (getEntityType(getPositionEntity(s, x, y))) {
    case PLACE:
      switch (getPositionEntity(s, x, y)->data.p->type){
      case WAY:
        return C_WAY;
      case BONFIRE:
        return C_BONFIRE;
      case DOOR:
        return C_DOOR;
      case OBSTACLE:
        return C_OBSTACLE;
      }
    }
  }
  return ENUM_NULL;
}

C_EntityType getPositionCEntityType(Stage * s, int x, int y){
  if (checkOOB(s, x, y) == 1) return -1;
  else {
    switch (getEntityType(getPositionEntity(s, x, y))) {
    case CHARACTER:
      return C_CHARACTER;
    case ITEM:
      return C_ITEM;
    case PLACE:
      return getPositionPlaceType(s, x, y);
    }
  }
  return -1;
}

Entity* getPositionEntityWMoveType(Stage * s, MoveType type){
  if (checkOOBWMoveType(s, 0, 0, type)) return NULL;
  switch (type) {
  case UP:
    return getPositionEntity(s, s->pos_x, s->pos_y - 1);
  case LEFT:
    return getPositionEntity(s, s->pos_x - 1, s->pos_y);
  case RIGHT:
    return getPositionEntity(s, s->pos_x + 1, s->pos_y);
  case DOWN:
    return getPositionEntity(s, s->pos_x, s->pos_y + 1);
  }
  return NULL;
}

EntityType getPositionEntityTypeWMoveType(Stage * s, MoveType type){
  if (checkOOBWMoveType(s, 0, 0, type)) return -1;
  return getEntityType(getPositionEntityWMoveType(s, type));
}

PlaceType getPositionPlaceTypeWMoveType(Stage * s, MoveType type){
  if (checkOOBWMoveType(s, 0, 0, type) == 1) return -1;
  else {
    Entity* e = getPositionEntityWMoveType(s, type);
    if (e->type != PLACE) assert(1);
    else return e->data.p->type;
  }
  return -1;
}

C_EntityType getPositionCEntityTypeWMoveType(Stage * s, MoveType type){
  if (checkOOBWMoveType(s, 0, 0, type) == 1) return -1;
  else {
    switch (getPositionEntityTypeWMoveType(s, type)) {
    case CHARACTER:
      return C_CHARACTER;
    case ITEM:
      return C_ITEM;
    case PLACE:
      switch (getPositionPlaceTypeWMoveType(s, type)) {
      case WAY:
        return C_WAY;
      case BONFIRE:
        return C_BONFIRE;
      case DOOR:
        return C_DOOR;
      case OBSTACLE:
        return C_OBSTACLE;
      }
    }
  }
  return -1;
}

char** getMapAsPOV(Stage* s){
  char** str = (char**)malloc(POV_LINES * sizeof(char *));
  for(int i = 0; i < 5; ++i) str[i] = (char*)malloc(POV_CHARS * sizeof(char));
  char c;
  
  str[0][3] = '\0';
  str[1][7] = '\0';
  str[2][5] = '\0';
  str[3][7] = '\0';
  str[4][3] = '\0';

  memcpy(str[0], "| |", 3);
  memcpy(str[1], "-------", 7);
  memcpy(str[2], "  o  ", 5);
  memcpy(str[3], "-------", 7);
  memcpy(str[4], "| |", 3);

  Entity* e = getPositionEntityWMoveType(s, UP);
  if(e == NULL) {
    memcpy(str[0], "   ", 3);
    memset(str[1] + 2, ' ', 3);
  }
  else {
    c = getCEntityType(e);
    if(c == C_OBSTACLE) memcpy(str[0], "   ", 3);
    else {
      memset(str[1] + 2, ' ', 3);
      str[0][1] = c;
    }
  }

  e = getPositionEntityWMoveType(s, LEFT);
  if (e == NULL) {
    memset(str[1], ' ', 2);
    memset(str[3], ' ', 2);
  }
  else {
    c = getCEntityType(e);
    if(c == C_OBSTACLE) {
      memset(str[1], ' ', 2);
      memset(str[3], ' ', 2);
      str[2][1] = '|';
    }
    else {
      str[2][0] = c;
    }
  }

  e = getPositionEntityWMoveType(s, RIGHT);
  if (e == NULL) {
    memset(str[1] + 5, ' ', 2);
    memset(str[3] + 5, ' ', 2);
  }
  else {
    c = getCEntityType(e);
    if(c == C_OBSTACLE) {
      memset(str[1] + 5, ' ', 2);
      memset(str[3] + 5, ' ', 2);
      str[2][3] = '|';
    }
    else {
      str[2][4] = c;
    }
  }

  e = getPositionEntityWMoveType(s, DOWN);
  if (e == NULL) {
    memcpy(str[4], "   ", 3);
    memset(str[3] + 2, ' ', 3);
  }
  else {
    c = getCEntityType(e);
    if (c == C_OBSTACLE) memcpy(str[4], "   ", 3);
    else {
      str[4][1] = c;
      memset(str[3] + 2, ' ', 3);
    }
  }
  return str;
}

MoveReturn moveCharacter(Stage *s, MoveType type) {
  Entity* e = getPositionEntityWMoveType(s, type);

  if (checkOOBWMoveType(s, 0, 0, type) == 1) return DIED;
  else {
    if (getEntityType(e) == PLACE && e->data.p->type == OBSTACLE) return BLOCKED;
    switch (type) {
    case LEFT:
      --s->pos_x;
      break;
    case RIGHT:
      ++s->pos_x;
      break;
    case UP:
      --s->pos_y;
      break;
    case DOWN:
      ++s->pos_y;
      break;
    }
  }
  if (getEntityType(e) == CHARACTER) return FIGHT;
  else return MOVED;
}

void deleteStage(Stage * s){
  for (int i = 0; i < s->size_y; ++i) {
    for (int j = 0; j < s->size_x; ++j) {
      if (s->map[i][j]->type == CHARACTER) deleteCharacter(s->map[i][j]);
      else if (s->map[i][j]->type == ITEM) deleteItem(s->map[i][j]);
      else if (s->map[i][j]->type == PLACE) deletePlace(s->map[i][j]);
    }
  }
  free(s);
}
