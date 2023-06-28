#include "MouseObject.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Enum.h"

#include "UIPanel.h"
#include "UIQuest.h"

MouseObject* MouseObject::MainMouse = nullptr;

MouseObject::MouseObject()
{

}

MouseObject::~MouseObject()
{

}

void MouseObject::Start()
{
	MainMouse = this;

	if (false == ResourcesManager::GetInst().IsLoadTexture("Mouse.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Mouse.bmp"), 4, 2);

		CursorRenderer = CreateRenderer("Mouse.bmp", RenderOrder::MouseUI);
		CursorRenderer->UICameraSetting();
		CursorRenderer->SetOrder(4);

		CursorRenderer->CreateAnimation("Idle", "Mouse.bmp", 0, 0, false);
		CursorRenderer->CreateAnimation("Grab", "Mouse.bmp", 4, 6, 0.4f, true);
		CursorRenderer->CreateAnimation("GrabIdle", "Mouse.bmp", 6, 6, false);
		CursorRenderer->SetRenderScale({ 50, 50 });
		CursorRenderer->ChangeAnimation("Idle");

		Collision = CreateCollision(CollisionOrder::MouseObject);
		Collision->SetCollisionPos({ -5, -10 });
		Collision->SetCollisionScale({ 10, 10 });
		Collision->IsUIOn();
	}

}

void MouseObject::Update(float _Delta)
{
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	SetPos(MousePos);
}

void MouseObject::Render(float _Delta)
{

}

void MouseObject::ChangeAnimationState(const std::string& _StateName)
{

	std::string AnimationName;

	AnimationName = _StateName;

	CursorRenderer->ChangeAnimation(AnimationName);
}