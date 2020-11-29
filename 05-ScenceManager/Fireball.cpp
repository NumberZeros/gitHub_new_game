#include "Fireball.h"
#include <time.h>
#include "Utils.h"
#include "Textures.h"
#include "Game.h"


CFB::CFB() {
	this->SetState(FB_STATE_HIDDEN);
	x = -100;
	y = -100;
	isHidden = false;
	level = 1;
}

void CFB::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//DebugOut(L"isHidden  %d\n", this->isHidden);
	//DebugOut(L"action_time UPDATE %d\n", this->action_time);
	//nếu đang hiện 
	if (!isHidden) {
		if (GetTickCount() - action_time > FB_ATTACK_TIME || this->y > 400)
		{
			isHidden = true;
			this->action_time = 0;
			ResetBB();
			axe_isAtk = 0;
			DebugOut(L"axe_isatk: %d \f", GetTickCount() - action_time);
		}
		else
		{
			x += dx;
			y -= speedy * dt;
			speedy -= 0.019;
		}
	}
}

void CFB::Attack(DWORD dt)
{

}

void CFB::Render()
{
	if (isHidden) return;
	//int ani = GetAnimation();
	animation_set->at(0)->Render(nx, x, y, 255);
	RenderBoundingBox();
}
void CFB::ResetAnimation(int ani)
{
	animation_set->at(ani)->ResetFrame();
}

void CFB::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + width;
	top = y;
	bottom = y + height;
}

void CFB::SetState(int state)
{
	CGameObject::SetState(state);
	int ani;
	switch (state)
	{
	case FB_STATE_ATTACK:
		ani = 0;
		if (nx > 0) vx = FB_SPEED_X;
		else vx = -FB_SPEED_X;
		frame = 3;
		this->action_time = GetTickCount();
		isHidden = false;
		axe_isAtk = 1;
		break;
	case FB_STATE_HIDDEN:
		ani = GetAnimation();
		//ResetAnimation(ani);
		isHidden = true;
		axe_isAtk = 0;
		speedy = FB_SPEED_Y;
		break;
	default:
		break;
	}
}

CFB* CFB::__instance = NULL;
CFB* CFB::GetInstance()
{
	if (__instance == NULL) __instance = new CFB();
	return __instance;
}

int CFB::GetAnimation() {
	int ani;
	switch (this->level)
	{
	case 1: {
		ani = FB_ANI;
		break;
	}
	default:
		ani = FB_STATE_HIDDEN;
		break;
	}
	return ani;
}

void CFB::UpdatePosionWithSimon(int _x, int _y, int _nx) {
	this->x = _x;
	this->y = _y;
	this->nx = _nx;

}

void CFB::GetPositionForSimon() {


}