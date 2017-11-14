// Practica1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h> 

#define KEY_A 'a'
#define KEY_D 'd'
#define ESC 27
#define KEY_J 'j'
#define KEY_K 'k'
void restart();

using namespace std;
//Mapa
const int width = 60;
char map[width];


//Posiciones
int pos				 = width / 2;
int bullet_pos_left  = -1;
int bullet_pos_right = width;
int enemy_pos;

//Flags
int flag_bullet = 0;
int flag_enemy  = 0;
int flag_muerto = 0;
int flag_seta   = 0;
//Otros
char tecla;
int random			 = 0;
int seta			 = 0;
int random_pos       =-1;
unsigned int counter = 0;
char * level         = "Nivel 1";
int life			 = 3;
int score			 = 0;
int main()
{
	

	while (1) {
		score++;
		random = rand() % 30 + 1;
		seta = rand() % 100 + 1;
		//Monitorizacion de teclas
		if (_kbhit()) {
			tecla = _getch();
			switch (tecla) {
				case KEY_A:
					if (pos > 0) 
						pos--;
					break;

				case KEY_D:
					if (pos < width) 
						pos++;
					break;

				case ESC:
					return 0;
					break;

				case KEY_J:
					if (!flag_bullet) {
						flag_bullet = 1;
						bullet_pos_left = pos - 1;
					}
					break;

				case KEY_K:
					if (!flag_bullet) {
						flag_bullet = 1;
						bullet_pos_right = pos + 1;
					}
					break;
			}
		}
		
		// Genereacion y actualizacion del mapa
		if (pos >= 0 && pos < width) {
			for (int i = 0; i < width; i++) {
				map[i] = '_';
			}
			if (random_pos != -1)
				map[random_pos] = '@';
			map[pos] = 'X';

			//Actualizacion de la posicion del enemigo
			switch (flag_enemy) {
			case 1:
				enemy_pos++;
				map[enemy_pos] = '#';
				break;
			case 2:
				enemy_pos--;
				map[enemy_pos] = '#';
				break;
			default:
				break;
			}

			//Generecion de enemigo
			if (random == 2 && !flag_enemy) {
				enemy_pos = 0;
				flag_enemy = 1;
				map[enemy_pos] = '#';
			}

			if (random == 8 && !flag_enemy) {
				enemy_pos = width - 1;
				flag_enemy = 2;
				map[enemy_pos] = '#';
			}

			//Movimiento de la balas
			if (bullet_pos_left != -1) {
				map[bullet_pos_left] = '<';
				bullet_pos_left--;
			}

			if (bullet_pos_right != width) {
				map[bullet_pos_right] = '>';
				bullet_pos_right++;
			}

			//Reset del flag de bala
			if (bullet_pos_left < 0 && bullet_pos_right >= width) {
				flag_bullet = 0;
			}

			//Eliminacion de enemigo
			if (flag_bullet && flag_enemy) {
				if (enemy_pos == bullet_pos_left|| enemy_pos == bullet_pos_left-1 || enemy_pos == bullet_pos_right || enemy_pos == bullet_pos_right + 1) {
					enemy_pos = -1;
					bullet_pos_left = -1;
					bullet_pos_right = width;
					flag_bullet = 0;
					flag_enemy = 0;
					score += 100;
				}
			}

			//Te han dado!
			if (enemy_pos == pos) {
				life--;
				restart();
				Sleep(3000);	
			}
			if (pos == random_pos) {
				score += 1000;
				random_pos = -1;
			}
			if (seta == 42  && random_pos==-1) {
				random_pos = rand() % width;
				
			}
			//Imprimir el codigo por pantalla
			for (int i = 0; i < width; i++) {
				cout << map[i] ;
			}
			cout << level << " || Score: "<< score <<" || Vidas restantes: ";
			cout << life << "\r";
			
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
		


	}
    return 0;
}


void restart() {
	//Posiciones
	pos = width / 2;
	bullet_pos_left = -1;
	bullet_pos_right = width;
	enemy_pos= -1;
	random_pos = -1;

	//Flags
	flag_bullet = 0;
	flag_enemy = 0;
	flag_muerto = 0;
	flag_seta = 0;
	counter = 0;
	if (!life) {
		cout << "Eres un manco" << endl;
		system("PAUSE");
		level = "Nivel 1";
		life = 3;      
		score = 0;
	}
}

