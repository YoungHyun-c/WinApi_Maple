#include "FadeObject.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

FadeObject::FadeObject() 
{
}

FadeObject::~FadeObject() 
{
}

void FadeObject::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("FADE.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("FADE.bmp"));
	}

	GameEngineRenderer* Render = CreateUIRenderer(200);
	Render->SetTexture("FADE.bmp");
	Render->SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half());
	Render->SetRenderScale(GameEngineWindow::MainWindow.GetScale());
	// Render->SetAlpha();
	// Render->AddAlpha(-Delta * 255.0f);
}

