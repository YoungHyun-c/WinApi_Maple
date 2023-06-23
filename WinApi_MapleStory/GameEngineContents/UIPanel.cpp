#include "UIPanel.h"
#include "Enum.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "MouseObject.h"



UIPanel* UIPanel::UI = nullptr;

void UIPanel::InvenOn() 
{
	UIItemRenderer->On();
	for (size_t y = 0; y < IconRenders.size(); y++)
	{
		for (size_t x = 0; x < IconRenders[y].size(); x++)
		{
			IconRenders[y][x]->On();
		}
	}
}

void UIPanel::InvenOff()
{
	UIItemRenderer->Off();
	for (size_t y = 0; y < IconRenders.size(); y++)
	{
		for (size_t x = 0; x < IconRenders[y].size(); x++)
		{
			IconRenders[y][x]->Off();
		}
	}
}

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
		InvenPos = { 700, 300 };
		InvenSize = {120, 160};
		IconInter = { 36, 36 };
		UIItemRenderer = CreateUIRenderer("Inventory.bmp", RenderOrder::PlayUI);
		UIItemRenderer->SetRenderPos({ 700, 300 });
		UIItemRenderer->Off();

		IconRenders.resize(6);
		IconCollisions.resize(6);

		for (size_t y = 0; y < 6; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				float4 StartPos = InvenPos - InvenSize.Half();
				float4 IconPos;
				IconPos.X = x * IconInter.X;
				IconPos.Y = y * IconInter.Y;
				StartPos += IconPos;


				GameEngineCollision* InvenCollision = CreateCollision(CollisionOrder::InvenIcon);
				InvenCollision->SetCollisionPos(StartPos);
				InvenCollision->SetCollisionScale(IconInter);
				InvenCollision->IsUIOn();


				GameEngineRenderer* Icon = CreateUIRenderer("Apple.bmp", RenderOrder::InvenIcon);
				Icon->SetRenderPos(StartPos);
				Icon->Off();

				IconCollisions[y].push_back(InvenCollision);
				IconRenders[y].push_back(Icon);
			}
		}
	}

	IconRenders[0][0]->SetTexture("Empty.bmp");
	IconRenders[1][2]->SetTexture("Empty.bmp");
	IconRenders[3][2]->SetTexture("Empty.bmp");
	IconRenders[4][0]->SetTexture("Empty.bmp");

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
	if (true == UIItemRenderer->IsUpdate())
	{
		for (size_t y = 0; y < IconRenders.size(); y++)
		{
			for (size_t x = 0; x < IconRenders[y].size(); x++)
			{
				if (
					true == IconCollisions[y][x]->CollisonCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
					&& GameEngineInput::IsDown(VK_LBUTTON)
					)
				{
					int a = 0;
				}
			}
		}
	}


	if (GameEngineInput::IsDown('I'))
	{
		Item = !Item;
		if (Item)
		{
			InvenOn();
		}
		else
		{
			InvenOff();
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