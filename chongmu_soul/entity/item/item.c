#include "../item/item.h"
#include "../../ui/control/cstring.h"
#include "../entity.h"
#include <stdlib.h>
#include <string.h>

Item * createItem(unsigned int id, char description[], ItemType type, unsigned char atk, unsigned char def, Effect* e){
  Item* i = (Item*)malloc(sizeof(Item));

  //TODO : Find better way to set array size
  i->id = id;
  copyStringTXTAREA(i->description, description);

  i->stats.atk = atk;
  i->stats.def = def;
  i->type = type;

  if (i->e == NULL) i->e = (Effect*)malloc(sizeof(Effect));
  else i->e = e;

  return i;
}

char** getItemAsChar(Item* i) {
  char* atk;
  char* def;

  char** str = (char**)malloc(ITEM_LINES * sizeof(char*));
  for (int i = 0; i < ITEM_LINES; ++i) {
    str[i] = (char*)malloc(TXTAREA_WIDTH * sizeof(char));
    memset(str[i], ' ', TXTAREA_WIDTH * sizeof(char));
  }

  memcpy(str[0], "Name : ", 7 * sizeof(char));
  memcpy(str[0] + 7, getItemName(i), strlen(getItemName(i)) * sizeof(char));
  str[0][7 + strlen(getItemName(i))] = '\0';

  memcpy(str[1], "Description : ", 13 * sizeof(char));
  memcpy(str[1] + 14, i->description, strlen(i->description) * sizeof(char));
  str[1][14 + strlen(i->description)] = '\0';

  atk = getIntAsString(i->stats.atk);
  memcpy(str[2], "ATK=", 4 * sizeof(char));
  memcpy(str[2] + 4, atk, strlen(atk) * sizeof(char));
  str[2][4 + strlen(atk)] = '\0';
  free(atk);

  def = getIntAsString(i->stats.def);
  memcpy(str[3], "DEF=", 4 * sizeof(char));
  memcpy(str[3] + 4, def, strlen(def) * sizeof(char));
  str[3][4 + strlen(def)] = '\0';
  free(def);

  return str;
}

char* getItemName(Item* i) {
  return ((Entity*)i->addressEntity)->name;
}

int getItemAttack(Item* i) {
  return i->stats.atk;
}

int getItemDefense(Item* i) {
  return i->stats.def;
}

void deleteItem(Item * i){
  free(i);
}
