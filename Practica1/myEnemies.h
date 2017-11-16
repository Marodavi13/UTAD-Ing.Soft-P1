#pragma once

class CEnemies {
public:
	CEnemies(const char &side);
	~CEnemies();
	int getPos();
	char getSide();
	void move();
private:
	char m_side;
	int m_pos;
};