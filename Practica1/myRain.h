#pragma once
#define RAIN_HI '|'
#define RAIN_ME '/'
#define RAIN_LO '-'
#define NO_RAIN '_'



class CRain {
public:
	CRain(const int &size);
	~CRain();
	void updateRain(const int &size);
	char * getRain();
private:
	char * m_tear;
	
};