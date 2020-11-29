#pragma once
#include "PlayScence.h"
#include "GameObject.h"
class CMerman: public CGameObject
{
public:
	bool isAttack = false;
	//virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool isHidden = false;
	bool isGrounded = false;	
public:
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CMerman();
	virtual void SetState(int state);
	void attack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void die();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

