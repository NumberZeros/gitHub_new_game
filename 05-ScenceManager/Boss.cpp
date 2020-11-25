#include "PlayScence.h"

Boss::Boss()
{
	height = BOX_HEIGTH;
	width = BOX_WIDTH;
	SetState(BOX_SLEEP);
	vx = vy = SPEED_BOX;
}

Boss::Boss(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CSimon*>(obj))
		{
			CSimon* e = dynamic_cast<CSimon*>(obj);

			float left, top, right, bottom;
			e->GetBoundingBox(left, top, right, bottom);
			if (CheckColli(left, top, right, bottom))
			{
				isDone = false;
				x += dx;
				y += dy;
				if (!e->isImmortal) 
					e->SetState(SIMON_STATE_HURT);
			}
		}
		if (dynamic_cast<CBrick*>(obj))
		{
			vx = 0;
			vy = 0;
		}
	}
}

void Boss::Update(CSimon* simon, DWORD dt)
{
	//DebugOut(L"time %d \n", GetTickCount() - action_time);
	if (GetTickCount() - action_time > 6000) {
		action_time = GetTickCount();
		isDone = true;
	}
	else if (GetTickCount() - action_time > 3000) {
		/*vx = vy = SPEED_BOX;
		FlowSimon(simon->x, simon->y, dt);*/
		if (isDone)
		{
			vx = vy = BOX_RUN_FLOW_SIMON;
			FlowSimon(simon->x, simon->y, dt);
		}

	}
	else if (GetTickCount() - action_time > 0)
	{
		vx = vy = SPEED_BOX;
		FlowSimon(simon->x, simon->y, dt);
		/*if (isDone)
		{
			vx = vy = BOX_RUN_FLOW_SIMON;
			FlowSimon(simon->x, simon->y, dt);
		}*/
	}
	
	 

	/// <summary>
	/// truong hop ngoai vung camera
	/// </summary>

}

bool Boss::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	Boss::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}

void Boss::Render()
{
	animation_set->at(state)->Render(nx, x, y, 255);

	RenderBoundingBox();
}

void Boss::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
		case BOX_ATTACK:
			isAttack = true;
			action_time = GetTickCount();
			isDone = true;
			break;
		case BOX_DIE:
			isAttack = false;
			action_time = GetTickCount();
			isDie = true;
			break;
		default:
			isAttack = false;
			action_time = 0;
			break;
	}
}

void Boss::FlowSimon(float simonX, float simonY, DWORD dt)
{
	if (x != simonX) {
		if (x > simonX)
			x -= dx;
		else
			x += dx;
	}
	if (y != simonY) {
		if (y > simonY)
			y -= dy;
		else
			y += dy;
	}
	
}

void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = left + width;
	top = y;
	bottom = y + height;

}
