#pragma once
class CMushroom {
public:
	CMushroom();
	~CMushroom();
	int  getPos();
	void setPos();
	void resetPos();
private:
	int       m_pos   = -1;
	const int m_score = 1000 ;
};