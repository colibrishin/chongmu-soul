#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include "character.h"
#include "../item/inventory.h"
#include "../entity.h"

Character* createCharacter(int maxhp, Inventory* inventory, unsigned int pattern_length, unsigned char pattern[], Item* item, Effect* e){
  if (inventory == NULL) inventory = (Inventory*)malloc(sizeof(Inventory));

  Character* c = (Character*)malloc(sizeof(Character));

  c->max_hp = maxhp;
  c->hp = maxhp;

  if (e == NULL) c->e = createEffect(1, 0, 0);
  else c->e = e;

  c->pattern_length = pattern_length;
  if (c->pattern_length == 0) {
    c->pattern_length = MIN_PATTERN;
    memset(c->pattern, 0, MIN_PATTERN * sizeof(unsigned char));
    c->pattern[c->pattern_length - 1] = '\0';
  }
  else if (c->pattern_length < MAX_PATTERN) {
    memcpy(c->pattern, pattern, c->pattern_length * sizeof(unsigned int));
    c->pattern[c->pattern_length - 1] = '\0';
  }
  else if (c->pattern_length >= MAX_PATTERN) {
    c->pattern_length = MAX_PATTERN;
    memcpy(c->pattern, pattern, MAX_PATTERN * sizeof(unsigned char));
    c->pattern[MAX_PATTERN - 1] = '\0';
  }

  if(e == NULL)

  c->inventory = inventory;
  c->armor = item;
  if (c->armor != NULL) addItem(c->inventory, c->armor);

  return c;
}

char* getCharacterName(Character * c){
  return ((Entity*)c->addressEntity)->name;
}

int getCharacterDamage(Character * c){
  int dmg = 0;
  Item* i = c->armor;

  srand(time(NULL));
  if (rand() <= c->e->c.chance) dmg += c->e->c.increasement;
  
  assert(getEntityType(c->armor) != ITEM);
  dmg += getItemAttack(i);

  return dmg;
}

// Problem : Duplicated free? how to make program knows its freed or else way
void deleteCharacter(Character* c) {
  deleteInventory(c->inventory);
  free(c);
}