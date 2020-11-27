#include "Brick.h"
#include "Simon.h"
#include "Utils.h"
void CBrick::Render()
{
	animation_set->at(0)->Render(1,x, y);
	RenderBoundingBox();
	//type = 0;
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (type_brick != 0)
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
}
bool CBrick::CheckColli(float left_a, float top_a, float right_a, float bottom_a)
{
	float l, t, r, b;
	CBrick::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}