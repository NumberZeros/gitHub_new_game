#include "Merman.h"
#include <time.h>
#include "PlayScence.h"
#include "Scence.h"

CMerman::CMerman() 
{

		srand(time(NULL));
		//x = rand() % (150 - 10 + 1) + 10;
		isHidden = false;
		height = MERMAN_BBOX_HEIGHT;
		width = MERMAN_BBOX_WIDTH;
		//SetState(MERMAN_JUMP);

}

CMerman::~CMerman()
{
}

void CMerman::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CMerman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	//fall down	

		vy += MERMAN_GRAVITY * dt;
	//	DebugOut(L"merman state: %d \t", state);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	srand(time(NULL));
	//int res = rand() % (8500 - 4000 + 1) + 4000;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount() - action_time > 1300) {
		SetState(MERMAN_WALKING);
	}
	if (GetTickCount() - action_time > 3500) {
		this->SetState(MERMAN_SHOOT_FIREBALL);		
	}
	if (isHidden)
	{
		if (GetTickCount() - action_time >= 500)
			ResetBB();
	}

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
		this->nx = 1;
	}

	if (vx > 0 && x > 450) {
		x = 450; vx = -vx;
		this->nx = -1;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0, rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += dx;
		y += min_ty * dy + ny * 0.1f;

		for (UINT i = 0; i < coObjects->size(); i++)
		{
			
			LPGAMEOBJECT obj = coObjects->at(i);
		
		   if (dynamic_cast<CWeapon*>(obj))
			{
				CWeapon* e = dynamic_cast<CWeapon*>(obj);

				float left, top, right, bottom;
				obj->GetBoundingBox(left, top, right, bottom);

				if (e->frame == 2) {
					if (CheckColli(left, top, right, bottom))
					{
						this->isHidden = true;
						die();
					}
				}
			}

			else if (dynamic_cast<CAxe*>(obj))
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
			else if (dynamic_cast<CKnife*>(obj))
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
			else if (dynamic_cast<CHlw*>(obj))
			{
				CHlw* e = dynamic_cast<CHlw*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);
				if (CheckColli(left, top, right, bottom))
				{
					e->SetState(HLW_STATE_COLLIDE);
					e->speedy = 0;
					e->nx = 0;

					this->isHidden = true;
					e->ResetBB();
				}

				else if (dynamic_cast<CSimon*>(obj)) {
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
			}
		}
		/*for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj)) {
				CBrick* item = dynamic_cast<CBrick*>(e->obj);
				if (e->ny >= 0)
				{
					vy = 0;
				}
			}
		}*/
	}
   for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMerman::Render()
{
	animation_set->at(this->state)->Render(nx, x, y);
	RenderBoundingBox();
}


void CMerman::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MERMAN_WALKING:
		//DebugOut(L"nx %d \n", nx);
		if (nx > 0)
			vx = MERMAN_WALKING_SPEED_X;
		else
			vx = -MERMAN_WALKING_SPEED_X;
		//DebugOut(L"vx %f \n", vx);
		break;
	case MERMAN_DEAD:
		vx = 0;
		break;
	case MERMAN_JUMP:
		action_time = GetTickCount();
		vx = 0;
		vy -= MERMAN_JUMP_SPEED_Y;
		break;
	case MERMAN_SHOOT_FIREBALL:
		
		action_time = GetTickCount();
		vx = vy = 0;
		//attack();
		isAttack = true;
		break;
	default:
			break;
	}
}

void CMerman::attack()
{
	
	//CAxe* fb = ((CPlayScene*)scence)->axe;
	//CFB* fb = ((CPlayScene*)scence)->axe;
    animation_set->at(MERMAN_SHOOT_FIREBALL);
	action_time = GetTickCount();
	fb->UpdatePosionWithSimon(this->GetPositionX(), this->GetPositionY(), this->nx);
	fb->speedy = FB_SPEED_Y;
	fb->SetState(FB_STATE_ATTACK);
	DebugOut(L"fb state: %d \t", fb->state);
	//this->SetState(MERMAN_FIREBALL);
	item->SetState(ITEM_ANI_KNIFE);
}

void CMerman::die()
{
	isHidden = true;
	action_time = GetTickCount();
	this->state = MERMAN_DEAD;
	vx = 0;
}


bool CMerman::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CMerman::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}

