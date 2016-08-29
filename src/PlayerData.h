#pragma once
#include <pebble.h>
#include "usefulFunctions.h"

#define MAX_NAME_SIZE 10
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

typedef struct ProjectileData{
  double speed;
  double damage;
  void (*draw)(Layer*, GContext*, Vec2d, int);//draw(Layer *layer, GContext *gcx, Vec2d center)
  void (*explode)(Layer*, GContext*, Vec2d, int);//explode(Layer *layer, GContext *gcx, Vec2d coords)
  int id;
}ProjectileData;

typedef struct Projectile{
  Vec2d coords;
  Vec2d Vel;
  ProjectileData *data;
}Projectile;

typedef struct Weapon{
  GBitmap *icon;
  int shotDelay;
  void (*fire)(Vec2d, int);//fire(Vec2d coords)
  void (*draw)(Layer*, GContext*, Vec2d, int);//draw(Vec2d center)
  int id;
  char name[MAX_NAME_SIZE];
}Weapon;

typedef struct Ship{
  GBitmap *icon;
  void (*draw)(Layer*, GContext*, int, int);
  double health, maxHealth;
  double armor, armorRegen, maxArmor;
  double speed;
  double cost;
  bool bought;
  int length;
  int id;
  char name[MAX_NAME_SIZE];
}Ship;

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