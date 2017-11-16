#include "Base.h"
#include "myMap.h"
#include <iostream>

using namespace std;


CMap::CMap(const int &width) {
	m_lives = INITIAL_LIVES;
	m_level = "Nivel 1";
	m_score = INITIAL_SCORE;
	m_counter = INITIAL_SCORE;
	m_map = new char [width];
	for (int i = 0; i < width; i++) {
		*(m_map+i) = '_';
	}
}
CMap::~CMap() {
	delete m_map;
}
void CMap::setMap(const char * table, const int &size) {
	for (int i = 0; i < size; i++) 	{
		m_map[i] = table[i];
	}

}
void CMap::resetMap() {
	for (int i = 0; i < width; i++) {
		m_map[i] = '_';
	}
}
void CMap::setTile(const int &pos, const char &c) {
	m_map[pos] = c;
}
int CMap::getLives() {
	return m_lives;
}

void CMap::removeLives() {
	m_lives--;
}
void CMap::setLevel(char *level) {
	m_level=level;
}
char * CMap::getLevel() {
	return m_level;
}
void CMap::addScore(const int &score) {
	m_score += score;
}
int CMap::getScore() {
	return m_score;
}
void CMap::resetScore() {
	m_score = INITIAL_SCORE;
}
int CMap::getCounter() {
	return m_counter;
}
void CMap::addCounter() {
	m_counter++;
}
void CMap::resetCounter() {
	m_counter = 0;
}
void CMap::resetLives() {
	m_lives = INITIAL_LIVES;
}
void CMap::draw() {
	//Imprimir el codigo por pantalla
	if (m_counter < 0xFF) m_counter++;
	for (int i = 0; i < width; i++) {
		cout << m_map[i];
	}
	cout << m_level << " || Score: " << m_score << " || Vidas restantes: ";
	cout << getLives() << "\r";
	}

	
