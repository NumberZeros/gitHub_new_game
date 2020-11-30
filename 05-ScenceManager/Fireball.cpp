#include "Fireball.h"
#include <time.h>
#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "Simon.h"
#include "PlayScence.h"
CFB::CFB() {
	this->SetState(FB_STATE_HIDDEN);
	
	//x = -100;
	//y = -100;
	//isHidden = true;
	//level = 1;
}

void CFB::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	int distance = 0;
	//DebugOut(L"isHidden  %d\n", this->isHidden);
	//DebugOut(L"action_time UPDATE %d\n", this->action_time);
	//nếu đang hiện 
	if (!isHidden) {
		if (GetTickCount() - action_time > fb_atk_time || this->y > 400)
		{
			isHidden = true;
			this->action_time = 0;
			ResetBB();
			fb_isAtk = 0;
			DebugOut(L"axe_isatk: %d \f", GetTickCount() - action_time);
		}
		else
		{
			x += dx;
			distance += dx;
			if (distance > 420)
			{
				isHidden = true;
				this->action_time = 0;
				ResetBB();
				fb_isAtk = 0;
			}
		}
	}

	for (UINT i = 0; i < coObjects->size(); i++)
	{

		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CSimon*>(obj)) {
			CSimon* simon = dynamic_cast<CSimon*>(obj);
			float left, top, right, bottom;
			simon->GetBoundingBox(left, top, right, bottom);
			if (!isHidden && !simon->isImmortal) {		/// khi doi chua chuyen thanh lua va simon chua tung va cham voi quai nao
				if (CheckColli(left, top, right, bottom))
				{
					simon->SetState(SIMON_STATE_HURT);
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CFB::Attack(int _x, int _y, int _nx, int _atktime)
{
	this->x = _x;
	this->y = _y;
	this->nx = _nx;
	this->fb_atk_time = _atktime;
	SetState(FB_STATE_ATTACK);
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
		fb_isAtk = 1;
		break;
	case FB_STATE_HIDDEN:
		ani = GetAnimation();
		//ResetAnimation(ani);
		isHidden = true;
		fb_isAtk = 0;
		//speedy = FB_SPEED_Y;
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

}
bool CFB::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CFB::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}
