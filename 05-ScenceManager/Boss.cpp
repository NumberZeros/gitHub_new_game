#include "PlayScence.h"

Boss::Boss()
{
	height = BOX_WIDTH;
	width = BOX_HEIGTH;
	SetState(BOX_SLEEP);
	vx = vy = SPEED_BOX;
}

Boss::Boss(float _x, float _y)
{
	x = _x;
	y = _y;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);

}

void Boss::Update(CSimon* simon, DWORD dt)
{
	//DebugOut(L"time %d \n", GetTickCount() - action_time);
	if (GetTickCount() - action_time > 6000) {
		vx = vy = -BOX_RUN_FLOW_SIMON;
		FlowSimon(simon->x -50, simon->y -50, dt);
		action_time = GetTickCount();
	}
	else if (GetTickCount() - action_time > 4000) {
		//vx = vy = SPEED_BOX;
		vx = vy = BOX_RUN_FLOW_SIMON;
		FlowSimon(simon->x, simon->y, dt);
	}
	else if (GetTickCount() - action_time > 2000) {
		x = x;
		y = y;
	}
	else if (GetTickCount() - action_time > 0) {
		vx = vy = SPEED_BOX;
		FlowSimon(simon->x, simon->y, dt);
	}
	
	 

	/// <summary>
	/// truong hop ngoai vung camera
	/// </summary>
	if (y > 362) {
		vy = -SPEED_BOX;
	}

}

bool Boss::CheckColli(float left_a, float top_a, float right_a, float bottom_a)
{
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
