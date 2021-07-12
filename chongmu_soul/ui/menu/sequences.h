#pragma once
#include "../../afx.h"
#include "../../stage/stage.h"
#include "../../stage/battle.h"

Stage** newGame();
void diedMenu(Battle* b, Stage* s[STAGE_N_REFSTAGE]);
Stage* loadGame();
void itemMenu(Character* chr, Item* i, Battle *b);
MoveReturn inventoryMenu(Stage* s);
MoveReturn exploreMenu(Stage** s);
Stage* battleMenu(Stage* s);
Stage* mainMenu();
void Splash();