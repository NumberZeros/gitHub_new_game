#pragma once
#include "GameObject.h"

#define VAMPIREBAT_FLYING_SPEED_X								0.1f

#define VAMPIREBAT_GRAVITY												0.001f
#define VAMPIREBAT_DEAD											1
#define VAMPIREBAT_BBOX_WIDTH											32
#define VAMPIREBAT_BBOX_HEIGHT									32
#define VAMPIREBAT_FLYING												0
			

class CVampireBat : public CGameObject
{

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool isFire = false;
public:
	int id;
	float min, max;
	int ybat;
	bool getisFire() { return isFire; }
	void setisFire(bool _isFire) { isFire = _isFire; }
	int getID() { return id; }
	void SetID(int _id) { id = _id; };
	float getMin() { return min; }
	void setMin(float _min) { min = _min; }
	float getMax() { return max; }
	void setMax(float _max) { max = _max; }
	int getYbat() { return ybat; }
	void setYbat(float _ybat) { ybat = _ybat; }
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CVampireBat();
	virtual void SetState(int state);
	void die();
};



