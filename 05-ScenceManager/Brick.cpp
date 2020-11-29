#include "Brick.h"
#include "Simon.h"
#include "PlayScence.h"
CBrick::CBrick()
{
	height = BRICK_BBOX_HEIGHT;
	width = BRICK_BBOX_WIDTH;
}
void CBrick::Render()
{
	animation_set->at(0)->Render(1,x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	if (type != 0)
		height = width = BRICK_BOX_TYPE;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CSimon*>(obj))
		{
			CSimon* e = dynamic_cast<CSimon*>(obj);

			float left, top, right, bottom;
			e->GetBoundingBox(left, top, right, bottom);
			if (type != 0)
			{
				if (CheckColli(left, top, right, bottom))
				{
					e->simon_stair_type = type;

				}
			}

		}
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