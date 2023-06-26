#include "PracticeLevel.h"
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
#include "MouseObjectPlay.h"	
#include "UICollision.h"
#include "GlobalValue.h"


PracticeLevel::PracticeLevel()
{

}

PracticeLevel::~PracticeLevel()
{

}

void PracticeLevel::Start()
{
	GameEngineWindow::MainWindow.CursorOff();

	if (false == ResourcesManager::GetInst().IsLoadTexture("PracticeLevel.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PracticeLevel.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PracticeLevel_Debug.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Quest.bmp"));
	}

	GameEngineSound::SetGlobalVolume(0.3f);
	if (nullptr == GameEngineSound::FindSound("YggdrasilPrayer.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("YggdrasilPrayer.mp3"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("PracticeLevel.bmp", "PracticeLevel_Debug.bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("PracticeLevel_Debug.bmp");
	//MainRenderer = CreateRenderer(RenderOrder::Play);
}

void PracticeLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("PracticeLevel.Bmp");
	if (nullptr == Ptr)
	{
		MsgBoxAssert("맵 텍스처를 알수가 없습니다.");
	}
	GlobalValue::MapScale = Ptr->GetScale();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}


	//BGMPlayer = GameEngineSound::SoundPlay("YggdrasilPrayer.mp3");

	LevelPlayer->SetGroundTexture("PracticeLevel_Debug.bmp");

}

void PracticeLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('B'))
	{
		BackGroundPtr->SwitchRenderer();
	}

	if (true == GameEngineInput::IsDown('0'))
	{
		GameEngineCore::ChangeLevel("StartLevel");
	}

	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}


void PracticeLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}