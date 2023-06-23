#include "UICollision.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Enum.h"

UICollision* UICollision::UIIcon = nullptr;

UICollision::UICollision()
{
	UIIcon = this;
}

UICollision::~UICollision()
{

}

void UICollision::Start()
{
	// 랜더러를 만들필요가 없다.
	IconCollision = CreateCollision(CollisionOrder::InvenIcon);
	IconCollision->SetCollisionPos({ 640, 220 });
	IconCollision->SetCollisionScale({ 30, 30 });
	//IconCollision->SetCollisionPos({ 675, 220 });

	IconCollision->Off();

	{
		UIItemPotionRenderer = CreateUIRenderer("Apple.bmp", RenderOrder::InvenIcon);
		//UIItemPotionRenderer->SetRenderPos({ 640, 220 });
		UIItemPotionRenderer->Off();
	}
}

void UICollision::Update(float _Delta)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	SetPos(CameraPos);

	std::vector<GameEngineCollision*> Results;

	if (IconCollision->Collision(CollisionOrder::MouseObject, Results))
	{
		for (size_t i = 0; i < Results.size(); i++)
		{
			//Results[i]->GetActor()->Off();
			//GameEngineLevel::CollisionDebugRenderSwitch();
			//IconCollision->SetCollisionPos({ 675, 220 });
			IconCollision->Off();
			UIItemPotionRenderer->Off();
		}
	}


	if (GameEngineInput::IsDown('I'))
	{
		PotionItem = !PotionItem;
		if (PotionItem)
		{
			IconCollision->On();
			UIItemPotionRenderer->On();
		}
		else
		{
			IconCollision->Off();
			UIItemPotionRenderer->Off();
		}
	}
}

void UICollision::Render(float _Delta)
{

}