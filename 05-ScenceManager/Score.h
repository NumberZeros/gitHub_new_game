#pragma once
#include "GameObject.h"
#include"HealthBar.h"
#include"Number.h"
#include"Simon.h"

class Score : public CGameObject
{
public:
	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetX(float _x) { x = _x; }
};

