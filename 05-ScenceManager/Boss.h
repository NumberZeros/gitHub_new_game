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
	int boss_HP = 16;
	int bossZone;
public:

	Boss();
	Boss(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Update(CSimon* simon, DWORD dt);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	void SetState(int state);
	void FlowSimon(float x,float y, DWORD dt);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};