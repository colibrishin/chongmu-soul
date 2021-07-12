#pragma once
#include "../../afx.h"
#include "../enum.h"
#include "afxplace.h"

typedef struct Place {
  void* addressEntity;
  PlaceType type;
} Place;

Place* createPlace(PlaceType type);
char* getPlaceName(Place* p);
void deletePlace(Place* p);