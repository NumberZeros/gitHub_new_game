//#include "PlayScence.h"
//
//class CBlackLeopard : public CGameObject
//{
//	bool isHidden = false;
//	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
//	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
//	virtual void Render();
//	void die();
//	DWORD action_time;
//public:
//	float distance;
//	CBlackLeopard();
//	virtual void SetState(int state);
//	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
//};



#pragma once
#include "GameObject.h"
#include "Simon.h"

class CBlackLeopard : public CGameObject
{

public:
	bool isDie = false;
	int height;
	int width;
	bool isAttack;
public:

	CBlackLeopard();
	CBlackLeopard(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Update(CSimon* simon, DWORD dt);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	void SetState(int state);
	void die();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};