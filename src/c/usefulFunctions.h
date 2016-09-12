#pragma once

#include <pebble.h>
#include <math.h>

#define MAX_SQRT 10

#define HEIGHT 168.0
#define WIDTH 144.0

typedef struct {
  double x;
  double y;
} Vec2d;

typedef struct {
  bool up;
  bool down;
  bool sel;
  bool back;
} Buttons;

double sqrt(double num);
int sign(double num);

bool rectCollision(GRect rec1, GRect rec2);

void scaleVec(Vec2d *vec, Vec2d *out, double scalar);
void addVecs(Vec2d *vec1, Vec2d *vec2, Vec2d *out);
void subVecs(Vec2d *vec1, Vec2d *vec2, Vec2d *out);
double normVec(Vec2d *vec);

Buttons buttonsPressed;

void initButtons(Buttons whichButtons);