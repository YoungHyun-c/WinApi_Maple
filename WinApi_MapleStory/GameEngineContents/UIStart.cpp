#include "UIStart.h"
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


UIStart::UIStart()
{

}

UIStart::~UIStart()
{

}

void UIStart::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("StartButton1.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources\\");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("StartButton2.bmp"));
	}

	{
		UIStartRenderer = CreateUIRenderer("StartButton2.bmp", RenderOrder::PlayUI);
		UIStartRenderer->SetRenderPos({ 512, 380 });
		UIStartRenderer->On();

		StartCollision = CreateCollision(CollisionOrder::StartIcon);
		StartCollision->SetCollisionPos({ 512, 380 });
		StartCollision->SetCollisionScale({ 300, 240 });
	}
}

void UIStart::Update(float _Delta)
{
	if (true == StartCollision->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect))
	{
		UIStartRenderer->On();
		if (GameEngineInput::IsDown(VK_LBUTTON))
		{
			GameEngineCore::ChangeLevel("PracticeLevel");
			StartCollision->Off();
			UIStartRenderer->Off();
		}
	}
	else
	{
		UIStartRenderer->Off();
	}
}