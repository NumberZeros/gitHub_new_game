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
	int actionAttack = 0;	// 0 right 1 left
	int start_x;
	int start_y;
	int simon_HP;
	int simon_Score = 10;
	int simon_Mana, simon_P, simon_Sub, simon_stage = 1;
	int simon_stair_type = 0;
	int xbr = 0;

	bool isSit;
	bool isAttack;
	bool isGrounded;
	bool isImmortal = false;
	bool isEndGame = false;
	bool isDoneAttack = true;
	bool isAutoMove = false;
	bool isOnStair = false;
	bool isStairUp = false;
	bool isStairDown = false;

	float lenghtStair;
	float startStair;
	DWORD timeImmortal;
public:
	//get n set
	int getNumber() { return number; }
	void setNumber(int _number) { number = _number; }
	int getLevel() { return level; }
	void setLevel(int _level) { level = _level; }
	int getUntouchable() { return untouchable; }
	void setUntouchable(int _untouchable) { untouchable = _untouchable; }
	int getactionAttack() { return actionAttack; }
	void setactionAttack(int _actionAttack) { actionAttack = _actionAttack; }
	int getstart_x() { return start_x; }
	void setstart_x(int _start_x) { start_x = _start_x; }
	int getstart_y() { return start_y; }
	void setstart_y(int _start_y) { start_y = _start_y; }
	int getsimon_HP() { return simon_HP; }
	void setsimon_HP(int _simon_HP) { simon_HP = _simon_HP; }
	int getsimon_Score() { return simon_Score; }
	void setsimon_Score(int _simon_Score) { simon_Score = _simon_Score; }
	int getsimon_Mana() { return simon_Mana; }
	void setsimon_Mana(int _simon_Mana) { simon_Mana = _simon_Mana; }
	int getsimon_P() { return simon_P; }
	void setsimon_P(int _simon_P) { simon_P = _simon_P; }
	int getsimon_Sub() { return simon_Sub; }
	void setsimon_Sub(int _simon_Sub) { simon_Sub = _simon_Sub; }
	int getsimon_stage() { return simon_stage; }
	void setsimon_stage(int _simon_stage) { simon_stage = _simon_stage; }
	int getsimon_stair_type() { return simon_stair_type; }
	void setsimon_stair_type(int _simon_stair_type) { simon_stair_type = _simon_stair_type; }
	int getxbr() { return xbr; }
	void setxbr(int _xbr) { xbr = _xbr; }

	bool getisSit() { return isSit; }
	void setisSit(bool _isSit) { isSit = _isSit; }
	bool getisAttack() { return isAttack; }
	void setisAttack(bool _isAttack) { isAttack = _isAttack; }
	bool getisGrounded() { return isGrounded; }
	void setisGrounded(bool _isGrounded) { isGrounded = _isGrounded; }
	bool getisImmortal() { return isImmortal; }
	void setisImmortal(bool _isImmortal) { isImmortal = _isImmortal; }
	bool getisEndGame() { return isEndGame; }
	void setisEndGame(bool _isEndGame) { isEndGame = _isEndGame; }
	bool getisDoneAttack() { return isDoneAttack; }
	void setisDoneAttack(bool _isDoneAttack) { isDoneAttack = _isDoneAttack; }
	bool getisAutoMove() { return isAutoMove; }
	void setisAutoMove(bool _isAutoMove) { isAutoMove = _isAutoMove; }
	bool getisOnStair() { return isOnStair; }
	void setisOnStair(bool _isOnStair) { isOnStair = _isOnStair; }
	bool getisStairUp() { return isStairUp; }
	void setisStairUp(bool _isStairUp) { isStairUp = _isStairUp; }
	bool getisStairDown() { return isStairDown; }
	void setisStairDown(bool _isStairDown) { isStairDown = _isStairDown; }

	float getlenghtStair() { return lenghtStair; }
	void setlenghtStair(bool _lenghtStair) { lenghtStair = _lenghtStair; }
	float getstartStair() { return startStair; }
	void setstartStair(bool _startStair) { startStair = _startStair; }
	//end get n set

	virtual void AutoWalk(int des);
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
	void ResetStair();
	void StartMap4();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};