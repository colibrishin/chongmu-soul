#pragma once
#include "../afx.h"
#include "../entity/enum.h"
#include "../entity/character/character.h"
#include "../entity/item/item.h"
#include "../entity/place/place.h"

typedef union uData {
  Character* c;
  Item* i;
  Place *p;
} uData;

typedef struct Entity {
  char name[TXTAREA_WIDTH];
  EntityType type;
  uData data;
} Entity;

Entity* createEntity(char name[], EntityType type, void* data);
void* getEntityData(Entity* e);
EntityType getEntityType(Entity* e);
C_EntityType getCEntityType(Entity* e);
void setEntityProperty(Entity *e, EntityType type, void* data);
void deleteEntity(Entity * e);
