#include "entity.h"
#include <stdlib.h>

Entity* convertEntity(void* data, EntityType type) {
  Entity* ret = malloc(sizeof(Entity));
  ret->type = type;

  switch (ret->type) {
  case CHARACTER:
    ret->data.c = (Character*)data;
    break;
  case ITEM:
    ret->data.i = (Item*)data;
    break;
  case PLACE:
    ret->data.p = (Place*)data;
    break;
  }
  return ret;
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