#include "Base.h"
#include "myEnemies.h"
#include <Windows.h>
CEnemies::CEnemies(const char &side) {
	
	switch (side){
	case 'i':  m_side = 'i'; m_pos = 0;         break;
	case 'd':  m_side = 'd'; m_pos = width - 1; break;
	default:                                    break;
	}

}
CEnemies::~CEnemies() {}

int CEnemies::getPos() {
	return m_pos;
}

char CEnemies::getSide() {
	return m_side;
}

void CEnemies::move() {
	switch (m_side){
	case 'i': m_pos++; break;
	case 'd': m_pos--; break;
	default :          break;
	}
}
