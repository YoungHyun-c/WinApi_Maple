#include "UIPanel.h"
#include "Enum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>


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
	// 위치를 옮기지 않았다.
	// GetPos();
	// 카메라가 안움직여

	{
		UIItemRenderer = CreateUIRenderer("Inventory.bmp", RenderOrder::PlayUI);
		UIItemRenderer->SetRenderPos({ 700, 300 });
		UIItemRenderer->Off();
	}

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
		}
		else
		{
			UIItemRenderer->Off();
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