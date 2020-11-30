
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
	if (boss_HP < 1 && !isDie)
		SetState(BOX_DIE);

	if (y <= 90)		////vi tri bien 
	{
		vy = SPEED_BOX;
		y+=dy;
		
	}
	if (x > 1200)		//// vi tri bien
		vx = -SPEED_BOX;

	if (isDie) {
		vx = vy = 0;
		boss_HP = 0;
		if (GetTickCount() - action_time > 1500)
			ResetBB();
	}

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
		else if (dynamic_cast<CBrick*>(obj))
		{
			CBrick* e = dynamic_cast<CBrick*>(obj);

			float left, top, right, bottom;
			e->GetBoundingBox(left, top, right, bottom);
			if (CheckColli(left, top, right, bottom))
			{
				vy = 0;
				vx = 0;
			}
		}
		if (dynamic_cast<CWeapon*>(obj))
		{
			CWeapon* e = dynamic_cast<CWeapon*>(obj);

			float left, top, right, bottom;
			obj->GetBoundingBox(left, top, right, bottom);

			if (e->frame == 2) {
				if (CheckColli(left, top, right, bottom))
					boss_HP -= 1;
			}
		}
		if (dynamic_cast<CAxe*>(obj))
		{
			CAxe* e = dynamic_cast<CAxe*>(obj);

			float left, top, right, bottom;
			obj->GetBoundingBox(left, top, right, bottom);
			if (CheckColli(left, top, right, bottom))
			{
				boss_HP -= 1;
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
				boss_HP -= 1;
				e->ResetBB();
			}
		}
	}
}

void Boss::Update(CSimon* simon, DWORD dt)
{
	if (GetTickCount() - action_time > 6000) {
		action_time = GetTickCount();
		isDone = true;
	}
	else if (GetTickCount() - action_time > 4000) {
		vx = vy = BOX_RUN_FLOW_SIMON;
		FlowSimon(simon->x -100, simon->y - 200, dt);
	}
	else if (GetTickCount() - action_time > 2000) {
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

void Boss::die()
{
	/*SetState(BOX_DIE);*/
	
}

void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = left + width;
	top = y;
	bottom = y + height;

}
