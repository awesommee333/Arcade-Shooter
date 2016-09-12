#pragma once
#include "usefulFunctions.h"
#include "PlayerData.h"
#include "Enemies.h"
#include "ShipStructs.h"

#define NUM_STORE_ITEMS 10
#define MAX_STORE_TITLE 16
#define NUM_MENU_ICONS 3
#define NUM_SETTINGS_ICONS 2
#define MAX_SETTINGS_SUB 5

#define MAX_DIFFICULTY 4
#define MAX_SPEED 3

#define FPS 30.0

Window *game_window;
Window *menu_window;
Window *store_window;
Window *settings_window;
Window *help_window;
BitmapLayer *background_layer;
GBitmap *background;
Layer *game_layer;
TextLayer *text_layer;
MenuLayer *main_menu;
MenuLayer *settings_menu;
MenuLayer *store_menu;
ScrollLayer *help_scroll;

const char *menuBuffer[]={"Play", "Settings", "Help"};
GBitmap *menuIcons[NUM_MENU_ICONS];

char *settingsBuffer[]={"Difficulty: ", "Speed: "};
char settingsNums[NUM_SETTINGS_ICONS][MAX_SETTINGS_SUB];
GBitmap *settingsIcons[NUM_SETTINGS_ICONS];

const char *helpText="This is the help menu";

char storeBuffer[NUM_STORE_ITEMS][MAX_STORE_TITLE];

int difficulty=1;
int speed=1;