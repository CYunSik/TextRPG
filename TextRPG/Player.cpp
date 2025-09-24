#include "Player.h"
#include "GameManager.h"
#include "Monster.h"

CPlayer::CPlayer() : mState(ePlayerState::search)
{

}
CPlayer::~CPlayer()
{

}

bool CPlayer::Init()
{
	// 타이틀 화면
	printf("ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ\n");
	printf("ㅁ                                    ㅁ\n");
	printf("ㅁ              Text RPG              ㅁ\n");
	printf("ㅁ                                    ㅁ\n");
	printf("ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ\n");

	// 플레이어 이름 받기
	COUT("플레이어의 이름을 입력해주세요 : ");
	cin >> mName;

	// 직업 선택하기
	int selectJob = 0;
	do
	{
		COUTN("");
		COUTN("직업을 선택해주세요.");
		COUTN("[ 1.전사   2.마법사   3.도적   4.궁수] ");
		cin >> selectJob;
	} while (selectJob < 1 || selectJob > 4);

	mJob = (eJobClass)selectJob;
	switch (mJob)
	{
	case eJobClass::Warrior:	// 전사
		AllStateSet(200, 10, 6);
		break;
	case eJobClass::Wizard:		// 마법사
		AllStateSet(150, 17, 0);
		break;
	case eJobClass::Thief:		// 도적
		AllStateSet(130, 14, 3);
		break;
	case eJobClass::Archer:		// 궁수
		AllStateSet(150, 14, 2);
		break;
	}

	return true;
}

void CPlayer::Draw()
{
	// 플레이어 정보 출력
	PlayerInfoDraw();

	// 플레이어가 할수있는 일
	if (mState == ePlayerState::search)
	{
		// 일반 상태일때
		PlayerSearchDraw();
	}
	else if (mState == ePlayerState::combat)
	{
		// 전투 상태일때
		PlayerCombatDraw();
	}
}

void CPlayer::Update()
{
	int message = CGameManager::GetInst()->GetInputMessage();

	switch (mState)
	{
	case ePlayerState::search:	// 일반 상태일때
		BasicStateUpdate(message);
		break;
	case ePlayerState::combat:	// 나중에 전투가 시작되었을때
		CombatStateUpdate(message);
		break;
	}
}

void CPlayer::PlayerInfoDraw()
{
	COUTN("---------------- 플레이어 정보 --------------");
	// 이름
	COUT("이름\t: " << mName << "\t\t|\t");
	// 직업
	COUTN("직업\t: " << JobToString(mJob));
	// 경험치 / 최대 목표 경험치
	COUT("경험치\t: " << mExp << " / " << mMaxExp << "\t|\t");
	// 레벨
	COUTN("레벨\t: " << mLevel);
	// 체력
	COUT("체력\t: " << mHP << " / " << mMaxHP << "\t|\t");
	// 돈
	COUTN("돈\t: " << mMoney);
	// 공격력
	COUT("공격력\t: " << mATK << "\t\t|\t");
	// 방어력
	COUTN("방어력\t: " << mDEF);
	COUTN("---------------------------------------------");
}

void CPlayer::PlayerSearchDraw() const
{
	COUTN("");
	COUTN("\t==================================");
	COUTN("\t|            행동 선택           |");
	COUTN("\t---------------------------------");
	COUTN("\t|     [1] 탐색       [2] 휴식    |");
	COUTN("\t|     [3] 다음지역   [4] 상점    |");
	COUTN("\t==================================");
}

void CPlayer::PlayerCombatDraw() const
{
	COUTN("");
	COUTN("\t==================================");
	COUTN("\t|            행동 선택           |");
	COUTN("\t---------------------------------");
	COUTN("\t|  [1] 공격  [2] 방어  [3] 도망  |");
	COUTN("\t==================================");
}

void CPlayer::PlayerStoreDraw() const
{
	COUTN("-------------------- 상점 -------------------");
	COUTN("번호\t아이템\t\t효과\t\t가격");
	COUTN("  1\t공격 물약\t공격력 + 1\t50원");
	COUTN("  2\t방어 물약\t방어력 + 1\t50원");
	COUTN("  3\t최대 체력 물약\t최대 체력 + 15\t50원");
	COUTN("  4\t경험치 물약\t경험치 + 30\t50원");
	COUTN("---------------------------------------------");
}

string CPlayer::JobToString(const eJobClass& _job)
{
	switch (_job)
	{
	case eJobClass::Warrior:
		return string("전사");
	case eJobClass::Wizard:
		return string("마법사");
	case eJobClass::Thief:
		return string("도적");
	case eJobClass::Archer:
		return string("궁수");
	}
}

void CPlayer::BasicStateUpdate(int _message)
{
	switch (_message)
	{
	case 1:	// 탐색
		SearchUpdate(_message);
		break;
	case 2:	// 휴식
		RestUpdate(_message);
		break;
	case 3: // 다음 지역
		NextArea(_message);
		break;
	case 4:	// 상점
		StoreUpdate(_message);
		break;
	}
}

void CPlayer::CombatStateUpdate(const int _message)
{
	switch (_message)
	{
	case 1:	// 공격
		// 플레이어가 공격
		PlayerATK();
		// 몬스터가 공격
		MonsterATK();
		break;
		
	case 2: // 방어
		mCombatMode = ePlayerCombatMode::Defense;
		break;

	case 3: // 도망
		// 보스전은 도망불가능
		if (mCombatMode == ePlayerCombatMode::Boss)
		{
			COUTN("보스전은 도망갈 수 없다!");
			SYSPAUSE;
		}
		else
		{
			// 50퍼 확률도 도망
			CombatRun();
		}
		break;
	}
}

void CPlayer::SearchUpdate(int _message)
{
	// 나중에 함수화

	// 탐색중입니다.
	COUTN("탐색 중입니다.");
	// 3초정도 뜸들이기
	SLEEP_N(3);

	// 랜덤하게 탐색
	int behavior = 0;
	behavior = (rand() % (int)eEventType::MAX);

	// 랜덤으로 돈 증가
	int RandomMoney = rand() % 50 + 1;

	/*
		1. 아무것도 못 찾음
		2. 몬스터 조우
		3. 보물 찾기
		4. 다음 층 이동
	*/
	switch ((eEventType)behavior)
	{
	case eEventType::Tresure:
		// 보물을 찾았습니다.
		COUTN("");
		COUTN("보물을 찾았습니다!!!");
		// 골드(돈) 증가시키기
		COUTN(RandomMoney << "원을 획득하였습니다.");
		mMoney += RandomMoney;
		SYSPAUSE;
		break;

	case eEventType::Enemy:
		// 적을 생성시켜준다.
		// 이미 몬스터가 있어?
		if (CGameManager::GetInst()->IsValidMonster())
		{
			assert(0);
			// 삭제하고
			// CGameManager::GetInst()->DeleteMonster();
			return; // 위에 코드랑 둘중 하나
		}

		// 몬스터를 만들어준다.
		CGameManager::GetInst()->CreateMonster();
		// 플레이어는 전투중 상태로 변경한다.
		mState = ePlayerState::combat;
		
		COUTN("");
		COUTN("적을 만났습니다!");
		SYSPAUSE;
		break;

	case eEventType::Mine:
		// 함정을 밟는다.
		COUTN("");
		COUTN("함정을 밟았습니다...");
		COUTN("체력이 10 감소됩니다.");
		SYSPAUSE;
		mHP -= 10;
		break;
	}
}

void CPlayer::RestUpdate(const int _message)
{
	int Rest = 0;

	COUTN("50원을 소모하여 체력 30을 회복하겠습니까?");
	COUT("[예 : 1, 아니요 : 2] : ");
	cin >> Rest;

	switch (Rest)
	{
	case 1:	// 체력 회복
		if (mMoney < 50)
		{
			COUTN("돈이 부족합니다.");
			SYSPAUSE;
			break;
		}
		else
		{
			mHP += 30;
			mMoney -= 50;
			if (mHP >= mMaxHP)
			{
				mHP = mMaxHP;
			}
			SLEEP_N(3);
			COUTN("50원을 소모하여 체력 30을 회복하였습니다!");
			SYSPAUSE;
			break;
		}
	case 2:	// 탐색으로 돌아가기
		COUTN("메인으로 돌아갑니다.");
		SYSPAUSE;
		break;
	default:
		COUTN("잘못 선택하였습니다.");
		SYSPAUSE;
	}
}

void CPlayer::NextArea(const int _message)
{
	// 다음 지역으로 이동
	int NextArea = 0;
	COUTN("보스를 처치 후 다음 지역으로 이동하겠습니까? (보스전은 도망갈 수 없다) [충분히 강해진 후 추천] ");
	COUT("[예 : 1, 아니요 : 2] : ")
	cin >> NextArea;
	switch (NextArea)
	{
	case 1:
		if (CGameManager::GetInst()->IsValidMonster())
		{
			assert(0);
			// 삭제하고
			return;
		}
		// 보스를 만들어준다.
		CGameManager::GetInst()->CreateBoss();
		// 플레이너는 전투중 상태로 변경한다.
		mState = ePlayerState::combat;
		mCombatMode = ePlayerCombatMode::Boss;

		COUTN("");
		COUTN("보스가 나타났습니다.");
		SYSPAUSE;
		break;
	case 2:
		COUTN("좀 더 강해진 후에 도전하자.");
		SYSPAUSE;
		break;
	default:
		COUTN("잘못 선택하였습니다.");
		SYSPAUSE;
		break;
	}
}

void CPlayer::StoreUpdate(const int _message)
{
	SYSCLS;
	// 아이템 번호
	int ItemNum = 0;
	PlayerStoreDraw();

	COUTN("");
	COUTN("상점에 오신걸 환영합니다!");
	COUT("구매할 아이템 번호를 입력하세요(취소 : 0) : ");
	cin >> ItemNum;

	switch (ItemNum)
	{
	case 0:
		COUTN("");
		COUTN("메인으로 돌아갑니다.");
		SYSPAUSE;
		break;
	case 1:
		if (mMoney < 50)
		{
			COUTN("");
			COUTN("돈이 부족합니다.");
			SYSPAUSE;
		}
		else
		{
			COUTN("");
			COUTN("공격 물약을 구매하였습니다! 공격력 + 1");
			mATK++;
			mMoney -= 50;
			SYSPAUSE;
		}
		break;
	case 2:
		if (mMoney < 50)
		{
			COUTN("");
			COUTN("돈이 부족합니다.");
			SYSPAUSE;
		}
		else
		{
			COUTN("");
			COUTN("방어 물약을 구매하였습니다! 방어력 + 1");
			mDEF++;
			mMoney -= 50;
			SYSPAUSE;
		}
		break;
	case 3:
		if (mMoney < 50)
		{
			COUTN("");
			COUTN("돈이 부족합니다.");
			SYSPAUSE;
		}
		else
		{
			COUTN("");
			COUTN("최대 체력 물약을 구매하였습니다! 최대 체력 + 15");
			mMaxHP += 15;
			mHP += 15;
			mMoney -= 50;
			SYSPAUSE;
		}
		break;
	case 4:
		if (mMoney < 50)
		{
			COUTN("");
			COUTN("돈이 부족합니다.");
			SYSPAUSE;
		}
		else
		{
			COUTN("");
			COUTN("경험치 물약을 구매하였습니다! 경험치 + 30");
			mExp += 30;
			mMoney -= 50;

			if (mExp >= mMaxExp)
			{
				PlayerLevelUp();
			}
			SYSPAUSE;
		}
		break;
	default:
		COUTN("");
		COUTN("잘못된 아이템 번호입니다.");
		SYSPAUSE;
	}
}

void CPlayer::PlayerATK()
{
	CGameManager* GameMgr = CGameManager::GetInst();
	CMonster* pMonster = GameMgr->GetMonster();

	// 최소 1 데미지
	int MinDamage = 1;

	// 플레이어 공격
	if (mHP > 0)
	{
		int MonsterDEF = pMonster->GetDEF();
		int PlayerATK = rand() % mATK + 1;

		// 공격력의 반이상 수치값만 공격
		while (PlayerATK <= (mATK / 2))
		{
			PlayerATK = rand() % mATK + 1;
		}

		// 음수방지
		if ((PlayerATK - MonsterDEF) <= 0)
		{
			// 플레이어가 몬스터 공격
			pMonster->TakeDamage(MinDamage);
			Sleep(1000);
			COUTN(pMonster->GetName() << "의 방어력 " << MonsterDEF << " 만큼 감소한 데미지 "
				<< FONTCOLOR_RED << MinDamage << FONTCOLOR_REST << "를 " << mName << "이 " << pMonster->GetName() <<"에게 입혔습니다.");
		}
		else
		{
			// 플레이어가 몬스터 공격
			pMonster->TakeDamage(PlayerATK - MonsterDEF);
			Sleep(1000);
			COUTN(pMonster->GetName() << "의 방어력 " << MonsterDEF << " 만큼 감소한 데미지 "
				<< FONTCOLOR_RED << PlayerATK - MonsterDEF << FONTCOLOR_REST << "를 " << mName << "이 " << pMonster->GetName() << "에게 입혔습니다.");
		}
	}
}

void CPlayer::MonsterATK()
{
	CGameManager* GameMgr = CGameManager::GetInst();
	CMonster* pMonster = GameMgr->GetMonster();

	// 최소 1 데미지
	int MinDamage = 1;

	// 몬스터 공격력 가져오기
	int MonsterATK = pMonster->GetATK();
	int RandMonATK = rand() % MonsterATK + 1;

	// 만약 몬스터가 살아있다면
	if (pMonster->GetHP() > 0)
	{
		// 공격력의 반이상 수치값만 공격
		while (RandMonATK <= (MonsterATK / 2))
		{
			RandMonATK = rand() % MonsterATK + 1;
		}

		// 음수 방지
		if ((RandMonATK - mDEF) <= 0)
		{
			TakeDamage(MinDamage);
			Sleep(1000);
			COUTN(mName << "의 방어력 " << mDEF << " 만큼 감소한 데미지 "
				<< FONTCOLOR_RED << MinDamage << FONTCOLOR_REST << "를 " << pMonster->GetName() << "이 " << mName << "에게 입혔습니다.");
		}
		else
		{
			// 몬스터가 플레이어 공격
			TakeDamage(RandMonATK - mDEF);
			Sleep(1000);
			COUTN(mName << "의 방어력 " << mDEF << " 만큼 감소한 데미지 "
				<< FONTCOLOR_RED << RandMonATK - mDEF << FONTCOLOR_REST << "를 " << pMonster->GetName() <<"이 " << mName << "에게 입혔습니다.");
		}

		SYSPAUSE;
	}
	else
	{
		// 전투가 끝났다
		CombatEnd();
	}
}

void CPlayer::CombatRun()
{
	CGameManager* GameMgr = CGameManager::GetInst();
	CMonster* pMonster = GameMgr->GetMonster();

	int escape = rand() % 100;
	if (escape >= 50)
	{
		SLEEP_N(2);
		COUTN("도망치는데 성공했습니다!");

		SYSPAUSE;
		mState = ePlayerState::search;

		// 몬스터를 지워준다
		GameMgr->DeleteMonster();
	}
	else
	{
		SLEEP_N(2);
		COUTN("도망치는데 실패했습니다!");
		MonsterATK();
	}
}

void CPlayer::CombatEnd()
{
	CGameManager* GameMgr = CGameManager::GetInst();
	CMonster* pMonster = GameMgr->GetMonster();

	int MonsterEXP = pMonster->GetExp();
	int MonsterMoney = pMonster->GetMoney();

	COUTN("");
	IsDead(pMonster->GetName(), pMonster->GetHP());
	COUTN("획득한 경험치 : " << MonsterEXP << " exp");
	COUTN("획득한 돈 : " << MonsterMoney << " 원");

	mExp += MonsterEXP;
	mMoney += MonsterMoney;

	if (mExp >= mMaxExp)
	{
		PlayerLevelUp();
	}

	SYSPAUSE;
	mState = ePlayerState::search;

	// 몬스터를 지워준다
	GameMgr->DeleteMonster();

	// 보스전이 끝났다면
	if (mCombatMode == ePlayerCombatMode::Boss)
	{
		mCombatMode = ePlayerCombatMode::None;
		GameMgr->NextStage();
	}
}

void CPlayer::PlayerLevelUp()
{
	int UpHP = 20;
	int UpATK = 3;
	int UpDEF = 1;

	mExp = mExp - mMaxExp;
	mLevel += 1;
	mMaxExp += 20;
	mMaxHP += UpHP;
	mHP += UpHP;
	mATK += UpATK;
	mDEF += UpDEF;

	COUTN("");
	COUTN("레벨업!!!");
	COUTN(mLevel << " 레벨 달성");
	COUTN("최대 체력 상승 + " << UpHP);
	COUTN("공격력 상승 + " << UpATK);
	COUTN("방어력 상승 + " << UpDEF);
}
