#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class EndLevel : public GameEngineLevel
{
public:
	// constructer destructer
	EndLevel();
	~EndLevel();

	// delete Function
	EndLevel(const EndLevel& _Other) = delete;
	EndLevel(EndLevel&& _Other) noexcept = delete;
	EndLevel& operator = (const EndLevel& _Other) = delete;
	EndLevel& operator = (EndLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;

	class BackGround* BackGroundPtr;
	GameEngineSoundPlayer BGMPlayer;
};

