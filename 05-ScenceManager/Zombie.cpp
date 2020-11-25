#include "PlayScence.h"
#include "Zombie.h"

CZombie::CZombie()
{
	isHidden = false;
	SetState(ZOMBIE_WALKING);
	height = ZOMBIE_BBOX_HEIGHT;
	width = ZOMBIE_BBOX_WIDTH;
}

void CZombie::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += ZOMBIE_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (isHidden)
	{
		if (GetTickCount() - action_time >= 500)
			ResetBB();
	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0, rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += dx;
		y += min_ty * dy + ny * 0.1f;

		if (vx < 0 && x < 0) {
			x = 0; vx = -vx;
			this->nx = 1;
		}

		if (vx > 0 && x > SCREEN_WIDTH - 30) {
			x = SCREEN_WIDTH; vx = -vx;
			this->nx = -1;
		}

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
						die();
				}
			}
			if (dynamic_cast<CAxe*>(obj))
			{
				CAxe* e = dynamic_cast<CAxe*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);
				if (CheckColli(left, top, right, bottom))
					die();
			}
			if (dynamic_cast<CSimon*>(obj)) {
				CSimon* simon = dynamic_cast<CSimon*>(obj);
				float left, top, right, bottom;
				obj->GetBoundingBox(left, top, right, bottom);
				if (!isHidden && !simon->isImmortal) {		/// khi ma chua chuyen thanh lua va simon chua tung va cham voi quai nao
					if (CheckColli(left, top, right, bottom))
					{
						simon->SetState(SIMON_STATE_HURT);
						/*if (vx < 0)
							simon->vx = -SIMON_HURT_SPEED;
						else
							simon->vx = SIMON_HURT_SPEED;*/
					}
				}
			}
		}
	}
}

void CZombie::Render()
{
	animation_set->at(this->state)->Render(nx, x, y);
	RenderBoundingBox();
}


void CZombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOMBIE_WALKING:
		DebugOut(L"nx %d \n", nx);
		if (nx > 0)
			vx = ZOMBIE_WALKING_SPEED_X;
		else
			vx = -ZOMBIE_WALKING_SPEED_X;
		DebugOut(L"vx %f \n", vx);
		break;
	case ZOMBIE_DEAD:
		vx = 0;
	}
}
void CZombie::die()
{
	isHidden = true;
	action_time = GetTickCount();
	this->state = ZOMBIE_DEAD;
	vx = 0;

}
bool CZombie::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CZombie::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}
