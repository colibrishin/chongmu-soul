#pragma once

typedef struct Critical {
  int chance;
  float increasement;
} Critical;

typedef struct HPGeneration {
  int perhp;
  int interval;
} HPGeneration;

typedef struct Effect {
  unsigned char drunk;
  unsigned char immune;
  HPGeneration h;
  Critical c;
} Effect;

Effect* createEffect(int chance, unsigned char drunk, unsigned char immune);
void setEffectFromEffect(Effect* dst, Effect* src);

