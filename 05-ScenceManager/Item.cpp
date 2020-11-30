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
		if (isTorch || isCandle || isBrick) 
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
	case ITEM_ANI_SMALLHEART:
		this->width = ITEM_SMALLHEART_BBOX_WIDTH;
		this->height = ITEM_SMALLHEART_BBOX_HEIGHT;
		break;
	case ITEM_ANI_BLUEMONEY:
		this->width = ITEM_BLUEMONEY_BBOX_WIDTH;
		this->height = ITEM_BLUEMONEY_BBOX_HEIGHT;
		break;
	case ITEM_ANI_REDMONEY:
		this->width = ITEM_REDMONEY_BBOX_WIDTH;
		this->height = ITEM_REDMONEY_BBOX_HEIGHT;
		break;
	case ITEM_ANI_WHITEMONEY:
		this->width = ITEM_WHITEMONEY_BBOX_WIDTH;
		this->height = ITEM_WHITEMONEY_BBOX_HEIGHT;
		break;
	case ITEM_ANI_KNIFE:
		this->width = ITEM_KNIFE_BBOX_WIDTH;
		this->height = ITEM_KNIFE_BBOX_HEIGHT;
		break;
	case ITEM_ANI_BRICK:
		this->width = ITEM_BRICK_BBOX_WIDTH;
		this->height = ITEM_BRICK_BBOX_HEIGHT;
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
		if (id == ITEM_ANI_SMALLHEART)
		{
			ani = GetAnimation();
			this->isSmallHeart = true;
			this->isCandle = false;
			this->isFire = false;
			this->isHidden = false;
		}
		if (id == ITEM_ANI_BLUEMONEY)
		{
			ani = GetAnimation();
			this->isBlueMoney = true;
			this->isCandle = false;
			this->isFire = false;
			this->isHidden = false;
		}
		if (id == ITEM_ANI_REDMONEY)
		{
			ani = GetAnimation();
			this->isRedMoney = true;
			this->isCandle = false;
			this->isFire = false;
			this->isHidden = false;
		}
		if (id == ITEM_ANI_WHITEMONEY)
		{
			ani = GetAnimation();
			this->isWhiteMoney = true;
			this->isCandle = false;
			this->isFire = false;
			this->isHidden = false;
		}
		if (id == ITEM_ANI_KNIFE)
		{
			ani = GetAnimation();
			this->isKnife = true;
			this->isCandle = false;
			this->isFire = false;
			this->isHidden = false;
		}
		if (id == ITEM_ANI_BRICK)
		{
			ani = GetAnimation();
			this->isBrick = true;
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
	case ITEM_ANI_SMALLHEART:
		ani = ITEM_ANI_SMALLHEART;
		break;
	case ITEM_ANI_BLUEMONEY:
		ani = ITEM_ANI_BLUEMONEY;
		break;
	case ITEM_ANI_REDMONEY:
		ani = ITEM_ANI_REDMONEY;
		break;
	case ITEM_ANI_WHITEMONEY:
		ani = ITEM_ANI_WHITEMONEY;
		break;
	case ITEM_ANI_KNIFE:
		ani = ITEM_ANI_KNIFE;
		break;
	case ITEM_ANI_BRICK:
		ani = ITEM_ANI_BRICK;
		break;
	default:
		ani = ITEM_STATE_HIDDEN;
		break;
	}
	return ani;
}

