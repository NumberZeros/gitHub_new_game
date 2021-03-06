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
#include "Item.h"
#include "VampireBat.h"
#include "Merman.h"

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
	simon_Score = 1;
	simon_Mana = 15;
	simon_Sub = 2;
	simon_P = 0;
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

	//DebugOut(L"simon st type: %d \t", simon_stair_type);
	/*DebugOut(L"istdown: %d \t", isStairDown);
	DebugOut(L"istUP: %d \t", isStairUp);*/


	if (isAutoMove) {						// chuyen xy ly cho map intro
		state = SIMON_STATE_WALKING;
		vx = -0.05;
		x += vx*dt;
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (dynamic_cast<Gate*>(obj)) {
				Gate* gate = dynamic_cast<Gate*>(obj);
				float left, top, right, bottom;
				obj->GetBoundingBox(left, top, right, bottom);
				if (CheckColli(left, top, right, bottom))
				{
					CGame* game = CGame::GetInstance();
					CGame::GetInstance()->SwitchScene(game->current_scene + 1);
				}
			}
		}
	}


	if (simon_HP < 1)
		state = SIMON_STATE_DIE;
		

	if ((isImmortal && !isDone) || isAttack || simon_HP < 1)
	{
		dx = 0;
		if (simon_HP < 1)
			dy = 0;
	}
		
	//jump
	if (!isGrounded) {
		if (GetTickCount() - action_time > SIMON_RESET_JUMP_TIME) {
			action_time = 0;
			isGrounded = true;
		}
	}
	if (isStairUp)
	{
		vy = 0;
		x += 0.916f * nx;
		y -= 0.916f;
	}
	// 111: ULR, 112: URL, 113: DLR, 114: DRL
	if (!isStairUp && (simon_stair_type== BRICK_TYPE_ULR || simon_stair_type== BRICK_TYPE_URL))
	{
		if (isOnStair)
			SetState(SIMON_STATE_STAIR_UP_IDLE);
	}
	if (isStairDown)
	{
		vy = 0;
		x += 0.916f * nx;
		y += 0.916f;
	}
	if (!isStairDown && (simon_stair_type == BRICK_TYPE_DLR || simon_stair_type == BRICK_TYPE_DRL))
	{
		if (isOnStair)
			SetState(SIMON_STATE_STAIR_DOWN_IDLE);
	}
	//attact
	if (isAttack) {
		if (GetTickCount() - action_time > SIMON_ATTACK_TIME) {
			isAttack = false;
			isDoneAttack = true;
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
		if (GetTickCount() - timeImmortal > 500) 
			isDone = true;
		else 
			vx = -SIMON_HURT_SPEED;
			
		if (GetTickCount() - timeImmortal > 2000)
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
			CGame* game = CGame::GetInstance();
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
				if (item->id == ITEM_ANI_CHAIN) {
					level += 1;
					item->isHidden = true;
					item->ResetBB();
					if (level >= 3)
						level = 3;
				}
				if (item->id == ITEM_ANI_HOLYWATER) {
					simon_HP = 16;
					item->isHidden = true;
					item->ResetBB();
					simon_Sub = 3;
					number = 1;
					
				}
				if (item->id == ITEM_ANI_BIGHEART)
				{
					item->isHidden = true;
					item->ResetBB();
					number = 2;
					//simon_Mana += 5;
					isEndGame = true;
				}
				if (item->id == ITEM_ANI_MEAT)
				{
					item->isHidden = true;
					item->ResetBB();
					number = 3;
					simon_HP = 16;
				}
				if (item->id == ITEM_ANI_SMALLHEART)
				{
					item->isHidden = true;
					item->ResetBB();
					//simon_Mana += 1;
					
					number = 4;
				}
				if (item->id == ITEM_ANI_BLUEMONEY)
				{
					item->isHidden = true;
					item->ResetBB();
					simon_Score += 5;
					number = 5;
				}
				if (item->id == ITEM_ANI_REDMONEY)
				{
					item->isHidden = true;
					item->ResetBB();
					number = 6;
					simon_Score += 10;
				}
				if (item->id == ITEM_ANI_WHITEMONEY)
				{
					item->isHidden = true;
					item->ResetBB();
					number = 7;
					simon_Score += 15;
				}
				if (item->id == ITEM_ANI_KNIFE)
				{
					item->isHidden = true;
					item->ResetBB();
					number = 8;
					simon_Sub = 0;
				}

				GetNumber();
			} 
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (brick->type && brick->type != 0) {
					if (x > brick->x + 20 && x < brick->x + 23) {
						simon_stair_type = brick->type;
						lenghtStair = brick->lenghtStair;
					}
				}
				else
					ResetStair();
			}
			else if (dynamic_cast<CMerman*>(e->obj) || dynamic_cast<CZombie*>(e->obj) || dynamic_cast<CVampireBat*>(e->obj) || dynamic_cast<CBlackLeopard*>(e->obj)) {
				x += dx;
			}
			else if (dynamic_cast<Boss*>(e->obj)) 
			{
				Boss* item = dynamic_cast<Boss*>(e->obj);
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
					else
						dy = 0;

			}else if (dynamic_cast<Gate*>(e->obj))
			{
				Gate* gate = dynamic_cast<Gate*>(e->obj);
				CGame::GetInstance()->SwitchScene(game->current_scene + 1);
				simon_stage += 1;
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

void CSimon::AutoWalk(int des)
{
	//if (des - this->xbr != 0)
	//{
	//	if (des - this->xbr > 0)
	//	{
	//		nx = -1;
	//	}
	//	else if (des - this->xbr < 0)
	//	{
	//		nx = 1;
	//	}
	//	SetState(SIMON_STATE_WALKING);
	//}
	////else SetState(SIMON_STATE_IDLE);
}

void CSimon::Render()
{
	int ani = 0;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (isAttack) {
		if (isSit)
			ani = SIMON_ANI_SIT_HIT;
		else
			ani = SIMON_ANI_STAND_HIT;
	}
	else if (isStairUp)
		ani = SIMON_ANI_STAIR_UP;
	else if (isStairDown)
		ani = SIMON_ANI_STAIR_DOWN;
	else if (state == SIMON_STATE_STAIR_DOWN_IDLE)
		ani = SIMON_ANI_STAIR_DOWN_IDLE;
	else if (state == SIMON_STATE_STAIR_UP_IDLE)
		ani = SIMON_ANI_STAIR_UP_IDLE;
	else {
		// di chuyen 
		if (state == SIMON_STATE_IDLE)
		{
			if (isSit && vx == 0)
				ani = SIMON_ANI_SIT_DOWN;
			else
				ani = SIMON_ANI_IDLE;
		}
		
		else if (isImmortal && !isDone)
			ani = SIMON_ANI_HURT;
		else
			ani = SIMON_ANI_WALKING;
	}
	int alpha = 255;
	if (isImmortal) alpha = 128;

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
		if (isOnStair)
		{
			vy = 0;
			vx = 0;
			break;
		}
		else
		{
			vy += SIMON_GRAVITY * dt;
			isOnStair = false;
			isStairDown = false;
			isStairUp = false;
			vx = 0;
			break;
		}
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
			vy = -0.2;
			vx = 0;
		}
		else {
			dx = 0;
			dy = 0;
			simon_HP = 0;
		}
		break;
	case SIMON_STATE_STAIR_UP:
		vx = 0;
		isStairUp = true;
		isStairDown = false;
		isOnStair = true;
		break;
	case SIMON_STATE_STAIR_DOWN:
		vx = 0;
		isStairUp = false;
		isStairDown = true;
		isOnStair = true;
		break;
	case SIMON_STATE_STAIR_DOWN_IDLE:
		if (isOnStair == true)
		{
			vy = 0;
			vx = 0;
			break;
		}
	case SIMON_STATE_STAIR_UP_IDLE:
		if (isOnStair == true)
		{
			vy = 0;
			vx = 0;
			break;
		}
	case SIMON_ANI_DIE:
		action_time = GetTickCount();
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
}

void CSimon::ResetStair()
{
	/*state = SIMON_STATE_IDLE;
	vx = vy = 0;*/
	startStair = 0;
	lenghtStair = 0;
	simon_stair_type = 0;
	isStairUp = false;
	isStairDown = false;
	isOnStair = false;
	
}

void CSimon::StartMap4()
{
	startStair = 64.0f;
	lenghtStair = 96;
	simon_stair_type = OBJECT_TYPE_BRICK_DLR;
	SetState(SIMON_STATE_STAIR_UP);
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
	isDoneAttack = false;
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
	vx = vy = 0;
	startStair = 0;
	lenghtStair = 0;
	simon_stair_type = 0;
	isStairUp = false;
	isStairDown = false;
	isOnStair = false;
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
	
}