#include <stdio.h>
#include <stdlib.h>
#include "../control/cstring.h"
#include "../../entity/entity.h"
#include "../../stage/stage.h"
#include "menus.h"

void Splash() {
	char c;

  do {
    printWithBars("MMMMMMMMMMMMMMMMMMM   :MMMMMMMMMMMMMMMMMMMNMMdoooohNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMmmmmmm/ -mMMMMMMMMMMMMMMMMMM: -:  ``     -yMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMM:          .:sMMMMMMMMMMMMMMM   mhhmNhhho   MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMddy::sdNMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMNmmmmmmmm/    MMMMMMMMMMMMMMMs  `MMMMMMN.  `MMMMMMMMMMMMMMMMNhNMMMMMMMMMMMMMMs.  `.   `+MMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMMMMNo`   .yMMMMMMMMMMMMMMMM   MMMMMN`  .MMMMMMMMMMMMMMMNo` `MMMMMMMMMMMMMM   yMMNN   MMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMMN+     `+mMMMMMMMMMMMMMM+`   ooooo   :MMMMMMMMMMMMMMM+   .yMMMMMMMMMMMMMM   mMMMN   MMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMm   -so:    :odMMMMMMMMMMdo:          `:odMMMMMMMMMMm/   -oodMMMMMMMMMMMMM:   :o/   -MMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMM   :MMMMmo/`   :ohMMMMMMMMMMMMMMMmooo/`   MMMMMMMMM:   -``    :ohNMMMMMMMMMm/`````:dMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMM+./MMMMMMMMMm+.`  -MMMMMMMMMMMMMMMMMMMMmydMMMMMMMh:  `dMmMmy+.`   -yMMmMMMMMMMMMMMMMMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNhhmMMMMdhhhhhhhhdNMMMMMMMMMMMMMMy   +mM- .MMMMNho::+M- .:::::::shhhhhdNMMMMMMMMM");
    printWithBars("MMMMMMMNhhNMMMMMMMMMMNs:oMMMMMMMMMMMM:          `..........-oMMs//oMMM   MMMMMMMMMMMs///////.        .MMMMMMMMM");
    printWithBars("MMMMMMM-   ``.+oooosm`  -MMMMMMMMMMMMMNNNNNNNNyoo   oooooooosMMMMMMMMM   MMMMMMMMMMMMMMMMMMMM   NNNNNMMMMMMMMMM");
    printWithBars("MMMMMMMMhooo-             `/ooooooomMMMMMMMMMMMM+   MMMMMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMMM   MMMMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMMMMdoooooo:          :MMMMMMMMMMM   hMMMMMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMM/   MMMMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMmoodMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMM   MMMMMMMMMdooooohNNN   dNNMMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMh+//////+yMMMMMMMMMMMMMMMMMMMMMMM   MMMMMMMMMMMMmmmmmmm   mmmMMMMMMo-..`           -MMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMy   ::::.  .:sNMMMMMMMMMMMMMMMMMMM   MMMMMMMMMMM:             .:::::/yMMNhhhhhhhhh.  .MMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMs   oMMMMNdo.  `NMMMMMMMMMMMMMMMMMM   MMMMMMMMMMMNmmmmmmmmmmms//////. `MMMMMMMMMMMMN   MMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMM   yMMMMMMMMM-  `+MMMMMMMMMMMMMMMM+  `MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNMMMNsoooooo+.`   MMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMM   /MMMMMMMMMMh   MMMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN+`           .ooyMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMd   :dMMMMMMMMM   MMMMMMMMMMMMMMMM   :MMMMMMMMMMMMMMMMMMMMMMMMMMMMMm/   -oohMMMMMMMMMMMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMm/   :hNNNNdo:   MMMMMMMMMMMMMMMMm   MMMMMMMMMMMMMMMMMMMMMMMMMMMMM   .dMMMMMMMMMMMMMMMMMMMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMMm+.        `./dMMMMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMMMMMMMMMMMM+`  -+ymmmmmmmmh+////+yMMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMMMMMmhhhhhhhmMMMMMMMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNo:.            `::::+MMMMMMMM");
    printWithBars("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMy/oMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNmmmmmmmmmmmmNMMMMMMMMMMMMM");
    printBars();
    printWithBars("Enter to Continue...");
    c = getchar();
    fseek(stdin, 0, SEEK_END);
    system("cls");
  } while (c != '\n');
}

Stage* newGame() {
  system("cls");
  loadingMenu("Creating Character...");
  Item* c_i = createItem("Air-force Uniform", "Not the best, but not the worst.", ARMOR, 2, 10, NORMAL);
  Character* c = createCharacter("Vapen", 50, createInventory(10), NULL, NULL, NORMAL, c_i);
  
  /*
  unsigned char m1_p[5] = { 1,1,1,1,0 };
  Item* m1_i = createItem("Public Work Uniform", "No... Why.", ARMOR, 0, 2, NORMAL);
  Character* m1 = createCharacter("Youtube Mongoose", 25, (Inventory*)malloc(sizeof(Inventory)), 5, m1_p, NORMAL, m1_i);

  unsigned char j_p[] = { 1,1,1,1,1,1,1,1,1,1 };
  Item* j_i = createItem("Military Uniform", "The symbol of a real man.", ARMOR, 15, 50, NORMAL);
  Character* j = createCharacter("Mad-Joon", 60000, (Inventory*)malloc(sizeof(Inventory)), 10, j_p, NORMAL, j_i);
  */

  loadingMenu("Creating Places...");
  Place* w = createPlace("Way", WAY);
  Place* o = createPlace("Wall", OBSTACLE);

  loadingMenu("Creating Stage...");

  Entity* elist[] = { convertEntity(o, PLACE), convertEntity(c, CHARACTER), convertEntity(w, PLACE) };
  unsigned int* fm[][5] = { 1,2,2,2,0,
                           0,2,0,2,0,
                           0,2,2,2,0,
                           0,0,0,2,0,
                           0,0,0,2,2 };

  Stage* s = createStageWFillmap("Test", 5, 5, elist, fm);

  return s;
}

void loadGame() {

}

void exploreMenu(Stage* s) {
  char str[5][7] = { "| |", "-------", "     ", "-------", "| |" };
  char t_str[5][7];
  char c;

  for(int i = 0; i < 5; ++i) memcpy(t_str[i], str[i], sizeof(str[i]));

  // get MoveType, Check ExploreMap
  // void* If pointer is null, change array
  // if else check c, if c is obstacle change array

  Entity *e = getPositionEntity(s, s->pos_x, s->pos_y, UP);
  if (e == NULL) {
    memset(t_str[0], ' ', 3);
    t_str[1][2] = ' ';
    t_str[1][3] = ' ';
    t_str[1][4] = ' ';
  }
  else {
    c = getPositionCEntityType(s, UP);
    if (c == C_OBSTACLE) memcpy(t_str[1], str[1], sizeof(str[1]));
    else t_str[0][1] = c;
  }
  t_str[0][3] = '\0';

  e = getPositionEntity(s, s->pos_x, s->pos_y, LEFT);
  if (e == NULL) {
    t_str[1][0] = ' ';
    t_str[1][1] = ' ';
  }
  else {
    c = getPositionCEntityType(s, LEFT);
    if (c == C_OBSTACLE) {
      t_str[1][0] = ' ';
      t_str[1][1] = ' ';
      t_str[2][1] = '|';
    }
    else t_str[2][0] = c;
  }

  e = getPositionEntity(s, s->pos_x, s->pos_y, RIGHT);

  if (e == NULL) {
    t_str[1][6] = ' ';
    t_str[1][5] = ' ';
  }
  else {
    c = getPositionCEntityType(s, RIGHT);
    if (c == C_OBSTACLE) {

    }
  }

}

void mainMenu() {
  char c;
  unsigned char isValid = 0;
  char str[][110] = { "New Game", "Load Save", "Exit" };
  char helpstr[] = "Select Menu...";
  system("cls");
  while(1) {
    centerAlignMenu(3, str, helpstr);
    c = getchar();
    fseek(stdin, 0, SEEK_END);
    switch (c) {
    case '1':
      return newGame();
    case '2':
      return loadGame();
    case '3':
      return;
    }
    memcpy(helpstr, "Invalid Input!", sizeof(helpstr));
  }
}