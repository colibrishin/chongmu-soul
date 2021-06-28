#pragma once
#include <stdio.h>
#include "../entity/enum.h"
#include "../entity/character/character.h"
#include "../entity/item/item.h"
#include "../entity/place/place.h"

typedef union {
  Character* c;
  Item* i;
  Place *p;
} uData;

typedef struct {
  EntityType type;
  uData data;
} Entity;

Entity* convertEntity(void* data, EntityType type);
void* getEntityProperty(Entity* e);
void setEntityProperty(Entity *e, EntityType type, void* data);
void deleteEntity(Entity * e);