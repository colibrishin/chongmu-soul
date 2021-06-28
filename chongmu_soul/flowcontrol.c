#include <stdio.h>
#include "ui/control/cwindow.h"
#include "ui/menu/sequences.h"

int main(void) {
	setTitle("Chongmu Soul");
	getHandle();
	Splash();
  mainMenu();
  exploreMenu(newGame());
}