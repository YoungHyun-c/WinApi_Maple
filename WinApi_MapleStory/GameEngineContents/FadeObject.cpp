#include "FadeObject.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "Enum.h"

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

	Render = CreateUIRenderer(RenderOrder::Fade);
	Render->SetTexture("FADE.bmp");
	Render->SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half());
	Render->SetRenderScale(GameEngineWindow::MainWindow.GetScale());
}

void FadeObject::Update(float _Time)
{
	if (FadeDir == true)
	{
		trueValue -= _Time * 200;
		if (0.0f >= trueValue)
		{
			Death();
			return;
		}
		Render->SetAlpha(static_cast<unsigned char>(trueValue));
	}

	if (FadeDir == false)
	{
		falseValue += _Time * 200;
		if (255.0f <= falseValue)
		{
			Death();
			return;
		}
		Render->SetAlpha(static_cast<unsigned char>(falseValue));
	}
}