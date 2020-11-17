#pragma once
#include "GameObject.h"
#include "Utils.h"
#include"Weapon.h"
#include"Axe.h"

//#define BLACK_LEOPARD_ACTIVE		0    
#define BLACK_LEOPARD_DESTROYED		3
#define BLACK_LEOPARD_RUN			1
#define BLACK_LEOPARD_IDLE			0
//#define BLACK_LEOPARD_JUMP			4

#define BLACK_LEOPARD_ANI_IDLE			0
#define BLACK_LEOPARD_ANI_JUMP			3
#define BLACK_LEOPARD_ANI_RUN			1
#define BLACK_LEOPARD_ANI_RUN_RIGHT		2

#define BLACK_LEOPARD_RUNNING_SPEED_X	0.3f
#define BLACK_LEOPARD_RUNNING_SPEED_Y	0.2f
#define BLACK_LEOPARD_GRAVITY			0.001f

#define BLACK_LEOPARD_BBOX_WIDTH			64
#define BLACK_LEOPARD_BBOX_HEIGHT			32
#define BLACK_LEOPARD_ACTIVE_BBOX_WIDTH		100
#define BLACK_LEOPARD_ACTIVE_BBOX_HEIGHT	200

class CBlackLeopard : public CGameObject
{
	bool isHidden = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void die();
	DWORD action_time;
public:
	CBlackLeopard();
	virtual void SetState(int state);
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
};

