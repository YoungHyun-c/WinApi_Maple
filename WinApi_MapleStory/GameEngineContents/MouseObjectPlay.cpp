#include "MouseObjectPlay.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Enum.h"

#include "UIPanel.h"

MouseObjectPlay::MouseObjectPlay()
{

}

MouseObjectPlay::~MouseObjectPlay()
{

}

void MouseObjectPlay::Start()
{
	Collision = CreateCollision(CollisionOrder::MouseObjectPlay);
	Collision->SetCollisionPos({ -5, -10 });
	Collision->SetCollisionScale({ 20, 20 });
}

void MouseObjectPlay::Update(float _Delta)
{
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	float4 PlayMousePos = CameraPos + MousePos;
	SetPos(PlayMousePos);
}


void MouseObjectPlay::Render(float _Delta)
{

}