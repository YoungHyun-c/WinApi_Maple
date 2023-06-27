#include "StartLevel.h"

#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCollision.h>

#include <GameEngineCore/GameEngineRenderer.h>

#include "BackGround.h"
#include "UIStart.h"
#include "UIPanel.h"
#include "UIQuest.h"
#include "MouseObject.h"
#include "Enum.h"


StartLevel::StartLevel()
{

}

StartLevel::~StartLevel()
{
	
}


void StartLevel::Start()
{
	GameEngineWindow::MainWindow.CursorOff();

	if (false == ResourcesManager::GetInst().IsLoadTexture("LoginBack_Test.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LoginBack_Test.bmp"));
	}

	GameEngineSound::SetGlobalVolume(0.3f);
	if (nullptr == GameEngineSound::FindSound("Login.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Login.mp3"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("LoginBack_Test.bmp", "LoginBack_Test.bmp");


	D = CreateActor<MouseObject>();
	S = CreateActor<UIStart>();
	S->SetMouseObject(D);
}

void StartLevel::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		GameEngineCore::ChangeLevel("PracticeLevel");
	}

	if (true == GameEngineInput::IsDown('R'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}
}


void StartLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//BGMPlayer = GameEngineSound::SoundPlay("Login.mp3");
}


void StartLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();

	P = CreateActor<UIPanel>();
	Qu = CreateActor<UIQuest>();
	Qu->SetMouseObject(D);
	P->SetMouseObject(D);

	Qu->OverOn();
	D->OverOn();
	P->OverOn();
}