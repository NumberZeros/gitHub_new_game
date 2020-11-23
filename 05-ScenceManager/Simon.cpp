#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Simon.h"
#include "Game.h"
#include "PlayScence.h"
#include "Zombie.h"
#include "Goomba.h"
#include "Portal.h"
#include "BlackLeopard.h"
#include "HealthBar.h"
#include "Weapon.h"

CSimon::CSimon(float x, float y) : CGameObject()
{
	level = 1;
	SetState(SIMON_STATE_IDLE);
	nx = 1;
	isGrounded = true;
	height = SIMON_HEGHT;
	width = SIMON_WIDTH;
	this->start_x = x;
	this->start_y = y;
	this->x = x;
	this->y = y;
	simon_HP = 16;
	simon_Score = 000000;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += SIMON_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (simon_HP < 1)
		state = SIMON_STATE_DIE;
		

	if ((isImmortal && isDone == true) || isAttack || simon_HP < 1)
		dx = 0;
	//jump
	if (!isGrounded) {
		if (GetTickCount() - action_time > SIMON_RESET_JUMP_TIME) {
			action_time = 0;
			isGrounded = true;
		}
	}

	//attact
	if (isAttack) {
		if (GetTickCount() - action_time > SIMON_ATTACK_TIME) {
			isAttack = false;
			isDone = true;
			action_time = 0;
		}
	}

	//sit
	if (isSit) {
		if (vx != 0) {
			isSit = false;
			height += SIMON_HEGHT_RESET_SIT;
			y -= SIMON_HEGHT_RESET_SIT;
		}
	}

	if (isImmortal) {
		if (GetTickCount() - timeImmortal > 300) 
		{
			if(simon_HP > 1)
				SetState(SIMON_STATE_IDLE);
			isDone = true;
		}
		else 
			vx = -SIMON_HURT_SPEED;
			
		if (GetTickCount() - timeImmortal > 1000)
		{
			isImmortal = false;
			timeImmortal = 0;
		}
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		//hb->UpdateHP(simon_HP);
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;


		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CItem*>(e->obj)) {
				CItem* item = dynamic_cast<CItem*>(e->obj);
				if (item->isTorch || item->isFire || item->isCandle) {
					if (e->nx != 0)
						x += dx;
					if (!isGrounded) {
						if (ny < 0)
							y += dy;
						if (ny > 0) {
							vy = -SIMON_JUMP_SPEED_Y;
							y += dy;
						}
					}
				}
				else if (item->id == ITEM_ANI_CHAIN) {
					level += 1;
					item->isHidden = true;
					item->ResetBB();
				}
				else if (item->id == ITEM_ANI_HOLYWATER) {
					simon_HP = 16;
					item->isHidden = true;
					item->ResetBB();
				}
			} 
			else if (dynamic_cast<Gate*>(e->obj))
			{
				Gate* gate = dynamic_cast<Gate*>(e->obj);
				CGame* game = CGame::GetInstance();
				CGame::GetInstance()->SwitchScene(game->current_scene +1);

			}
			else if (dynamic_cast<CZombie*>(e->obj) || dynamic_cast<CBlackLeopard*>(e->obj)) {
				x += dx;
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

bool CSimon::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CSimon::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}

void CSimon::Render()
{
	int ani = -1;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else {
		/// di chuyen 
		if (state == SIMON_STATE_IDLE)
		{
			if (isSit && vx == 0)
				ani = SIMON_ANI_SIT_DOWN;
			else
				ani = SIMON_ANI_IDLE;
		} else
			ani = SIMON_ANI_WALKING;

		///tan cong
		if (isAttack) {
			if (isSit)
				ani = SIMON_ANI_SIT_HIT;
			else
				ani = SIMON_ANI_STAND_HIT;
		}
		if (isImmortal && isDone == false)
			ani = SIMON_ANI_HURT;

	}
	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(nx, x, y, alpha);

	RenderBoundingBox();
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING:
		if (nx > 0)
			vx = SIMON_WALKING_SPEED;
		else
			vx = -SIMON_WALKING_SPEED;
		break;
	case SIMON_STATE_JUMP:
		action_time = GetTickCount();
		isGrounded = false;
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_HIT:
		vx = 0;
		attack();
		break;
	case SIMON_STATE_SIT_DOWN:
		SitDown();
		break;
	case SIMON_STATE_HURT:
		if (simon_HP > 0) {
			isDone = false;
			simon_HP -= 1;
			isImmortal = true;
			timeImmortal = GetTickCount();
			vy = -SIMON_JUMP_SPEED_Y;
			vx = 0;
		}
		else {
			dx = 0;
			dy = 0;
			simon_HP = 0;
		}
		break;
	case SIMON_ANI_DIE:
		action_time = GetTickCount();
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
}

void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = left + width;
	top = y;
	bottom = y + height;

}

void CSimon::SitDown()
{
	if (!isSit) {
		vx = 0;
		isSit = true;
		height -= SIMON_HEGHT_RESET_SIT;
	}
}

void CSimon::attack()
{
	animation_set->at(SIMON_ANI_STAND_HIT)->ResetFrame();
	action_time = GetTickCount();
	isDone = false;
	isAttack = true;
}

void CSimon::ResetAnimation() {
	for (int i = 0; i < animation_set->size(); i++) {
		animation_set->at(i)->ResetFrame();
	}
}
void CSimon::Reset()
{
	SetState(SIMON_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

