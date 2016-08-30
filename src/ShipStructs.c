#include <pebble.h>
#include "ShipStructs.h"

void updateProjectiles(Weapon *currentWeapon, double fps){
  for(int i=0;i<currentWeapon->numProjectiles;i++){
    Vec2d tmp=currentWeapon->projectiles[i].Vel;
    scaleVec(&tmp, &tmp, currentWeapon->projectiles[i].data->speed/fps);
    addVecs(&currentWeapon->projectiles[i].coords, &tmp, &currentWeapon->projectiles[i].coords);
  }
}

void pushBullet(Weapon *currentWeapon, Vec2d coords, Vec2d vel, ProjectileData *projData){
  for(int i=currentWeapon->numProjectiles;i>0;i--){
    currentWeapon->projectiles[i]=currentWeapon->projectiles[i-1];
  }
  currentWeapon->projectiles[0]=(Projectile){coords, vel, projData};
  currentWeapon->numProjectiles++;
  if(currentWeapon->numProjectiles>=currentWeapon->maxProjectiles)
    currentWeapon->numProjectiles=currentWeapon->maxProjectiles;
}

void pullBullet(Weapon *currentWeapon, int id){
  for(int i=id+1;i<currentWeapon->maxProjectiles;i++){
    currentWeapon->projectiles[i-1]=currentWeapon->projectiles[i];
  }
  currentWeapon->numProjectiles--;
  if(currentWeapon->numProjectiles<0)
    currentWeapon->numProjectiles=0;
}

void drawSimpleProj(Layer *layer, GContext *gcx, Vec2d center, int id){
  graphics_context_set_fill_color(gcx, GColorWhite);
  GRect bullet={{(int)center.x-1, (int)center.y-1}, {3, 3}};
  
  graphics_fill_rect(gcx, bullet, 0, GCornerNone);
}

void initProjectileTypes(){
  projectileTypes[0]=(ProjectileData){
    .speed=80.0,
    .damage=1.0,
    .draw=drawSimpleProj
  };
}

void drawSimpleShip(Layer *layer, GContext *gcx, int center, Ship *ship){
  graphics_context_set_fill_color(gcx, GColorWhite);
  GRect shipMain={{0, center-9}, {10, 19}};
  
  graphics_fill_rect(gcx, shipMain, 3, GCornerNone);
}

void initShips(){
   allShips[0]=(Ship){
    .draw=&drawSimpleShip,
    .speed=HEIGHT/2,
    .length=10
  };
}

void basicWeaponDraw(Layer* layer, GContext* gcx, Vec2d coords, Weapon *weapon){
  graphics_context_set_fill_color(gcx, GColorRed);
  
  GRect shipShoot={{coords.x , coords.y-1}, {5, 3}};
  graphics_fill_rect(gcx, shipShoot, 0, GCornerNone);
}

void basicWeaponFire(Vec2d coords, Weapon *weapon){
  pushBullet(weapon, coords, (Vec2d){1.0, 0.0}, &projectileTypes[0]);
}

void initWeapons(){
  allWeapons[0]=(Weapon){
    .shotDelay=10,
    .draw=&basicWeaponDraw,
    .fire=&basicWeaponFire,
    .maxProjectiles=15,
    .numProjectiles=0
  };
}

void initAllShips(){
  initProjectileTypes();
  initShips();
  initWeapons();
}