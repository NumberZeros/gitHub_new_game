#pragma once
#include "GameObject.h"
class CZombie : public CGameObject
{
public:
	int id;
	bool isFire = false;
	float min, max;
	int zombie_item;
public:
	//get n set
	float getmin() { return min; }
	void setmin(float _min) { min = _min; }
	float getmax() { return max; }
	void setmax(float _max) { max = _max; }
	int getid() { return id; }
	void setid(int _id) { id = _id; }
	int getzombie_item() { return zombie_item; }
	void setzombie_item(int _zombie_item) { zombie_item = _zombie_item; }
	bool getisFire() { return isFire; }
	void setisFire(bool _isFire) { isFire = _isFire; }
	//end get n set
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void SetID(int _id) { id = _id; };
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CZombie();
	virtual void SetState(int state);
	void die();
	bool Checkcam();
};

