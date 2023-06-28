#include "NineNpc.h"
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
#include "EreveLevel.h"


NineNpc::NineNpc()
{

}

NineNpc::~NineNpc()
{

}

void NineNpc::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Quest.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources\\");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Quest.bmp"));
	}

	{
		NineQuest = CreateRenderer("Quest.bmp", RenderOrder::PlayUI);
		//NineQuest->SetRenderPos({ 340.0f, 640.0f });
		NineQuest->GetActor()->SetPos({ 350.0f, 650.0f });
		NineQuest->On();


		NineQuestCollision = CreateCollision(CollisionOrder::QuestIcon);
		//NineQuestCollision->SetCollisionPos({ 340.0f, 640.0f });
		NineQuestCollision->GetActor()->SetPos({ 350.0f, 650.0f });
		NineQuestCollision->SetCollisionScale({ 30, 30 });
		NineQuestCollision->SetCollisionType(CollisionType::Rect);
		//NineQuestCollision->GetActor()->SetPos({ 350, 550 });
	}
};


void NineNpc::Update(float _Delta)
{
	//std::vector<GameEngineCollision*> Results;

	std::vector<GameEngineCollision*> Col;
	if (NineQuestCollision->Collision(CollisionOrder::MouseObjectPlay, Col))
	{
		int a = 0;
	}


	if (true == NineQuestCollision->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect)
		&& GameEngineInput::IsDown(VK_LBUTTON))
	{
		int a = 0;
	}

}
