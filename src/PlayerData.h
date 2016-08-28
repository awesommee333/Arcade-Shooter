#pragma once
#include <pebble.h>
#include "usefulFunctions.h"

#define MAX_NAME_SIZE 10
#define MAX_PROJ_NUM 15
#define NUM_SHIPS 1
#define NUM_WEAPONS 1

Window *ship_store;
Window *weapon_store;
Window *upgrades_store;
MenuLayer *ship_menu;
MenuLayer *weapon_menu;
MenuLayer *upgrades_menu;

typedef struct ProjectileData{
  double speed;
  double damage;
  void *draw;
  void *explode;
}ProjectileData;

typedef struct Projectile{
  Vec2d coords;
  Vec2d Vel;
  ProjectileData *data;
}Projectile;

typedef struct Weapon{
  GBitmap *icon;
  void *fire;
  char name[MAX_NAME_SIZE];
}Weapon;

typedef struct Ship{
  GBitmap *icon;
  void *draw;
  double health, maxHealth;
  double armor, armorRegen, maxArmor;
  double speed;
  double cost;
  char name[MAX_NAME_SIZE];
}Ship;

void handlePlayer();
void enableAccel(bool enable);

Projectile allProjectiles[MAX_PROJ_NUM];
Ship *currentShip;
Weapon *currentWeapon;

Ship allShips[NUM_SHIPS];
Weapon allWeapons[NUM_WEAPONS];