#include "BellomBoss.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"

#include <GameEnginePlatform/GameEngineInput.h>"
#include "Enum.h"

BellomBoss::BellomBoss()
{

}

BellomBoss::~BellomBoss()
{

}

void BellomBoss::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Bellom1.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");

		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Bellom.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bellom1.bmp"), 4, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bellom2.bmp"), 4, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bellom3.bmp"), 4, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BellomAttackReady.bmp"), 6, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BellomAttack.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BellomAttackBall.bmp"), 5, 2);
	}

	{
		Bellom = CreateRenderer(RenderOrder::Monster);
		Bellom->CreateAnimation("Left_Ready", "Bellom1.bmp", 0, 7, 0.2f, false);
		Bellom->CreateAnimation("Left_Wake", "Bellom2.bmp", 0, 7, 0.2f, false);
		Bellom->CreateAnimation("Left_Down", "Bellom3.bmp", 0, 11, 0.2f, false);
		Bellom->CreateAnimation("AttackReady", "BellomAttackReady.bmp", 0, 9, 0.2f, false);
		Bellom->CreateAnimation("Attack", "BellomAttack.bmp", 0, 5, 0.2f, false);
		Bellom->CreateAnimation("AttackBall", "BellomAttackBall.bmp", 0, 9, 0.2f, false);
		Bellom->SetRenderScale({ 1024, 1024 });
		//Bellom->SetRenderPos({ 1700, 300 });
		//Bellom->ChangeAnimation("AttackReady");
		Bellom->Off();
	}

	BellomSummon = CreateCollision(CollisionOrder::BossSummon);
	BellomSummon->SetCollisionPos({ 1690, 650 });
	BellomSummon->SetCollisionScale({ 200, 100 });

}

void BellomBoss::Update(float _Delta)
{
	std::vector<GameEngineCollision*> Col;
	if (BellomSummon->Collision(CollisionOrder::MouseObjectPlay, Col, CollisionType::Rect, CollisionType::Rect)
		&& GameEngineInput::IsDown(VK_LBUTTON))
	{
		Bellom->On();
		Bellom->SetRenderPos({ 1700, 400 });
		Bellom->ChangeAnimation("Left_Ready");
		Summon = true;
		BellomSummon->Off();
	}

	if (true == Summon)
	{
		MoveTime += _Delta;
	}

	if (MoveTime >= 1.5f && true == Bellom->IsAnimationEnd())
	{
		Bellom->ChangeAnimation("Left_Wake");
	}

	if (MoveTime >= 3.0f && true == Bellom->IsAnimationEnd())
	{
		Bellom->ChangeAnimation("Left_Down");
	}

	//if (GameEngineInput::IsDown(VK_F6))
	//{
	//	Bellom->ChangeAnimation("AttackReady");

	//	Bellom->SetRenderPos({ 1700, 300 });
	//	Bellom->SetRenderScale({ 1024, 1024 });
	//}
	//if (GameEngineInput::IsDown(VK_F7))
	//{
	//	//Bellom->ChangeAnimation("Attack");
	//	//Bellom->SetRenderPos({ 150, 430 });
	//	//Bellom->SetRenderScale({ 1536, 1024 });
	//	Bellom->ChangeAnimation("Attack");
	//	Bellom->SetRenderPos({ 1700, 300 });
	//	Bellom->SetRenderScale({ 1024, 1024 });
	//}
	//if (GameEngineInput::IsDown(VK_F8))
	//{
	//	Bellom->ChangeAnimation("AttackBall");
	//	Bellom->SetRenderPos({ 1700, 300 });
	//	Bellom->SetRenderScale({ 1024, 1024 });
	//}
	//if (GameEngineInput::IsDown(VK_F9))
	//{
	//	Bellom->ChangeAnimation("Left_Ready");
	//	Bellom->SetRenderPos({ 1700, 300 });
	//	Bellom->SetRenderScale({ 1024, 1024 });
	//}

	//MoveTime += _Delta;
	//if (MoveTime <= 1.5f)
	//{
	//	Bellom->ChangeAnimation("AttackReady");
	//}

	//if (MoveTime >= 3.0f && true == Bellom->IsAnimationEnd())
	//{
	//	Bellom->ChangeAnimation("Attack");
	//}

	//if (MoveTime >= 4.0f && true == Bellom->IsAnimationEnd())
	//{
	//	Bellom->ChangeAnimation("AttackBall");
	//}

	//if (MoveTime >= 7.0f)
	//{
	//	MoveTime = 0.0f;
	//}

	//if (true == Bellom->IsAnimationEnd())
	//{
	//	Bellom->ChangeAnimation("AttackBall");
	//}
	//MoveTime += _Delta;

	//if (MoveTime >= 2.5f)
	//{
	//	Bellom->ChangeAnimation("Attack");
	//}
	//if (MoveTime >= 5.0f)
	//{
	//	Bellom->ChangeAnimation("AttackBall");
	//	if (true == Bellom->IsAnimationEnd())
	//	{
	//		MoveTime = 0.0f;
	//	}
	//}
}