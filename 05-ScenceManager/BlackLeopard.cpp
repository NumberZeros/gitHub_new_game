
#include "PlayScence.h"
#include "BlackLeopard.h"
#include <time.h>


CBlackLeopard::CBlackLeopard()
{
	height = BLACK_LEOPARD_BBOX_HEIGHT;
	width = BLACK_LEOPARD_BBOX_WIDTH;
	SetState(BLACK_LEOPARD_IDLE);
	isHidden = false;
}

CBlackLeopard::CBlackLeopard(float _x, float _y)
{
	x = _x;
	y = _y;
}

void CBlackLeopard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += BLACK_LEOPARD_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (isHidden) {
		if (GetTickCount() - action_time >= 1500)
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

			else if (vx > 0 && x > SCREEN_WIDTH) {
				x = SCREEN_WIDTH; vx = -vx;
				this->nx = -1;
			}
			else if (ny == -1.0f)
			{
				vy = 0;
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
				obj->GetBoundingBox(left, top, right, bottom);

				if (e->frame == 2) {
					if (CheckColli(left, top, right, bottom))
						die();
				}
			}
			if (dynamic_cast<CAxe*>(obj))
			{
				CAxe* e = dynamic_cast<CAxe*>(obj);

				float left, top, right, bottom;
				obj->GetBoundingBox(left, top, right, bottom);

				if (CheckColli(left, top, right, bottom))
				{
					die();
					e->ResetBB();
				}
			}
			if (dynamic_cast<CKnife*>(obj))
			{
				CKnife* e = dynamic_cast<CKnife*>(obj);
				float left, top, right, bottom;
				obj->GetBoundingBox(left, top, right, bottom);
				if (CheckColli(left, top, right, bottom))
				{
					die();
					e->ResetBB();
				}
			}
		}
	}


}

bool CBlackLeopard::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CBlackLeopard::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}

void CBlackLeopard::Render()
{
	animation_set->at(this->state)->Render(nx, x, y);
	RenderBoundingBox();
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
	case BLACK_LEOPARD_JUMP:
		break;
	case BLACK_LEOPARD_DESTROYED:
		vx = 0;
		break;
	default:
		vx = 0;
		nx = -1;
		break;
	}
}

void CBlackLeopard::die()
{
	isHidden = true;
	action_time = GetTickCount();
	this->state = BLACK_LEOPARD_DESTROYED;
	vx = 0;
}



void CBlackLeopard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + width;
	top = y;
	bottom = y + height;

}

//void CBlackLeopard::die()
//{
//	isHidden = true;
//	action_time = GetTickCount();
//	this->state = BLACK_LEOPARD_DESTROYED;
//	height = BLACK_LEOPARD_BBOX_HEIGHT_DIE;
//	vx = 0;
//}