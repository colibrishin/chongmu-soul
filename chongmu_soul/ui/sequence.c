#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu/sequences.h"
#include "../entity/item/afxitem.h"
#include "../entity/entity.h"
#include "../battle/battle.h"
#include "../ui/menu/menus.h"

Stage** newGame() {
  loadingScreen("Creating Character...");
  unsigned char c_p[] = { 1, 1, 0, 0, 1 };
  Entity* c_i = createEntity("Air-force Uniform", ITEM, createItem(0, "Not the best, but not the worst.", ARMOR, 10, 5, NULL));
  Entity* c = createEntity("Vapen", CHARACTER, createCharacter(50, createInventory(10), sizeof(c_p), c_p, (Item*)getEntityData(c_i), NULL));

  /*
  unsigned char m1_p[5] = { 1,1,1,1,0 };
  Item* m1_i = createItem("Public Work Uniform", "No... Why.", ARMOR, 0, 2, NORMAL);
  Character* m1 = createCharacter("Youtube Mongoose", 25, (Inventory*)malloc(sizeof(Inventory)), 5, m1_p, NORMAL, m1_i);

  unsigned char j_p[] = { 1,1,1,1,1,1,1,1,1,1 };
  Item* j_i = createItem("Military Uniform", "The symbol of a real man.", ARMOR, 15, 50, NORMAL);
  Character* j = createCharacter("Mad-Joon", 60000, (Inventory*)malloc(sizeof(Inventory)), 10, j_p, NORMAL, j_i);
  */

  loadingScreen("Creating Places...");
  Entity* w = createEntity("Way", PLACE, createPlace(WAY));
  Entity* o = createEntity("Wall", PLACE, createPlace(OBSTACLE));

  loadingScreen("Creating Stage...");

  Entity* elist[] = { o, c, w };
  unsigned int fm[][5] = { { 1,2,2,2,0 },
  { 0,2,0,2,0 },
  { 0,2,2,2,0 },
  { 0,0,0,2,0 },
  { 0,0,0,2,2 } };

  Stage* s1 = createStageWFillmap("Test", 5, 5, o, elist, fm);
  Stage* s2 = createStageEmpty(5, 5);
  copyStage(s2, s1, 0);

  Stage** s = (Stage**)malloc(STAGE_N_REFSTAGE * sizeof(Stage*));
  s[CURRENT_STAGE] = s1;
  s[REFERENCE_STAGE] = s2;

  return s;
}


void diedMenu(Battle *b, Stage* s[STAGE_N_REFSTAGE]) {
  char diedstr[TXTAREA_WIDTH] = "YOU DIED, Vapen specially sucks. Enter to Continue.";
  char c = ' ';

  if (b == NULL) {
    do {
      char** str = getMapAsPOV(s[CURRENT_STAGE]);
      characterPOVScreen(str, diedstr);
      c = getchar();
    } while (c != '\n');
    copyStage(s[CURRENT_STAGE], s[REFERENCE_STAGE], 0);
    return;
  }
}

Stage* loadGame() {
  Stage* s = NULL;
  return s;
}

void itemMenu(Character* chr, Item* i, Battle *b) {
  char** str;
  char helpstr[TXTAREA_WIDTH] = "Equip to e, Quit to q";
  char c = ' ';

  do {
    // str[4][TXTWIDTH_SIZE]
    str = getItemAsChar(i);
    centerAlignScreen(ITEM_LINES, str, helpstr);
    c = getchar();
    fseek(stdin, 0, SEEK_END);

    if (c == 'e') {
      if (chr->armor == i) memcpy(helpstr, "You already equiped this item.", 31 * sizeof(char));
      else {
        memcpy(helpstr, "You equipment is changed.", 26 * sizeof(char));
        chr->armor = i;
      }
    }
    for (int i = 0; i < 4; ++i) free(str[i]);
  } while (c != 'q');
}

MoveReturn inventoryMenu(Stage * s){
  ItemReturn it;
  char** str;
  char helpstr[TXTAREA_WIDTH] = "Choose number, q to quit";
  Character* chr = (Character*)getEntityData(getPositionEntity(s, 0, 0));
  char c[3] = " ";
  int n;

  do {
    // str[inventory->occupied][TXTAREA_WIDTH]
    str = getAllItemNames(chr->inventory);
    centerAlignMenu(chr->inventory->occupied, str, helpstr);
    
    fgets(c, 3, stdin);
    fseek(stdin, 0, SEEK_END);

    // what if string is not a number?
    if (strcmp(c, "q") == 1) break;
    else {
      // 0 - 1 = OOB warning
      n = atoi(c) - 1;
      itemMenu(chr, chr->inventory->items[n], NULL);
    }

    for (int i = 0; i < chr->inventory->occupied; ++i) free(str[i]);
  } while (1);
}


MoveReturn exploreMenu(Stage** s) {
  MoveReturn isValidMove = MOVED;
  char c;
  char helpstr[TXTAREA_WIDTH] = "Left = a, Right = d, Up = w, Down = s, Inventory = i";
  do {
    // str[POV_LINES][POV_CHARS]
    char** str = getMapAsPOV(s[CURRENT_STAGE]);
    characterPOVScreen(str, helpstr);
    c = getchar();
    fseek(stdin, 0, SEEK_END);

    switch (c) {
    case 'a':
      isValidMove = moveCharacter(s[CURRENT_STAGE], LEFT);
      break;
    case 'd':
      isValidMove = moveCharacter(s[CURRENT_STAGE], RIGHT);
      break;
    case 'w':
      isValidMove = moveCharacter(s[CURRENT_STAGE], UP);
      break;
    case 's':
      isValidMove = moveCharacter(s[CURRENT_STAGE], DOWN);
      break;
    case 'i':
      isValidMove = inventoryMenu(s[CURRENT_STAGE]);
    default:
      break;
    }

    if (isValidMove == MOVED) memcpy(helpstr, "Left = a, Right = d, Up = w, Down = s, Inventory = i", sizeof(helpstr));
    if (isValidMove == BLOCKED) memcpy(helpstr, "Do Something.", sizeof(helpstr));
    if (isValidMove == DIED) return DIED;
    if (isValidMove == FIGHT) return FIGHT;
  } while (isValidMove == MOVED || isValidMove == BLOCKED);

  return ENUM_NULL;
}

Item* battleInventoryMenu(Battle* b) {
  char** str;
  char helpstr[TXTAREA_WIDTH] = "Select Item to use, q to quit";
  char c[3] = "";
  int n;

  do {
    str = getAllItemNames(b->away->inventory);
    centerAlignMenu(b->away->inventory->occupied, str, helpstr);

    fgets(c, 3, stdin);
    fseek(stdin, 0, SEEK_END);

    memcpy(helpstr, "Select Item to use, q to quit", TXTAREA_WIDTH * sizeof(char));
    // what if string is not a number?
    if (strcmp(c, "q") == 1) break;
    else {
      // 0 - 1 = OOB Warning
      n = atoi(c) - 1;
      // This needs to be more flexible, like divide use for me or use for enemy
      if (b->away->inventory->items[n]->type == USEABLE) {
        setEffectFromEffect(b->home->e, b->away->inventory->items[n]->e);
        deleteItemFromInventory(b->away->inventory, b->away->inventory->items[n], n);
      }
      else memcpy(helpstr, "Not Useable Item.", TXTAREA_WIDTH * sizeof(char));
    }
  } while (1);

  return NULL;
}

Stage* battleMenu(Stage* s) {
  Battle* b = createBattle(s, (Character*)getEntityData(getPositionEntity(s, 0, 0)), (Character*)getEntityData(getPositionEntity(s, s->pos_x, s->pos_y)));
  BattleReturn hasDied = 0;
  BattleType awaymove = 0;
  BattleType homemove = 0;
  char c;

  Item* i = NULL;
  int homedmg = 0;
  int awaydmg = 0;

  char helpstr[TXTAREA_WIDTH] = "Attack - w, Roll - s, Inventory - i";
  char** str;
  do {
    str = getBattlePOV(b);
    battleScreen(str, helpstr);
    c = getchar();
    fseek(stdin, 0, SEEK_END);

    switch (c) {
    case 'w':
      awaymove = ATTACK;
      break;
    case 's':
      awaymove = DODGE;
      break;
    case 'i':
      awaymove = USE_ITEM;
      break;
    }

    if (awaymove == USE_ITEM) battleInventoryMenu(b);

    if (awaymove != USE_ITEM) {
      // Player order function
      awaydmg = calculateBattleAttack(b, awaymove, AWAY);
      // Bot Pattern function
      homemove = getPatternAttack(b, b->turn, HOME);
      homedmg = calculateBattleAttack(b, homemove, HOME);
      hasDied = sumUpBattle(b, awaydmg, awaymove, homedmg, homemove);
      
      ++b->turn;
      homedmg = 0;
      awaydmg = 0;
    }

  } while (hasDied == IN_PROGRESS);

  if (hasDied == DEAD) {
    memcpy(helpstr, "YOU DIED, Enter to go Main menu", TXTAREA_WIDTH * sizeof(char));
    str = getBattlePOV(b);
    battleScreen(str, helpstr);
    c = getchar();
    fseek(stdin, 0, SEEK_END);

    if (c == '\n') {

    }
  }
  if(hasDied == KILLED)

  return s;
}

Stage* mainMenu() {
  char c;
  unsigned char isValid = 0;
  
  char str[][TXTAREA_WIDTH] = { "New Game", "Load Save", "Exit" };
  
  char** t_str = (char**)malloc(sizeof(str) / TXTAREA_WIDTH * sizeof(char*));
  for (int i = 0; i < sizeof(str) / TXTAREA_WIDTH; ++i) {
    t_str[i] = (char*)malloc(TXTAREA_WIDTH * sizeof(char));
    memcpy(t_str[i], str[i], TXTAREA_WIDTH * sizeof(char));
  }

  char helpstr[] = "Select Menu...";

  while (1) {
    centerAlignMenu(sizeof(str) / TXTAREA_WIDTH, t_str, helpstr);
    c = getchar();
    fseek(stdin, 0, SEEK_END);
    switch (c) {
    case '1':
      return (Stage*)newGame();
    case '2':
      return (Stage*)loadGame();
    case '3':
      return NULL;
    }
    memcpy(helpstr, "Invalid Input!", sizeof(helpstr));
  }

  for (int i = 0; i < sizeof(str) / TXTAREA_WIDTH; ++i) free(t_str[i]);
}

void Splash() {
  char c;

  do {
    system("cls");
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
  } while (c != '\n');
}