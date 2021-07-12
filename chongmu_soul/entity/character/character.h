#pragma once
#include "../../afx.h"
#include "afxcharacter.h"
#include "effect.h"
#include "../item/item.h"
#include "../item/inventory.h"
#include "../enum.h"

typedef struct Character {
  void* addressEntity;
  unsigned int max_hp;
  int hp;
  unsigned int pattern_length;
  unsigned char pattern[MAX_PATTERN];
  Item* armor;
  Inventory* inventory;
  Effect* e;
} Character;

Character* createCharacter(int maxhp, Inventory* inventory, unsigned int pattern_length, unsigned char pattern[], Item* item, Effect* e);
char* getCharacterName(Character *c);
int getCharacterDamage(Character* c);
void deleteCharacter(Character* c);