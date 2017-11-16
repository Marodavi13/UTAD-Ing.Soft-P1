#include "myRain.h"
#include <Windows.h>
#include "Base.h"

int random2;
int random3;
CRain::CRain(const int &size) {
	m_tear = new char[180];

	for (int i = 0; i < size; i++) {
		random2 = rand() % 20;
		if (random2 == 15) m_tear[i] = RAIN_HI;
		else               m_tear[i] = NO_RAIN;
	}
}
CRain::~CRain() {
	delete m_tear;
}

char * CRain::getRain(){
	return m_tear;
}
void CRain::updateRain(const int &size) {
	for (int i = 0; i < size; i++) {
		switch (m_tear[i])
		{
		case RAIN_HI: m_tear[i] = RAIN_ME; break;
		case RAIN_ME: m_tear[i] = RAIN_LO; break;
		case RAIN_LO: m_tear[i] = NO_RAIN; break;
		case NO_RAIN: 
			          random3   = rand() % 40;
			          if (random3 == 27) m_tear[i] = RAIN_HI;
					  break; 
		default:                           break;
		}
	}
}

