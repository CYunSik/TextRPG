#pragma once
#include "Object.h"

class CPlayer : public CObject
{
private:
	ePlayerState mState;

public:
	CPlayer();
	virtual ~CPlayer() override;

	// 나누는게 좋다. 보기 좋아서 생성자와 함수 구분
public:
	virtual bool Init() override;
	virtual void Draw() override;
	virtual void Update() override;

private:
	// 플레이어 정보
	void PlayerInfoDraw();
	// 플레이어 탐색 상태 상태창
	void PlayerSearchDraw() const;
	// 플레이어 전투 상태 상태창
	void PlayerCombatDraw() const;
	// 숫자 입력받은거 문자로 직업 이름 바꿔주기
	string JobToString(const eJobClass& _job);

	// 일반 상태
	void BasicStateUpdate(const int _message);
	// 전투상태
	void CombatStateUpdate(const int _message);
	// 일반 상태에서 탐색했을때
	void SearchUpdate(const int _message);
	// 일반 상태에서 휴식했을때
	void RestUpdate(const int _message);
	// 일반 상태에서 다음 지역으로 넘어가기
	void NextArea(const int _message);
	// 플레이어가 죽었는지
	bool PlayerIsAlive();

	// 플레이어 레벨업
	void PlayerLevelUp();
};

