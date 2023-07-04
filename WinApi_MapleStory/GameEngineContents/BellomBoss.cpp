#include "BellomBoss.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>"
#include <GameEnginePlatform/GameEngineWindow.h>



#include "Player.h"
#include "PlayActor.h"
#include "Enum.h"

BellomBoss* BellomBoss::MainBoss = nullptr;
bool BellomBoss::Summon = false;

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
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\Bellom\\");

		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Bellom.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bellom1.bmp"), 4, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bellom2.bmp"), 4, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bellom3.bmp"), 4, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BellomAttackReady.bmp"), 6, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BellomAttack.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BellomAttackBall.bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BossDie.bmp"), 10, 1);
	}

	{
		Bellom = CreateRenderer(RenderOrder::Monster);
		Bellom->CreateAnimation("Left_Ready", "Bellom1.bmp", 0, 7, 0.2f, false);
		Bellom->CreateAnimation("Left_Wake", "Bellom2.bmp", 0, 7, 0.2f, false);
		Bellom->CreateAnimation("Left_Down", "Bellom3.bmp", 0, 11, 0.2f, false);
		Bellom->CreateAnimation("AttackReady", "BellomAttackReady.bmp", 0, 9, 0.2f, false);
		Bellom->CreateAnimation("Attack", "BellomAttack.bmp", 0, 5, 0.2f, false);
		Bellom->CreateAnimation("AttackBall", "BellomAttackBall.bmp", 0, 9, 0.2f, false);
		Bellom->CreateAnimation("Die", "BossDie.bmp", 0, 9, 0.2f, false);
		Bellom->SetRenderScale({ 1024, 1024 });
		//Bellom->SetRenderPos({ 1700, 300 });
		//Bellom->ChangeAnimation("AttackReady");
		Bellom->Off();
	}

	GameEngineSound::SetGlobalVolume(0.3f);
	if (nullptr == GameEngineSound::FindSound("BellomAttack1.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomAttack1.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomDamage.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomDie.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomDamage.mp3"));
	}

	// º§·ë ¼ÒÈ¯
	{
		BellomSummon = CreateCollision(CollisionOrder::BossSummon);
		BellomSummon->SetCollisionPos({ 1690.0f, 650.0f });
		BellomSummon->SetCollisionScale({ 200.0f, 100.0f });
	}

	// º§·ë ¸öÅë
	{
		BellomBody = CreateCollision(CollisionOrder::MonsterBody);
		BellomBody->SetCollisionPos({ 1730.0f, 600.0f });
		BellomBody->SetCollisionScale({ 150.0f, 300.0f });
		BellomBody->Off();
	}

}

void BellomBoss::Update(float _Delta)
{
	std::vector<GameEngineCollision*> Col;
	if (BellomSummon->Collision(CollisionOrder::MouseObjectPlay, Col, CollisionType::Rect, CollisionType::Rect)
		&& GameEngineInput::IsDown(VK_LBUTTON))
	{
		Bellom->On();
		Bellom->SetRenderPos({ 1700, 400 });
		GameEngineSound::SoundPlay("BellomAttack1.mp3");
		Bellom->ChangeAnimation("Left_Ready");
		Summon = true;
		BellomSummon->Off();
		BellomBody->On();
	}

	if (true == Summon)
	{
		MoveTime += _Delta;
	}

	if (MoveTime >= 1.5f && true == Bellom->IsAnimationEnd())
	{
		Bellom->ChangeAnimation("Left_Wake");
	}

	std::vector<GameEngineCollision*> _BellomBodyCol;
	if (true == BellomBody->Collision(CollisionOrder::PlayerAttack, _BellomBodyCol
		, CollisionType::Rect
		, CollisionType::Rect) && GameEngineInput::IsDown(VK_SHIFT))
	{
		GameEngineSoundPlayer BellomDamage = GameEngineSound::SoundPlay("BellomDamage.mp3");
		GetMainBossHP(141);
		GetMainBossHpBarMove();
		AttackCount += 1;
		return;
	}

	if (MoveTime >= 10.0f && AttackCount == 10)
	{
		Bellom->SetRenderScale({ 896, 896 });
		Bellom->SetRenderPos({ 1700, 370 });
		Bellom->ChangeAnimation("Die");

		if (true == Bellom->IsAnimationEnd())
		{
			Death();
		}
	}

	// ¶÷´Ù.
	//BellomBody->CollisionCallBack(
	//	CollisionOrder::PlayerAttack
	//	, CollisionType::Rect
	//	, CollisionType::Rect
	//	, [](GameEngineCollision* _this, GameEngineCollision* _Other)
	//	{
	//		if (true == GameEngineInput::IsUp(VK_SHIFT))
	//		{
	//			GameEngineActor* ThisActor = _this->GetActor();
	//			BellomBoss* BossPtr = dynamic_cast<BellomBoss*>(ThisActor);

	//			GameEngineActor* PlayerActor = _Other->GetActor();
	//			Player* PlayerPtr = dynamic_cast<Player*>(PlayerActor);

	//			GameEngineSoundPlayer BellomDamage = GameEngineSound::SoundPlay("BellomDamage.mp3");
	//			//ThisActor->
	//		}
	//		//ThisActor->AttackDamage(100);
	//		//ThisActor->Death();
	//	}
	//	, [](GameEngineCollision* _this, GameEngineCollision* _Other)
	//	{

	//	}
	//	, [](GameEngineCollision* _this, GameEngineCollision* _Other)
	//	{
	//		GameEngineActor* ThisActor = _this->GetActor();
	//		BellomBoss* BossPtr = dynamic_cast<BellomBoss*>(ThisActor);

	//		GameEngineActor* PlayerActor = _Other->GetActor();
	//		Player* PlayerPtr = dynamic_cast<Player*>(PlayerActor);

	//		GameEngineSoundPlayer BellomDamage = GameEngineSound::SoundPlay("BellomDamage.mp3");
	//		//ThisActor->AttackDamage(100);
	//		//ThisActor->Death();
	//	}
	//);


	//if (MoveTime >= 3.0f && true == Bellom->IsAnimationEnd())
	//{
	//	Bellom->ChangeAnimation("Left_Down");
	//}

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

void BellomBoss::Render(float _Delta)
{

}

void BellomBoss::LevelStart()
{
	MainBoss = this;
}

