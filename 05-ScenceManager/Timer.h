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


	int time; 
	int timeremain = 300;
	bool isStop=false;
	int score=0;
	int getScore() { return score; }
	int getTimeremain() { return timeremain; }
	bool getIsStop() { return isStop; }
	void setTimeremain(int _timeremain) { timeremain = _timeremain; }
	void setIsStop(int _isStop) { isStop = _isStop; }
	int a, b, c;

	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
	//int HealthBar::UpdateHP( int _hp);
	//Timer();

};
