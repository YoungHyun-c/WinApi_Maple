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
	int StoneCount = 0;

	float NextMoveTime = 0.0f;
	float NextLevelTime = 2.0f;


	float StoneSummonTime = 0.0f;
	float StoneSummonLimitTime = 5.0f;
	class StoneDrop* StonDrop1;
	class StoneDrop* StonDrop2;
	class StoneDrop* StonDrop3;
	class StoneDrop* StonDrop4;
	class StoneDrop* StonDrop5;
	class StoneDrop* StonDrop6;
	class StoneDrop* StonDrop7;
	class StoneDrop* StonDrop8;
	class StoneDrop* StonDrop9;

	GameEngineSoundPlayer BGMPlayer;
};

