#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class MonsterState
{
	Idle,
	Run,
	Death,
	Attack,
	Max, // 일반적으로 사용하지 않는 값.
};

enum class MonsterDir
{
	Right,
	Left,
	Max,
};

// 설명 :
class Monster : public PlayActor
{
private:
	static std::list<Monster*> AllMonster;

public:
	static Monster* BlueSnailMonster;
	static void AllMonsterDeath();
	// constructer destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator = (const Monster& _Other) = delete;
	Monster& operator = (Monster&& _Other) noexcept = delete;

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
	MonsterDir Dir = MonsterDir::Right;
	std::string CurState = "";
	std::string AnimationName;

	float M_FMoveTime = 0.0f;
	float M_FMoveLimitTime = 5.0f;
	float M_FStopTime = 0.0f;
	float M_FStopLimitTime = 3.5f;
	int idx = rand() % 2;

	GameEngineRenderer* BlueSnailRenderer = nullptr;
	GameEngineCollision* BodyCollsion = nullptr;
	GameEngineCollision* MonsterBodyCol = nullptr;

	std::vector<GameEngineCollision*> _Col;

	void DirCheck();

	void ChangeAnimationState(const std::string& _StateName);

private:

	//void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	float BlueSnailX = { 300.0f };
	float BlueSnailY = { 300.0f };

	////////////////////// DebugValue
	float4 LeftCheck = { -18.0f, 0.0f };
	float4 RightCheck = { 18.0f, 0.0f };
	
	float Speed = 30.0f;
	
	float4 BlueSnailMovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	bool MonsterStatus = false;

};