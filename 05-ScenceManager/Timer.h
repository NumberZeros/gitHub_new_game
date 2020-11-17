#pragma once
#include "GameObject.h"
#include "Simon.h"
#include <string>

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 16

#define ONE_SECOND	1000
class Timer : public CGameObject
{
public:
	DWORD action_time = GetTickCount();
	int yy = 0;
	int array_number[10] = { 0,1,2,3,4,5,6,7,8,9 };
	string num;
	int start, end;
	int time; 
	int timeremain = 400;
	int timemax=400;
	int a, b, c;
	void Start();
	void Stop();
	bool IsTimeUp();
	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
	//int HealthBar::UpdateHP( int _hp);
	Timer();

};
