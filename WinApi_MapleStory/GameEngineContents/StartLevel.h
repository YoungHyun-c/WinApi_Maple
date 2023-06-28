#pragma once
#include <GameEngineCore/GameENgineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <vector>

// Ό³Έν :
class StartLevel : public GameEngineLevel
{
public:
	// constructer destructer
	StartLevel();
	~StartLevel();

	// delete Function
	StartLevel(const StartLevel& _Other) = delete;
	StartLevel(StartLevel&& _Other) noexcept = delete;
	StartLevel& operator = (const StartLevel& _Other) = delete;
	StartLevel& operator = (StartLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	class BackGround* BackGroundPtr;

	class UIStart* S = nullptr;
	class MouseObject* D = nullptr;
	class UIPanel* P = nullptr;
	class UIQuest* Qu = nullptr;

	class NineNpc* NineN = nullptr;

	GameEngineRenderer* UIStartRenderer = nullptr;
	GameEngineCollision* StartCollision = nullptr;

	GameEngineSoundPlayer BGMPlayer;

private:
	void Start() override;
	void Update(float _DeltaTime) override;

};

