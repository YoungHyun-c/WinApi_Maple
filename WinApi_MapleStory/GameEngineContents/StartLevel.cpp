#include "StartLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

StartLevel::StartLevel()
{

}

StartLevel::~StartLevel()
{
	
}

void StartLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown(VK_RETURN))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}