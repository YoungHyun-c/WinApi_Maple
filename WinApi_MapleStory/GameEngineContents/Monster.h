#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class MonsterState
{
	Idle,
	Run,
	Jump,
	DoubleJump,
	Attack,
	Max, // �Ϲ������� ������� �ʴ� ��.
};

enum class MonsterDir
{
	Right,
	Left,
	Max,
};

// ���� :
class Monster : public GameEngineActor
{
private:
	static std::list<Monster*> AllMonster;

public:
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

protected:
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	// Ŭ������ ���� �ǰ�.
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

	int TestValue = 0;

	GameEngineCollision* BodyCollsion = nullptr;

	void DirCheck();

	void ChangeAnimationState(const std::string& _StateName);

private:
	static int BackGroundSizeforCamX;
	static int BackGroundSizeforCamY;


	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	////////////////////// DebugValue
	float4 LeftCheck = { -20.0f, -15.0f };
	float4 RightCheck = { 20.0f, -15.0f };

	float4 GroundCheck = { 0.0f, 30.0f };
	float4 RopeCheck = { 0.0f, 10.0f };
	float4 PotalCheck = { 0.0f, 10.0f };

	//////////////////////
	//bool	M_Skill; // ��ų
	//bool	M_Item;	 // ������
	///// ����

	//////////////////////
	bool Jump;
	bool DoubleJump;

};