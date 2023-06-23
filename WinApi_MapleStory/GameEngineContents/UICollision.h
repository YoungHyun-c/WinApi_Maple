#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UICollision : public GameEngineActor
{
	static UICollision* UIIcon;

public:
	// constructer destructer
	UICollision();
	~UICollision();

	// delete Function
	UICollision(const UICollision& _Other) = delete;
	UICollision(UICollision&& _Other) noexcept = delete;
	UICollision& operator = (const UICollision& _Other) = delete;
	UICollision& operator = (UICollision&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	bool PotionItem = false;

	GameEngineCollision* Collision;
	GameEngineCollision* IconCollision;

	GameEngineRenderer* UIItemPotionRenderer = nullptr;
private:

};

