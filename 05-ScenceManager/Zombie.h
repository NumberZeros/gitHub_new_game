#pragma once
#include "GameObject.h"
class CZombie : public CGameObject
{

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool isFire = false;
public:
	int id;
	void SetID(int _id) { id = _id; };
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CZombie();
	virtual void SetState(int state);
	void die();
	bool Checkcam();
};

