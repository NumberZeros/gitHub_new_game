#pragma once
#include "GameObject.h"

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 16
#define MAX_SIMON_HP 16
#define MAX_BOSS_HP 16

class HealthBar : public CGameObject
{
public:
	int hp;
	int hplost;
	int hpboss;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
	int HealthBar::UpdateHP( int _hp);
	HealthBar();

};

