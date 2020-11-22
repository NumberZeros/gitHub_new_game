#include "Item.h"
#include <time.h>
#include "PlayScence.h"
CItem::CItem()
{
	nx = 1;
	SetState(ITEM_STATE_HIDDEN);
	x = -100;
	y = -100;
	isHidden = true;
	id = 1;
}

CItem::~CItem()
{
}


void CItem::Render()
{
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx, x, y, 255);
	RenderBoundingBox();
}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	r = x + width;
	t = y;
	b = y + height;

}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	coEvents.clear();

	//cham dat
	CalcPotentialCollisions(coObjects, coEvents);
	CheckSize();

	if (isFire == true)
	{
		if (GetTickCount() - action_time > ITEM_TIME_FIRE) {
			dx = 0;
			isFire = false;
			isTorch = false;
			this->action_time = 0;
			SetID(secondGood);
		}
	}
	else
	{
		if (id != ITEM_ANI_CANDLE && id != ITEM_ANI_TORCH) {
			y += speedy * dt;
		}
	}

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
			if (dynamic_cast<CSimon*>(e->obj)) {
				CSimon* simon = dynamic_cast<CSimon*>(e->obj);
				if (isTorch || isFire || isCandle) {
					if (nx != 0)
						simon->x += simon->dx;
					if (!simon->isGrounded) {
						if (ny < 0)
							simon->y += simon->dy;
						if (ny > 0) {
							simon->vy = -SIMON_JUMP_SPEED_Y;
							simon->y += simon->dy;
						}
					}
				}
				else if (id == ITEM_ANI_CHAIN) {
					simon->level += 1;
					isHidden = true;
					ResetBB();
				}
			}
		}
	}

	for (UINT i = 0; i < coObjects->size(); i++)
	{

		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CBrick*>(obj))
		{
			CBrick* e = dynamic_cast<CBrick*>(obj);

			float left, top, right, bottom;
			e->GetBoundingBox(left, top, right, bottom);
			if (CheckColli(left, top, right, bottom))
			{
				speedy = 0;
			}
		}
		if (isTorch || isCandle) 
		{
			
			if (dynamic_cast<CWeapon*>(obj))
			{
				CWeapon* e = dynamic_cast<CWeapon*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (e->frame == 2) {
					if (CheckColli(left, top, right, bottom))
					{
						SetID(ITEM_ANI_EFFECTFIRE);
						this->isFire = true;
						action_time = GetTickCount();
					}
				}
			}
		}

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

bool CItem::CheckColli(float left_a, float top_a, float right_a, float bottom_a)
{
	float l, t, r, b;
	CItem::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}
void CItem::CheckSize()
{
	switch (id)
	{
	case ITEM_ANI_CHAIN: {
		this->width = ITEM_CHAIN_BBOX_WIDTH;
		this->height = ITEM_CHAIN_BBOX_HEIGHT;
		break;
	}
	case ITEM_ANI_BIGHEART: {
		this->width = ITEM_BIGHEART_BBOX_WIDTH;
		this->height = ITEM_BIGHEART_BBOX_HEIGHT;
		break;
	}
	case ITEM_ANI_TORCH:
		this->width = ITEM_TORCH_BBOX_WIDTH;
		this->height = ITEM_TORCH_BBOX_HEIGHT;
		break;
	case ITEM_ANI_CANDLE:
		this->width = ITEM_CANDLE_BBOX_WIDTH;
		this->height = ITEM_CANDLE_BBOX_HEIGHT;
		break;
	case ITEM_ANI_EFFECTFIRE:
		this->width = ITEM_EFFECTFIRE_BBOX_WIDTH;
		this->height = ITEM_EFFECTFIRE_BBOX_HEIGHT;
		break;
	case ITEM_ANI_HOLYWATER:
		this->width = ITEM_HOLYWATER_BBOX_WIDTH;
		this->height = ITEM_HOLYWATER_BBOX_HEIGHT;
		break;
	case ITEM_ANI_MEAT:
		this->width = ITEM_MEAT_BBOX_WIDTH;
		this->height = ITEM_MEAT_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}

void CItem::SetState(int state)
{
	int ani;
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_SHOW:
		if (id == ITEM_ANI_TORCH)
		{
			ani = GetAnimation();
			this->isTorch = true;
			this->isCandle = false;
			this->isFire = false;
			this->isHidden = false;
		}
		else if (id == ITEM_ANI_EFFECTFIRE)
		{
			ani = GetAnimation();
			this->action_time = GetTickCount();
			this->isFire = true;
			this->isHidden = false;
		}
		else if (id == ITEM_ANI_CANDLE) {
			ani = GetAnimation();
			this->isTorch = false;
			this->isCandle = true;
			this->isFire = false;
			this->isHidden = false;
		}
		if (id == ITEM_ANI_HOLYWATER)
		{
			ani = GetAnimation();
			this->isHolyWater = true;
			this->isCandle = false;
			this->isFire = false;
			this->isHidden = false;
		}
		if (id == ITEM_ANI_MEAT)
		{
			ani = GetAnimation();
			this->isMeat = true;
			this->isCandle = false;
			this->isFire = false;
			this->isHidden = false;
		}
		else
		{
			vy += speedy * dt;
			ani = GetAnimation();
			this->action_time = GetTickCount();
			isHidden = false;
		}
		break;
	case ITEM_STATE_HIDDEN:
		ani = GetAnimation();
		isHidden = true;
		isTorch = false;
		isCandle = false;
		isFire = false;
		break;
	default:
		break;
	}
}
int CItem::GetAnimation()
{
	int ani;
	switch (id)
	{
	case ITEM_ANI_TORCH:
		ani = ITEM_ANI_TORCH;
		break;
	case ITEM_ANI_BIGHEART:
		ani = ITEM_ANI_BIGHEART;
		break;
	case ITEM_ANI_CANDLE:
		ani = ITEM_ANI_CANDLE;
		break;
	case ITEM_ANI_EFFECTFIRE:
		ani = ITEM_ANI_EFFECTFIRE;
		break;
	case ITEM_ANI_HOLYWATER:
		ani = ITEM_ANI_HOLYWATER;
		break;
	case ITEM_ANI_MEAT:
		ani = ITEM_ANI_MEAT;
		break;
	default:
		ani = ITEM_STATE_HIDDEN;
		break;
	}
	return ani;
}

