#pragma once
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define ESC 27
#define KEY_SHOOT_LEFT 'j'
#define KEY_SHOOT_RIGHT 'k'
#define MAX_NUM_BULLETS 4
#define MAX_NUM_ENEMIES 8
#define KEY_RAIN 176
#define INITIAL_POS width/2
#define INITIAL_LIVES 3
#define INITIAL_LEVEL 1
#define INITIAL_SCORE 0

const int width = 180;

void restart();
void refresh_score();
void pushed_key();
void create_map();
void move_enemies();
void generate_enemies();
void move_bullets();
void collisions();
void get_mushroom();
void generate_mushroom();
void refresh_level();
void gotoxy(int column, int line);
int wherex();
int wherey();