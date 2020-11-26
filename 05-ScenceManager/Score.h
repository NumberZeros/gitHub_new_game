#pragma once
#include "GameObject.h"
#include"HealthBar.h"
#include"Number.h"
#include"Simon.h"

class Score : public CGameObject
{
public:
	int a[6];
	int p[2];
	int m[2];
	int score, mana, point, stage=1;
	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
};

