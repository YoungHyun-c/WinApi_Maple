#pragma once
#include <GameEngineCore/GameENgineLevel.h>

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
	void Update(float _DeltaTime) override;

private:

};

