#include "Item.h"
#include "Define.h"
#include <time.h>
#include "Utils.h"
#include "Textures.h"
#include "Game.h"
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


void CItem::Render()
{
	if (isHidden) return;
	int ani = GetAnimation();
	animation_set->at(ani)->Render(nx, x, y, 255);
	RenderBoundingBox();
}
void CItem::SetState(int state)
{
	int ani;
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_STATE_SHOW:
		if (this->id == ITEM_ANI_TORCH)
		{
			ani = GetAnimation();
			this->action_time = GetTickCount();
			isTorch = true;
			isHidden = false;
		}
		if (this->id == ITEM_ANI_EFFECTFIRE)
		{
			ani = GetAnimation();
			this->action_time = GetTickCount();
			isFire = true;
			isHidden = false;
		}
		else
		{
			vy += speedy * dt;
			ani = GetAnimation();
			this->action_time = GetTickCount();
			isKnife = true;
			isChain = true;
			isBigHeart = true;
			isHidden = false;
		}
		break;
	case ITEM_STATE_HIDDEN:
		ani = GetAnimation();
		isHidden = true;
		isTorch = false;
		isChain = false;
		isBigHeart = false;
		isKnife = false;
		isFire = false;
		break;
	default:
		break;
	}
}
int CItem::GetAnimation()
{
	int ani;
	switch (this->id)
	{
	case ITEM_ANI_TORCH:
		ani = ITEM_ANI_TORCH;
		this->isTorch = true;
		this->isHidden = false;
		break;
	case ITEM_ANI_CHAIN:
		ani = ITEM_ANI_CHAIN;
		this->isChain = true;
		this->isHidden = false;
		break;
	case ITEM_ANI_BIGHEART:
		ani = ITEM_ANI_BIGHEART;
		this->isBigHeart = true;
		this->isHidden = false;
		break;
	case ITEM_ANI_KNIFE:
		ani = ITEM_ANI_KNIFE;
		this->isKnife = true;
		this->isHidden = false;
		break;
	case ITEM_ANI_EFFECTFIRE:
		ani = ITEM_ANI_EFFECTFIRE;
		this->isFire = true;
		this->isHidden = false;
		break;
	default:
		ani = ITEM_STATE_HIDDEN;
		this->isHidden = true;
		break;
	}
	return ani;
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
	vy += speedy * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CheckSize();


	if (isFire == true) {
		if (GetTickCount() - action_time > ITEM_TIME_FIRE) {
			if (GetTickCount() - action_time > ITEM_DISAPPEAR_TIME)
			{
				isFire = false;
				this->action_time = 0;
				this->isHidden = true;
				ResetBB();

			}
			else if (this->id = ITEM_ANI_BIGHEART) {
				this->SetID(ITEM_ANI_BIGHEART);
				y -= speedy * dt;
				speedy -= 0.019;
			}
			else if (this->id = ITEM_ANI_CHAIN) {
				this->SetID(ITEM_ANI_CHAIN);
				y -= speedy * dt;
				speedy -= 0.019;
			}
		}
	}
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (this->isTorch == true) {
			if (dynamic_cast<CWeapon*>(obj))
			{
				CWeapon* e = dynamic_cast<CWeapon*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);

				if (e->frame == 2) {
					if (CheckColli(left, top, right, bottom))
					{
						DebugOut(L"\nCo va cham");
						SetID(ITEM_ANI_EFFECTFIRE);
						this->isFire = true;
						this->isTorch = false;

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
	switch (this->id)
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
	case ITEM_ANI_EFFECTFIRE:
		this->width = ITEM_EFFECTFIRE_BBOX_WIDTH;
		this->height = ITEM_EFFECTFIRE_BBOX_HEIGHT;
		break;
	default:
		break;
	}
}

