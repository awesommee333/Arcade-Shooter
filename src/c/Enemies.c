#include <pebble.h>
#include "Enemies.h"

void drawEnems(Layer *layer, GContext *gcx){
  for(int i=0;i<numEnems;i++){
    drawShip(layer, gcx, allEnemies[i], false);
  }
}

void pullEnem(int id){
  free(allEnemies[id]->ship);
  free(allEnemies[id]->weapon);
  free(allEnemies[id]);
  for(int i=id+1;i<numEnems;i++){
    allEnemies[i-1]=allEnemies[i];
  }
  numEnems--;
  if(numEnems<0)
    numEnems=0;
}

void handleEnems(double fps){
  int sub=0;
  for(int i=0;i<numEnems;i++){
    if(allEnemies[i-sub]->ship->health>0.0)
      fireShip(allEnemies[i-sub], true);
    updateProjectiles(allEnemies[i-sub]->weapon, fps);
    if(allEnemies[i-sub]->weapon->numProjectiles<=0 && allEnemies[i-sub]->ship->health<=0.0){
      pullEnem(i);
      sub++;
    }
  }
}

void tmpEnemInit(){
  numEnems=1;
  allEnemies[0]=malloc(sizeof(FullShip));
  allEnemies[0]->ship=malloc(sizeof(Ship));
  memcpy(allEnemies[0]->ship, &allShips[0], sizeof(Ship));
  allEnemies[0]->weapon=malloc(sizeof(Weapon)+allWeapons[0].maxProjectiles);
  memcpy(allEnemies[0]->weapon, &allWeapons[0], sizeof(Weapon));
  allEnemies[0]->prevShot=0;
  
  allEnemies[0]->ship->health=allEnemies[0]->ship->maxHealth;
  allEnemies[0]->ship->coords.x=100.0;
  allEnemies[0]->ship->coords.y=HEIGHT/2.0;
}