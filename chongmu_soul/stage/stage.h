#pragma once
#include "../entity/entity.h"
#include <assert.h>

typedef struct {
  char name[80];
  int pos_x;
  int pos_y;
  int size_x;
  int size_y;
  Entity*** map;
} Stage;

Entity*** createEntityMapWCharacter(Character* c, int x, int y);
Entity*** createEmptyEntityMap(int x, int y);
Stage* createStageWFillmap(char name[], int x, int y, Entity* lists[], unsigned int* fillmap[]);
Stage* createStage(char name[], int x, int y, Entity** map[]);
const unsigned int checkOOB(Stage *s, int x, int y, MoveType type);
Entity* getPositionEntity(Stage* s, int x, int y, MoveType type);
EntityType getPositionEntityType(Stage* s, MoveType type);
C_EntityType getPositionCEntityType(Stage *s, MoveType type);
PlaceType getPositionPlaceType(Stage* s, MoveType type);
const int moveCharacter(Stage* s, int x, int y, MoveType type);
void deleteStage(Stage *s);