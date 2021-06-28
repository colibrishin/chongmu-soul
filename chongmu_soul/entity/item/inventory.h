#pragma once
#include "../item/item.h"

typedef struct {
  int max_size;
  int occupied;
  Item** items;
} Inventory;

Inventory* createInventory(int max_size);
void addItem(Inventory* in, Item* i);