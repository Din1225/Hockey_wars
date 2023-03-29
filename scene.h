#include "global.h"
#include "charater.h"

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void about1_init();
void about1_process(ALLEGRO_EVENT event);
void about1_draw();
void about1_destroy();

void about2_init();
void about2_process(ALLEGRO_EVENT event);
void about2_draw();
void about2_destroy();

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();

void choose_scene_init();
void choose_process(ALLEGRO_EVENT event);
void choose_scene_draw();
void choose_scene_destroy();

void game_soccer_init();
void game_soccer_draw();
void game_soccer_destroy();

void game_ice_init();
void game_ice_draw();
void game_ice_destroy();

void game_beach_init();
void game_beach_draw();
void game_beach_destroy();

void game_outspace_init();
void game_outspace_draw();
void game_outspace_destroy();

void end_init();
void end_draw();
void end_process(ALLEGRO_EVENT event);
void end_destroy();

extern void game_destroy();
