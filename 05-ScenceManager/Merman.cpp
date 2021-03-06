#include "Merman.h"
#include "Axe.h"
CMerman::CMerman() {
	srand(time(NULL));
	nx = rand() % (1 - (-1) + 1) -1;
	isHidden = false;	
	height = MERMAN_BBOX_HEIGHT;
	width = MERMAN_BBOX_WIDTH;
	SetState(MERMAN_JUMP);	
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
	CAxe* knife = new CAxe();
	CGameObject::Update(dt, coObjects);
	//fall down	
	vy += MERMAN_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	srand(time(NULL));
	int res = rand() % (7000 - 2500 + 1) + 2500;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount() - action_time > 1200) {
		SetState(MERMAN_WALKING);
	}
	if (GetTickCount() - action_time > res) {
		this->SetState(MERMAN_SHOOT_FIREBALL);
		knife->UpdatePosionWithSimon(this->GetPositionX(), this->GetPositionY(), this->nx);
		knife->speedy = AXE_SPEED_Y;
		knife->SetState(AXE_STATE_ATTACK);
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
			if (dynamic_cast<CHlw*>(obj))
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
					ResetBB();
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
		break;
	case MERMAN_JUMP:
		action_time = GetTickCount();
		vx = 0;
		vy -= MERMAN_JUMP_SPEED_Y;
		break;
	case MERMAN_SHOOT_FIREBALL:
		action_time = GetTickCount();
		vx = vy = 0;
		attack();
		break;
	default:
			break;
	}
}
void CMerman::attack()
{
	animation_set->at(MERMAN_SHOOT_FIREBALL)->ResetFrame();
	action_time = GetTickCount();
	isDone = false;
	isAttack = true;
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

