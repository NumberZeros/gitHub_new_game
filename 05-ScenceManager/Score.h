#pragma once
#include "GameObject.h"
#include"HealthBar.h"
#include"Number.h"
#include <string>
#include"Simon.h"

class Score : public CGameObject
{
public:
	int score;
	int mana;
	int point;
	int a[6];
	int m[2];
	int p[2];
	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
};

