#ifndef __PILLAR_H__
#define __PILLAR_H__
class Pillar
{
public:
	Pillar(void);
	~Pillar(void);
	void SetX(float x);
	int GetX();
	void SetBY(float y);
	int GetBY();
public:
	float m_x;
	float m_blanky;
};

#endif

