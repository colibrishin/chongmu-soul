#include "place.h"
#include "../entity.h"
#include <stdlib.h>

Place * createPlace(PlaceType type){
  Place* p = (Place*)malloc(sizeof(Place));

  p->type = type;

  return p;
}

char* getPlaceName(Place* p) {
  return ((Entity*)p->addressEntity)->name;
}

void deletePlace(Place * p){
  free(p);
}
