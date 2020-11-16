#pragma once
#include "GameObject.h"
#define VAMPIREBAT_FLYING_SPEED_X								0.35f
#define VAMPIREBAT_FLYING_SPEED_Y										0.25f
#define VAMPIREBAT_GRAVITY										0.001f

#define VAMPIREBAT_BBOX_WIDTH											32
#define VAMPIREBAT_BBOX_HEIGHT									32

#define VAMPIREBAT_FLYING												2

#define VAMPIREBAT_ANI_FLYING									0
#define	VAMPIREBAT_SPEED_X		0.2212f
#define	VAMPIREBAT_SPEED_Y		0.3f
#define DELTA_SPEEDY			0.0019f

class CVampireBat : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool isHidden = false;
public:
	float deltaspeed = DELTA_SPEEDY;
	float speedy = VAMPIREBAT_SPEED_Y;
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	CVampireBat();
	virtual void SetState(int state);
};


