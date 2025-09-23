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
	printf("\n");
	printf("  ████   ████  ████   ████  ████   ████  ████   ████\n");
	printf("  █  █   █  █  █  █   █  █  █  █   █  █  █  █   █  █\n");
	printf("  █  █   █  █  █  █   █  █  █  █   █  █  █  █   █  █\n");
	printf("  █  █   █  █  █  █   █  █  █  █   █  █  █  █   █  █\n");
	printf("  ████   ████  ████   ████  ████   ████  ████   ████\n");
	printf("\n");
	printf("      ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ\n");
	printf("      ㅁ                                    ㅁ\n");
	printf("      ㅁ         멸  망  의   지 역         ㅁ\n");
	printf("      ㅁ                                    ㅁ\n");
	printf("      ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ\n");

	// 플레이어 이름 받기
	COUT("이름을 입력해주세요 : ");
	cin >> mName;

	// 직업 선택하기
	int selectJob = 0;
	do
	{
		COUTN("직업을 선택해주세요.");
		COUTN("1.전사 2.마법사 3.도적 4.궁수");
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
	COUTN("--------------- 플레이어 정보 ---------------");
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
	COUTN("\t|       [1] 공격   [2] 도망      |");
	COUTN("\t==================================");
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
		break;
	}
}

void CPlayer::CombatStateUpdate(const int _message)
{
	// 0 데미지
	int ZeroDamage = 0;
	switch (_message)
	{
	case 1:	// 공격
		// 플레이어 공격
		if (CGameManager::GetInst()->GetPlayer()->PlayerIsAlive())
		{
			int MonsterDEF = CGameManager::GetInst()->GetMonster()->GetDEF();
			int PlayerATK = rand() % mATK + 1;

			// 공격력의 반이상 수치값만 공격
			while (PlayerATK <= (mATK / 2))
			{
				PlayerATK = rand() % mATK + 1;
			}
			// 플레이어가 몬스터 공격
			CGameManager::GetInst()->GetMonster()->TakeDamage(PlayerATK - MonsterDEF);

			if ((PlayerATK - MonsterDEF) <= 0)
			{
				Sleep(1000);
				COUTN("몬스터의 방어력 " << MonsterDEF << " 만큼 감소한 데미지 "
					<< FONTCOLOR_RED << ZeroDamage << FONTCOLOR_REST << "를 플레이어가 몬스터에게 입혔습니다.");
			}
			else
			{
				Sleep(1000);
				COUTN("몬스터의 방어력 " << MonsterDEF << " 만큼 감소한 데미지 "
					<< FONTCOLOR_RED << PlayerATK - MonsterDEF << FONTCOLOR_REST  << "를 플레이어가 몬스터에게 입혔습니다.");
			}
		}

		// 만약 몬스터가 살아있다면
		if (CGameManager::GetInst()->GetMonster()->MonsterIsAlive())
		{
			int MonsterATK = CGameManager::GetInst()->GetMonster()->GetATK();
			int RandMonATK = rand() % MonsterATK + 1;

			// 공격력의 반이상 수치값만 공격
			while (RandMonATK <= (MonsterATK / 2))
			{
				RandMonATK = rand() % MonsterATK + 1;
			}

			// 몬스터가 플레이어 공격
			TakeDamage(RandMonATK - mDEF);

			if ((RandMonATK - mDEF) <= 0)
			{
				Sleep(1000);
				COUTN("플레이어의 방어력 " << mDEF << " 만큼 감소한 데미지 "
					<< FONTCOLOR_RED << ZeroDamage << FONTCOLOR_REST << "를 몬스터가 플레이어에게 입혔습니다.");
			}
			else
			{
				Sleep(1000);
				COUTN("플레이어의 방어력 " << mDEF << " 만큼 감소한 데미지 "
					<< FONTCOLOR_RED << RandMonATK - mDEF << FONTCOLOR_REST << "를 몬스터가 플레이어에게 입혔습니다.");
			}

			SYSPAUSE;
		}
		else
		{
			int MonsterEXP = CGameManager::GetInst()->GetMonster()->GetExp();
			int MonsterMoney = CGameManager::GetInst()->GetMonster()->GetMoney();

			COUTN("");
			COUTN("몬스터를 죽였습니다!");
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
			CGameManager::GetInst()->DeleteMonster();
		}
		
		break;

	case 2: // 도망
		int escape = rand() % 100;
		if (escape >= 50)
		{
			COUTN("도망치는데 성공했습니다!");

			SYSPAUSE;
			mState = ePlayerState::search;

			// 몬스터를 지워준다
			CGameManager::GetInst()->DeleteMonster();
		}
		else
		{
			COUTN("도망치는데 실패했습니다!");
			// 만약 몬스터가 살아있다면
			if (CGameManager::GetInst()->GetMonster()->MonsterIsAlive())
			{
				int MonsterATK = CGameManager::GetInst()->GetMonster()->GetATK();
				int RandMonATK = rand() % MonsterATK + 1;

				// 공격력의 반이상 수치값만 공격
				while (RandMonATK <= (MonsterATK / 2))
				{
					RandMonATK = rand() % MonsterATK + 1;
				}

				// 몬스터가 플레이어 공격
				TakeDamage(RandMonATK - mDEF);

				if ((RandMonATK - mDEF) <= 0)
				{
					Sleep(1000);
					COUTN("플레이어의 방어력 " << mDEF << " 만큼 감소한 데미지 " << ZeroDamage << "를 몬스터가 플레이어에게 입혔습니다.");
				}
				else
				{
					Sleep(1000);
					COUTN("플레이어의 방어력 " << mDEF << " 만큼 감소한 데미지 " << RandMonATK - mDEF << "를 몬스터가 플레이어에게 입혔습니다.");
				}

				SYSPAUSE;
			}
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
	SLEEP3;

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
		COUTN(RandomMoney << "원을 찾았습니다!!!");
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
		// 플레이너는 전투중 상태로 변경한다.
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

	COUT("50원을 소모하여 체력 30을 회복하겠습니까? (예 : 1, 아니요 : 2) ");
	cin >> Rest;

	switch (Rest)
	{
	case 1:	// 체력 회복
		if (mMoney < 50)
		{
			COUTN("골드가 부족합니다.");
		}
		else
		{
			mHP += 30;
			mMoney -= 50;
			if (mHP >= mMaxHP)
			{
				mHP = mMaxHP;
			}
			SLEEP3;
			COUTN("50원을 소모하여 체력 30을 회복하였습니다!");
			SYSPAUSE;
			break;
		}
	case 2:	// 탐색으로 돌아가기
		COUTN("탐색으로 돌아갑니다.");
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
	COUTN("다음 지역으로 이동하겠습니까? (예 : 1, 아니요 : 2) [충분히 강해진 후 추천] ");
	cin >> NextArea;
	switch (NextArea)
	{
	case 1:
		CGameManager::GetInst()->NextStage();
		SYSPAUSE;
		break;
	case 2:
		COUTN("좀더 강해진 후에 가자.");
		SYSPAUSE;
		break;
	default:
		COUTN("잘못 선택하였습니다.");
		SYSPAUSE;
		break;
	}
}

bool CPlayer::PlayerIsAlive()
{
	if (mHP <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CPlayer::PlayerLevelUp()
{
	int UpHP = 20;
	int UpATK = 3;
	int UpDEF = 1;

	mExp = mExp - mMaxExp;
	mLevel += 1;
	mMaxExp += 10;
	mMaxHP += UpHP;
	mHP += UpHP;
	mATK += UpATK;
	mDEF += UpDEF;


	COUTN("");
	COUTN("레벨업!!!");
	COUTN(mLevel << " 레벨 달성");
	COUTN("체력 상승 +" << UpHP);
	COUTN("공격력 상승 +" << UpATK);
	COUTN("방어력 상승 +" << UpDEF);
}
