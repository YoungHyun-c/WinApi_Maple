#include "ContentCore.h"
#include "StartLevel.h"
#include "PracticeLevel.h"
#include "EreveLevel.h"
#include "PlayLevel.h"
#include "GardenLevel.h"
#include "BossLevel.h"
#include "EndLevel.h"
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
	GameEngineSound::SetGlobalVolume(0.3f);

	GameEngineCore::CreateLevel<StartLevel>("StartLevel");
	GameEngineCore::CreateLevel<PracticeLevel>("PracticeLevel");
	GameEngineCore::CreateLevel<EreveLevel>("EreveLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<GardenLevel>("GardenLevel");
	GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	GameEngineCore::CreateLevel<EndLevel>("EndLevel");

	GameEngineCore::ChangeLevel("StartLevel");
	//GameEngineCore::ChangeLevel("PracticeLevel");
	//GameEngineCore::ChangeLevel("EreveLevel");
	//GameEngineCore::ChangeLevel("PlayLevel");
	//GameEngineCore::ChangeLevel("GardenLevel");
	//GameEngineCore::ChangeLevel("BossLevel");
	//GameEngineCore::ChangeLevel("EndLevel");
}