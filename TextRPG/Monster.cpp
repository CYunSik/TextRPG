#include "Monster.h"
#include "Player.h"
#include "GameManager.h"

CMonster::CMonster()
{
	// 생성자
	// 동적으로 생성되고 나서 초기화를 해준다.
	Init();
}

CMonster::~CMonster()
{
	// 소멸자
}

bool CMonster::Init()
{
	// 몬스터 종료 받고 랜덤하게 스탯을 부여한다. 보스 제외
	mMonsterType = (eMonsterType)(rand() % (int)eMonsterType::End);
	
	switch (mMonsterType)
	{
	// 이름 능력치를 넣는 함수가 필요하다.
	// 이름 레벨 돈 경험치 체력 공격력 방어력
	case eMonsterType::Slime:
		MonsterSetting("슬라임", 1, 30, 50, 30, 15, 2);
		// 함수 포인터를 이용해서 슬라임을 출력
		mDrawMonsterImage = GlobalFunc::PrintSlimeImage;
		break;

	case eMonsterType::Goblin:
		MonsterSetting("고블린", 1, 50, 70, 40, 20, 3);
		mDrawMonsterImage = GlobalFunc::PrintGoblinImage;
		break;

	case eMonsterType::Skeleton:
		MonsterSetting("스켈레톤", 1, 100, 100, 50, 25, 5);
		mDrawMonsterImage = GlobalFunc::PrintSkeletonImage;
		break;
	}

	MosterPowerUP(mAreaName);

	return true;
}

bool CMonster::InitBoss()
{
	mMonsterType = eMonsterType::Boss;
	MonsterSetting("드래곤", 5, 200, 150, 100, 30, 10);
	mDrawMonsterImage = GlobalFunc::PrintDragonBoss;

	MosterPowerUP(mAreaName);

	return true;
}

void CMonster::Draw()
{
	MonsterInfoDraw();
}

void CMonster::Update()
{
}

void CMonster::MonsterSetting(string _name, int _level, int _money, int _exp, int _hp, int _atk, int _def)
{
	// 기본 능력치 세팅
	mName = _name;
	mLevel = _level;
	mMoney = _money;
	mExp = _exp;
	mMaxHP = _hp;
	mHP = mMaxHP;
	mATK = _atk;
	mDEF = _def;
}

void CMonster::MosterPowerUP(eAreaName _area)
{
	switch (_area)
	{
	case eAreaName::Forest:
		break;

	case eAreaName::Rival:
		// 능력치, 보상 강화
		mName += "[강]";
		mLevel += 5;
		mMoney = static_cast<int>(mMoney * 1.5f);
		mExp = static_cast<int>(mExp * 1.5f);
		mHP = static_cast<int>(mHP * 1.5f);
		mMaxHP = static_cast<int>(mMaxHP * 1.5f);
		mATK = static_cast<int>(mATK * 1.5f);
		mDEF += 5;
		break;

	case eAreaName::Mountaion:
		// 능력치, 보상 강화
		mName += "[산]";
		mLevel += 10;
		mMoney = static_cast<int>(mMoney * 2.0f);
		mExp = static_cast<int>(mExp * 2.0f);
		mHP = static_cast<int>(mHP * 2.0f);
		mMaxHP = static_cast<int>(mMaxHP * 2.0f);
		mATK = static_cast<int>(mATK * 2.0f);
		mDEF += 10;
		break;

	case eAreaName::Hell:
		// 능력치, 보상 강화
		mName += "[지옥]";
		mLevel += 20;
		mMoney = static_cast<int>(mMoney * 3.0f);
		mExp = static_cast<int>(mExp * 3.0f);
		mHP = static_cast<int>(mHP * 3.0f);
		mMaxHP = static_cast<int>(mMaxHP * 3.0f);
		mATK = static_cast<int>(mATK * 3.0f);
		mDEF += 25;
		break;
	}
}

void CMonster::MonsterInfoDraw()
{
	COUTN("---------------- 몬스터 정보 ----------------");
	// 이름
	COUT("이름\t: " << mName << "\t|\t");
	// 종족
	COUTN("종족\t: " << MonsteTypeToString(mMonsterType));
	// 체력
	COUT("체력\t: " << mHP << " / " << mMaxHP << "\t|\t");
	// 레벨
	COUTN("레벨\t: " << mLevel);
	// 공격력
	COUT("공격력\t: " << mATK << "\t\t|\t");
	// 방어력
	COUTN("방어력\t: " << mDEF);
	COUTN("---------------------------------------------");
	COUTN("");
	mDrawMonsterImage();
	COUTN("");
}

string CMonster::MonsteTypeToString(eMonsterType _monstertype)
{
	switch (_monstertype)
	{
	case eMonsterType::Slime:
		return "물질";
	case eMonsterType::Goblin:
		return "오크";
	case eMonsterType::Skeleton:
		return "해골";
	case eMonsterType::Boss:
		return "용[보스]";
	}

	return string();
}