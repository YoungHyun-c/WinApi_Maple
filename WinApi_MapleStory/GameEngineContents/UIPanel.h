#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

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

	void InvenOn();
	void InvenOff();

	void SetMouseObject(class MouseObject* _MObject)
	{
		MObject = _MObject;
	}

protected:
	void Start() override;

	void Update(float _Delta) override;


	GameEngineRenderer* UIItemRenderer = nullptr;
	std::vector<std::vector<GameEngineRenderer*>> IconRenders;
	std::vector<std::vector<GameEngineCollision*>> IconCollisions;

	std::string GetTextSave = "";
	std::string GetSwitchTextSave = "";

	int ValueY = 0;
	int ValueX = 0;

	GameEngineRenderer* UISkillRenderer = nullptr;
	GameEngineRenderer* UIStatusRenderer = nullptr;

	GameEngineRenderer* PlayerStateRender = nullptr;


	//GameEngineRenderer* UIStartRenderer = nullptr;
	//GameEngineCollision* StartCollision = nullptr;

	bool Item = false;
	bool SKill = false;
	bool Status = false;
	bool StateRender = false;

	bool m_bClick;

	float4 InvenPos;
	float4 IconInter;
	float4 InvenSize;

private:
	class MouseObject* MObject;

};