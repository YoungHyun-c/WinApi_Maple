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
	}

	{
		UIQuestRenderer = CreateUIRenderer("Quest.bmp", RenderOrder::PlayUI);
		UIQuestRenderer->SetRenderPos({ 500, 300 });
		UIQuestRenderer->On();

		QuestCollision = CreateCollision(CollisionOrder::QuestIcon);
		QuestCollision->SetCollisionPos({ 500, 300 });
		QuestCollision->SetCollisionScale({ 30, 30 });
	}

}

void UIQuest::Update(float _Delta)
{
	if (true == QuestCollision->CollisionCheck(MObject->GetCollision(), CollisionType::Rect, CollisionType::Rect) && GameEngineInput::IsDown(VK_LBUTTON))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
		QuestCollision->Off();
		UIQuestRenderer->Off();
		int a = 0;
	}
	float4 Pos = Player::GetMainPlayer()->MainRenderer->GetActor()->GetPos() + float4 { 10.0f, -60.0f };
	UIQuestRenderer->SetRenderPos(Pos);
	QuestCollision->SetCollisionPos(Pos);
}