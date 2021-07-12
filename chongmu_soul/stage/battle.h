#pragma once
#include "../afx.h"
#include "../stage/stage.h"
#include "../ui/control/cstring.h"

typedef struct Battle {
  int turn;
  Character* home;
  Character* away;
  unsigned int home_atk;
  unsigned int away_atk;
} Battle;

Battle* createBattle(Stage* s, Character* a, Character* h);
void getBattleNameHP(Character* c, char** str);
char** getBattlePOV(Battle *b);
BattleType getPatternAttack(Battle* b, int turn, AttackFrom af);
int calculateBattleAttack(Battle* b, BattleType bt, AttackFrom af);
void applyBattleEffect(Character* c, int* dmg);
BattleReturn sumUpBattle(Battle* b, int ad, BattleType at, int hd, BattleType ht);