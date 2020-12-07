#pragma once
#include "Define.h"
#include "GameObject.h"
#include "Item.h"
#include "Axe.h"
class CMerman : public CGameObject
{
	CAxe* fb = new CAxe();
public:
	bool isHidden = false;
	bool isAttack = false;
	float min, max;

public:
	CItem* item = new CItem();
	bool isJump = false;
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CMerman();
	~CMerman();
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void die();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

