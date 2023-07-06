#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class TailState
{
	Ready,			//Ready
	Down,			//GroundIn
	AttackReady,	//Ready
	Death,			//Die
	Max,
};


// 설명 :
class BellomTail : public PlayActor
{
private:
	static BellomTail* MainTail;

public:
	static BellomTail* GetMainTail()
	{
		return MainTail;
	}
	// constructer destructer
	BellomTail();
	~BellomTail();

	// delete Function
	BellomTail(const BellomTail& _Other) = delete;
	BellomTail(BellomTail&& _Other) noexcept = delete;
	BellomTail& operator = (const BellomTail& _Other) = delete;
	BellomTail& operator = (BellomTail&& _Other) noexcept = delete;

protected:
	void StateUpdate(float _Delta);

	void ReadyStart();
	void ReadyUpdate(float _Delta);

	void DownStart();
	void DownUpdate(float _Delta);

	void ChangeState(TailState State);

	void ChangeAnimationState(const std::string& _StateName);

private:
	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;

	// 벨룸꼬리 상태 관하여
	GameEngineRenderer* BellomTails = nullptr;
	TailState State = TailState::Max;
	std::string CurState = "";
	std::string AnimationName;

	float BT_FWakeTime = 0.0f;
	float BT_FWakeLimitTime = 3.4f;
	float BT_FDownTime = 0.0f;
	float BT_FDownLimitTime = 10.0f;
	float BellomTailesSavePosX = 0.0f;
	bool BellomTailSummon = false;

	////////////////////// DebugValue
	float4 CheckPos = float4::ZERO;
};

