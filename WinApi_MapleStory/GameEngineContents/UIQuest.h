#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class UIQuest : public GameEngineActor
{
public:
	// constructer destructer
	UIQuest();
	~UIQuest();

	// delete Function
	UIQuest(const UIQuest& _Other) = delete;
	UIQuest(UIQuest&& _Other) noexcept = delete;
	UIQuest& operator = (const UIQuest& _Other) = delete;
	UIQuest& operator = (UIQuest&& _Other) noexcept = delete;

	void SetMouseObject(class MouseObject* _MObject)
	{
		MObject = _MObject;
	}


protected:
	void Start() override;

	void Update(float _Delta) override;

	GameEngineRenderer* UIQuestRenderer = nullptr;
	GameEngineCollision* QuestCollision = nullptr;

private:
	class MouseObject* MObject;
};
