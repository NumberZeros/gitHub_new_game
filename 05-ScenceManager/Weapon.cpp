#include "Weapon.h"
#include <time.h>
#include "PlayScence.h"
#include "Textures.h"
#include "Game.h"


CWeapon::CWeapon() {
	this->SetState(WEAPON_STATE_HIDDEN);
	x = -100;
	y = -100;
	isHidden = false;
	level = 1;
}

CWeapon::~CWeapon()
{
	this->SetState(WEAPON_STATE_HIDDEN);
	heigth = WEAPON_HEGTH_ANI_1;
	width = WEAPON_WIDHT_ANI_1;
	isHidden = false;
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (level == 3) {
		width = WEAPON_WIDHT_ANI_3;
	}
	else {
		width = WEAPON_WIDHT_ANI_1;
	}
	if (!isHidden) {
		if (GetTickCount() - action_time > SIMON_ATTACK_TIME) {
			isHidden = true;
			this->action_time = 0;
			ResetBB();
		}
	}
}

bool CWeapon::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CWeapon::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}

void CWeapon::Render()
{
	RenderBoundingBox();
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx,x, y, 255);
}
void CWeapon::ResetAnimation()
{
	for (int i = 0; i < animation_set->size(); i++) {
		animation_set->at(i)->ResetFrame();
	}
}

void CWeapon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x;
	right = x + width;
	top = y;
	bottom = y + height;
}

void CWeapon::SetState(int state)
{
	CGameObject::SetState(state);
	int ani;
	switch (state)
	{
	case WEAPON_STATE_ATTACK:
		ani = GetAnimation();
		animation_set->at(ani)->ResetFrame();
		frame = 3;
		this->action_time = GetTickCount();
		isHidden = false;
		break;
	case WEAPON_STATE_HIDDEN:
		isHidden = true;
		break;
	default:
		break;
	}
}

void CWeapon::CheckSize() {

}

CWeapon* CWeapon::__instance = NULL;
CWeapon* CWeapon::GetInstance()
{
	if (__instance == NULL) __instance = new CWeapon();
	return __instance;
}

int CWeapon::GetAnimation() {
	int ani;
		switch (level)
		{
		case 1: {
			ani = WEAPON_ANI_1;
			break;
		}
		case 2: {
			ani = WEAPON_ANI_2;
			break;
		}
		case 3: {
			ani = WEAPON_ANI_3;
			break;
		}
		default:
			ani = WEAPON_STATE_HIDDEN;
			break;
		}
	return ani;
}

void CWeapon::UpdatePosionWithSimon(float _x, float _y, int _nx) {
	//DebugOut(L"x update %f \n", _x);
	//DebugOut(L"y update %f \n", _y);
	nx = _nx;
	int ani = GetAnimation();
	int currenFrame = animation_set->at(ani)->GetCurrentFrame();
	if (nx > 0) {
		if (currenFrame != frame) {
			if (currenFrame == 0) {
				SetFrame(frame - 1);
				x = _x - 10;
				y = _y + 11.0f;
				frame = 0;
			}
			else if (currenFrame == 1) {
				x = _x - 10.0f;
				y = _y + 2;
				frame = 1;
			}
			else if(currenFrame == 2) {
				x = _x + 43;
				if (level == 3) {
					
					y = _y + 17;
				}
				else if (level == 2) {
					y = _y + 5;
				}
				else {
					y = _y + 8.0f;
				}
				frame = 2;
			}
		}
	}
	else {
		if (currenFrame != frame) {
			if (currenFrame == 0) {
				SetFrame(frame - 1);
				x = _x + 55;
				y = _y + 11;
				frame = 0;
			}
			else if (currenFrame == 1) {
				x = _x + 30 ;
				y = _y + 5;
				frame = 1;
			}
			else if (currenFrame == 2) {

				if (level == 3) {
					x = _x - 73;
					y = _y + 18;
				}
				else if (level == 2) {
					x = _x - 45;
					y = _y + 3;
				}
				else {
					x = _x - 45;
					y = _y + 10;
				}
				frame = 2;
			}
		}
	}
}

