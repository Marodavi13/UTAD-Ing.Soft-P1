#pragma once
class CMap {
public:
	CMap(const int &size);
	~CMap();
	void resetMap();
	void setMap(const char * table, const int &size);
	void setTile(const int &pos, const char &c);
	void draw();
	int getLives();
	void removeLives();
	void resetLives();
	void setLevel(char *level);
	char * getLevel();
	void addScore(const int &score);
	int getScore();
	void resetScore();
	int getCounter();
	void addCounter();
	void resetCounter();

private:
	char * m_map;
	char * m_level;
	unsigned int m_score;
	int m_lives;
	int m_counter;
 };