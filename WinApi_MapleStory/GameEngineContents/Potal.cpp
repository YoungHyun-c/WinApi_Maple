#include "Potal.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Player.h"
#include "Enum.h"

Potal::Potal()
{

}

Potal::~Potal()
{

}

void Potal::Start()
{
	//GardenPotal = CreateCollision(CollisionOrder::GardenPotal);
	//GardenPotal->SetCollisionScale({ 100, 100 });

	//BossPotal = CreateCollision(CollisionOrder::BossPotal);
	//BossPotal->SetCollisionScale({ 100 ,100 });
	GameEngineCollision* PotalScale = CreateCollision(CollisionOrder::Potal);
	PotalScale->SetCollisionScale({ 100, 100 });
}

void Potal::Update(float _Delta)
{
	
}
