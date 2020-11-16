#include "VampireBat.h"
#include "PlayScence.h"

void CVampireBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
	vy = 1;
}
int vecty = 1;
void CVampireBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	DWORD now = GetTickCount();
	CGameObject::Update(dt, coObjects);
	//vy += VAMPIREBAT_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	x += VAMPIREBAT_FLYING_SPEED_X * dt * vx;
	y += VAMPIREBAT_FLYING_SPEED_Y * dt * vecty;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
		this->nx = 1;

	}
	if (vx > 0 && x > SCREEN_WIDTH - 30) {
		x = SCREEN_WIDTH; vx = -vx;
		this->nx = -1;
	}
	if (y < 100 || y > 200)
	{
		vecty = - vecty;
	}

	if (coEvents.size() == 0)
	{

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0, rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += dx;
		y += min_ty * dy + ny * 0.1f;

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CWeapon*>(obj))
			{
				CWeapon* e = dynamic_cast<CWeapon*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (e->frame == 2) {
					if (CheckColli(left, top, right, bottom))
					{
						this->isHidden = true;
						ResetBB();
					}
				}
			}
			if (dynamic_cast<CAxe*>(obj))
			{
				CAxe* e = dynamic_cast<CAxe*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);
				if (CheckColli(left, top, right, bottom))
				{
					this->isHidden = true;
					ResetBB();
				}

			}
		}
	}
}

void CVampireBat::Render()
{
	if (isHidden)
		return;
	int ani = VAMPIREBAT_ANI_FLYING;

	if (state == VAMPIREBAT_ANI_FLYING)
		ani = VAMPIREBAT_ANI_FLYING;
	else
		ani = VAMPIREBAT_ANI_FLYING;
	animation_set->at(ani)->Render(nx, x, y);
	RenderBoundingBox();
	height = VAMPIREBAT_BBOX_HEIGHT;
	width = VAMPIREBAT_BBOX_WIDTH;
}

CVampireBat::CVampireBat()
{
	SetState(VAMPIREBAT_FLYING);

}


void CVampireBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VAMPIREBAT_FLYING:
		DebugOut(L"nx %d \n", nx);
		if (nx > 0)
			vx = VAMPIREBAT_FLYING_SPEED_X;
		else
			vx = -VAMPIREBAT_FLYING_SPEED_X;
		DebugOut(L"vx %f \n", vx);
		break;
	}
}
bool CVampireBat::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CVampireBat::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}
