#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class UIStart : public GameEngineActor
{
public:
	// constructer destructer
	UIStart();
	~UIStart();

	// delete Function
	UIStart(const UIStart& _Other) = delete;
	UIStart(UIStart&& _Other) noexcept = delete;
	UIStart& operator = (const UIStart& _Other) = delete;
	UIStart& operator = (UIStart&& _Other) noexcept = delete;

	void SetMouseObject(class MouseObject* _MObject)
	{
		MObject = _MObject;
	}

protected:

	void Start() override;

	void Update(float _Delta) override;

	GameEngineRenderer* UIStartRenderer = nullptr;
	GameEngineCollision* StartCollision = nullptr;

private:
	class MouseObject* MObject;

};

