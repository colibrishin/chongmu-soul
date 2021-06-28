#pragma once

typedef enum {
  CHARACTER = 0,
  ITEM = 1,
  PLACE = 2
} EntityType;

typedef enum {
  C_CHARACTER = 'C',
  C_ITEM = 'I',
  C_WAY = ' ',
  C_BONFIRE = 'B',
  C_DOOR = 'D',
  C_OBSTACLE = 'O'
} C_EntityType;

typedef enum {
  NORMAL = 0,
  INVINSIBLE = 1,
  DRUNK = 2
} DebuffType;

typedef enum {
  WEAPON = 0,
  USEABLE = 1,
  ARMOR = 2
} ItemType;

typedef enum {
  WAY = 0,
  BONFIRE = 1,
  DOOR = 2,
  OBSTACLE = 3
} PlaceType;

typedef enum {
  UP = 0,
  LEFT = 1,
  RIGHT = 2,
  DOWN = 3
} MoveType;

typedef enum {
  DIED = -1,
  MOVED = 0,
  BLOCKED = 1,
  FIGHT = 2
} MoveReturn;