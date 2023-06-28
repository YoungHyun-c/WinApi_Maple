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
#include "GlobalValue.h"


NineNpc::NineNpc()
{

}

NineNpc::~NineNpc()
{

}

void NineNpc::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("3.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources\\");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("3.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("4.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("5.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("6.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("7.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("8.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("9.bmp"));

	}

	{
		NineQuest = CreateRenderer("Quest.bmp", RenderOrder::PlayUI);
		NineQuest->SetRenderPos({ 340.0f, 640.0f });
		NineQuest->On();


		NineQuestCollision = CreateCollision(CollisionOrder::QuestIcon);
		NineQuestCollision->SetCollisionPos({ 340.0f, 640.0f });
		NineQuestCollision->SetCollisionScale({ 30, 30 });
		NineQuestCollision->SetCollisionType(CollisionType::Rect);
	}

	{
		ScriptRenderer = CreateUIRenderer("3.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GlobalValue::ScriptValue);
		ScriptRenderer->Off();
	}
};


void NineNpc::Update(float _Delta)
{
	std::vector<GameEngineCollision*> Col;
	if (NineQuestCollision->Collision(CollisionOrder::MouseObjectPlay, Col) && true == GameEngineInput::IsDown(VK_LBUTTON))
	{
		ScriptRenderer->On();
		Script = true;
	}

	if (Script == true && Scripti == 1)
	{
		ScriptRenderer->Off();
		ScriptRenderer = CreateUIRenderer("4.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GlobalValue::ScriptValue);
		ScriptRenderer->On();
	}

	if (Script == true && Scripti == 2)
	{
		ScriptRenderer->Off();
		ScriptRenderer = CreateUIRenderer("5.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GlobalValue::ScriptValue);
		ScriptRenderer->On();
	}

	if (Script == true && Scripti == 3)
	{
		ScriptRenderer->Off();
		ScriptRenderer = CreateUIRenderer("6.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GlobalValue::ScriptValue);
		ScriptRenderer->On();
	}

	if (Script == true && Scripti == 4)
	{
		ScriptRenderer->Off();
		ScriptRenderer = CreateUIRenderer("7.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GlobalValue::ScriptValue);
		ScriptRenderer->On();
	}

	if (Script == true && Scripti == 5)
	{
		ScriptRenderer->Off();
		ScriptRenderer = CreateUIRenderer("8.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GlobalValue::ScriptValue);
		ScriptRenderer->On();
	}

	if (Script == true && Scripti == 6)
	{
		ScriptRenderer->Off();
		ScriptRenderer = CreateUIRenderer("9.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half());
		ScriptRenderer->On();
	}

	if (3.0f < GetLiveTime() && Scripti == 6)
	{
		GameEngineCore::ChangeLevel("PlayLevel");
		Script = false;
	}

	if (Script == true && true == GameEngineInput::IsDown(VK_RETURN))
	{
		Scripti++;
		ResetLiveTime();
	}
}
