#include "../stage/battle.h"
#include "../entity/item/item.h"
#include "../entity/character/character.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Battle* createBattle(Stage* s, Character* a, Character* h){
  Battle* b = (Battle*)malloc(sizeof(Battle));

  b->turn = 0;

  b->away = a;
  b->home = h;

  b->away_atk = 0;
  b->home_atk = 0;

  return b;
}

// name to str[0], hp to str[1] in str pointer perspective
void getBattleNameHP(Character* c, char** str) {

  if (strlen(getCharacterName(c)) >= BATTLESTAGE_CHARS) memcpy(str[0], getCharacterName(c), BATTLESTAGE_CHARS * sizeof(char));
  else memcpy(str[0] + getBackwardTextPosition(strlen(getCharacterName(c))), getCharacterName(c), strlen(getCharacterName(c)) * sizeof(char));
  str[0][BATTLESTAGE_CHARS - 1] = '\0';

  char* hp[2] = { getIntAsString(c->max_hp), getIntAsString(c->hp) };

  memcpy(str[1] + getBackwardTextPosition(strlen(hp[0])), hp[0], strlen(hp[0]) * sizeof(char));
  str[1][getBackwardTextPosition(strlen(hp[0])) - 1] = '/';
  memcpy(str[1] + getBackwardTextPosition(strlen(hp[0]) + strlen(hp[1])) - 1, hp[1], strlen(hp[1]) * sizeof(char));
  str[1][BATTLESTAGE_CHARS - 1] = '\0';

  free(hp[0]);
  free(hp[1]);
}

char** getBattlePOV(Battle* b) {
  char** str = (char**)malloc(BATTLESTAGE_LINES * sizeof(char*));
  for (int i = 0; i < BATTLESTAGE_LINES; ++i) str[i] = (char*)malloc(BATTLESTAGE_CHARS * sizeof(char));

  for (int i = 0; i < BATTLESTAGE_LINES; ++i) memset(str[i], ' ', BATTLESTAGE_CHARS * sizeof(char));
  char* turn = getIntAsString(b->turn);
  memcpy(str[0], "Turn : ", 7 * sizeof(char));
  memcpy(str[0] + 8, turn, strlen(turn) * sizeof(char));
  str[0][BATTLESTAGE_CHARS - 1] = '\0';
  free(turn);

  getBattleNameHP(b->home, str + 1);
  str[3][0] = 'o';
  str[3][1] = '\0';
  str[4][0] = (b->home_atk == 1) ? '|' : ' ';
  str[4][1] = '\0';
  str[5][0] = (b->away_atk == 1) ? '|' : ' ';
  str[5][1] = '\0';
  str[6][0] = 'o';
  str[6][1] = '\0';
  getBattleNameHP(b->away, str + 7);

  return str;
}

BattleType getPatternAttack(Battle* b, int turn, AttackFrom af){
  switch (af) {
  case HOME:
    if (b->home->pattern[turn % b->home->pattern_length] == 1) return ATTACK;
    return DODGE;
  case AWAY:
    if (b->away->pattern[turn % b->away->pattern_length] == 1) return ATTACK;
    return DODGE;
  }

  return ENUM_NULL;
}

int calculateBattleAttack(Battle* b, BattleType bt, AttackFrom af) {
  int dmg = 0;

  if (bt == DODGE) {
    switch (af) {
    case HOME:
      b->home_atk = 0;
      break;
    case AWAY:
      b->away_atk = 0;
      break;
    }

    return 0;
  }

  switch (af) {
  case HOME:
    dmg = getCharacterDamage(b->home) - getItemDefense(b->home->armor);
    b->home_atk = 1;
    
    if (b->away->e->immune == 1 || b->home->e->drunk == 1) {
      dmg = 0;
      b->home_atk = 0;
    }

    applyBattleEffect(b->home, &dmg);
    break;
  case AWAY:
    dmg = getCharacterDamage(b->away) - getItemDefense(b->home->armor);
    b->away_atk = 1;

    if (b->home->e->immune == 1 || b->away->e->immune == 1) {
      dmg = 0;
      b->away_atk = 0;
    }
    applyBattleEffect(b->away, &dmg);
    break;
  }

  return dmg < 0 ? 0 : dmg;
}

void applyBattleEffect(Character* c, int* dmg) {
  srand(time(NULL));
  if (rand() == c->e->c.chance) *dmg += *dmg * c->e->c.increasement;
  if (c->e->immune == 1 && c->e->drunk == 1) *dmg = 0;
}

BattleReturn sumUpBattle(Battle* b, int ad, BattleType at, int hd, BattleType ht) {
  if(at == ATTACK) b->home->hp -= ad;
  if (ht == ATTACK) b->away->hp -= hd;

  if (b->away->hp <= 0) return DEAD;
  else if (b->home->hp <= 0) return KILLED;
  else return IN_PROGRESS;
}