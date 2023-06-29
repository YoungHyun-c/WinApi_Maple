#pragma once
#include "PlayActor.h"

enum class PlayerState
{
	Idle,
	Run,
	Jump,
	DoubleJump,
	Rope,
	Prone,
	Attack,
	ProneAttack,
	Max, // 일반적으로 사용하지 않는 값.
};

enum class PlayerDir
{
	Right,
	Left,
	Max,
};

// 설명 :
class Player : public PlayActor
{
private:
	static Player* MainPlayer;

public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}


public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;
	
	GameEngineRenderer* UIRenderer = nullptr;

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

	void ChangeState(PlayerState State);

	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Right;
	std::string CurState = "";
	std::string AnimationName = "";

	int TestValue = 0;

	static bool DebugMode;

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
	float4 LeftCheck = { -20.0f, -5.0f };
	float4 RightCheck = { 20.0f, -5.0f };

	float4 GroundCheck = { 0.0f, 30.0f };
	float4 RopeCheck = { 0.0f, 10.0f };
	float4 PotalCheck = { 0.0f, 10.0f };

	//////////////////////
	//bool	M_Skill; // 스킬
	//bool	M_Item;	 // 아이템
	///// 보류

	//////////////////////
	bool Jump;
	bool DoubleJump;

};

