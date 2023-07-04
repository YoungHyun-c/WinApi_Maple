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
#include "BellomBoss.h"

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

void UIPanel::InvenCollisionOn()
{
	for (size_t y = 0; y < IconCollisions.size(); y++)
	{
		for (size_t x = 0; x < IconCollisions[y].size(); x++)
		{
			IconCollisions[y][x]->On();
		}
	}
}

void UIPanel::InvenCollisionOff()
{

	for (size_t y = 0; y < IconCollisions.size(); y++)
	{
		for (size_t x = 0; x < IconCollisions[y].size(); x++)
		{
			IconCollisions[y][x]->Off();
		}
	}
}

void UIPanel::OneClickCheckIconRender()
{
	for (size_t y = 0; y < IconRenders.size(); y++)
	{
		for (size_t x = 0; x < IconRenders[y].size(); x++)
		{
			if (IconRenders[y][x]->GetTexture() == "Apple.bmp")
			{

			}
		}
	}
}

void UIPanel::DoubleClickCheckIconRender()
{
	for (size_t y = 0; y < IconRenders.size(); y++)
	{
		for (size_t x = 0; x < IconRenders[y].size(); x++)
		{
			// 사과
			if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
				&& IconRenders[y][x]->GetTexture() == "Apple.bmp")
			{
				if (MovePlayerHP + 50 <= 1410)
				{
					HpBarPosX += 2.5f;
					Player::GetMainPlayer()->GetMainPlayerHp(50);
					PlayerHPBarRender->SetRenderScale({ HpBarX += 5, 14 });
					PlayerHPBarRender->SetRenderPos({ HpBarPosX, 710 });
				}

				if (MovePlayerHP + 50 > 1410)
				{
					Player::GetMainPlayer()->SetMainPlayerHP(1410);
					PlayerHPBarRender->SetRenderScale({ 141, 14 });
					PlayerHPBarRender->SetRenderPos({ 520, 710 });
				}
			}
			// 빨간포션
			if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
				&& IconRenders[y][x]->GetTexture() == "RedPotion.bmp")
			{
				if (MovePlayerHP + 100 <= 1410)
				{
					HpBarPosX += 5.0f;
					Player::GetMainPlayer()->GetMainPlayerHp(100);
					PlayerHPBarRender->SetRenderScale({ HpBarX += 10, 14 });
					PlayerHPBarRender->SetRenderPos({ HpBarPosX, 710 });
				}

				if (MovePlayerHP + 100 > 1410)
				{
					Player::GetMainPlayer()->SetMainPlayerHP(1410);
					PlayerHPBarRender->SetRenderScale({ 141, 14 });
					PlayerHPBarRender->SetRenderPos({ 520, 710 });
				}
			}
			// 파란포션
			if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
				&& IconRenders[y][x]->GetTexture() == "BluePotion.bmp")
			{
				if (MovePlayerMP + 100 <= 1410)
				{
					MpBarPosX += 5.0f;
					Player::GetMainPlayer()->GetMainPlayerMp(100);
					PlayerMPBarRender->SetRenderScale({ MpBarX += 10, 14 });
					PlayerMPBarRender->SetRenderPos({ MpBarPosX, 725 });
				}

				if (MovePlayerMP + 100 > 1410)
				{
					Player::GetMainPlayer()->SetMainPlayerMP(1410);
					PlayerMPBarRender->SetRenderScale({ 141, 14 });
					PlayerMPBarRender->SetRenderPos({ 520, 725 });
				}

			}
			// 하얀포션
			if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
				&& IconRenders[y][x]->GetTexture() == "WhitePotion.bmp")
			{
				if (MovePlayerHP + 300 <= 1410)
				{
					HpBarPosX += 15.0f;
					Player::GetMainPlayer()->GetMainPlayerHp(300);
					PlayerHPBarRender->SetRenderScale({ HpBarX += 30, 14 });
					PlayerHPBarRender->SetRenderPos({ HpBarPosX, 710 });
				}

				if (MovePlayerHP + 300 > 1410)
				{
					Player::GetMainPlayer()->SetMainPlayerHP(1410);
					PlayerHPBarRender->SetRenderScale({ 141, 14 });
					PlayerHPBarRender->SetRenderPos({ 520, 710 });
				}
			}
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

		///// 캐릭터UI렌더
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BarUI.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MPBar.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ExpUI.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ExpBar.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ChatCloseUI.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ChatOpenUI.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("QuickSlot.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("QuickSlotAlpha.bmp"));


		///// 보스UI렌더
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BellomProfile.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("EnergyBarS.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("EnergyBarM.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("EnergyBarE.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BellomHPBar.bmp"));
	}

	{
		PlayerBarRender = CreateUIRenderer("BarUI.bmp", RenderOrder::PlayUI);
		PlayerBarRender->SetRenderPos({ 510, 710 });
		PlayerBarRender->On();
	}

	{
		PlayerHPBarRender = CreateUIRenderer("HPBar.bmp", RenderOrder::PlayUI);
		PlayerHPBarRender->SetRenderPos({ 520, 710 });
		PlayerHPBarRender->SetRenderScale({ HpBarX, 14});
		PlayerHPBarRender->On();
	}

	{
		PlayerMPBarRender = CreateUIRenderer("MPBar.bmp", RenderOrder::PlayUI);
		PlayerMPBarRender->SetRenderPos({ 520, 725 });
		PlayerMPBarRender->On();
	}

	{
		PlayerEXPBarRender = CreateUIRenderer("ExpUI.bmp", RenderOrder::PlayUI);
		PlayerEXPBarRender->SetRenderPos({ 510, 750 });
		PlayerEXPBarRender->On();
	}

	{
		PlayerEXPUIBarRender = CreateUIRenderer("ExpBar.bmp", RenderOrder::PlayUI);
		PlayerEXPUIBarRender->SetRenderPos({ 510, 750 });
		PlayerEXPUIBarRender->On();
	}

	{
		PlayerChatOpenRender = CreateUIRenderer("ChatOpenUI.bmp", RenderOrder::PlayUI);
		PlayerChatOpenRender->SetRenderPos({ 217, 680 });
		PlayerChatOpenRender->On();
	}

	{
		PlayerChatCloseRender = CreateUIRenderer("ChatCloseUI.bmp", RenderOrder::PlayUI);
		PlayerChatCloseRender->SetRenderPos({ 217, 720 });
		PlayerChatCloseRender->Off();
	}

	{
		PlayerQuickSloteRender = CreateUIRenderer("QuickSlot.bmp", RenderOrder::PlayUI);
		PlayerQuickSloteRender->SetRenderPos({ 900, 700 });
		PlayerQuickSloteRender->On();
	}

	{
		PlayerQuickSlotAlphaRender = CreateUIRenderer("QuickSlotAlpha.bmp", RenderOrder::PlayUI);
		PlayerQuickSlotAlphaRender->SetRenderPos({ 900, 700 });
		PlayerQuickSlotAlphaRender->On();
	}

	{
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


				InvenCollision = CreateCollision(CollisionOrder::InvenIcon);
				InvenCollision->SetCollisionPos(StartPos);
				InvenCollision->SetCollisionScale(IconInter);
				InvenCollision->IsUIOn();

				GameEngineRenderer* Icon = CreateUIRenderer("Empty.bmp", RenderOrder::InvenIcon);
				Icon->SetRenderPos(StartPos);
				Icon->Off();

				IconCollisions[y].push_back(InvenCollision);
				IconRenders[y].push_back(Icon);
				InvenCollision->Off();
			}
		}
	}

	IconRenders[0][0]->SetTexture("Apple.bmp");
	IconRenders[0][1]->SetTexture("RedPotion.bmp");
	IconRenders[0][2]->SetTexture("BluePotion.bmp");
	IconRenders[0][3]->SetTexture("WhitePotion.bmp");
	IconRenders[1][0]->SetTexture("Apple.bmp");
	IconRenders[1][1]->SetTexture("WhitePotion.bmp");
	IconRenders[1][2]->SetTexture("WhitePotion.bmp");

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
					OneClickCheckIconRender();
					m_bClick = true;
					MObject->ChangeAnimationState("GrabIdle");
				}
				else if (true == IconCollisions[y][x]->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
					&& GameEngineInput::IsDown(VK_LBUTTON) && IconRenders[y][x]->GetTexture() != "Empty.bmp")
				{
					int a = 0;
					DoubleClickCheckIconRender();
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
			InvenCollisionOn();
			InvenOn();
		}
		else
		{
			InvenCollisionOff();
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

	if (GameEngineInput::IsDown('C'))
	{
		CharUIRender = !CharUIRender;
		if (CharUIRender)
		{
			PlayerChatOpenRender->Off();
			PlayerChatCloseRender->On();
		}
		else
		{
			PlayerChatOpenRender->On();
			PlayerChatCloseRender->Off();
		}
	}
	
	////////// 체력 관련
	MovePlayerHP = Player::GetMainPlayer()->GetMainPlayerHpValue();
	if (MovePlayerHP -300 >= 0 && GameEngineInput::IsDown('-'))
	{
		HpBarPosX -= 15.0f;
		Player::GetMainPlayer()->GetMainPlayerHp(-300);
		PlayerHPBarRender->SetRenderScale({ HpBarX -= 30, 14});
		PlayerHPBarRender->SetRenderPos({ HpBarPosX, 710 });
	}
	if (MovePlayerHP + 300 <= 1410 && GameEngineInput::IsDown('='))
	{
		HpBarPosX += 15.0f;
		Player::GetMainPlayer()->GetMainPlayerHp(300);
		PlayerHPBarRender->SetRenderScale({ HpBarX += 30, 14 });
		PlayerHPBarRender->SetRenderPos({ HpBarPosX, 710 });
	}
	if (MovePlayerHP + 300 > 1410 && GameEngineInput::IsDown('='))
	{
		Player::GetMainPlayer()->SetMainPlayerHP(1410);
		PlayerHPBarRender->SetRenderScale({ HpBarX = 141.0f, 14 });
		PlayerHPBarRender->SetRenderPos({ HpBarPosX = 520.0f, 710 });
	}


	/////// 마나 관련
	MovePlayerMP = Player::GetMainPlayer()->GetMainPlayerMpValue();
	if (MovePlayerMP - 300 >= 0 && GameEngineInput::IsDown('-'))
	{
		MpBarPosX -= 15.0f;
		Player::GetMainPlayer()->GetMainPlayerMp(-300);
		PlayerMPBarRender->SetRenderScale({ MpBarX -= 30, 14 });
		PlayerMPBarRender->SetRenderPos({ MpBarPosX , 725 });
	}
	if (MovePlayerMP + 300 <= 1410 && GameEngineInput::IsDown('='))
	{
		MpBarPosX += 15.0f;
		Player::GetMainPlayer()->GetMainPlayerMp(300);
		PlayerMPBarRender->SetRenderScale({ MpBarX += 30, 14 });
		PlayerMPBarRender->SetRenderPos({ MpBarPosX , 725 });
	}
	if (MovePlayerMP + 300 > 1410 && GameEngineInput::IsDown('='))
	{
		Player::GetMainPlayer()->SetMainPlayerMP(1410);
		PlayerMPBarRender->SetRenderScale({ MpBarX = 141.0f, 14 });
		PlayerMPBarRender->SetRenderPos({ MpBarPosX = 520.0f, 725 });
	}


	if (true == BellomBoss::GetMainBoss()->BellomSummoner())
	{
		GameEngineRenderer* BossProfile = CreateUIRenderer("BellomProfile.bmp", RenderOrder::PlayUI);
		BossProfile->SetRenderPos({ 200.0f, 30.0f });

		GameEngineRenderer* BossHPUIS = CreateUIRenderer("EnergyBarS.bmp", RenderOrder::PlayUI);
		BossHPUIS->SetRenderPos({ 230.0f, 30.0f });
		GameEngineRenderer* BossHPUIM = CreateUIRenderer("EnergyBarM.bmp", RenderOrder::PlayUI);
		BossHPUIM->SetRenderPos({ 580.0f, 30.0f });
		GameEngineRenderer* BossHPUIE = CreateUIRenderer("EnergyBarE.bmp", RenderOrder::PlayUI);
		BossHPUIE->SetRenderPos({ 935.0f, 30.0f });

		GameEngineRenderer* BossHPBar = CreateUIRenderer("BellomHPBar.bmp", RenderOrder::BossHPBar);
		BossHPBar->SetRenderPos({ 582.5f, 30.0f });
		//BossHPBar->SetRenderScale({ 710,12 });
		//BossHPBar->SetRenderScale({ 510,12 });
	}
}