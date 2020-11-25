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
#define ITEM_ANI_CANDLE										19
#define ITEM_ANI_KNIFE										21
#define ITEM_ANI_EFFECTFIRE											20
#define ITEM_ANI_MEAT										11
#define ITEM_ANI_SMALLHEART											12
#define ITEM_ANI_BLUEMONEY									13
#define ITEM_ANI_REDMONEY											14
#define ITEM_ANI_WHITEMONEY									15
#define ITEM_ANI_HOLYWATER											22


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

#define ITEM_CANDLE_BBOX_WIDTH								16
#define ITEM_CANDLE_BBOX_HEIGHT										32

#define ITEM_HOLYWATER_BBOX_WIDTH							32
#define ITEM_HOLYWATER_BBOX_HEIGHT									30

#define ITEM_MEAT_BBOX_WIDTH								32
#define ITEM_MEAT_BBOX_HEIGHT										26

#define	ITEM_SMALLHEART_BBOX_WIDTH							16
#define	ITEM_SMALLHEART_BBOX_HEIGHT									16

#define ITEM_WHITEMONEY_BBOX_WIDTH							30
#define ITEM_WHITEMONEY_BBOX_HEIGHT									30

#define ITEM_BLUEMONEY_BBOX_WIDTH							30
#define ITEM_BLUEMONEY_BBOX_HEIGHT									30

#define ITEM_REDMONEY_BBOX_WIDTH							30
#define ITEM_REDMONEY_BBOX_HEIGHT									30

#define	ITEM_SPEED_Y										0.2f

class CItem : public CGameObject
{
public:
	int id;
	int state;
	bool isKnife = false;
	bool isRedMoney = false;
	bool isBlueMoney = false;
	bool isSmallHeart = false;
	bool isWhiteMoney = false;
	bool isTorch = false;
	bool isChain = false;
	bool isCandle = false;
	bool isHolyWater = false;
	bool isMeat = false;
	int secondGood;
public:

	CItem();
	~CItem();
	bool isFire = false;
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



