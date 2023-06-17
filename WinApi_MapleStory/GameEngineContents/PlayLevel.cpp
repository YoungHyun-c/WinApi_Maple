#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>


// Contents
#include "Player.h"
#include "BackGround.h"
#include "PlayActor.h"

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}


void PlayLevel::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("RUTAMAP_NPC.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RUTAMAP_NPC.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("RUTAMAP_DebugT.bmp"));
	}

	GameEngineSound::SetGlobalVolume(0.4f);
	if (nullptr == GameEngineSound::FindSound("YggdrasilPrayer.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("YggdrasilPrayer.mp3"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("RUTAMAP_NPC.bmp", "RUTAMAP_DebugT.bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("RUTAMAP_DebugT.bmp");
	//LevelPlayer->OverOn();
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	/*if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}*/

	//GameEngineSound::SoundPlay()

	//BGMPlayer = GameEngineSound::SoundPlay("YggdrasilPrayer.mp3");

	LevelPlayer->SetGroundTexture("RUTAMAP_DebugT.bmp");

}

void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRenderer();
	}
	
}