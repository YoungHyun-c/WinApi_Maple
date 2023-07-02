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

	void InvenCollisionOn();
	void InvenCollisionOff();

	void SetMouseObject(class MouseObject* _MObject)
	{
		MObject = _MObject;
	}

protected:
	void Start() override;

	void Update(float _Delta) override;


	GameEngineRenderer* UIItemRenderer = nullptr;
	GameEngineCollision* InvenCollision = nullptr;
	std::vector<std::vector<GameEngineRenderer*>> IconRenders;
	std::vector<std::vector<GameEngineCollision*>> IconCollisions;

	std::string GetTextSave = "";
	std::string GetSwitchTextSave = "";

	int ValueY = 0;
	int ValueX = 0;

	GameEngineRenderer* UISkillRenderer = nullptr;
	GameEngineRenderer* UIStatusRenderer = nullptr;

	GameEngineRenderer* PlayerBarRender = nullptr;
	GameEngineRenderer* PlayerHPBarRender = nullptr;
	int MovePlayerHP = 0;
	int MovePlayerMP = 0;
	float HpBarX = 141.0f;
	float MpBarX = 141.0f;
	float HpBarPosX = 520.0f;
	float MpBarPosX = 520.0f;
	GameEngineRenderer* PlayerMPBarRender = nullptr;
	GameEngineRenderer* PlayerEXPBarRender = nullptr;
	GameEngineRenderer* PlayerEXPUIBarRender = nullptr;

	GameEngineRenderer* PlayerChatOpenRender = nullptr;
	GameEngineRenderer* PlayerChatCloseRender = nullptr;

	GameEngineRenderer* PlayerQuickSloteRender = nullptr;
	GameEngineRenderer* PlayerQuickSlotAlphaRender = nullptr;


	//GameEngineRenderer* UIStartRenderer = nullptr;
	//GameEngineCollision* StartCollision = nullptr;

	bool Item = false;
	bool SKill = false;
	bool Status = false;
	bool StateRender = false;
	bool CharUIRender = false;

	bool m_bClick;

	float4 InvenPos = { 700, 300 };
	float4 InvenSize = { 120, 160 };
	float4 IconInter = { 36, 36 };

private:
	class MouseObject* MObject;

};