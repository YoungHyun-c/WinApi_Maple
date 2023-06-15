#include "ContentCore.h"
#include "StartLevel.h"
#include "PlayLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

ContentCore::ContentCore()
{

}

ContentCore::~ContentCore()
{

}

void ContentCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 50, 50 }, { 1024, 768 });

	GameEngineCore::CreateLevel<StartLevel>("StartLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");

	GameEngineCore::ChangeLevel("PlayLevel");
}