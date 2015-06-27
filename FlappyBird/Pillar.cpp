#include "Pillar.h"


Pillar::Pillar(void)
{
}


Pillar::~Pillar(void)
{
}

void Pillar::SetX(float x){
	m_x = x;
}

void Pillar::SetBY(float y){
	m_blanky = y;
}

int Pillar::GetX(){
	return m_x;
}

int Pillar::GetBY(){
	return m_blanky;
}