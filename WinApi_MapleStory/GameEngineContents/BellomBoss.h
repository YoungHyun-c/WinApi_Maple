#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

// Ό³Έν :
class BellomBoss : public PlayActor
{
private:
	static BellomBoss* MainBoss;

public:
	static BellomBoss* GetMainBoss()
	{
		return MainBoss;
	}

public:
	// constructer destructer
	BellomBoss();
	~BellomBoss();

	// delete Function
	BellomBoss(const BellomBoss& _Other) = delete;
	BellomBoss(BellomBoss&& _Other) noexcept = delete;
	BellomBoss& operator = (const BellomBoss& _Other) = delete;
	BellomBoss& operator = (BellomBoss&& _Other) noexcept = delete;

	static bool BellomSummoner()
	{
		return Summon;
	}

	void SetMainBossHp(float _Value)
	{
		BellomBossHp = _Value;
	}

	void GetMainBossHP(float _Value)
	{
		BellomBossHp -= _Value;
	}

	float GetMainBossHpValue()
	{
		return BellomBossHp;
	}

	float GetMainBossHpBarMove()
	{
		return BossHpBarX -= 35.0f;
	}

	float GetMainBossHpBar()
	{
		return BossHpBarX;
	}

protected:
	GameEngineRenderer* Bellom = nullptr;
	GameEngineCollision* BellomBody = nullptr;
	GameEngineCollision* BellomSummon = nullptr;
private:
	void LevelStart() override;
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	int AttackCount = 0;

	float MoveTime = 0.0f;
	static bool Summon;
	float BellomBossHp = 1410.0f;
	float BossHpBarX = 582.5f;
};

