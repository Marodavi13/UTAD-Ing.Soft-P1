// Practica1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 
#include <vector>
#include <string>

#define KEY_A 'a'
#define KEY_D 'd'
#define ESC 27
#define KEY_J 'j'
#define KEY_K 'k'
#define MAX_NUM_BULLETS 4
#define MAX_NUM_ENEMIES 8
#define KEY_RAIN 176

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
void draw_map();
void refresh_level();

using namespace std;
//Mapa
const int width = 60;
char map[width];


//Posiciones
int pos				 = width / 2;

//Flags
int flag_bullet = 0;
int flag_enemy  = 0;
int flag_dead = 0;
int flag_mushroom   = 0;

//Otros
char key;
unsigned int random			 = 0;
int mushroom		 = 0;
unsigned int random_pos       =-1;
unsigned int random_rain;
unsigned int counter = 0;
char * level         = "Nivel 1";
int life			 = 3;
int score			 = 0;
//Vectores de posiciones

std::vector <int> bullets_pos_left, bullets_pos_right;
std::vector <int> enemies_pos_left, enemies_pos_right;
int main()
{
	cout  <<"\n \n \n \n \n \n" << endl;

	while (1) {
		refresh_score();
		pushed_key();
		if (pos >= 0 && pos < width) {
			create_map();
			move_enemies();
			generate_enemies();
			move_bullets();
			collisions();
			get_mushroom();
			generate_mushroom();
			draw_map();
			refresh_level();
		}
	}
    return 0;
}
void refresh_score() {
	score++;
	random = rand() % 20 + 1;
	mushroom = rand() % 100 + 1;
}
void pushed_key() {
	//Monitorizacion de keys
	if (_kbhit()) {
		key = _getch();
		switch (key) {
		case KEY_A:
			if (pos > 0)
				pos--;
			break;

		case KEY_D:
			if (pos < width)
				pos++;
			break;

		case ESC:
			exit(EXIT_SUCCESS);
			break;
		case KEY_J:
			if (flag_bullet < MAX_NUM_BULLETS) {
				flag_bullet++;
				bullets_pos_left.push_back(pos - 1);

			}
			break;
		case KEY_K:
			if (flag_bullet < MAX_NUM_BULLETS) {
				flag_bullet++;
				bullets_pos_right.push_back(pos + 1);

			}
			break;
		}
	}
}
void create_map() {
	for (int i = 0; i < width; i++) {
		random_rain = rand() % 5;
		if (random_rain == 1) map[i] = KEY_RAIN;
		else				  map[i] = '_';
	}
	if (random_pos != -1)
		map[random_pos] = '@';
		map[pos] = 'X';
}
void move_enemies() {
	//Actualizacion de la posicion del enemigo izquierdo
	if (enemies_pos_left.size()) {
		for (int i = 0; i < enemies_pos_left.size(); i++) {
			map[enemies_pos_left.at(i)] = '#';
			enemies_pos_left[i]++;
		}
	}
	//Actualizacion de la posicion del enemigo derecho
	if (enemies_pos_right.size()) {
		for (int i = 0; i < enemies_pos_right.size(); i++) {
			map[enemies_pos_right.at(i)] = '#';
			enemies_pos_right[i]--;
		}
	}
}
void generate_enemies() {
	//Generacion de enemigo izquierdo
	if (random == 7 && flag_enemy <= 4) {
		enemies_pos_left.push_back(0);
		flag_enemy++;
		map[0] = '#';
	}
	//Generacion de enemigo derecho
	if (random == 13 && !flag_enemy) {
		enemies_pos_right.push_back(width - 1);
		flag_enemy++;
		map[width - 1] = '#';
	}
}
void move_bullets() {
	if (bullets_pos_left.size()) {
		//Movimiento de la balas izda
		for (int i = 0; i < bullets_pos_left.size(); i++) {
			map[bullets_pos_left.at(i)] = '<';
			bullets_pos_left[i]--;
		}
		//Eliminación balas izda fuera del mapa
		if (bullets_pos_left.at(0) < 0) {
			bullets_pos_left.erase(bullets_pos_left.begin());
			flag_bullet--;
		}
	}
	if (bullets_pos_right.size()) {
		//Movimiento de la balas dcha
		for (int i = 0; i < bullets_pos_right.size(); i++) {
			map[bullets_pos_right.at(i)] = '>';
			bullets_pos_right[i]++;
		}
		//Eliminación balas dcha fuera del mapa
		if (bullets_pos_right.at(0) >= width) {
			bullets_pos_right.erase(bullets_pos_right.begin());
			flag_bullet--;
		}
	}
}
void collisions() {
	//Colision con el enemigo izdo
	if (enemies_pos_left.size()) {
		if (enemies_pos_left.at(0) == pos) {
			life--;
			restart();
			Sleep(3000);
		}
		else if (bullets_pos_left.size()) {
			if (enemies_pos_left.at(0) == bullets_pos_left.at(0) || enemies_pos_left.at(0) == bullets_pos_left.at(0) - 1) {
				bullets_pos_left.erase(bullets_pos_left.begin());
				enemies_pos_left.erase(enemies_pos_left.begin());
				flag_bullet--;
				flag_enemy--;
				score += 100;
			}
		}
	}
	//Colision con el enemigo dcha
	if (enemies_pos_right.size()) {
		if (enemies_pos_right.at(0) == pos) {
			life--;
			restart();
			Sleep(3000);
		}
		else if (bullets_pos_right.size()) {
			if (enemies_pos_right.at(0) == bullets_pos_right.at(0) || enemies_pos_right.at(0) == bullets_pos_right.at(0) + 1) {
				bullets_pos_right.erase(bullets_pos_right.begin());
				enemies_pos_right.erase(enemies_pos_right.begin());
				flag_bullet--;
				flag_enemy--;
				score += 100;
			}
		}
	}
}
void get_mushroom() {
	//Cogida del mushroom
	if (pos == random_pos) {
		score += 1000;
		random_pos = -1;
	}
}
void generate_mushroom() {
	//Generacion mushroom
	if (mushroom == 42 && random_pos == -1) {
		random_pos = rand() % width;

	}
}
void draw_map() {
	//Imprimir el codigo por pantalla
	for (int i = 0; i < width; i++) {
		cout << map[i];
	}
	cout << level << " || Score: " << score << " || Vidas restantes: ";
	cout << life << "\r";
}
void refresh_level() {
	//Niveles
	if (counter < 0xFFFFFFFF)
		counter++;
	if (counter < 100) {
		level = "Nivel 1";
		Sleep(80);
	}
	else if (counter < 250) {
		level = "Nivel 2";
		Sleep(60);
	}
	else if (counter < 450) {
		level = "Nivel 3";
		Sleep(35);
	}
	else if (counter < 700) {
		level = "Nivel 4";
		Sleep(20);
	}
	else if (counter < 1050) {
		level = "Nivel 5";
		Sleep(17);
	}
	else {
		level = "Nivel 6";
		Sleep(13);
	}
}
void restart() {
	//Posiciones
	pos = width / 2;
	bullets_pos_left.clear();
	bullets_pos_right.clear();
	enemies_pos_left.clear();
	enemies_pos_right.clear();
	random_pos = -1;

	//Flags
	flag_bullet = 0;
	flag_enemy = 0;
	flag_dead = 0;
	flag_mushroom = 0;
	counter = 0;
	if (!life) {
		cout << "Eres un manco" << endl;
		system("PAUSE");
		level = "Nivel 1";
		life = 3;      
		score = 0;
	}
}

