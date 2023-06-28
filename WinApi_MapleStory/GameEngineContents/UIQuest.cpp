#include "UIQuest.h"
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
#include <GameEngineBase/GameEngineTime.h>


UIQuest::UIQuest()
{

}

UIQuest::~UIQuest()
{

}

void UIQuest::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Quest.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources\\");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Quest.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("1.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("2.bmp"));
	}

	{
		UIQuestRenderer = CreateUIRenderer("Quest.bmp", RenderOrder::PlayUI);
		UIQuestRenderer->SetRenderPos({ 500, 400 });
		UIQuestRenderer->On();

		QuestCollision = CreateCollision(CollisionOrder::QuestIcon);
		QuestCollision->SetCollisionPos({ 500, 400 });
		QuestCollision->SetCollisionScale({ 30, 30 });
	}

	{
		ScriptRenderer = CreateUIRenderer("1.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos({ 500, 400 });
		ScriptRenderer->Off();

		ScriptCollision = CreateCollision(CollisionOrder::QuestIcon);
		ScriptCollision->SetCollisionPos({ 650, 480 });
		ScriptCollision->SetCollisionScale({ 50, 30 });
		ScriptCollision->Off();
	}

	Script = false;
	ScriptEnd = false;

}

void UIQuest::Update(float _Delta)
{
	std::vector<GameEngineCollision*> Col;
	if (QuestCollision->Collision(CollisionOrder::MouseObjectPlay, Col) && GameEngineInput::IsDown(VK_LBUTTON))
	{
		ScriptRenderer->On();
		ScriptCollision->On();
		Script = true;
	}

	if (ScriptCollision->Collision(CollisionOrder::MouseObjectPlay, Col) && GameEngineInput::IsDown(VK_LBUTTON)
		&& Script == true)// || GameEngineInput::IsDown(VK_RETURN))
	{
		ScriptRenderer->Off();
		ScriptRenderer = CreateUIRenderer("2.bmp", RenderOrder::PlayUI);
		ScriptRenderer->SetRenderPos({ 500, 400 });
		ScriptRenderer->On();
		ScriptEnd = true;
	}
	if (ScriptEnd == true && GameEngineInput::IsDown(VK_RETURN))
	{
		ScriptRenderer->Off();
		ScriptCollision->Off();
		QuestCollision->Off();
		UIQuestRenderer->Off();
		GameEngineCore::ChangeLevel("EreveLevel");
		ScriptEnd = false;
	}
	float4 Pos = Player::GetMainPlayer()->MainRenderer->GetActor()->GetPos() + float4 { 10.0f, -60.0f };
	UIQuestRenderer->SetRenderPos(Pos);
	QuestCollision->SetCollisionPos(Pos);
}