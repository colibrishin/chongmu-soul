#pragma once
#include "../enum.h"
#include "../item/item.h"

typedef struct {
  union {
    unsigned char atk : 8;
    unsigned char def : 8;
  };
  unsigned int code : 16;
} ItemStats;

typedef struct {
  char name[80];
  char description[110];
  ItemType type;
  ItemStats stats;
  DebuffType isDebuff;
} Item;

Item* createItem(char name[], char description[], ItemType type, unsigned char atk, unsigned char def, DebuffType debuff);
void deleteItem(Item* i);