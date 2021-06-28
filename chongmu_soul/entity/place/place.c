#include "place.h"

Place* createPlace(char name[], PlaceType type) {
  Place* p = (Place*)malloc(sizeof(Place));

  memcpy(p->name, name, sizeof(name));
  p->type = type;

  return convertEntity(PLACE, p);
}

void deletePlace(Place * p){
  free(p);
}
