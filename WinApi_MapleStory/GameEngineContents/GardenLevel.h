#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class GardenLevel : public GameEngineLevel
{
public:
	// constructer destructer
	GardenLevel();
	~GardenLevel();

	// delete Function
	GardenLevel(const GardenLevel& _Other) = delete;
	GardenLevel(GardenLevel&& _Other) noexcept = delete;
	GardenLevel& operator = (const GardenLevel& _Other) = delete;
	GardenLevel& operator = (GardenLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	class BackGround* BackGroundPtr;
	class Player* LevelPlayer = nullptr;

	GameEngineSoundPlayer BGMPlayer;
};

