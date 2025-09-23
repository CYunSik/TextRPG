#pragma once
#include "GameInfo.h"

// 추상클래스
class CObject
{
protected:
	string mName = "";
	// 직업
	eJobClass mJob;
	// 돈
	int mMoney = 0;
	// 경험치
	int mExp = 0;
	// 도달 경험치
	int mMaxExp = 100;
	// 레벨
	int mLevel = 1;
	// 체력
	int mHP = DEFAULT_HP;
	// 최대체력
	int mMaxHP = DEFAULT_HP;
	// 공격력
	int mATK = DEFAULT_ATK;
	// 방어력
	int mDEF = DEFAULT_DEF;

public:
	// get
	string GetName() { return mName; }
	// eJobClass GetJobb() { return mJob; }
	int GetMoney() { return mMoney; }
	int GetExp() { return mExp; }
	int GetLevel() { return mLevel; }
	int GetHP() { return mHP; }
	int GetMaxHP() { return mMaxHP; }
	int GetATK() { return mATK; }
	int GetDEF() { return mDEF; }

	// set
	void SetMoney(int _money) { mMoney = _money; }
	void SetExp(int _exp) { mExp = _exp; }
	void SetLevel(int _level) { mLevel = _level; }
	void SetHP(int _hp) { mHP = _hp; }
	void SetMaxHP(int _maxhp) { mMaxHP = _maxhp; }
	void SetATK(int _atk) { mATK = _atk; }
	void SetDEF(int _def) { mDEF = _def; }

////////////////////////////////////////////////
	// 능력 스탯 지정해주는 함수
	// 체력, 공격력, 방어력
	inline void AllStateSet(int _hp, int _atk, int _def)
	{
		mMaxHP = _hp;
		mHP = mMaxHP;
		mATK = _atk;
		mDEF = _def;
	}


public:
	virtual bool Init() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;

	virtual void TakeDamage(int _damage);

public:
	CObject() = default;
	virtual ~CObject() = default;
};

