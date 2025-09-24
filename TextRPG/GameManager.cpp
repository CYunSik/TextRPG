#include "GameManager.h"
#include "Player.h"
#include "Monster.h"

CGameManager::CGameManager()
{
	// 생성자
	mPlayer = nullptr;
}

CGameManager::~CGameManager()
{
	// 소멸자
}

// 게임시작
void CGameManager::GameRun()
{
	// 게임 시작을 알리고 싶다.
	// 게임 초기화 Init
	if (!Init())
	{
		assert(0);
	}

	// 게임 종료전까지 반복 while
	while (IsGameOver())
	{
		// 게임 그려주기 Draw
		Draw();
		// 입력을 마지막에 해준다.
		Input();
		// 게임 로직 업데이트 Update
		Update();
	}
	// 게임 끝 해제해주기 Release
	Release();
}

void CGameManager::NextStage()
{
	// 다음지역으로 증가
	mAreaName = static_cast<eAreaName>(static_cast<int>(mAreaName) + 1);

	// 미리 컴파일된 헤더에서 함수 호출
	GlobalFunc::PrintUpFloor(); // 문열리기 연출
}

bool CGameManager::CreateMonster()
{
	// 몬스터를 랜덤하게 생성시켜주는 함수
	mMonster = new CMonster();
	mMonster->SetAreaNameType(mAreaName);
	mMonster->Init();
	if (mMonster == nullptr)
	{
		assert(0);
		return false;
	}
	return true;
}

bool CGameManager::CreateBoss()
{
	mMonster = new CMonster();
	mMonster->SetAreaNameType(mAreaName);
	mMonster->InitBoss();
	if (mMonster == nullptr)
	{
		assert(0);
		return false;
	}

	return true;
}

// 몬스터가 있는지
bool CGameManager::IsValidMonster()
{
	if (mMonster)
	{
		return true;
	}

	return false;
}

// 몬스터 삭제
void CGameManager::DeleteMonster()
{
	if (mMonster)
	{
		delete mMonster;
		mMonster = nullptr;
	}
}

bool CGameManager::IsGameOver()
{
	if (mPlayer == nullptr)
	{
		return false;
	}

	int PlayerHP = mPlayer->GetHP();
	if (PlayerHP <= 0)
	{
		COUTN("");
		COUTN("플레이어 [" << mPlayer->GetName() <<"]이 죽었습니다!");
		COUTN("Game Over!");
		return false;
	}
	else
	{
		return true;
	}
}

string CGameManager::AreaNameToString(eAreaName _areaname)
{
	switch (_areaname)
	{
	case eAreaName::Forest:
		return "모험의 숲";
	case eAreaName::Rival:
		return "성장의 강";
	case eAreaName::Mountaion:
		return "강자의 산";
	case eAreaName::Hell:
		return "지옥";
	}

	return string();
}

bool CGameManager::Init()
{
	// 난수 초기화 -> 현재 시간으로 난수 발생기를 초기화 한다.
	srand((unsigned int)time(0));

	// 게임 초기화 시작
	// 플레이어 생성
	mPlayer = new CPlayer;
	if (mPlayer == nullptr)
	{
		assert(0);
		return false;
	}
	// 플레이어 초기화
	mPlayer->Init();

	return true;
}

void CGameManager::GameProgress()
{
	COUTN("----------------- 멸망의 지역 ---------------");
	COUTN("                                           ");
	COUTN("                   " << AreaNameToString(mAreaName));
	COUTN("                                           ");
	COUTN("---------------------------------------------");
}

void CGameManager::Update()
{
	if (mPlayer)
	{
		mPlayer->Update();
	}
}

void CGameManager::Draw()
{
	// 화면 초기화
	SYSCLS;

	// 지금 게임이 어느 지역에서 진행되고 있는지 출력해준다.
	GameProgress();

	if (mMonster)
	{
		mMonster->Draw();
	}
	// 항상 nullptr 체크하는 버릇은 좋은거다
	// 실수방지
	if (mPlayer)
	{
		mPlayer->Draw();
	}

}

void CGameManager::Release()
{
	// 게임 종료
	// 플레이어 해제
	if (mPlayer)
	{
		delete mPlayer;
		mPlayer = nullptr;
	}
	// 종료되면 몬스터도 종료한다.
	if (mMonster)
	{
		delete mMonster;
		mMonster = nullptr;
	}
}

void CGameManager::Input()
{
	COUTN("---------------------------------------------");
	COUT("행동을 선택해 주세요 : ");
	std::cin >> mInputMessage;
	// SYSPAUSE;
	COUTN("---------------------------------------------");
}

