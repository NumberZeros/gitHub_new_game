


#pragma once
#include "GameObject.h"

class CBlackLeopard : public CGameObject
{
public:

	CBlackLeopard();
	CBlackLeopard(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	void SetState(int state);
	void die();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};