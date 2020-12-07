#pragma once
#include "GameObject.h"
#include "Simon.h"

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 16


class HealthBar : public CGameObject
{
public:
	int hp;
	int hplost;
	int hpboss;
	int hpbossLost;
	int getHp() { return hp; }
	int getHplost(){ return hplost; }
	int getHpboss() { return hpboss; }
	int getHpbossLost() { return hpbossLost; }
	void setHP(int _hp) { hp = _hp; }
	void setHplost(int _hplost) { hplost = _hplost; }
	void setHpboss(int _hpboss) { hpboss = _hpboss; }
	void setHpbossLost(int _hpbossLost) { hpbossLost = _hpbossLost; }
	virtual void Update(CSimon*simon);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
	//int HealthBar::UpdateHP( int _hp);
	HealthBar();

};

