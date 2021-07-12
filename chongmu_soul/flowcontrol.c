#include "ui/menu/sequences.h"
#include "ui/control/cwindow.h"

void main(void) {
  Stage* current_stage[STAGE_N_REFSTAGE];
  MoveReturn r;

	setTitle("Chongmu Soul");
	getHandle();
	Splash();

  memcpy(current_stage, mainMenu(), STAGE_N_REFSTAGE * sizeof(Stage*));
  if (current_stage == NULL) return;

  while(1) {
    r = exploreMenu(current_stage);
    if (r == DIED) diedMenu(NULL, current_stage);
    if (r == FIGHT) battleMenu(current_stage[CURRENT_STAGE]);
  }
}