#include "RutaNpc.h"
#include "Enum.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEnginePlatform/GameEngineWindow.h>
#include "MouseObject.h"
#include "Player.h"
#include "EreveLevel.h"
#include "GlobalValue.h"


RutaNpc::RutaNpc()
{

}

RutaNpc::~RutaNpc()
{

}

void RutaNpc::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("10.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources\\");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("10.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("11.bmp"));
	}

	{
		RutaQuest = CreateRenderer("Quest.bmp", RenderOrder::PlayUI);
		RutaQuest->SetRenderPos({ 1250, 730 });
		RutaQuest->On();
	}

	{
		RutaQuestCollision = CreateCollision(CollisionOrder::QuestIcon);
		RutaQuestCollision->SetCollisionPos({ 1250, 730 });
		RutaQuestCollision->SetCollisionScale({ 30, 30 });
		RutaQuestCollision->SetCollisionType(CollisionType::Rect);
	}

	{
		ScriptRenderer = CreateUIRenderer("10.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GlobalValue::ScriptValue);
		ScriptRenderer->Off();
	}

}

void RutaNpc::Update(float _Delta)
{
	std::vector<GameEngineCollision*> Col;
	if (RutaQuestCollision->Collision(CollisionOrder::MouseObjectPlay, Col) && true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ScriptRenderer->On();
		RutaScript = true;
	}

	if (RutaScript == true && RutaScripti == 1)
	{
		ScriptRenderer->Off();
		ScriptRenderer = CreateUIRenderer("11.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GlobalValue::ScriptValue);
		ScriptRenderer->On();
		RutaScript = false;
	}

	if (RutaScripti == 2)
	{
		RutaQuest->Off();
		ScriptRenderer->Off();
	}

	if (GameEngineInput::IsDown(VK_RETURN))
	{
		RutaScripti++;
	}
}