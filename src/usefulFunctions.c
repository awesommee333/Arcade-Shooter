#include "usefulFunctions.h"

double sqrt(double num){
  double a, b, e=0.001;
  a=num;
  b=num/a;
  for(int i=0; fabs(a*a-num)>e && i<MAX_SQRT; i++){
    a=(a+b)/2;
    b=num/a;
  }
  return a;
}
int sign(double num){
  if(num>0)
    return 1;
  else if(num<0)
    return -1;
  return 0;
}

bool rectCollision(GRect rec1, GRect rec2){
  rec1.origin.x+=rec1.size.w/2;
  rec1.origin.y+=rec1.size.h/2;
  rec2.origin.x+=rec2.size.w/2;
  rec2.origin.y+=rec2.size.h/2;
  if(abs(rec1.origin.x-rec2.origin.x)>(rec1.size.w+rec2.size.w)/2)
    return false;
  else if(abs(rec1.origin.y-rec2.origin.y)>(rec1.size.h+rec2.size.h)/2)
    return false;
  return true;
}

void scaleVec(Vec2d *vec, Vec2d *out, double multiplier){
  out->x=(vec->x)*multiplier;
  out->y=(vec->y)*multiplier;
}

void addVecs(Vec2d *vec1, Vec2d *vec2, Vec2d *out){
  out->x=vec1->x+vec2->x;
  out->y=vec1->y+vec2->y;
}

void subVecs(Vec2d *vec1, Vec2d *vec2, Vec2d *out){
  out->x=vec1->x-vec2->x;
  out->y=vec1->y-vec2->y;
}

double normVec(Vec2d *vec){
  double tmp=sqrt((vec->x)*(vec->x)+(vec->y)*(vec->y));
  return tmp;
}

static void upTrue(){
  buttonsPressed.up=true;
}

static void upFalse(){
  buttonsPressed.up=false;
}

static void downTrue(){
  buttonsPressed.down=true;
}

static void downFalse(){
  buttonsPressed.down=false;
}

static void selTrue(){
  buttonsPressed.sel=true;
}

static void selFalse(){
  buttonsPressed.sel=false;
}

static void backTrue(){
  buttonsPressed.back=true;
}

static void backFalse(){
  buttonsPressed.back=false;
}

void initButtons(Buttons whichButtons){
  if(whichButtons.up)
    window_raw_click_subscribe(BUTTON_ID_UP, upTrue, upFalse, NULL);
  if(whichButtons.down)
    window_raw_click_subscribe(BUTTON_ID_DOWN, downTrue, downFalse, NULL);
  if(whichButtons.sel)
    window_raw_click_subscribe(BUTTON_ID_SELECT, selTrue, selFalse, NULL);
  if(whichButtons.back)
    window_raw_click_subscribe(BUTTON_ID_BACK, backTrue, backFalse, NULL);
}