#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class BossState
{
	Summon,
	Idle,			//Wake
	Ready,			//Ready
	Wake,			//Wake
	Down,			//GroundIn
	AttackReady,	//Ready
	AttackBall,		//Ball
	AttackBallBomb,	//BallBomb
	Death,			//Die
	Max,
};

// 설명 :
class BellomBoss : public PlayActor
{
private:
	static BellomBoss* MainBoss;

public:
	static BellomBoss* GetMainBoss()
	{
		return MainBoss;
	}

public:
	// constructer destructer
	BellomBoss();
	~BellomBoss();

	// delete Function
	BellomBoss(const BellomBoss& _Other) = delete;
	BellomBoss(BellomBoss&& _Other) noexcept = delete;
	BellomBoss& operator = (const BellomBoss& _Other) = delete;
	BellomBoss& operator = (BellomBoss&& _Other) noexcept = delete;

	static bool BellomSummoner()
	{
		return Summon;
	}

	void SetMainBossHp(float _Value)
	{
		BellomBossHp = _Value;
	}

	void GetMainBossHP(float _Value)
	{
		BellomBossHp -= _Value;
	}

	float GetMainBossHpValue()
	{
		return BellomBossHp;
	}

	float GetMainBossHpBarMove()
	{
		return BossHpBarX -= 35.0f;
	}

	float GetMainBossHpBar()
	{
		return BossHpBarX;
	}

protected:
	void StateUpdate(float _Delta);

	void SummonStart();
	void SummonUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void ReadyStart();
	void ReadyUpdate(float _Delta);

	void DownStart();
	void DownUpdate(float _Delta);

	void WakeStart();
	void WakeUpdate(float _Delta);

	void AttackReadyStart();
	void AttackReadyUpdate(float _Delta);

	void AttackBallStart();
	void AttackBallUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);

	void ChangeState(BossState State);


	void ChangeAnimationState(const std::string& _StateName);

private:
	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// 벨룸 상태 관하여
	GameEngineRenderer* Bellom = nullptr;
	GameEngineCollision* BellomBody = nullptr;
	GameEngineCollision* BellomSummon = nullptr;
	int AttackCount = 0;
	float MoveTime = 0.0f;
	static bool Summon;
	float BellomBossHp = 1410.0f;
	float BossHpBarX = 582.5f;

	BossState State = BossState::Max;
	std::string CurState = "";
	std::string AnimationName;

	float B_FWakeTime = 0.0f;
	float B_FWakeLimitTime = 4.0f;
	float B_FDownTime = 0.0f;
	float b_FDownLimitTime = 3.0f;
	float DeathTime = 0.0f;
	float DeathLimitTime = 4.5f;
	int Attack = 0;
	int AttackCheck = 0;

	float BellomSaveAttackPosX = 0.0f;
	float BellomAttackReadyPosX = 0.0f;
	float BellomAttackPosX = 0.0f;
	float BellomAttackBallPosX = 0.0f;

	////////////////////// DebugValue
	float4 LeftCheck = { -40.0f, 0.0f };
	float4 RightCheck = { 40.0f, 0.0f };

	float Speed = 30.0f;

	float4 BlueSnailMovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	bool MonsterStatus = false;
	bool BossStop = false;
};

