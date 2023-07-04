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
#include "GlobalValue.h"
#include "FadeObject.h"
#include "RutaNpc.h"

#include "BellomBoss.h"
#include "Potal.h"

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
	LevelPlayer->SetPos({ 200,200 });
	//LevelPlayer->OverOn(); �÷��̾� �״�� �Ѿ��.

	{
		FadeObject* FObject = CreateActor<FadeObject>();
	}

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("RUTAMAP_NPC.Bmp");

	if (nullptr == Ptr)
	{
		MsgBoxAssert("�� �ؽ�ó�� �˼��� �����ϴ�.");
	}

	GlobalValue::MapScale = Ptr->GetScale();

	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}


	BGMPlayer = GameEngineSound::SoundPlay("YggdrasilPrayer.mp3");

	LevelPlayer->SetGroundTexture("RUTAMAP_DebugTT.bmp");

	//Boss->SetPos({ 700, 550 });

	GardenPotal = CreateActor<Potal>(UpdateOrder::Potal);
	GardenPotal->CreateCollision(CollisionOrder::GardenPotal);
	GardenPotal->SetPos({ 2000, 850 });

	RutaNpc* RutaNpcQuest = CreateActor<RutaNpc>(UpdateOrder::Player);
	RutaNpcQuest->SetMouseObject(MouseObject::GetMainMouse());
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

	if (true == GameEngineInput::IsDown('4'))
	{
		GameEngineCore::ChangeLevel("BossLevel");
	}
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}