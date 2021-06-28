#pragma once

typedef struct {
  int max_chance;
  int chance;
  unsigned int* crit;
} Critical;

typedef struct {
  int inc;
  int atk_stack;
} AttackIncreasement;

typedef struct {
  int hp_gen;
  AttackIncreasement* a;
  Critical* c;
} Effect;

Critical* createEffectCritical(int chance);