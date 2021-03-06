#include "Item.h"

CItem::CItem()
{
	id = 0;
	disappearStart = 0;
	nx = 1;
}

CItem::~CItem()
{
}

void CItem::StartDisappear()
{
	disappearStart = GetTickCount();
}

int CItem::GetAnimation()
{
	int ani;
	switch (this->id)
	{
	case 0: {
		ani = ITEM_ANI_ROI;
		break;
	}
	case 1: {
		ani = ITEM_ANI_TIM;
		break;
	}
	case 2: {
		ani = ITEM_ANI_HOLY_WATER;
		break;
	}
	default:
		ani = ITEM_ANI_MEAT;
		break;
	}
	return ani;
}
void CItem::Render()
{
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx, x, y, 255);
	RenderBoundingBox();
}
void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	r = x + width;
	t = y;
	b = y + height;

}
void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	vy += LARGE_HEART_GRAVITY * dt;
	vy += MEAT_GRAVITY * dt;
	vy += MONEY_BAG_GRAVITY * dt;
	vy += HOLY_WATER_GRAVITY * dt;
		CheckSize();

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;


			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// how to push back simon if collides with a moving objects, what if simon is pushed this way into another object?
			//if (rdx != 0 && rdx!=dx)
			//	x += nx*abs(rdx); 

			// block every object first!
			//if (this->state == 10)
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;


			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;
		}
}
void CItem::CheckSize()
{
	switch (this->id)
	{
	case 0: {
		this->height = HEIGHT_ID_ANI_0;
		this->width = WIDTH_ID_ANI_0;
		break;
	}
	case 1: {
		this->height = HEIGHT_ID_ANI_1;
		this->width = WIDTH_ID_ANI_1;
		break;
	}
	case 2: {
		height = HEIGHT_ID_ANI_2;
		width = WIDTH_ID_ANI_2;
		break;
	}
	default:
		height = HEIGHT_ID_ANI_3;
		width = WIDTH_ID_ANI_3;
		break;
	}
}

