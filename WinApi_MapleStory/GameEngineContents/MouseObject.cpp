#include "MouseObject.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include "Enum.h"

MouseObject::MouseObject()
{

}

MouseObject::~MouseObject()
{

}

void MouseObject::Start()
{
	GameEngineRenderer* CursorRender = CreateRenderer("Mouse.bmp", RenderOrder::Play);
	// 난 UI를 이걸 안하고 있다.
	CursorRender->UICameraSetting();

	//CursorRender->SetTexture("Mouse.bmp");
	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");

	GameEnginePath FolderPath = FilePath;

	FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Mouse.bmp"), 4, 2);

	CursorRender->CreateAnimation("Idle", "Mouse.bmp", 0, 1, 0.3f);
	CursorRender->SetRenderScale({ 50, 50 });
	CursorRender->ChangeAnimation("Idle");

	// CollisionOrder

	// 이녀석은 UI
	// GameEngineCollision* Col = CreateCollision();
}

void MouseObject::Update(float _Delta)
{
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	SetPos(MousePos);
}

void MouseObject::Render(float _Delta)
{

}