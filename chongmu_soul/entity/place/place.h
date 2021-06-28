#pragma once
#include "../enum.h"

typedef struct {
  char name[80];
  PlaceType type;
} Place;

Place* createPlace(char name[], PlaceType type);
void deletePlace(Place* p);