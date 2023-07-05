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
#include "Monster.h"

#include "MouseObject.h"
#include "GlobalValue.h"
#include "UIQuest.h"
#include "FadeObject.h"
#include "NineNpc.h"


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
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PracticeLevel_DebugT.bmp"));
	}

	GameEngineSound::SetGlobalVolume(0.3f);
	if (nullptr == GameEngineSound::FindSound("AboveTheTreetops.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("AboveTheTreetops.mp3"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("PracticeLevel.bmp", "PracticeLevel_DebugT.bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("PracticeLevel_DebugT.bmp");

	{
		FObject = CreateActor<FadeObject>();
	}

	Snail = CreateActor<Monster>(UpdateOrder::Monster);
	Snail->SetPos({ BlueSnailX, BlueSnailY });
	Snail->SetGroundTexture("PracticeLevel_DebugT.bmp");
	
	Snail = CreateActor<Monster>(UpdateOrder::Monster);
	Snail->SetPos({ BlueSnailX + 210, BlueSnailY - 45});
	Snail->SetGroundTexture("PracticeLevel_DebugT.bmp");

	//Snail = CreateActor<Monster>(UpdateOrder::Monster);
	//Snail->SetPos({ BlueSnailX,BlueSnailY+200 });
	//Snail = CreateActor<Monster>(UpdateOrder::Monster);
	//Snail->SetPos({ BlueSnailX, BlueSnailY+300 });
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


	BGMPlayer = GameEngineSound::SoundPlay("AboveTheTreetops.mp3");

	LevelPlayer->SetGroundTexture("PracticeLevel_DebugT.bmp");

}

void PracticeLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('B'))
	{
		BackGroundPtr->SwitchRenderer();
	}

	if (true == GameEngineInput::IsDown('2'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}

	if (true == GameEngineInput::IsDown('4'))
	{
		GameEngineCore::ChangeLevel("BossLevel");
	}

	if (1.0f <= GetLiveTime())
	{
		//Monster* NewMonster = CreateActor<Monster>(UpdateOrder::Monster);
		//ResetLiveTime();

		//Snail = CreateActor<Monster>(UpdateOrder::Monster);

		//Snail = CreateActor<Monster>(UpdateOrder::Monster);
		//Snail->SetPos({ BlueSnailX + 200, BlueSnailY - 40 });
	}

	//M_FMoveTime += _Delta;
}

void PracticeLevel::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	//{
	//	std::string StrPos = "";
	//	StrPos += "MoveTime : ";
	//	StrPos += std::to_string(M_FMoveTime);
	//	TextOutA(dc, BlueSnailX, BlueSnailY, StrPos.c_str(), static_cast<int>(StrPos.size()));
	//}
	//{
	//	std::string StrPos = "";
	//	StrPos += "MoveTime : ";
	//	StrPos += std::to_string(M_FMoveTime);
	//	TextOutA(dc, BlueSnailX, BlueSnailY+100, StrPos.c_str(), static_cast<int>(StrPos.size()));
	//}
	//{
	//	std::string StrPos = "";
	//	StrPos += "MoveTime : ";
	//	StrPos += std::to_string(M_FMoveTime);
	//	TextOutA(dc, BlueSnailX, BlueSnailY+200, StrPos.c_str(), static_cast<int>(StrPos.size()));
	//}
	//{
	//	std::string StrPos = "";
	//	StrPos += "MoveTime : ";
	//	StrPos += std::to_string(M_FMoveTime);
	//	TextOutA(dc, BlueSnailX, BlueSnailY+300, StrPos.c_str(), static_cast<int>(StrPos.size()));
	//}
}


void PracticeLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}