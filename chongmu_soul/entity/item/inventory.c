#include "../item/inventory.h"
#include "../entity.h"
#include "../item/item.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Inventory* createInventory(int size) {
  Inventory* i = (Inventory*)malloc(sizeof(Inventory));
  i->size = size;
  if (i->size > MAX_INVENTORY_SIZE) i->size = MAX_INVENTORY_SIZE;
  i->occupied = 0;
  memset(i->items, NULL, MAX_INVENTORY_SIZE * sizeof(Item*));

  return i;
}

// Need to be freed after used
// TODO : what if item occupied is 0?
char** getAllItemNames(Inventory * in){
  char** str = (char**)malloc(in->occupied * sizeof(char*));
  for (int i = 0; i < in->occupied; ++i) str[i] = (char*)malloc(TXTAREA_WIDTH * sizeof(char));

  for (int i = 0; i < in->occupied; ++i) memcpy(str[i], getItemName(in->items[i]), TXTAREA_WIDTH * sizeof(char));

  return str;
}

// TODO : what if there's no useable item?
// Need to be freed
Item** getUseableItem(Inventory * in){
  Item** ret = (Item**)malloc(in->occupied * sizeof(Item*));
  int useablecnt = 0;

  for (int i = 0; i < in->occupied; ++i) {
    if (in->items[i]->type == USEABLE) ret[useablecnt] = in->items[i];
    useablecnt++;
  }

  return ret;
}

int getUseableItemCount(Inventory * in){
  int useablecount = 0;
  for (int i = 0; i < in->occupied; ++i) if (in->items[i]->type == USEABLE) useablecount++;

  return useablecount;
}

void deleteItemFromInventory(Inventory * in, Item* i, int n){
  assert(in->items[n] != i);
  in->items[n] = NULL;
  if (n < in->occupied) {
    for (int i = n; i < in->occupied; ++i)
      in->items[i] = in->items[i + 1];
  }
  --in->occupied;
}

int addItem(Inventory *in, Item* i) {
  if (in->occupied >= in->size) return -1;

  in->items[in->occupied] = i;
  ++in->occupied;
  return 0;
}

void deleteInventory(Inventory * i){
  free(i);
}
