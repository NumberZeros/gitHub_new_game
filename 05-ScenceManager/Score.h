#pragma once
#include "GameObject.h"
#include"HealthBar.h"
#include"Number.h"
#include"Simon.h"

class Score : public CGameObject
{
public:
	DWORD action_time_score = GetTickCount();
	int a[6];
	int p[2];
	int m[2];
	int score, mana, point, stage = 1;
	int getScore() { return score; }
	int getMana() { return mana; }
	int getPoint() { return point; }
	int getStage() { return stage; }
	void setScore(int _score) { score = _score; }
	void setMana(int _mana) { mana = _mana; }
	void setPoint(int _point) { point = _point; }
	void setStage(int _stage) { stage = _stage; }
	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
};

