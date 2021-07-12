#pragma once

#define MAX_INVENTORY_SIZE 30
#define MAX_ATK_IN_BIT 8
#define MAX_DEF_IN_BIT 8

typedef enum ItemType{
  WEAPON = 0,
  USEABLE = 1,
  ARMOR = 2
} ItemType;

typedef enum ItemReturn {
  ITEMRETURN_USE = 0,
  ITEMRETURN_EXIT = 1,
} ItemReturn;