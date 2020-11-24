#pragma once
#include "GameObject.h"
class SubW : public CGameObject
{
public:
	int subw;
	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

