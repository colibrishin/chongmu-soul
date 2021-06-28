#include "../item/item.h"
#include <stdlib.h>
#include <string.h>

Item* createItem(char name[], char description[], ItemType type, unsigned char atk, unsigned char def, DebuffType debuff) {
  Item* i = (Item*)malloc(sizeof(Item));

  memcpy(i->name, name, strlen(name));
  memcpy(i->description, description, strlen(description));
  i->stats.atk = atk;
  i->stats.def = def;
  i->type = type;
  i->isDebuff = debuff;

  return i;
}

void deleteItem(Item * i){
  free(i);
}
