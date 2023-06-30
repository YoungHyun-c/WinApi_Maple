#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BellomBoss : public GameEngineActor
{
public:
	// constructer destructer
	BellomBoss();
	~BellomBoss();

	// delete Function
	BellomBoss(const BellomBoss& _Other) = delete;
	BellomBoss(BellomBoss&& _Other) noexcept = delete;
	BellomBoss& operator = (const BellomBoss& _Other) = delete;
	BellomBoss& operator = (BellomBoss&& _Other) noexcept = delete;

protected:
	GameEngineRenderer* Bellom = nullptr;
private:
	void Start() override;
	void Update(float _Delta) override;

	float MoveTime = 0.0f;
};

