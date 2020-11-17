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
	untouchable_start = 0;
	untouchable = 0;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	//HealthBar* hb = new HealthBar();
	// Simple fall down
	vy += SIMON_GRAVITY * dt;
	//hb->UpdateHP(this->simon_HP);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_ANI_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		
	}

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


		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back simon if collides with a moving objects, what if simon is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;


		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		//for (UINT i = 0; i < coObjects->size(); i++)
		//{
		//	LPGAMEOBJECT obj = coObjects->at(i);
		//}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CItem*>(e->obj)) {
				CItem* item = dynamic_cast<CItem*>(e->obj);
				if (item->isTorch || item->isFire|| item->isCandle) {
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
				else {
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
			else if (dynamic_cast<CZombie*>(e->obj)) {
				CZombie* zb = dynamic_cast<CZombie*>(e->obj);
					if (e->nx > 0 || e->nx <0) {
						simon_HP -= 1;
						DebugOut(L"co va cham x ne");
					}
					if (e->ny > 0 || e->ny < 0) {
						simon_HP -= 1;
					}
			}
			else if (dynamic_cast<CBlackLeopard*>(e->obj)) {
				CBlackLeopard* bl = dynamic_cast<CBlackLeopard*>(e->obj);
				if (e->nx > 0 || e->nx < 0) {
					simon_HP -= 1;
					DebugOut(L"co va cham x ne");
				}
				if (e->ny > 0 || e->ny < 0) {
					simon_HP -= 1;
				}
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
	if (state == SIMON_ANI_DIE)
		ani = SIMON_ANI_DIE;
	else {
		/// di chuyen 
		if (state == SIMON_STATE_IDLE) {
			if (isSit && vx == 0)
				ani = SIMON_ANI_SIT_DOWN;
			else
				ani = SIMON_ANI_IDLE;
		}

		else
			ani = SIMON_ANI_WALKING;

		///tan cong
		if (isAttack) {
			if (isSit && vx == 0)
				ani = SIMON_ANI_SIT_HIT;
			else
				ani = SIMON_ANI_STAND_HIT;
		}
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
	case SIMON_ANI_DIE:
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

