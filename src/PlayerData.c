#include "PlayerData.h"

void updateProjectiles(double fps){
  for(int i=0;i<numProjectiles;i++){
    Vec2d tmp=allProjectiles[i].Vel;
    scaleVec(&tmp, &tmp, allProjectiles[i].data->speed/fps);
    addVecs(&allProjectiles[i].coords, &tmp, &allProjectiles[i].coords);
  }
}

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
    currentWeapon->fire((Vec2d){currentShip->length, shipCoords}, currentWeapon->id);
    prevShotDelay=0;
  }
  
  updateProjectiles(fps);
}

void enableAccel(bool enable){
  
}

void pushBullet(Vec2d coords, Vec2d vel, ProjectileData *projData){
  for(int i=MAX_PROJ_NUM-1;i>0;i--){
    allProjectiles[i]=allProjectiles[i-1];
  }
  allProjectiles[0]=(Projectile){coords, vel, projData};
  numProjectiles++;
  if(numProjectiles>=MAX_PROJ_NUM)
    numProjectiles=MAX_PROJ_NUM;
}

void pullBullet(int id){
  for(int i=id+1;i<MAX_PROJ_NUM;i++){
    allProjectiles[i-1]=allProjectiles[i];
  }
  numProjectiles--;
  if(numProjectiles<0)
    numProjectiles=0;
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

void drawSimpleShip(Layer *layer, GContext *gcx, int center, int id){
  graphics_context_set_fill_color(gcx, GColorWhite);
  GRect shipMain={{0, center-9}, {10, 19}};
  
  graphics_fill_rect(gcx, shipMain, 3, GCornerNone);
}

void initShips(){
  allShips[0]=(Ship){
    .draw=&drawSimpleShip,
    .speed=50,
    .length=10,
    .id=0
  };
}

void setShip(int shipID){
  free(currentShip);
  currentShip=malloc(sizeof(Ship));
  memcpy(currentShip, &allShips[shipID], sizeof(Ship));
}

void setWeapon(int weaponID){
  free(currentWeapon);
  currentWeapon=malloc(sizeof(Weapon));
  memcpy(currentWeapon, &allWeapons[weaponID], sizeof(Weapon));
}

void basicWeaponDraw(Layer* layer, GContext* gcx, Vec2d coords, int id){
  graphics_context_set_fill_color(gcx, GColorRed);
  
  GRect shipShoot={{coords.x , coords.y-1}, {5, 3}};
  graphics_fill_rect(gcx, shipShoot, 0, GCornerNone);
}

void basicWeaponFire(Vec2d coords, int id){
  pushBullet(coords, (Vec2d){1.0, 0.0}, &projectileTypes[0]);
}

void initWeapons(){
  prevShotDelay=0;
  allWeapons[0]=(Weapon){
    .shotDelay=10,
    .draw=&basicWeaponDraw,
    .fire=&basicWeaponFire,
    .id=0
  };
}

void initPlayer(){
  initProjectileTypes();
  initShips();
  initWeapons();
  
  currentShip=malloc(sizeof(Ship));
  memcpy(currentShip, &allShips[0], sizeof(Ship));
  currentWeapon=malloc(sizeof(Weapon));
  memcpy(currentWeapon, &allWeapons[0], sizeof(Weapon));
  
  shipCoords=HEIGHT/2.0;
  prevShotDelay=0;
}

void deinitPlayer(){
  free(currentShip);
  free(currentWeapon);
}

void drawPlayerProjectiles(Layer *layer, GContext *gcx){
  for(int i=0;i<numProjectiles;i++){
    allProjectiles[i].data->draw(layer, gcx, allProjectiles[i].coords, allProjectiles[i].data->id);
  }
}

void drawPlayerData(Layer *layer, GContext *gcx){
  currentShip->draw(layer, gcx, shipCoords, currentShip->id);
  currentWeapon->draw(layer, gcx, (Vec2d){currentShip->length, shipCoords}, currentWeapon->id);
  drawPlayerProjectiles(layer, gcx);
}