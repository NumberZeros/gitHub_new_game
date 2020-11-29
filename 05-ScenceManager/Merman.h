#pragma once
#include "Define.h"
#include "GameObject.h"
#include "Item.h"
#include "Axe.h"
class CMerman: public CGameObject
{
	CAxe* fb = new CAxe();
public:
	bool isHidden = false;
public:
	CItem* item = new CItem();
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CMerman();
	~CMerman();
	virtual void SetState(int state);
	void attack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void die();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

