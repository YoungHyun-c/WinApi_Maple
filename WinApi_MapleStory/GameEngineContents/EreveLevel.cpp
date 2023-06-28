#include "EreveLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include <GameEngineCore/GameEngineCollision.h>

#include "UIPanel.h"
#include "UIStart.h"

// Contents
#include "Player.h"
#include "BackGround.h"
#include "PlayActor.h"
#include "Enum.h"

#include "MouseObject.h"
#include "GlobalValue.h"
#include "UIQuest.h"
#include "FadeObject.h"
#include "NineNpc.h"

EreveLevel::EreveLevel()
{

}

EreveLevel::~EreveLevel()
{

}

void EreveLevel::Start()
{
	GameEngineWindow::MainWindow.CursorOff();

	if (false == ResourcesManager::GetInst().IsLoadTexture("Ereve.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Ereve.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Ereve_Debug.bmp"));
	}

	GameEngineSound::SetGlobalVolume(0.3f);
	if (nullptr == GameEngineSound::FindSound("QueensGarden.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("QueensGarden.mp3"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("Ereve.bmp", "Ereve_Debug.bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("Ereve_Debug.bmp");

	{
		FadeObject* FObject = CreateActor<FadeObject>();
	}
}

void EreveLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("Ereve.Bmp");
	if (nullptr == Ptr)
	{
		MsgBoxAssert("맵 텍스처를 알수가 없습니다.");
	}
	GlobalValue::MapScale = Ptr->GetScale();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}


	//BGMPlayer = GameEngineSound::SoundPlay("QueensGarden.mp3");

	LevelPlayer->SetGroundTexture("Ereve_Debug.bmp");

	NineN = CreateActor<NineNpc>();
	NineN->SetMouseObject(MouseObject::GetMainMouse());
	float4 Pos = Player::GetMainPlayer()->MainRenderer->GetActor()->GetPos() + float4{ -150.0f, 80.0f };
	//NineN->SetPos({340.0f, 640.0f});
}

void EreveLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('B'))
	{
		BackGroundPtr->SwitchRenderer();
	}

	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void EreveLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}