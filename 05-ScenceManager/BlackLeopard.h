#include "PlayScence.h"

class CBlackLeopard : public CGameObject
{
	float distanceLimit;
	bool isHidden = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void die();
	DWORD action_time;
public:
	float distance;
	CBlackLeopard();
	virtual void SetState(int state);
	bool CheckColli(float left_a, float top_a, float right_a, float bottom_a);
};

