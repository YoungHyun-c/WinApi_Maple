#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <vector>

// Ό³Έν :
class EreveLevel : public GameEngineLevel
{
public:
	// constructer destructer
	EreveLevel();
	~EreveLevel();

	// delete Function
	EreveLevel(const EreveLevel& _Other) = delete;
	EreveLevel(EreveLevel&& _Other) noexcept = delete;
	EreveLevel& operator = (const EreveLevel& _Other) = delete;
	EreveLevel& operator = (EreveLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	//void Release() override;

	class BackGround* BackGroundPtr;
	class Player* LevelPlayer = nullptr;
	class TileMap* TileObject;


	GameEngineCollision* NPCCollision = nullptr;
	class NineNpc* NineN = nullptr;

	class FadeObject* FObject = nullptr;


	GameEngineSoundPlayer BGMPlayer;
};

