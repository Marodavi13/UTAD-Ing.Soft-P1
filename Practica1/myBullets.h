#pragma once

class CBullets {
public:
	~CBullets();
	CBullets(const char &side, const int &pos);
	int getPos();
	char getSide();
	void move();
private:
	char m_side;
	int m_pos;
};