#include "PlayerData.h"

void handlePlayer(Buttons pressedButtons, double fps){
  if(pressedButtons.up){
    currentShip->coords.y-=currentShip->speed/fps;
    if(currentShip->coords.y<0.0)
      currentShip->coords.y=0.0;
  }
  else if(pressedButtons.down){
    currentShip->coords.y+=currentShip->speed/fps;
    if(currentShip->coords.y>HEIGHT)
      currentShip->coords.y=HEIGHT;
  }
  
  fireShip(fullPlayerShip, false);
  
  updateProjectiles(currentWeapon, fps);
}

void enableAccel(bool enable){
  
}

void setShip(PlayerShip *ship, bool freeShip){
  if(freeShip)
    free(currentShip);
  currentShip=malloc(sizeof(Ship));
  memcpy(currentShip, ship->actualShip, sizeof(Ship));
  if(ship->custom){
    currentShip->maxHealth=ship->customMaxHealth;
    currentShip->maxArmor=ship->customMaxArmor;
    currentShip->armorRegen=ship->customArmorRegen;
    currentShip->speed=ship->customSpeed;
  }
  fullPlayerShip->ship=currentShip;
}

void setWeapon(PlayerWeapon *weapon, bool freeWeapon){
  if(freeWeapon)
    free(currentWeapon);
  int add=weapon->actualWeapon->maxProjectiles;
  if(weapon->custom)
    add=weapon->customMaxProjectiles;
  currentWeapon=malloc(sizeof(Weapon)+add*sizeof(Projectile));
  memcpy(currentWeapon, weapon->actualWeapon, sizeof(Weapon));
  if(weapon->custom){
    currentWeapon->maxProjectiles=weapon->customMaxProjectiles;
    currentWeapon->shotDelay=weapon->customShotDelay;
  }
  fullPlayerShip->weapon=currentWeapon;
}

void initPlayerShips(){
  allPlayerShips[0]=(PlayerShip){
    .actualShip=&allShips[0],
    .custom=false
  };
}

void initPlayerWeapons(){
  allPlayerWeapons[0]=(PlayerWeapon){
    .actualWeapon=&allWeapons[0],
    .custom=false
  };
}

void initPlayer(){
  initPlayerShips();
  initPlayerWeapons();
  
  fullPlayerShip=malloc(sizeof(FullShip));
  fullPlayerShip->prevShot=0;
  
  setShip(&allPlayerShips[0], false);
  setWeapon(&allPlayerWeapons[0], false);
  
  currentShip->coords.x=0.0;
  currentShip->coords.y=HEIGHT/2.0;
  currentShip->health=currentShip->maxHealth;
}

void deinitPlayer(){
  free(currentShip);
  free(currentWeapon);
  free(fullPlayerShip);
}

void drawPlayerData(Layer *layer, GContext *gcx){
  drawShip(layer, gcx, fullPlayerShip, true);
}