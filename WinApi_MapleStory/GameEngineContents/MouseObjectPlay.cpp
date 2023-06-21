#include "MouseObjectPlay.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Enum.h"

MouseObjectPlay::MouseObjectPlay()
{

}

MouseObjectPlay::~MouseObjectPlay()
{

}

void MouseObjectPlay::Start()
{
	// 랜더러를 만들필요가 없다.
	Collision = CreateCollision(CollisionOrder::MouseObject);
	Collision->SetCollisionScale({ 100, 100 });


}

void MouseObjectPlay::Update(float _Delta)
{
	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	float4 PlayMousePos = CameraPos + MousePos;
	SetPos(PlayMousePos);

	// 콜리전도 따라오게 되고 

	std::vector<GameEngineCollision*> Results;

	if (Collision->Collision(CollisionOrder::MonsterBody, Results))
	{
		for (size_t i = 0; i < Results.size(); i++)
		{
			Results[i]->GetActor()->Death();
		}
	}
}


void MouseObjectPlay::Render(float _Delta)
{

}