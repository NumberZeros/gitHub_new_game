#pragma once
#include "GameObject.h"
#define ZOMBIE_STATE_DIE			3	

class CZombie : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool isHidden = false;
	bool isFire = false;
	bool isZombie = false;
	int id;
public:
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CZombie();
	void SetID(int _id) { id = _id; };
	virtual void SetState(int state);
	
};

