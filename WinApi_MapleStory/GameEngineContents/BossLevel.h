#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class BossLevel : public GameEngineLevel
{
public:
	// constructer destructer
	BossLevel();
	~BossLevel();

	// delete Function
	BossLevel(const BossLevel& _Other) = delete;
	BossLevel(BossLevel&& _Other) noexcept = delete;
	BossLevel& operator = (const BossLevel& _Other) = delete;
	BossLevel& operator = (BossLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;

	class BackGround* BackGroundPtr;
	class Player* LevelPlayer = nullptr;

	float SummonTime = 0.0f;
	float SummonLimitTime = 8.0f;
	float MoveTime = 0.0f;
	float MoveLimitTime = 2.0f;
	int TailsCount = 0;

	float NextMoveTime = 0.0f;
	float NextLevelTime = 2.0f;

	GameEngineSoundPlayer BGMPlayer;
};

