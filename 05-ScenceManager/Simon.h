#pragma once
#include "GameObject.h"

class CSimon : public CGameObject
{
public:
	int number;
	int level;
	int untouchable;
	int height = 60;
	int width = 32;
	bool isSit;
	bool isAttack;
	bool isGrounded;
	bool isImmortal = false;
	int actionAttack = 0;	// 0 right 1 left
	int start_x;
	int start_y;
	int simon_HP;
	int simon_Score;
	int simon_Mana,simon_P,simon_Sub,simon_stage=1;
	bool isDoneAttack = true;
	bool isAutoMove = false;

	DWORD timeImmortal;
public:
	virtual void AutoWalk(int des);

	int simon_stair_type = 0;
	int xbr = 0;
	bool isStairUp = false;
	bool isStairDown = false;
	CSimon();
	virtual void SitDown();
	virtual void attack();
	virtual void ResetAnimation();
	virtual void Reset();
	CSimon(float x, float y);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
	virtual void Render();
	
	void SetNX(int _nx) { nx = _nx; }
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	bool GetAttack() { return this->isAttack; };
	int GetNumber() { return this->number; }
	void SimonColliWithItems(vector<LPGAMEOBJECT>* listitems);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};