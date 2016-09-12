#include "main.h"

Window *window;
TextLayer *text_layer;

void enterStore(){
  window_stack_push(store_window, true);
}

void configButtons(Window *window){
  initButtons((Buttons){true, true, false, false});
  window_single_click_subscribe(BUTTON_ID_SELECT, enterStore);
}

void lose(){
  window_stack_pop(true);
}

void handleAllCollisions(){
  handleCollisions(fullPlayerShip, allEnemies, numEnems);
  for(int i=0;i<numEnems;i++){
    handleCollisions(allEnemies[i], &fullPlayerShip, 1);
  }
}

void drawGame(Layer *layer, GContext *gcx){
  handlePlayer(buttonsPressed, FPS);
  handleEnems(FPS);
  handleAllCollisions();
  if(fullPlayerShip->ship->health<=0.0)
    lose();
  drawPlayerData(layer, gcx);
  drawEnems(layer, gcx);
}

void timerHandler(void *context){
  timeFrames++;
  layer_mark_dirty(game_layer);
  app_timer_register(1000.0/FPS, timerHandler, NULL);
}

void init_game(Window *window){
  Layer *window_layer=window_get_root_layer(window);
  GRect bounds=layer_get_bounds(window_layer);
  
  game_layer=layer_create(bounds);
  
  layer_add_child(window_layer, game_layer);
  layer_set_update_proc(game_layer, drawGame);
  
  initAllShips();
  initPlayer();
  
  tmpEnemInit();
  
  app_timer_register(1000.0/FPS, timerHandler, NULL);
}

void close_game(Window *window){
  deinitPlayer();
  layer_destroy(game_layer);
}

void init_store(Window *window){
  
}

void close_store(Window *window){
  
}

uint16_t num_main_menu_rows(MenuLayer *menu, uint16_t index, void* context){
  return NUM_MENU_ICONS;
}

void draw_menu(GContext *gcx, const Layer *cell_layer, MenuIndex *cell_index, void *context){
  menu_cell_basic_draw(gcx, cell_layer, menuBuffer[cell_index->row], NULL, menuIcons[cell_index->row]);
}

int16_t menu_cell_height(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context){
  return HEIGHT/NUM_MENU_ICONS;
}

void main_menu_select(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context){
  switch(cell_index->row){
    case 0:
      window_stack_push(game_window, true);
      break;
    case 1:
      window_stack_push(settings_window, true);
      break;
    case 2:
      window_stack_push(help_window, true);
      break;
    default:
      window_stack_push(game_window, true);
      break;
  }
}

void init_menu(Window *window){
  Layer *root_layer=window_get_root_layer(window);
  GRect bounds=layer_get_bounds(root_layer);
  
  main_menu=menu_layer_create(bounds);
  
  menu_layer_set_click_config_onto_window(main_menu, window);
  
  menu_layer_set_callbacks(main_menu, NULL, (MenuLayerCallbacks){
    .get_num_rows=num_main_menu_rows,
    .draw_row=draw_menu,
    .get_cell_height=menu_cell_height,
    .select_click=main_menu_select
  });
  
  menuIcons[1]=gbitmap_create_with_resource(RESOURCE_ID_SETTINGS_ICON);
  
  layer_add_child(root_layer, menu_layer_get_layer(main_menu));
}

void close_menu(Window *window){
  menu_layer_destroy(main_menu);
}


uint16_t num_settings_rows(MenuLayer *menu, uint16_t index, void* context){
  return NUM_SETTINGS_ICONS;
}

void draw_settings(GContext *gcx, const Layer *cell_layer, MenuIndex *cell_index, void *context){
  int printNum;
  switch(cell_index->row){
    case 0:
      printNum=difficulty;
      break;
    case 1:
      printNum=speed;
      break;
    default:
      printNum=0;
      break;
  }
  
  snprintf(settingsNums[cell_index->row], MAX_SETTINGS_SUB, "%d", printNum);
  
  menu_cell_basic_draw(gcx, cell_layer, settingsBuffer[cell_index->row], settingsNums[cell_index->row], settingsIcons[cell_index->row]);
}

int16_t settings_cell_height(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context){
  return HEIGHT/NUM_SETTINGS_ICONS;
}

void settings_select(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *context){
  switch(cell_index->row){
    case 0:
      difficulty++;
      if(difficulty>MAX_DIFFICULTY)
        difficulty=1;
      break;
    case 1:
      speed++;
      if(speed>MAX_SPEED)
        speed=1;
      break;
    default:
      break;
  }
  menu_layer_reload_data(menu_layer);
}

void init_settings(Window *window){
  Layer *root_layer=window_get_root_layer(window);
  GRect bounds=layer_get_bounds(root_layer);
  
  settings_menu=menu_layer_create(bounds);
  
  menu_layer_set_click_config_onto_window(settings_menu, window);
  
  menu_layer_set_callbacks(settings_menu, NULL, (MenuLayerCallbacks){
    .get_num_rows=num_settings_rows,
    .draw_row=draw_settings,
    .get_cell_height=settings_cell_height,
    .select_click=settings_select
  });
  
  layer_add_child(root_layer, menu_layer_get_layer(settings_menu));
}

void close_settings(Window *window){
  menu_layer_destroy(settings_menu);
}

void init_help(Window *window){
  
}

void close_help(Window *window){
  
}

void init(){
  menu_window=window_create();
  game_window=window_create();
  store_window=window_create();
  settings_window=window_create();
  help_window=window_create();
  
  window_set_background_color(game_window, GColorBlack);
  
  window_set_window_handlers(menu_window, (WindowHandlers){
    .load=init_menu,
    .unload=close_menu
  });
  
  window_set_window_handlers(game_window, (WindowHandlers){
    .load=init_game,
    .unload=close_game
  });
  
  window_set_window_handlers(store_window, (WindowHandlers){
    .load=init_store,
    .unload=close_store
  });
  
  window_set_window_handlers(settings_window, (WindowHandlers){
    .load=init_settings,
    .unload=close_settings
  });
  
  window_set_window_handlers(help_window, (WindowHandlers){
    .load=init_help,
    .unload=close_help
  });
  
  window_set_click_config_provider(game_window, (ClickConfigProvider) configButtons);
  
  window_stack_push(menu_window, true);
}

void deinit(){
  window_destroy(window);
  window_destroy(game_window);
  window_destroy(store_window);
  window_destroy(settings_window);
  window_destroy(help_window);
}

int main(){
  init();
  
  app_event_loop();
  
  deinit();
  
  return 0;
}