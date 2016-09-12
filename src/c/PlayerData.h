#pragma once
#include <pebble.h>
#include "ShipStructs.h"

#define NUM_PLAYER_SHIPS 1
#define NUM_PLAYER_WEAPONS 1

#define NUM_STORE_MENUS 3

Window *buy_stuff;
MenuLayer *store_menus[NUM_STORE_MENUS];

void handlePlayer(Buttons pressedButtons, double fps);
void enableAccel(bool enable);


void initPlayer();
void deinitPlayer();

void setShip(PlayerShip *ship, bool freeShip);
void setWeapon(PlayerWeapon *weapon, bool freeWeapon);
void drawPlayerData(Layer *layer, GContext *gcx);

Ship *currentShip;
Weapon *currentWeapon;

FullShip *fullPlayerShip;

PlayerShip allPlayerShips[NUM_PLAYER_SHIPS];
PlayerWeapon allPlayerWeapons[NUM_PLAYER_WEAPONS];

double maxHealthMult;
double damageMult;
double armorRegenMult;