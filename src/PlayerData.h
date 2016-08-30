#pragma once
#include <pebble.h>
#include "ShipStructs.h"

#define NUM_PLAYER_SHIPS 1
#define NUM_PLAYER_WEAPONS 1

Window *ship_store;
Window *weapon_store;
Window *upgrades_store;
MenuLayer *ship_menu;
MenuLayer *weapon_menu;
MenuLayer *upgrades_menu;

void handlePlayer(Buttons pressedButtons, double fps);
void enableAccel(bool enable);


void initPlayer();
void deinitPlayer();

void setShip(PlayerShip *ship, bool freeShip);
void setWeapon(PlayerWeapon *weapon, bool freeWeapon);
void drawPlayerData(Layer *layer, GContext *gcx);

Ship *currentShip;
Weapon *currentWeapon;

PlayerShip allPlayerShips[NUM_PLAYER_SHIPS];
PlayerWeapon allPlayerWeapons[NUM_PLAYER_WEAPONS];

double shipCoords;
int prevShotDelay;