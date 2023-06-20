#include "ContentCore.h"
#include "StartLevel.h"
#include "PlayLevel.h"
#include "GardenLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

ContentCore::ContentCore()
{

}

ContentCore::~ContentCore()
{

}

void ContentCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 50, 100 }, { 1024, 768 });

	GameEngineCore::CreateLevel<StartLevel>("StartLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<GardenLevel>("GardenLevel");

	GameEngineCore::ChangeLevel("PlayLevel");
	//GameEngineCore::ChangeLevel("GardenLevel");
}