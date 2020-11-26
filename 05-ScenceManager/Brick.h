#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

#define BRICK_TYPE_ULR	111
#define BRICK_TYPE_URL	112
#define BRICK_TYPE_DLR	113
#define BRICK_TYPE_DRL	114

class CBrick : public CGameObject
{
public:
	int type = 0;
	int type_brick = 0;
	int brick_x = 0;
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);

};