#pragma once
#include "./../../afx.h"
#include "item.h"

typedef struct Inventory {
  int size;
  int occupied;
  Item* items[MAX_INVENTORY_SIZE];
} Inventory;

Inventory* createInventory(int size);
char** getAllItemNames(Inventory *in);
Item** getUseableItem(Inventory* i);
int getUseableItemCount(Inventory *in);
void deleteItemFromInventory(Inventory* in, Item* i, int n);
int addItem(Inventory* in, Item* i);
