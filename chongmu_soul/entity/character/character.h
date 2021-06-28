#pragma once
#define MIN_PATTERN 5
#include "../item/inventory.h"
#include "../enum.h"

typedef struct {
  char name[80];
  unsigned int max_hp;
  int hp;
  unsigned int pattern_length;
  unsigned char* pattern;
  DebuffType status;
  Item* armor;
  Inventory* inventory;
} Character;

Character* createCharacter(char name[], int maxhp, Inventory* inventory, unsigned int pattern_length, unsigned char pattern[], DebuffType stat, Item* item);