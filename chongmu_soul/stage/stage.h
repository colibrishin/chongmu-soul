#pragma once
#include "../afx.h"
#include "../entity/entity.h"
#include "afxstage.h"

typedef struct Stage {
  char name[TXTAREA_WIDTH];
  int pos_x;
  int pos_y;
  int size_x;
  int size_y;
  Entity* replaceEntity;
  Entity*** map;
} Stage;

Entity*** createEmptyEntityMap(int x, int y);
Stage* createStageEmpty(int x, int y);
Stage* createStageWFillmap(char name[], int x, int y, Entity* replaceEntity, Entity* lists[], unsigned int* fillmap);
void copyStage(Stage* dst, Stage* src, unsigned char copyPos);

int checkOOB(Stage *s, int x, int y);
int checkOOBWMoveType(Stage* s, int x, int y, MoveType type);

Entity* getPositionEntity(Stage *s, int x, int y);
EntityType getPositionEntityType(Stage* s, int x, int y);
PlaceType getPositionPlaceType(Stage* s, int x, int y);
C_EntityType getPositionCEntityType(Stage* s, int x, int y);

Entity* getPositionEntityWMoveType(Stage* s, MoveType type);
EntityType getPositionEntityTypeWMoveType(Stage* s, MoveType type);
PlaceType getPositionPlaceTypeWMoveType(Stage* s, MoveType type);
C_EntityType getPositionCEntityTypeWMoveType(Stage* s, MoveType type);

char** getMapAsPOV(Stage* s);
MoveReturn moveCharacter(Stage* s, MoveType type);
void deleteStage(Stage *s);
