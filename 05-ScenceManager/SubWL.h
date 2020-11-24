#pragma once
#include "GameObject.h"

class SubWL : public CGameObject
{
public:
	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	SubWL();
};

