#pragma once
#include "GameObject.h"


#define ITEM_STATE_HIDDEN 0
#define ITEM_STATE_SHOW	  1

#define ITEM_GRAVITY										0.0001f
#define ITEM_TIME_FIRE												300

#define ITEM_DISAPPEAR_TIME									5000
#define ITEM_ANI_CHAIN												0
#define ITEM_ANI_BIGHEART									1
#define ITEM_ANI_TORCH												18
#define ITEM_ANI_KNIFE										21
#define ITEM_ANI_EFFECTFIRE											20


#define ITEM_CHAIN_BBOX_WIDTH										32
#define ITEM_CHAIN_BBOX_HEIGHT								32

#define ITEM_BIGHEART_BBOX_WIDTH									24
#define ITEM_BIGHEART_BBOX_HEIGHT							20

#define ITEM_TORCH_BBOX_WIDTH								32
#define ITEM_TORCH_BBOX_HEIGHT										64

#define ITEM_KNIFE_BBOX_WIDTH								34
#define ITEM_KNIFE_BBOX_HEIGHT										18

#define ITEM_EFFECTFIRE_BBOX_WIDTH							32
#define ITEM_EFFECTFIRE_BBOX_HEIGHT									64

#define	ITEM_SPEED_Y										0.2f

class CItem : public CGameObject
{
public:
	int id;
	int state;
	bool isTorch = false;
	bool isFire = false;
	bool isChain = false;
	bool isBigHeart = false;
	bool isKnife = false;
	int secondGood;
public:

	CItem();
	~CItem();
	float speedy = ITEM_SPEED_Y;
	void SetID(int _id) { id = _id; };
	int GetAnimation();
	void CheckSize();
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};
