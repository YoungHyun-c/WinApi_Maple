#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class StoneState
{
	Ready,			
	Attack,	
	Down,			
	Max,
};

// 설명 :
class StoneDrop : public PlayActor
{
private:
	static StoneDrop* MainStone;

public:
	static StoneDrop* GetMainStone()
	{
		return MainStone;
	}
	// constructer destructer
	StoneDrop();
	~StoneDrop();

	// delete Function
	StoneDrop(const StoneDrop& _Other) = delete;
	StoneDrop(StoneDrop&& _Other) noexcept = delete;
	StoneDrop& operator = (const StoneDrop& _Other) = delete;
	StoneDrop& operator = (StoneDrop&& _Other) noexcept = delete;

protected:
	void StateUpdate(float _Delta);

	void ReadyStart();
	void ReadyUpdate(float _Delta);

	void DownStart();
	void DownUpdate(float _Delta);

	void ChangeState(StoneState State);

	void ChangeAnimationState(const std::string& _StateName);

private:
	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;

	// 벨룸 종유석 상태 관하여
	GameEngineRenderer* StonDrop = nullptr;
	StoneState State = StoneState::Max;
	std::string CurState = "";
	std::string AnimationName;

	float BS_FWakeTime = 0.0f;
	float BS_FWakeLimitTime = 3.5f;
	float BS_FDownTime = 0.0f;
	float BS_FDownLimitTime = 8.0f;
	float BellomStoneSavePosX = 0.0f;
	bool BellomStoneSummon = false;

	////////////////////// DebugValue
	float4 CheckPos = float4::ZERO;

};

