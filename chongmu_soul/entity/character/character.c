#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "../item/inventory.h"

Character* createCharacter(char name[], int maxhp, Inventory* inventory, unsigned int pattern_length, unsigned char pattern[], DebuffType stat, Item* item) {
  if (inventory == NULL) inventory = (Inventory*)malloc(sizeof(Inventory));

  Character* c = (Character*)malloc(sizeof(Character));

  memcpy(c->name, name, strlen(name));
  c->max_hp = maxhp;
  c->hp = maxhp;

  c->pattern_length = pattern_length;
  if (pattern == NULL) {
    c->pattern_length = MIN_PATTERN;
    c->pattern = (unsigned char*)malloc(c->pattern_length);
    memset(c->pattern, 0, c->pattern_length);
  }
  else {
    c->pattern = (unsigned char*)malloc(pattern_length);
    memcpy(c->pattern, pattern, sizeof(pattern));
  }

  c->inventory = inventory;
  c->status = NORMAL;
  c->armor = item;
  if (c->armor != NULL) addItem(c->inventory, c->armor);

  return c;
}

void deleteCharacter(Character* c) {
  free(c->pattern);
  deleteInventory(c->inventory);
  free(c);
}
