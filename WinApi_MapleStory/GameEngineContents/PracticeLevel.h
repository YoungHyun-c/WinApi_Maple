#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class PracticeLevel : public GameEngineLevel
{
public:
	// constructer destructer
	PracticeLevel();
	~PracticeLevel();

	// delete Function
	PracticeLevel(const PracticeLevel& _Other) = delete;
	PracticeLevel(PracticeLevel&& _Other) noexcept = delete;
	PracticeLevel& operator = (const PracticeLevel& _Other) = delete;
	PracticeLevel& operator = (PracticeLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	//void Release() override;

	class BackGround* BackGroundPtr;
	class Player* LevelPlayer = nullptr;
	class UIPanel* P = nullptr;
	class MouseObject* M = nullptr;
	class TileMap* TileObject;

	GameEngineCollision* NPCCollision = nullptr;

	GameEngineSoundPlayer BGMPlayer;
};

