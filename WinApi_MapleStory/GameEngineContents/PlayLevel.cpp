#include "PlayLevel.h"
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

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}


void PlayLevel::Start()
{
	GameEngineWindow::MainWindow.CursorOff();

	if (false == ResourcesManager::GetInst().IsLoadTexture("RUTAMAP_NPC.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RUTAMAP_NPC.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RUTAMAP_DebugTT.bmp"));
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
	BackGroundPtr->Init("RUTAMAP_NPC.bmp", "RUTAMAP_DebugTT.bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("RUTAMAP_DebugTT.bmp");
	//LevelPlayer->OverOn(); 플레이어 그대로 넘어가기.

	//M = CreateActor<MouseObject>();
	//P = CreateActor<UIPanel>();
	//P->SetMouseObject(M);


}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("RUTAMAP_NPC.Bmp");

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

	LevelPlayer->SetGroundTexture("RUTAMAP_DebugTT.bmp");

}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('B'))
	{
		BackGroundPtr->SwitchRenderer();
	}

	if (true == GameEngineInput::IsDown('0'))
	{
		GameEngineCore::ChangeLevel("StartLevel");
	}

	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("PracticeLevel");
	}
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}