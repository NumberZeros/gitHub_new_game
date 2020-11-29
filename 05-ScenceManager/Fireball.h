#pragma once
#include "GameObject.h"
#include "Simon.h"

#define FB_STATE_HIDDEN 0
#define FB_STATE_ATTACK 1

#define FB_ATTACK_TIME 1400
#define FB_X 10
#define FB_Y 15
#define FB_GRAVITY		0.001f
#define	FB_SPEED_X		0.2212f
#define	FB_SPEED_Y		0.4f
#define FB_ANI	0

class CFB : public CGameObject
{
	static CFB* __instance;
	int level;
	int frame;
	int vy = 1;

	DWORD action_time;


public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	float speedy = FB_SPEED_Y;
	void ResetAnimation(int ani);
	void SetFrame(int _frame) { frame = _frame; };
	int GetFrame() { return frame; };
	void UpdatePosionWithSimon(int _x, int _y, int _nx);
	static CFB* GetInstance();
	CFB();

	int axe_isAtk = 1;

	void Attack(DWORD dt);

	void SetLevel(int _level) { level = _level; };
	int GetLevel() { return level; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetAnimation();
	void GetPositionForSimon();

};