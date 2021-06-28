#include "../stage/stage.h"
#include "../entity/enum.h"
#include <stdlib.h>
#include <string.h>

Entity*** createEntityMapWCharacter(Character * c, int x, int y){
  Entity*** e = (Entity***)malloc(y * sizeof(Entity));
  for (int i = 0; i < y; ++i) {
    e[i] = (Entity**)malloc(x * sizeof(Entity));
    memset(e[i], NULL, x * sizeof(Entity));
  }
  e[0][0] = convertEntity(c, CHARACTER);

  return e;
}

Entity *** createEmptyEntityMap(int x, int y){
  Entity*** e = (Entity***)malloc(y * sizeof(Entity));
  for (int i = 0; i < y; ++i) {
    e[i] = (Entity**)malloc(x * sizeof(Entity));
    memset(e[i], NULL, x * sizeof(Entity));
  }

  return e;
}

Stage * createStageWFillmap(char name[], int x, int y, Entity* lists[], unsigned int* fillmap[]){
  Stage *s = (Stage*)malloc(sizeof(Stage));

  s->pos_x = 0;
  s->pos_y = 0;
  s->size_x = x;
  s->size_y = y;

  s->map = createEmptyEntityMap(x, y);
  for (int i = 0; i < y; ++i) {
    for (int j = 0; j < x; ++j) {
      s->map[i][j] = lists[fillmap[i][j]];
    }
  }

  return s;
}

Stage * createStage(char name[], int x, int y, Entity** map[]){
  Stage* s = (Stage*)malloc(sizeof(Stage));

  memcpy(s->name, name, sizeof(name));
  s->pos_x = 0;
  s->pos_y = 0;
  
  s->size_x = x;
  s->size_y = y;

  s->map = (Entity***)malloc(y);
  for (int i = 0; i < y; ++i) s->map[i] = (Entity**)malloc(x);
  for (int i = 0; i < y; ++i) memcpy(s->map, map[i], x);

  return s;
}

const unsigned int checkOOB(Stage * s, int x, int y, MoveType type) {
  int move_x = 0;
  int move_y = 0;

  switch (type) {
  case -1:
    return (s->size_x <= x || s->size_y <= y) ? 1 : 0;
    break;
  case LEFT:
    move_x -= 1;
    break;
  case RIGHT:
    move_x += 1;
    break;
  case UP:
    move_y -= 1;
    break;
  case DOWN:
    move_y += 1;
    break;
  }

  return checkOOB(s, x + move_x, y + move_y, -1);
}

Entity* getPositionEntity(Stage *s, int x, int y, MoveType type) {
  if (checkOOB(s,x,y,type) == 0) {
    switch (type) {
    case LEFT:
      return s->map[y][x - 1];
    case RIGHT:
      return s->map[y][x + 1];
    case UP:
      return s->map[y - 1][x];
    case DOWN:
      return s->map[y + 1][x];
    }
  }
  return NULL;
}

EntityType getPositionEntityType(Stage * s, MoveType type){
  Entity *e = getPositionEntity(s, s->pos_x, s->pos_y, type);
  if (e != NULL) return e->type;
  else return -1;
}

C_EntityType getPositionCEntityType(Stage* s, MoveType type){
  if (checkOOB(s, s->pos_x, s->pos_y, type) == 1) return -1;
  else {
    switch (s->map[s->pos_y][s->pos_x]->type) {
    case CHARACTER:
      return C_CHARACTER;
    case ITEM:
      return C_ITEM;
    case PLACE:
      switch (s->map[s->pos_y][s->pos_y]->data.p->type) {
      case WAY:
        return C_WAY;
      case BONFIRE:
        return C_BONFIRE;
      case DOOR:
        return C_DOOR;
      case OBSTACLE:
        return OBSTACLE;
      }
    }
  }
}

PlaceType getPositionPlaceType(Stage * s, MoveType type){
  Entity* e = getPositionEntity(s, s->pos_x, s->pos_y, type);
  if (e->type == PLACE) return e->data.p->type;
  else return -1;
}

const int moveCharacter(Stage *s, int x, int y, MoveType type) {
  Entity* e = getPositionEntity(s, x, y, type);

  if (checkOOB(s,x,y,type) == 0) {
    if (e->type == PLACE) {
      if (e->data.p->type == OBSTACLE) return BLOCKED;
      switch (type) {
      case LEFT:
        --s->pos_x;
        break;
      case RIGHT:
        ++s->pos_x;
      case UP:
        --s->pos_y;
      case DOWN:
        ++s->pos_y;
      }
      return MOVED;
    }
    else if (e->type == CHARACTER) return FIGHT;
  }
  else return DIED;
}

void deleteStage(Stage * s){
  for (int i = 0; i < s->size_y; ++i) {
    for (int j = 0; j < s->size_x; ++j) {
      free(s->map[i][j]);
    }
  }
  for (int i = 0; i < s->size_y; ++i) free(s->map[i]);

  free(s);
}
