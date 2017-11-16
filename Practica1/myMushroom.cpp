#include "Base.h"
#include "myMushrooms.h"
#include <Windows.h>
CMushroom::CMushroom() {
}
CMushroom::~CMushroom() {}

int CMushroom::getPos() {
	return m_pos;
}
void CMushroom::setPos() {
	m_pos = rand() % width;
}
void CMushroom::resetPos() {
	m_pos = -1;
}