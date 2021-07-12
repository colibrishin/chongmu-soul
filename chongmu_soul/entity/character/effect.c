#include "effect.h"
#include "afxcharacter.h"
#include <stdlib.h>

Effect* createEffect(int chance, unsigned char drunk, unsigned char immune){
  Effect *e = (Effect*)malloc(sizeof(Effect));

  e->c.chance = chance;
  e->c.increasement = MIN_CRIT_DAMAGE;
  e->drunk = drunk;
  e->immune = immune;
  e->h.interval = 0;
  e->h.perhp = 0;

  return e;
}

void setEffectFromEffect(Effect* dst, Effect* src){
  dst->drunk = src->drunk;
  dst->immune = src->immune;

  dst->c.chance += src->c.chance;
  dst->c.increasement += src->c.increasement;

  dst->h.interval -= src->h.interval;
  dst->h.perhp += src->h.perhp;
}
