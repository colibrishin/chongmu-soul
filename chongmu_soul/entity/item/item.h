#pragma once
#include "../../afx.h"
#include "afxitem.h"
#include "../enum.h"
#include "../item/item.h"
#include "../character/effect.h"


typedef struct ItemStats {
  unsigned char atk : MAX_ATK_IN_BIT;
  unsigned char def : MAX_DEF_IN_BIT;
} ItemStats;

typedef struct Item {
  void* addressEntity;
  unsigned int id;
  char description[TXTAREA_WIDTH];
  ItemType type;
  ItemStats stats;
  Effect* e;
} Item;

Item* createItem(unsigned int id, char description[], ItemType type, unsigned char atk, unsigned char def, Effect* e);
char* getItemName(Item* i);
char** getItemAsChar(Item* i);
int getItemAttack(Item* i);
int getItemDefense(Item* i);
void deleteItem(Item* i);
