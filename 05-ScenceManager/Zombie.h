#pragma once
#include "GameObject.h"
class CZombie : public CGameObject
{
public:
	int id;
	bool isFire = false;
	float min, max;
	
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetID(int _id) { id = _id; };
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CZombie();
	virtual void SetState(int state);
	void die();
	bool Checkcam();
};

