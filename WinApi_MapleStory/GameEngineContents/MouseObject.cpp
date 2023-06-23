#include "MouseObject.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include "Enum.h"

#include "UIPanel.h"
#include "UICollision.h"

MouseObject::MouseObject()
{

}

MouseObject::~MouseObject()
{

}

void MouseObject::Start()
{
	GameEngineRenderer* CursorRender = CreateRenderer("Mouse.bmp", RenderOrder::PlayUI);

	CursorRender->UICameraSetting();

	GameEnginePath FilePath;
	FilePath.SetCurrentPath();
	FilePath.MoveParentToExistsChild("ContentsResources");

	GameEnginePath FolderPath = FilePath;

	FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Mouse.bmp"), 4, 2);
	CursorRender->SetOrder(4);
	CursorRender->CreateAnimation("Idle", "Mouse.bmp", 0, 0, false);
	CursorRender->SetRenderScale({ 50, 50 });
	CursorRender->ChangeAnimation("Idle");

	Collision = CreateCollision(CollisionOrder::MouseObject);
	Collision->SetCollisionScale({20, 20});
	Collision->IsUIOn();
	
	// CollisionOrder

	// ÀÌ³à¼®Àº UI
	// GameEngineCollision* Col = CreateCollision();
	//GameEngineCollision* UIStatusCollision = CreateCollision(CollisionOrder::InvenIcon);
	//UIStatusCollision->GetActor()->CreateRenderer("Apple.bmp", RenderOrder::PlayUI);
	//UIStatusCollision->SetCollisionScale({ 100, 100 });
	//UIStatusCollision->SetCollisionPos({ 100, 100 });
	//UIStatusCollision->GetActor()->CreateUIRenderer(RenderOrder::PlayUI);
	//UIStatusCollision->GetActor()->Render()
}

void MouseObject::Update(float _Delta)
{
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	SetPos(MousePos);
}

void MouseObject::Render(float _Delta)
{

}