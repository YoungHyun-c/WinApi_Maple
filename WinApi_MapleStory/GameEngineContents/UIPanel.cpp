#include "UIPanel.h"
#include "Enum.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>



UIPanel* UIPanel::UI = nullptr;

UIPanel::UIPanel()
{
	UI = this;
}

UIPanel::~UIPanel()
{
}

void UIPanel::Start()
{
	// ��ġ�� �ű��� �ʾҴ�.
	// GetPos();
	// ī�޶� �ȿ�����

	{
		UIItemRenderer = CreateUIRenderer("Inventory.bmp", RenderOrder::PlayUI);
		UIItemRenderer->SetRenderPos({ 700, 300 });
		UIItemRenderer->Off();
	}

	//{
	//	UIItemPotionRenderer = CreateUIRenderer("Apple.bmp", RenderOrder::InvenIcon);
	//	UIItemPotionRenderer->SetRenderPos({ 640, 220 });
	//	UIItemPotionRenderer->Off();
	//}

	{
		UISkillRenderer = CreateUIRenderer("Skill.bmp", RenderOrder::PlayUI);
		UISkillRenderer->SetRenderPos({ 500, 300 });
		UISkillRenderer->Off();
	}

	{
		UIStatusRenderer = CreateUIRenderer("Status.bmp", RenderOrder::PlayUI);
		UIStatusRenderer->SetRenderPos({ 200, 300 });
		UIStatusRenderer->Off();
	}
}

void UIPanel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('I'))
	{
		Item = !Item;
		if (Item)
		{
			UIItemRenderer->On();
			//UIItemPotionRenderer->On();
		}
		else
		{
			UIItemRenderer->Off();
			//UIItemPotionRenderer->Off();
		}
	}

	if (GameEngineInput::IsDown('K'))
	{
		SKill = !SKill;
		if (SKill)
		{
			UISkillRenderer->On();
		}
		else
		{
			UISkillRenderer->Off();
		}
	}

	if (GameEngineInput::IsDown('T'))
	{
		Status = !Status;
		if (Status)
		{
			UIStatusRenderer->On();
		}
		else
		{
			UIStatusRenderer->Off();
		}
	}


}