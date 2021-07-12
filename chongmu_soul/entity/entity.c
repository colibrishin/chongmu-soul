#include "../afx.h"
#include "entity.h"
#include <stdlib.h>
#include <string.h>


Entity * createEntity(char name[], EntityType type, void * data){
  Entity* e = (Entity*)malloc(sizeof(Entity));

  e->type = type;
  copyStringTXTAREA(e->name, name);

  switch (e->type) {
  case CHARACTER:
    e->data.c = (Character*)data;
    ((Character*)data)->addressEntity = e;
    break;
  case ITEM:
    e->data.i = (Item*)data;
    ((Item*)data)->addressEntity = e;
    break;
  case PLACE:
    e->data.p = (Place*)data;
    ((Place*)data)->addressEntity = e;
    break;
  }

  return e;
}

void* getEntityData(Entity* e){
  switch (e->type) {
  case CHARACTER:
    return (Character*)e->data.c;
  case ITEM:
    return (Item*)e->data.i;
  case PLACE:
    return (Place*)e->data.p;
  }
  return NULL;
}

EntityType getEntityType(Entity * e){
  return e->type;
}

C_EntityType getCEntityType(Entity * e){
  switch (e->type) {
  case CHARACTER:
    return C_CHARACTER;
  case ITEM:
    return C_ITEM;
  case PLACE:
    switch (e->data.p->type) {
    case WAY:
      return C_WAY;
    case BONFIRE:
      return C_BONFIRE;
    case DOOR:
      return DOOR;
    case OBSTACLE:
      return C_OBSTACLE;
    }
  }
  return ENUM_NULL;
}

void * getEntityProperty(Entity * e){
  switch (e->type) {
  case CHARACTER:
    return (Character*)e->data.c;
    break;
  case ITEM:
    return (Item*)e->data.c;
    break;
  case PLACE:
    return (Place*)e->data.c;
    break;
  }
  return NULL;
}

void setEntityProperty(Entity* e, EntityType t, void* data) {
  e->type = t;
  switch (e->type) {
  case CHARACTER:
    e->data.c = data;
    break;
  case ITEM:
    e->data.i = data;
    break;
  case PLACE:
    e->data.i = data;
    break;
  }
}

void deleteEntity(Entity * e){
  switch (e->type) {
  case CHARACTER:
    deleteCharacter(e->data.c);
    break;
  case ITEM:
    deleteItem(e->data.i);
    break;
  case PLACE:
    deletePlace(e->data.p);
    break;
  }
  free(e);
}