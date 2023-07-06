#include "EndLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/ResourcesManager.h>

#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BackGround.h"
#include "GlobalValue.h"

#include "Enum.h"
#include "FadeObject.h"


EndLevel::EndLevel()
{

}

EndLevel::~EndLevel()
{

}

void EndLevel::Start()
{
	GameEngineWindow::MainWindow.CursorOff();
	if (false == ResourcesManager::GetInst().IsLoadTexture("End.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("End.bmp"));
	}

	GameEngineSound::SetGlobalVolume(0.3f);
	if (nullptr == GameEngineSound::FindSound("Congratulation.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Congratulation.mp3"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("End.bmp", "End.bmp");
}

void EndLevel::Update(float _Delta)
{

}

void EndLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	FadeObject* FObject = CreateActor<FadeObject>();
	GameEngineSound::SoundPlay("Congratulation.mp3");
}

void EndLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}