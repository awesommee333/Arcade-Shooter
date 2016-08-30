#pragma once
#include "usefulFunctions.h"
#include <pebble.h>
#define MAX_NAME_SIZE 10
#define NUM_PROJECTILE_TYPES 1
#define NUM_SHIPS 1
#define NUM_WEAPONS 1

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
  void (*fire)(Vec2d, struct Weapon*);//fire(Vec2d coords)
  void (*draw)(Layer*, GContext*, Vec2d, struct Weapon*);//draw(Vec2d center)
  int maxProjectiles;
  int numProjectiles;
  Projectile projectiles[];//why does mallocing this to expand it still give and error when I try to access projectiles[num that's greater than 1?]
}Weapon;

typedef struct Ship{
  GBitmap *icon;
  void (*draw)(Layer*, GContext*, int, struct Ship*);
  void (*testCollision)(Vec2d*);
  double health, maxHealth;
  double armor, armorRegen, maxArmor;
  double speed;
  int length;
}Ship;

typedef struct PlayerShip{
  Ship *actualShip;
  bool custom;
  int customMaxHealth;
  int customArmorRegen, customMaxArmor;
  int customSpeed;
  int cost;
  double damageMultiplier;
  bool bought;
  char name[MAX_NAME_SIZE];
} PlayerShip;

typedef struct PlayerWeapon{
  Weapon *actualWeapon;
  bool custom;
  int customShotDelay;
  int customMaxProjectiles;
  int cost;
  bool bought;
  char name[MAX_NAME_SIZE];
}PlayerWeapon;

typedef struct EnemShip{
  Ship ship;
  Weapon weapon;
}EnemShip;

void pushBullet(Weapon *currentWeapon, Vec2d coords, Vec2d vel, ProjectileData *projData);
void pullBullet(Weapon *currentWeapon, int id);

Ship allShips[NUM_SHIPS];
ProjectileData projectileTypes[NUM_PROJECTILE_TYPES];
Weapon allWeapons[NUM_WEAPONS];

void initShips();
void initWeapons();
void initProjectileTypes();
void initAllShips();
void updateProjectiles(Weapon *currentWeapon, double fps);