#pragma once
#include "GameInfo.h"

class CGameManager
{
private:
	class CPlayer* mPlayer = nullptr;

	class CMonster* mMonster = nullptr;

	ePlayerCombatMode BossState;

	// 지역 이름
	eAreaName mAreaName;
	static string AreaNameToString(eAreaName _areaname);

	int mInputMessage = 0;

private:
	// 게임 초기화 Init
	bool Init();

	// 게임 진행도
	void GameProgress();

	// 게임 로직 업데이트 Update
	void Update();
	// 게임 그려주기 Draw
	void Draw();
	// 게임 끝 해제해주기 Release
	void Release();
	// 입력받기
	void Input();

public:
	void GameRun();

	int GetInputMessage()
	{
		return mInputMessage;
	}

	// 다음 층으로 이동
	void NextStage();

#pragma region Monster
	// 몬스터를 발견했다.
	// 몬스터를 랜덤하게 생성시켜주는 함수
	bool CreateMonster();
	// 보스몬스터 생성
	bool CreateBoss();

	bool IsValidMonster();
	void DeleteMonster();

	CMonster* GetMonster() { return mMonster; }
#pragma endregion

	CPlayer* GetPlayer() { return mPlayer; }

	bool IsGameOver();

private:
	// 싱글톤
	DECLARE_SINGLETON(CGameManager)

};

