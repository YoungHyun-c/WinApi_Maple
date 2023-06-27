#include "GardenLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>

#include "UIPanel.h"
#include "Player.h"
//#include "Monster.h"
#include "BackGround.h"
#include "GlobalValue.h"


GardenLevel::GardenLevel()
{

}

GardenLevel::~GardenLevel()
{

}

void GardenLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Garden_Test.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Garden_Test1.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Garden_Debug1.bmp"));
	}

	GameEngineSound::SetGlobalVolume(0.3f);
	if (nullptr == GameEngineSound::FindSound("AbyssCave.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("AbyssCave.mp3"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("Garden_Test1.bmp", "Garden_Debug1.bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("Garden_Debug1.bmp");
	LevelPlayer->SetPos({ 300, 400 });
}

void GardenLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}

	if (true == GameEngineInput::IsDown('B'))
	{
		BackGroundPtr->SwitchRenderer();
	}
}

void GardenLevel::Release()
{

}

void GardenLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("Garden_Test1.Bmp");

	if (nullptr == Ptr)
	{
		MsgBoxAssert("맵 텍스처를 알수가 없습니다.");
	}
	GlobalValue::MapScale = Ptr->GetScale();


	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}


	BGMPlayer = GameEngineSound::SoundPlay("AbyssCave.mp3");

	LevelPlayer->SetGroundTexture("Garden_Debug1.bmp");


}

void GardenLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}