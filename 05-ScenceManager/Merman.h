#pragma once
#include "GameObject.h"
class CMerman: public CGameObject
{
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
	bool isGrounded = false;

public:
	void die();
	bool isHidden = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CMerman();
	virtual void SetState(int state);
};

