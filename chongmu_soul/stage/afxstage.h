#pragma once

#define STAGE_N_REFSTAGE 2
#define CURRENT_STAGE 0
#define REFERENCE_STAGE 1

typedef enum MoveType {
  UP = 0,
  LEFT = 1,
  RIGHT = 2,
  DOWN = 3
} MoveType;

typedef enum MoveReturn {
  MOVED = 0,
  DIED = 1,
  BLOCKED = 2,
  FIGHT = 3
} MoveReturn;

typedef enum BattleType {
  ATTACK = 0,
  DODGE = 1,
  USE_ITEM = 2
} BattleType;

typedef enum BattleReturn {
  IN_PROGRESS = 0,
  DEAD = 1,
  KILLED = 2
} BattleReturn;

typedef enum AttackFrom {
  HOME = 0,
  AWAY = 1
} AttackFrom;