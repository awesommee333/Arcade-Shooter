#include <pebble.h>
#include "ShipStructs.h"

void fireShip(FullShip *comboShip, bool enem){
  if(timeFrames-comboShip->prevShot>comboShip->weapon->shotDelay){
    comboShip->weapon->fire((Vec2d){comboShip->ship->coords.x+comboShip->ship->length, comboShip->ship->coords.y}, comboShip->weapon, enem);
    comboShip->prevShot=timeFrames;
  }
}

void drawShip(Layer *layer, GContext *gcx, FullShip *comboShip, bool playerShip){
  comboShip->ship->draw(layer, gcx, comboShip->ship);
  double xCoord=comboShip->ship->coords.x-comboShip->weapon->height;
  if(playerShip)
    xCoord=comboShip->ship->coords.x+comboShip->ship->height;
  
  comboShip->weapon->draw(layer, gcx, (Vec2d){xCoord, comboShip->ship->coords.y}, comboShip->weapon);
  
  for(int i=0;i<comboShip->weapon->numProjectiles;i++){
    comboShip->weapon->projectiles[i].data->draw(layer, gcx, comboShip->weapon->projectiles[i].coords, comboShip->weapon->projectiles[i].data->id);
  }
}

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

void drawSimpleShip(Layer *layer, GContext *gcx, Ship *ship){
  graphics_context_set_fill_color(gcx, GColorWhite);
  GRect shipMain={{ship->coords.x, ship->coords.y-(double)ship->length}, {ship->height, ship->length*2+1}};
  
  graphics_fill_rect(gcx, shipMain, 3, GCornerNone);
}

bool simpleShipCollision(Vec2d *coords, Ship *ship){
  if(coords->x>=ship->coords.x && coords->x<=ship->coords.x+(double)ship->height){
    if(coords->y>=ship->coords.y-(double)ship->length && coords->y<=ship->coords.y+(double)ship->length)
      return true;
  }
  return false;
}

void initShips(){
   allShips[0]=(Ship){
    .draw=&drawSimpleShip,
    .testCollision=&simpleShipCollision,
    .speed=HEIGHT/2,
    .length=10,
    .height=10,
    .maxHealth=10.0,
    .health=0.0,
    .maxArmor=0.0,
    .armorRegen=0.0,
    .armor=0.0
  };
}

void basicWeaponDraw(Layer* layer, GContext* gcx, Vec2d coords, Weapon *weapon){
  graphics_context_set_fill_color(gcx, GColorRed);
  
  GRect shipShoot={{coords.x , coords.y-1}, {weapon->height, 3}};
  graphics_fill_rect(gcx, shipShoot, 0, GCornerNone);
}

void basicWeaponFire(Vec2d coords, Weapon *weapon, bool enem){
  double xSpd=1.0;
  if(enem)
    xSpd*=-1.0;
  pushBullet(weapon, coords, (Vec2d){xSpd, 0.0}, &projectileTypes[0]);
}

void initWeapons(){
  allWeapons[0]=(Weapon){
    .shotDelay=10,
    .draw=&basicWeaponDraw,
    .fire=&basicWeaponFire,
    .maxProjectiles=15,
    .numProjectiles=0,
    .damageMultiplier=1.0,
    .height=5
  };
}

void initAllShips(){
  initProjectileTypes();
  initShips();
  initWeapons();
}

void handleCollisions(FullShip *testShip, FullShip *ships[], int numShips){
  int sub=0;
  for(int i=0;i<testShip->weapon->numProjectiles;i++){
    for(int j=0;j<numShips;j++){
      if(testShip->weapon->projectiles[i-sub].coords.x<0.0 || testShip->weapon->projectiles[i-sub].coords.x>WIDTH){
        pullBullet(testShip->weapon, i-sub);
        sub++;
      }
      Ship *tmpShip=ships[j]->ship;
      if(testShip->ship->testCollision(&testShip->weapon->projectiles[i-sub].coords, tmpShip)){
        double damage=testShip->weapon->damageMultiplier*testShip->weapon->projectiles[i-sub].data->damage;
        if(tmpShip->health>0.0){
          if(tmpShip->armor>=damage)
            tmpShip->armor-=damage;
          else{
            tmpShip->health-=damage-tmpShip->armor;
            tmpShip->armor=0.0;
          }
          pullBullet(testShip->weapon, i-sub);
          sub++;
        }
      }
    }
  }
}