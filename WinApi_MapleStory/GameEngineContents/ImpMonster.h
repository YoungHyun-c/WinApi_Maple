#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>
#include "Monster.h"


// Ό³Έν :
class ImpMonster : public PlayActor
{
private:
	static std::list<ImpMonster*> AllMonster;

public:
	static void AllMonsterDeath();
	// constructer destructer
	ImpMonster();
	~ImpMonster();

	// delete Function
	ImpMonster(const ImpMonster& _Other) = delete;
	ImpMonster(ImpMonster&& _Other) noexcept = delete;
	ImpMonster& operator = (const ImpMonster& _Other) = delete;
	ImpMonster& operator = (ImpMonster&& _Other) noexcept = delete;

protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void ChangeState(MonsterState State);

	MonsterState State = MonsterState::Max;
	MonsterDir Dir = MonsterDir::Left;
	std::string CurState = "";
	std::string AnimationName;

	float M_FMoveTime = 0.0f;
	float M_FMoveLimitTime = 4.0f;
	float M_FStopTime = 0.0f;
	float M_FStopLimitTime = 1.0f;
	int idx = rand() % 2;

	GameEngineRenderer* ImpMonsterRenderer = nullptr;
	GameEngineCollision* ImpBodyCollision = nullptr;
	GameEngineCollision* ImpLeftAttackCollision = nullptr;
	GameEngineCollision* ImpRightAttackCollision = nullptr;

	void DirCheck();

	void ChangeAnimationState(const std::string& _StateName);

private:

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	float ImpX = { 300.0f };
	float ImpY = { 300.0f };

	////////////////////// DebugValue
	float4 LeftCheck = { -40.0f, 0.0f };
	float4 RightCheck = { 40.0f, 0.0f };

	float4 LeftAttackCheckTop = { -120.0f, 50.0f };
	float4 LeftAttackCheckBot = { -120.0f, -50.0f };

	float4 RightAttackCheckTop = { 120.0f, 50.0f };
	float4 RightAttackCheckBot = { 120.0f, -50.0f };
	
	float4 LeftAttackCheck = { -120.0f, 0.0f };
	float4 RightAttackCheck = { 120.0f, 0.0f };

	float4 ImpCollisionPosL = { 20, 0 };
	float4 ImpCollisionPosR = { -20, 0 };

	float Speed = 80.0f;
	bool WallCheck = false;
	bool ImpDeath = false;

	float4 IMPMovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	bool MonsterStatus = false;
	bool MonsterLeftAttack = false;
	bool MonsterRightAttack = false;

};

