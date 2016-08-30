#include "PlayerData.h"

void handlePlayer(Buttons pressedButtons, double fps){
  if(pressedButtons.up){
    shipCoords-=currentShip->speed/fps;
    if(shipCoords<0.0)
      shipCoords=0.0;
  }
  else if(pressedButtons.down){
    shipCoords+=currentShip->speed/fps;
    if(shipCoords>HEIGHT)
      shipCoords=HEIGHT;
  }
  
  prevShotDelay++;
  
  if(prevShotDelay>currentWeapon->shotDelay){
    currentWeapon->fire((Vec2d){currentShip->length, shipCoords}, currentWeapon);
    prevShotDelay=0;
  }
  
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
  
  setShip(&allPlayerShips[0], false);
  setWeapon(&allPlayerWeapons[0], false);
  
  shipCoords=HEIGHT/2.0;
  prevShotDelay=0;
}

void deinitPlayer(){
  free(currentShip);
  free(currentWeapon);
}

void drawPlayerProjectiles(Layer *layer, GContext *gcx){
  for(int i=0;i<currentWeapon->numProjectiles;i++){
    currentWeapon->projectiles[i].data->draw(layer, gcx, currentWeapon->projectiles[i].coords, currentWeapon->projectiles[i].data->id);
  }
}

void drawPlayerData(Layer *layer, GContext *gcx){
  currentShip->draw(layer, gcx, shipCoords, currentShip);
  currentWeapon->draw(layer, gcx, (Vec2d){currentShip->length, shipCoords}, currentWeapon);
  drawPlayerProjectiles(layer, gcx);
}