#include "Base.h"
#include "myPlayer.h"

CPlayer::CPlayer() {
	m_pos = INITIAL_POS;
}
CPlayer::~CPlayer() {}

int CPlayer::getPos() {
	return m_pos;
}
void CPlayer::resetPos() {
	m_pos = INITIAL_POS;
}

void CPlayer::moveLeft() {
	m_pos--;
}
void CPlayer::moveRight() {
	m_pos++;
}


