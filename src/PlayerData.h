#pragma once
#include <pebble.h>
#include "ShipStructs.h"

#define MAX_PROJ_NUM 15
#define NUM_PROJECTILE_TYPES 1
#define NUM_SHIPS 1
#define NUM_WEAPONS 1

Window *ship_store;
Window *weapon_store;
Window *upgrades_store;
MenuLayer *ship_menu;
MenuLayer *weapon_menu;
MenuLayer *upgrades_menu;

void pushBullet(Vec2d coords, Vec2d vel, ProjectileData *projData);
void pullBullet(int id);

void handlePlayer(Buttons pressedButtons, double fps);
void enableAccel(bool enable);

void initShips();
void initWeapons();
void initProjectileTypes();
void initPlayer();
void deinitPlayer();

void setShip(int shipID);
void drawPlayerData(Layer *layer, GContext *gcx);

ProjectileData projectileTypes[NUM_PROJECTILE_TYPES];

Projectile allProjectiles[MAX_PROJ_NUM];
int numProjectiles;
Ship *currentShip;
Weapon *currentWeapon;

Ship allShips[NUM_SHIPS];
Weapon allWeapons[NUM_WEAPONS];

double shipCoords;
int prevShotDelay;