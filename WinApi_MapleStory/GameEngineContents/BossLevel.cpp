#include "BossLevel.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>


#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "UIPanel.h"
#include "Player.h"
#include "BackGround.h"
#include "GlobalValue.h"
#include "EndLevel.h"

#include "BellomBoss.h"
#include "BellomTail.h"
#include "Enum.h"
#include "FadeObject.h"
BossLevel::BossLevel()
{

}

BossLevel::~BossLevel()
{

}

void BossLevel::Start()
{
	GameEngineWindow::MainWindow.CursorOff();
	if (false == ResourcesManager::GetInst().IsLoadTexture("BossLevel.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BossLevel.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BossLevel_Debug.bmp"));
	}

	GameEngineSound::SetGlobalVolume(0.3f);

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("BossLevel.bmp", "BossLevel_Debug.bmp");


	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("BossLevel_Debug.bmp");
	//LevelPlayer->SetPos({ 1700, 700 });
}

void BossLevel::Update(float _Delta)
{
	if (true == BellomBoss::GetMainBoss()->BellomSummoner())
	{
		SummonTime += _Delta;
	}

	if (SummonTime >= SummonLimitTime)
	{
		MoveTime += _Delta;
	}

	if (MoveTime >= MoveLimitTime && TailsCount < 5)
	{
		BellomTail* BossTail = CreateActor<BellomTail>(UpdateOrder::Monster);
		MoveTime = 0.0f;
		TailsCount += 1;
	}

	if (true == BellomBoss::GetMainBoss()->BellomDeath())
	{
		NextMoveTime += _Delta;
		if (NextMoveTime >= NextLevelTime)
		{
			GameEngineCore::ChangeLevel("EndLevel");
		}
	}
}

void BossLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BellomBoss* Boss = CreateActor<BellomBoss>(UpdateOrder::Monster);
	//BellomTail* BossTail = CreateActor<BellomTail>(UpdateOrder::Monster);

	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("BossLevel.Bmp");
	if (nullptr == Ptr)
	{
		MsgBoxAssert("맵 텍스처를 알수가 없습니다.");
	}
	GlobalValue::MapScale = Ptr->GetScale();


	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	LevelPlayer->SetGroundTexture("BossLevel_Debug.bmp");

	{
		FadeObject* FObject = CreateActor<FadeObject>();
	}
}

void BossLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}