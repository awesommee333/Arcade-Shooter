#pragma once
#include "Levels.h"
#include "ShipStructs.h"


int numEnems;
FullShip *allEnemies[MAX_LEVEL_ENEMIES];

void handleEnems(double fps);
void drawEnems(Layer *layer, GContext *gcx);
void tmpEnemInit();