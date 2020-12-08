#pragma once
#include "GameObject.h"
class SubW : public CGameObject
{
public:
	int subw;
	int getSubw() { return subw; }
	void setSubw(int _subw) { subw = _subw; }
	virtual void Update();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

