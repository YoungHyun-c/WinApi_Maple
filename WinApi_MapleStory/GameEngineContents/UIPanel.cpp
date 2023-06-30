#include "UIPanel.h"
#include "Enum.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEnginePath.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "MouseObject.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"

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

UIPanel::UIPanel() :
	m_bClick(false)
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
	// 카메라가 안움직임
	// 이미지 부르기.
	if (false == ResourcesManager::GetInst().IsLoadTexture("Inventory.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources\\");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Inventory.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Skill.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Status.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Apple.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RedPotion.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BluePotion.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("WhitePotion.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Empty.bmp"));


	}

	{
		PlayerStateRender = CreateUIRenderer("FADE.bmp", RenderOrder::PlayUI);
		PlayerStateRender->SetRenderPos({ 600, 680 });
		PlayerStateRender->SetRenderScale({ 210, 200 });
		PlayerStateRender->Off();
	}

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

	IconRenders[4][1]->SetTexture("RedPotion.bmp");
	IconRenders[4][2]->SetTexture("BluePotion.bmp");
	IconRenders[4][3]->SetTexture("WhitePotion.bmp");


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
				if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
					&& GameEngineInput::IsDown(VK_LBUTTON) && !m_bClick && IconRenders[y][x]->GetTexture() != "Empty.bmp")
				{
					m_bClick = true;
					MObject->ChangeAnimationState("GrabIdle");
				}
				else if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
					&& GameEngineInput::IsDown(VK_LBUTTON) && IconRenders[y][x]->GetTexture() != "Empty.bmp")
				{
					int a = 0;
					m_bClick = false;
					IconRenders[y][x]->SetTexture("Empty.bmp");
					MObject->ChangeAnimationState("Idle");
				}
				//if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
				//	&& GameEngineInput::IsDown(VK_LBUTTON) && IconRenders[y][x]->GetTexture() != "Empty.bmp")
				//{
				//	ValueY = y;
				//	ValueX = x;
				//	MObject->ChangeAnimationState("GrabIdle");
				//	GetTextSave = IconRenders[y][x]->GetTexture();
				//	GetTextSave;

				//	IconRenders[y][x]->SetTexture("Empty.bmp");
				//}
				//if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
				//	&& GameEngineInput::IsUp(VK_LBUTTON) && IconRenders[y][x]->GetTexture() != "Empty.bmp")
				//{
				//	MObject->ChangeAnimationState("Idle");
				//	GetSwitchTextSave = IconRenders[y][x]->GetTexture();

				//	IconRenders[y][x]->SetTexture(GetTextSave);

				//	//IconRenders[y][x]->SetTexture(Textl);
				//	ValueY;
				//	ValueX;
				//	IconRenders[ValueY][ValueX]->SetTexture(GetSwitchTextSave);
				//	
				//	GetTextSave = ("Empty.bmp");
				//	int a = 0;
				//}
				//if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
				//	&& GameEngineInput::IsUp(VK_LBUTTON) && IconRenders[y][x]->GetTexture() == "Empty.bmp")
				//{
				//	MObject->ChangeAnimationState("Idle");
				//	IconRenders[y][x]->SetTexture(GetTextSave);
				//	GetTextSave = ("Empty.bmp");
				//	int a = 0;
				//}
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

	if (GameEngineInput::IsDown(VK_F1))
	{
		StateRender = !StateRender;
		if (StateRender)
		{
			PlayerStateRender->On();
		}
		else
		{
			PlayerStateRender->Off();
		}
	}

}