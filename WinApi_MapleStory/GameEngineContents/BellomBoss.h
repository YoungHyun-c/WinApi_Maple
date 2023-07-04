#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BellomBoss : public GameEngineActor
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

protected:
	GameEngineRenderer* Bellom = nullptr;
	GameEngineCollision* BellomBody = nullptr;
	GameEngineCollision* BellomSummon = nullptr;
private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	float MoveTime = 0.0f;
	static bool Summon;
};

