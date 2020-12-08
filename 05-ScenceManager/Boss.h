#pragma once
#include "GameObject.h"
#include "Simon.h"

class Boss : public CGameObject
{
public:
	bool isDie = false;
	int height;
	int width;
	bool isAttack;
	int boss_HP = 3;
	int getBoss_hp() { return boss_HP; }
	int bossZone;
	bool isImmortal = false;
	DWORD timeImmortal;
public:

	bool getisDie() { return isDie; }
	void setisDie(bool _isDie) { isDie = _isDie; }
	bool getisAttack() { return isAttack; }
	void setisAttack(bool _isAttack) { isAttack = _isAttack; }
	bool getisImmortal() { return isImmortal; }
	void setisImmortal(bool _isImmortal) { isImmortal = _isImmortal; }
	int getHeight() { return height; }
	void setHeight(int _height) { height = _height; }
	int getWidth() { return width; }
	void setWidth(int _width) { width = _width; }
	int getboss_HP() { return boss_HP; }
	void setboss_HP(int _boss_HP) { boss_HP = _boss_HP; }
	int getbossZone() { return bossZone; }
	void setbossZone(int _bossZone) { bossZone = _bossZone; }

	Boss();
	Boss(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Update(CSimon* simon, DWORD dt);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	void SetState(int state);
	void FlowSimon(float x,float y, DWORD dt);
	void die();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};