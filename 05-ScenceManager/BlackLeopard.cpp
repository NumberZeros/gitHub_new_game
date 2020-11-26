#include "BlackLeopard.h"
#include "GameObject.h"
#include "PlayScence.h"

CBlackLeopard::CBlackLeopard()
{
	SetState(BLACK_LEOPARD_JUMP);
	height = BLACK_LEOPARD_BBOX_HEIGHT;
	width = BLACK_LEOPARD_BBOX_WIDTH;
}

void CBlackLeopard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CBlackLeopard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += BLACK_LEOPARD_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (isHidden) {
		if (GetTickCount() - action_time >= 1500)
			ResetBB();
	}

	CalcPotentialCollisions(coObjects, coEvents);

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
				state = BLACK_LEOPARD_RUN;
			}

			else if (vx > 0 && x > 500) {
				x = 500; vx = -vx;
				this->nx = -1;
				state = BLACK_LEOPARD_RUN;
			}
		

		
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<CSimon*>(obj)) {
				CSimon* simon = dynamic_cast<CSimon*>(obj);
				float left, top, right, bottom;
				obj->GetBoundingBox(left, top, right, bottom);
				if (!isHidden && !simon->isImmortal) {		/// khi ma chua chuyen thanh lua va simon chua tung va cham voi quai nao
					if (CheckColli(left, top, right, bottom))
					{
						simon->SetState(SIMON_STATE_HURT);
					}
				}
			}
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
		}
	}


}

void CBlackLeopard::Render()
{
	animation_set->at(state)->Render(nx, x, y);
	RenderBoundingBox();
	
}

void CBlackLeopard::die()
{
	isHidden = true;
	action_time = GetTickCount();
	this->state = BLACK_LEOPARD_DESTROYED;
	height = BLACK_LEOPARD_BBOX_HEIGHT_DIE;
	vx = 0;
}

void CBlackLeopard::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BLACK_LEOPARD_RUN:
		if (nx > 0)
			vx = BLACK_LEOPARD_RUNNING_SPEED_X;
		else
			vx = -BLACK_LEOPARD_RUNNING_SPEED_X;
		break;
	case BLACK_LEOPARD_IDLE:
		vx = 0;
		nx = -1;
		break;
	case BLACK_LEOPARD_DESTROYED:
		vx = 0;
	case BLACK_LEOPARD_JUMP:
		vx = BLACK_LEOPARD_RUNNING_SPEED_X;
		vy = BLACK_LEOPARD_GRAVITY * BLACK_LEOPARD_RUNNING_SPEED_Y;
	}
}

bool CBlackLeopard::CheckColli(float left_a, float top_a, float right_a, float bottom_a)
{
	float l, t, r, b;
	CBlackLeopard::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}
