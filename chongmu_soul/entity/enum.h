#pragma once

typedef enum EntityType {
  CHARACTER = 0,
  ITEM = 1,
  PLACE = 2
} EntityType;

typedef enum C_EntityType{
  C_CHARACTER = 'C',
  C_ITEM = 'I',
  C_WAY = ' ',
  C_BONFIRE = 'B',
  C_DOOR = 'D',
  C_OBSTACLE = 'O'
} C_EntityType;