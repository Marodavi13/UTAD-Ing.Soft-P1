#include "Base.h"
#include "myBullets.h"

CBullets::~CBullets() {}
CBullets::CBullets(const char &side, const int &pos) {
	m_side = side;
	m_pos = pos;
}
int CBullets::getPos() {
	return m_pos;
}
char CBullets::getSide() {
	return m_side;
}

void CBullets::move() {
	switch (m_side) {
	case 'i':  m_pos--;  break;
	case 'd':  m_pos++;  break;
	default:   break;
	}
}