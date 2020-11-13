#pragma once
#include "GameObject.h"

#define	ITEM_SPEED_Y		0.0001f

class CItem : public CGameObject
{
public:
	int id;
	int height = 1;
	int width = 1;
	int locationX = 1;
	int locationY = 1;
	bool isCandle = false;
	bool isTorch = false;
	bool isFire = false;
	bool isBluemoneybag = false;
	bool isMeat = false;
	bool isSmallHeart = false;
	bool isRoi = false;
	bool isBigHeart = false;
	bool isHolyWater = false;
public:

	CItem();
	~CItem();
	void SetID(int _id) { id = _id; };
	float speedy = ITEM_SPEED_Y;
	int GetAnimation();
	//void SetState(int state);
	void CheckSize();
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
