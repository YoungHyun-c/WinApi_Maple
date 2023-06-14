#include "PlayLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/TileMap.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include "Monster.h"
#include "FadeObject.h"
#include "PlayUIManager.h"


// Contents
#include "Player.h"
#include "BackGround.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Start() 
{
	GameEngineSound::SetGlobalVolume(0.05f);

	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("StageTestPixel.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Tile.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet("Tile.bmp", 24, 40);

	}

	if (nullptr == GameEngineSound::FindSound("BGMTest.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BGMTest.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("1-Up.wav"));
		
	}




	// ResourcesManager::GetInst().TextureLoad("AAA.Png", 경로);

	// 플레이 레벨이 만들어졌다.
	// 이 레벨에는 뭐가 있어야지?
	// 플레이어 만들고
	// 맵만들고
	// 몬스터 만들고
	// 액터

	// 자기 임의대로 만들겠다는 것이고 xxxxx
	// Player* NewPlayer = new Player();

	// GameEngineWindow::MainWindow.CursorOff();

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("StageTest.Bmp", "StageTestPixel.bmp");

	// TileObject = CreateActor<TileMap>();
	// TileObject->CreateTileMap("Tile.bmp", 20, 20, {50, 50}, 0);
	/*for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			TileObject->SetTile(x, y, 0);
		}
	}*/


	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("StageTestPixel.bmp");
	// LevelPlayer->GravityOff();
	LevelPlayer->OverOn();

	//{
	//	GameEngineActor* FObject = CreateActor<FadeObject>();
	//}
	

	CreateActor<PlayUIManager>();
}


void PlayLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		// BGMPlayer.Stop();

		// GameEngineCore::ChangeLevel("TitleLevel");

		TileObject->SetTile(LevelPlayer->GetPos(), 3);


	}

	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}

	if (1.0f <= GetLiveTime())
	{
		Monster* NewMonster = CreateActor<Monster>();
		ResetLiveTime();
	}

	// GameEngineCore::ChangeLevel("TitleLevel");
}
void PlayLevel::Release() 
{
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel) 
{


	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다");
	}

	// BGMPlayer = GameEngineSound::SoundPlay("BGMTest.mp3");

	GameEngineSound::SoundPlay("1-Up.wav");
	

	LevelPlayer->SetGroundTexture("StageTestPixel.bmp");

	//float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	////LevelPlayer->SetPos(WinScale.Half());
	//// 0 0
	//// x y
	//GetMainCamera()->SetPos(LevelPlayer->GetPos() - WinScale.Half());

}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{

}