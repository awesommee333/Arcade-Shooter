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
  void (*fire)(Vec2d, struct Weapon*, bool enem);//fire(Vec2d coords)
  void (*draw)(Layer*, GContext*, Vec2d, struct Weapon*);//draw(Vec2d center)
  double damageMultiplier;
  int maxProjectiles;
  int numProjectiles;
  int height;
  Projectile projectiles[];
}Weapon;

typedef struct Ship{
  GBitmap *icon;
  void (*draw)(Layer*, GContext*, struct Ship*);
  bool (*testCollision)(Vec2d*, struct Ship*);
  double health, maxHealth;
  double armor, armorRegen, maxArmor;
  double speed;
  int height, length;
  Vec2d coords;
}Ship;

typedef struct PlayerShip{
  Ship *actualShip;
  bool custom;
  GBitmap *customIcon;
  int customMaxHealth;
  int customArmorRegen, customMaxArmor;
  int customSpeed;
  int cost;
  bool bought;
  char name[MAX_NAME_SIZE];
} PlayerShip;

typedef struct PlayerWeapon{
  Weapon *actualWeapon;
  bool custom;
  double customDamageMultiplier;
  int customShotDelay;
  int customMaxProjectiles;
  int cost;
  bool bought;
  char name[MAX_NAME_SIZE];
}PlayerWeapon;

typedef struct FullShip{
  Ship *ship;
  Weapon *weapon;
  int prevShot;
}FullShip;

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

void fireShip(FullShip *comboShip, bool enem);
void drawShip(Layer *layer, GContext *gcx, FullShip *comboShip, bool playerShip);
void handleCollisions(FullShip *ship, FullShip *ships[], int numShips);

int timeFrames;