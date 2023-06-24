#include "MouseObjectPlay.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Enum.h"

#include "UICollision.h"
#include "UIPanel.h"

MouseObjectPlay::MouseObjectPlay()
{

}

MouseObjectPlay::~MouseObjectPlay()
{

}

void MouseObjectPlay::Start()
{
	return;
	Collision = CreateCollision(CollisionOrder::MouseObject);
	Collision->SetCollisionScale({ 50, 50 });
}

void MouseObjectPlay::Update(float _Delta)
{
	return;
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	float4 PlayMousePos = CameraPos + MousePos;
	SetPos(PlayMousePos);
}


void MouseObjectPlay::Render(float _Delta)
{

}