#pragma once
class CPlayer {
public:
	CPlayer();
	~CPlayer();
	int getPos();
	void resetPos();
	void moveRight();
	void moveLeft();
private:
	int m_pos;
};