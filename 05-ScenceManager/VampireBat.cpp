#include "VampireBat.h"
#include "PlayScence.h"

CVampireBat::CVampireBat()
{
	isHidden = false;
	SetState(VAMPIREBAT_FLYING);
	height = VAMPIREBAT_BBOX_HEIGHT;
	width = VAMPIREBAT_BBOX_WIDTH;	
}

void CVampireBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
	
}

void CVampireBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	y = sin(x * 0.03) * 41.3 + ybat;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (x > max) {
		nx = -1;
		vx = -VAMPIREBAT_FLYING_SPEED_X;
	}
	else if (x < min) {
		nx = 1;
		vx = VAMPIREBAT_FLYING_SPEED_X;
	}
	if (isHidden)
	{
 		if (GetTickCount() - action_time >= 500)
			ResetBB();
	}

	if (coEvents.size() == 0)
	{
		this->x += dx;
		this->y += dy;
	}

	//if (this->vx < 0 && this->x < 0) {
	//	this->x = 0; this->vx = -vx;
	//	this->nx = 1;
	//}

	//if (this->vx > 0 && this->x > SCREEN_WIDTH - 30) {
	//	this->x = SCREEN_WIDTH + 60; this->vx = -vx;
	//	this->nx = -1;
	//}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0, rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		this->x += dx;
		this->y += min_ty * dy + ny * 0.1f;


		

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
					die();
				}
			}
			else if (dynamic_cast<CAxe*>(obj))
			{
				CAxe* e = dynamic_cast<CAxe*>(obj);

				float left, top, right, bottom;
				e->GetBoundingBox(left, top, right, bottom);
				if (CheckColli(left, top, right, bottom))
				die();
			}
			else if (dynamic_cast<CSimon*>(obj)) {
				CSimon* simon = dynamic_cast<CSimon*>(obj);
				float left, top, right, bottom;
				simon->GetBoundingBox(left, top, right, bottom);
				if (!isHidden && !simon->isImmortal) {		/// khi doi chua chuyen thanh lua va simon chua tung va cham voi quai nao
					if (CheckColli(left, top, right, bottom))
					{
						die();
						simon->SetState(SIMON_STATE_HURT);
						
						
					}
				}
			}
		}
	}
}

void CVampireBat::Render()
{
	animation_set->at(this->state)->Render(nx, x, y);
	RenderBoundingBox();
}


void CVampireBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VAMPIREBAT_FLYING:
		DebugOut(L"nx %d \n", nx);
		if (nx > 0)
			vx = VAMPIREBAT_FLYING_SPEED_X;
		else
			vx = -VAMPIREBAT_FLYING_SPEED_X;
		DebugOut(L"vx %f \n", vx);
		break;
	case VAMPIREBAT_DEAD:
		vx = 0;
	}
}
void CVampireBat::die()
{
	isHidden = true;
	action_time = GetTickCount();
	this->state = VAMPIREBAT_DEAD;
	vx = 0;

}
bool CVampireBat::CheckColli(float left_a, float top_a, float right_a, float bottom_a) {
	float l, t, r, b;
	CVampireBat::GetBoundingBox(l, t, r, b);

	if (CGameObject::AABBCheck(l, t, r, b, left_a, top_a, right_a, bottom_a))
		return true;
	else
		return false;
}
