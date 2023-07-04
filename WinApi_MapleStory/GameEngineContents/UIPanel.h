#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// 설명 :
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

	void OneClickCheckIconRender();
	void DoubleClickCheckIconRender();

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

	float ValueY = 0;
	float ValueX = 0;

	GameEngineRenderer* UISkillRenderer = nullptr;
	GameEngineRenderer* UIStatusRenderer = nullptr;

	GameEngineRenderer* PlayerBarRender = nullptr;
	GameEngineRenderer* PlayerHPBarRender = nullptr;
	float MovePlayerHP = 0;
	float MovePlayerMP = 0;
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

	bool Item = false;
	bool SKill = false;
	bool Status = false;
	bool StateRender = false;
	bool CharUIRender = false;

	bool m_bClick;

	float4 InvenPos = { 700, 300 };
	float4 InvenSize = { 120, 160 };
	float4 IconInter = { 36, 36 };

	/////////// 보스
	GameEngineRenderer* BossProfile = nullptr;
	GameEngineRenderer* BossHPUIS = nullptr;
	GameEngineRenderer* BossHPUIM = nullptr;
	GameEngineRenderer* BossHPUIE = nullptr;
	GameEngineRenderer* BossHPBar = nullptr;

	float MoveBossHP = 0;
	float MoveBossPrevHP = 1410.0f;
	float BossHpBarX = 0;

private:
	class MouseObject* MObject;

};