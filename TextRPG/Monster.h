#pragma once
#include "Object.h"

class CMonster : public CObject
{
protected:
	eMonsterType mMonsterType;

	// 몬스터를 그려주는 함수
	void (*mDrawMonsterImage)();

protected:
	void MonsterInfoDraw();

	static string MonsteTypeToString(eMonsterType _monstertype);

public:
	CMonster();
	~CMonster();

public:
	virtual bool Init() override;
	virtual void Draw() override;
	virtual void Update() override;

	// get
	eMonsterType GetMonsterType() { return mMonsterType; }
	// set
	void SetMonsterType(eMonsterType _type) { mMonsterType = _type; }

	// 몬스터 스탯 정보
	void MonsterSetting(string _name, int _level, int _money, int _exp, int _hp, int _atk, int _def);

	// 보스 몬스터 생성
	bool InitBoss();

	// 몬스터 생존 여부
	bool MonsterIsAlive();
};

