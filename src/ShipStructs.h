#pragma once
#include "usefulFunctions.h"
#include <pebble.h>
#define MAX_NAME_SIZE 10
#define MAX_LEVEL_ENEMIES 60

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
  double cost;
  bool bought;
  char name[MAX_NAME_SIZE];
}Weapon;

typedef struct Ship{
  GBitmap *icon;
  void (*draw)(Layer*, GContext*, int, int);
  void (*testCollision)(Vec2d*);
  double health, maxHealth;
  double armor, armorRegen, maxArmor;
  double speed;
  double cost;
  bool bought;
  int length;
  int id;
  char name[MAX_NAME_SIZE];
}Ship;