#include "Merman.h"
#include "PlayScence.h"*
CMerman::CMerman() {
	isHidden = false;
	SetState(MERMAN_WALKING);
	height = MERMAN_BBOX_HEIGHT;
	width = MERMAN_BBOX_WIDTH;
	Jump();
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

	DWORD now = GetTickCount();
	CGameObject::Update(dt, coObjects);
	if (now == 0)
	{
		this->x = x;
		this->y = 500;
		vy -= MERMAN_GRAVITY * dt;
	}

	//fall down
	
	vy += MERMAN_GRAVITY * dt;
	//this->SetState(MERMAN_JUMP);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

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

	if (vx > 0 && x > SCREEN_WIDTH) {
		x = SCREEN_WIDTH; vx = -vx;
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
				e->GetBoundingBox(left, top, right, bottom);

				if (e->frame == 2) {
					if (CheckColli(left, top, right, bottom))
					{
						this->isHidden = true;
						die();
					}
				}
			}
			if (dynamic_cast<CAxe*>(obj))
			{
				CAxe* e = dynamic_cast<CAxe*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);
				if (CheckColli(left, top, right, bottom))
				{
					die();
				}

			}
			if (dynamic_cast<CSimon*>(obj)) {
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
		DebugOut(L"nx %d \n", nx);
		if (nx > 0)
			vx = MERMAN_WALKING_SPEED_X;
		else
			vx = -MERMAN_WALKING_SPEED_X;
		DebugOut(L"vx %f \n", vx);
		break;
	case MERMAN_DEAD:
		vx = 0;
	}
}
void CMerman::die()
{
	isHidden = true;
	action_time = GetTickCount();
	this->state = MERMAN_DEAD;
	vx = 0;

}

void CMerman::Jump()
{

}
bool CMerman::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CMerman::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}

