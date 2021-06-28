#include "../item/inventory.h"
#include <stdlib.h>

Inventory* createInventory(int max_size) {
  Inventory* i = (Inventory*)malloc(sizeof(Inventory));
  i->max_size = max_size;
  i->occupied = 0;
  i->items = (Item*)malloc(i->max_size * sizeof(Item));

  return i;
}

void addItem(Inventory *in, Item* i) {
  if (i->type == ITEM) {
    in->items[in->occupied] = i;
    ++in->occupied;
  }
}

void deleteInventory(Inventory * i){
  free(i->items);
  free(i);
}
