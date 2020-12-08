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
#define ITEM_ANI_BRICK										23


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

#define ITEM_BRICK_BBOX_WIDTH								32
#define ITEM_BRICK_BBOX_HEIGHT										32

#define	ITEM_SPEED_Y										0.2f

class CItem : public CGameObject
{
public:
	int id;
	int state;
	bool isBrick = false;
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
	bool isFire = false;
	int secondGood;
public:
	///////////////
	//GET SET
	int getID() { return id; }
	void SetID(int _id) { id = _id; }
	int getState() { return state; }
	void SetState(int _state);
	int getSecondGood() { return secondGood; }
	void setSecondGood(int _secondgood) { secondGood = _secondgood; }
	bool getisBrick() { return isBrick; }
	void setisBrick(bool _isBrick) { isBrick = _isBrick; }
	bool getisKnife() { return isKnife; }
	void setisKnife(bool _isKnife) { isKnife = _isKnife; }
	bool getisRedMoney() { return isRedMoney; }
	void setisRedMoney(bool _isRedMoney) { isRedMoney = _isRedMoney; }
	bool getisBlueMoney() { return isBlueMoney; }
	void setisBlueMoney(bool _isBlueMoney) { isBlueMoney = _isBlueMoney; }
	bool getisSmallHeart() { return isSmallHeart; }
	void setisSmallHeart(bool _isSmallHeart) { isSmallHeart = _isSmallHeart; }
	bool getisWhiteMoney() { return isWhiteMoney; }
	void SetisWhiteMoney(bool _isWhiteMoney) { isWhiteMoney = _isWhiteMoney; }
	bool getisTorch() { return isTorch; }
	void setisTorch(bool _isTorch) { isTorch = _isTorch; }
	bool getisChain() { return isChain; }
	void setisChain(bool _isChain) { isChain = _isChain; }
	bool getisCandle() { return isCandle; }
	void setisCandle(bool _isCandle) { isCandle = _isCandle; }
	bool getisHolyWater() { return isHolyWater; }
	void setisHolyWater(bool _isHolyWater) { isHolyWater = _isHolyWater; }
	bool getisMeat() { return isMeat; }
	void setisMeat(bool _isMeat) { isMeat = _isMeat; }
	bool getisFire() { return isFire; }
	void setisFire(bool _isFire) { isFire = _isFire; }
    //GET SET
	///////////////
	CItem();
	~CItem();
	
	float speedy = ITEM_SPEED_Y;
	
	int GetAnimation();
	void CheckSize();
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};



