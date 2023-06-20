#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class UIPanel : public GameEngineActor
{
public:
	static UIPanel* UI;

public:
	// constrcuter destructer
	UIPanel();
	~UIPanel();

	// delete Function
	UIPanel(const UIPanel& _Other) = delete;
	UIPanel(UIPanel&& _Other) noexcept = delete;
	UIPanel& operator=(const UIPanel& _Other) = delete;
	UIPanel& operator=(UIPanel&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;


	GameEngineRenderer* UIItemRenderer = nullptr;
	GameEngineRenderer* UISkillRenderer = nullptr;
	GameEngineRenderer* UIStatusRenderer = nullptr;

	bool Item = false;
	bool SKill = false;
	bool Status = false;
private:

};