#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MonsterState
{
	Idle,
	Run,
	Jump,
	DoubleJump,
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
class Monster : public GameEngineActor
{
private:
	static std::list<Monster*> AllMonster;

public:
	static void AllMonsterDeath();
	// constructer destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator = (const Monster& _Other) = delete;
	Monster& operator = (Monster&& _Other) noexcept = delete;

	GameEngineRenderer* BlueSnailRenderer = nullptr;

	//GameEngineRenderer*  = nullptr;
	GameEngineRenderer* Ptr = nullptr;

protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	// 클래스로 만들어도 되고.
	void JumpStart();
	void JumpUpdate(float _Delta);

	void DoubleJumpStart();
	void DoubleJumpUpdate(float _Delta);

	void ProneStart();
	void ProneUpdate(float _Delta);

	void RopeStart();
	void RopeUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void ProneAttackStart();
	void ProneAttackUpdate(float _Delta);

	void ChangeState(MonsterState State);

	MonsterState State = MonsterState::Max;
	MonsterDir Dir = MonsterDir::Right;
	std::string CurState = "";

	float M_FMoveTime = 0.0f;
	float M_FMoveLimitTime = 0.0f;
	float M_FStopTime = 3.5f;

	GameEngineCollision* BodyCollsion = nullptr;

	void DirCheck();

	void ChangeAnimationState(const std::string& _StateName);

private:

	//void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	//void Render(float _Delta) override;

	float BlueSnailX = { 300.0f };
	float BlueSnailY = { 300.0f };
	float4 BlueSnailMovePos = float4::ZERO;

	////////////////////// DebugValue
	float4 LeftCheck = { -20.0f, -15.0f };
	float4 RightCheck = { 20.0f, -15.0f };

	float4 GroundCheck = { 0.0f, 30.0f };
	float4 RopeCheck = { 0.0f, 10.0f };
	float4 PotalCheck = { 0.0f, 10.0f };

	//////////////////////
	bool Jump;
	bool DoubleJump;

};