// Practica1.cpp : Defines the entry point for the console application.
//
#include "Base.h"
#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 
#include <vector>
#include <string>
#include "myBullets.h"
#include "myEnemies.h"
#include "myMap.h"
#include "myMushrooms.h"
#include "myPlayer.h"
#include "myRain.h"

using namespace std;
COORD                      resultx,resulty;
//Flags
int flag_bullet		= 0;
int flag_enemy		= 0;
int flag_dead		= 0;
int flag_mushroom   = 0;

//Otros
char key;
unsigned int random_rain;
unsigned int random;

//Vectores de posiciones
std::vector <CBullets> bullets_left, bullets_right;
std::vector <CEnemies> enemies_left, enemies_right;

//Objetos
CPlayer	  player1;
CMap	  map(width);
CMushroom mushroom;
CRain     rain(width);

int main()
{
	cout << wherex() << wherey() << endl;
	cout  <<"\n \n \n \n \n \n" << endl;
	while (1) {
		refresh_score(); 
		pushed_key();
		if (player1.getPos() >= 0 && player1.getPos() < width) {
			create_map();
			generate_mushroom();
			map.setTile(mushroom.getPos(), '@');
			move_enemies();
			generate_enemies();
			move_bullets();
			collisions();
			get_mushroom();
			map.draw();
			refresh_level();
		}
		else {
			cout << "Error" << endl;
			system("PAUSE");
		}
	}
    return 0;
}
void refresh_score() {
	map.addScore(1);
	map.addCounter();
	random = rand() % 20 + 1;
}
void pushed_key() {
	//Monitorizacion de keys
	if (_kbhit()) {
		key = _getch();
		switch (key) {
		case KEY_LEFT:        if (player1.getPos() > 0)      player1.moveLeft();  break;
			
		case KEY_RIGHT:       if (player1.getPos() < width)  player1.moveRight(); break;
	
		case ESC:			  exit(EXIT_SUCCESS);								  break;
			
		case KEY_SHOOT_LEFT:
			if (flag_bullet < MAX_NUM_BULLETS) {
				flag_bullet++;
				CBullets bullet('i', player1.getPos() - 1);
				bullets_left.push_back(bullet);
			}
			break;
		case KEY_SHOOT_RIGHT:
			if (flag_bullet < MAX_NUM_BULLETS) {
				flag_bullet++;
				CBullets bullet('d', player1.getPos() + 1);
				bullets_right.push_back(bullet);

			}
			break;
		}
	}
}
void create_map() {
	map.resetMap();
	rain.updateRain(width);
	map.setMap(rain.getRain(),width);
	map.setTile(player1.getPos(), 'X');
}

//meto lluvia
void generate_mushroom() {
	//Generacion mushroom
	int random1 = rand() % 100 + 1;
	if (random1 == 42 && mushroom.getPos() == -1) {
		mushroom.setPos();
	}
}
void move_enemies() {
	//Actualizacion de la posicion del enemigo izquierdo
	if (enemies_left.size()) {
		for (int i = 0; i < enemies_left.size(); i++) {
			map.setTile(enemies_left.at(i).getPos(), '#');
			enemies_left.at(i).move();
		}
	}
	//Actualizacion de la posicion del enemigo derecho
	if (enemies_right.size()) {
		for (int i = 0; i < enemies_right.size(); i++) {
			map.setTile(enemies_right.at(i).getPos(), '#');
			enemies_right.at(i).move();
		}
	}
}
void generate_enemies() {
	//Generacion de enemigo 
	if (random == 7 && flag_enemy <= 4) {
		CEnemies enemy('i');
		enemies_left.push_back(enemy);
		flag_enemy++;
		map.setTile(0,'#');
	}
	if (random == 13 && flag_enemy <= 4) {
		CEnemies enemy('d');
		enemies_right.push_back(enemy);
		flag_enemy++;
		map.setTile(width-1, '#');
	}
}
void move_bullets() {
	if (bullets_left.size()) {
		//Movimiento de la balas izda
		for (int i = 0; i < bullets_left.size(); i++) {
			map.setTile(bullets_left.at(i).getPos(),'<');
			bullets_left.at(i).move();
		}
		//Eliminación balas izda fuera del mapa
		if (bullets_left.at(0).getPos() < 0) {
			bullets_left.erase(bullets_left.begin());
			flag_bullet--;
		}
	}
	if (bullets_right.size()) {
		//Movimiento de la balas dcha
		for (int i = 0; i < bullets_right.size(); i++) {
			map.setTile(bullets_right.at(i).getPos(), '>');
			bullets_right.at(i).move();
		}
		//Eliminación balas dcha fuera del mapa
		if (bullets_right.at(0).getPos() >= width) {
			bullets_right.erase(bullets_right.begin());
			flag_bullet--;
		}
	}
}
void collisions() {
	//Colision con el enemigo izdo
	if (enemies_left.size()) {
		if (enemies_left.at(0).getPos() >= player1.getPos()) {
			map.removeLives();
			restart();
			Sleep(3000);
		}
		else if (bullets_left.size()) {
			if (enemies_left.at(0).getPos() >= bullets_left.at(0).getPos()) {
				bullets_left.erase(bullets_left.begin());
				enemies_left.erase(enemies_left.begin());
				flag_bullet--;
				flag_enemy--;
				map.addScore(100);
			}
		}
	}
	//Colision con el enemigo dcha
	if (enemies_right.size()) {
		if (enemies_right.at(0).getPos() <= player1.getPos()) {
			map.removeLives();
			restart();
			Sleep(3000);
		}
		else if (bullets_right.size()) {
			if (enemies_right.at(0).getPos() <= bullets_right.at(0).getPos()) {
				bullets_right.erase(bullets_right.begin());
				enemies_right.erase(enemies_right.begin());
				flag_bullet--;
				flag_enemy--;
				map.addScore(100);
			}
		}
	}
}
void get_mushroom() {
	//Cogida del mushroom
	if (player1.getPos() == mushroom.getPos()) {
		map.addScore(1000);
		mushroom.resetPos();
	}
}
void refresh_level() {
	if (map.getCounter() < 100) {
		map.setLevel("Nivel 1");
		Sleep(80);
	}
	else if (map.getCounter() < 250) {
		map.setLevel("Nivel 2");
		Sleep(60);
	}
	else if (map.getCounter() < 450) {
		map.setLevel("Nivel 3");
		Sleep(35);
	}
	else if (map.getCounter() < 700) {
		map.setLevel("Nivel 4");
		Sleep(20);
	}
	else if (map.getCounter() < 1050) {
		map.setLevel("Nivel 5");
		Sleep(17);
	}
	else {
		map.setLevel("Nivel 6");
		Sleep(13);
	}
}
void restart() {
	//Posiciones
	player1.resetPos();
	bullets_left.clear();
	bullets_right.clear();
	enemies_left.clear();
	enemies_right.clear();
	mushroom.resetPos();

	//Flags
	flag_bullet = 0;
	flag_enemy = 0;
	flag_dead = 0;
	flag_mushroom = 0;
	map.resetCounter();
	if (!map.getLives()) {
		cout << "Eres un manco" << endl;
		system("PAUSE");
		map.setLevel("Nivel 1");
		map.resetLives();
		map.resetScore();
	}
}
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return resultx.X;
}
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return resulty.Y;
}