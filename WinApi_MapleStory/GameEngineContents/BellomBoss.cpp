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
		Bellom->CreateAnimation("Left_Wake", "Bellom2.bmp", 0, 7, 0.15f, false);
		Bellom->CreateAnimation("Left_Down", "Bellom3.bmp", 0, 11, 0.15f, false);
		Bellom->CreateAnimation("Left_AttackReady", "BellomAttackReady.bmp", 0, 9, 0.1f, false);
		Bellom->CreateAnimation("Left_Attack", "BellomAttack.bmp", 0, 5, 0.1f, false);
		Bellom->CreateAnimation("Left_AttackBall", "BellomAttackBall.bmp", 0, 9, 0.1f, false);
		Bellom->CreateAnimation("Left_Death", "BossDie.bmp", 0, 9, 0.2f, false);
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

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomDamage.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomDeath.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomAttack1.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomAttack5.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomAttack9.mp3"));
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
		ChangeState(BossState::Summon);
		BellomSummon->Off();
		Summon = true;
	}

	// °¡¸¸È÷ ³ÀµÎ°í Á×ÀÌ±â
	if (GameEngineInput::IsDown(VK_F6))
	{
		Bellom->SetRenderPos({ Player::GetMainPlayer()->GetPos().X, 400 });
		GameEngineSound::SoundPlay("BellomAttack9.mp3");
		Bellom->ChangeAnimation("Left_Wake");
		Bellom->SetRenderPos({ 1700, 380 });
		Bellom->SetRenderScale({ 1024, 1024 });
		BellomBody->On();
		BellomBody->SetCollisionPos({ 1730.0f, 600.0f });
		BellomBody->SetCollisionScale({ 150.0f, 300.0f });
		BossStop = true;
	}

	// ¸ð¼Ç Å×½ºÆ®
	if (GameEngineInput::IsDown(VK_F7))
	{
		Bellom->SetRenderPos({ Player::GetMainPlayer()->GetPos().X, 400 });
		ChangeAnimationState("Ready");
		//GameEngineSound::SoundPlay("BellomAttack9.mp3");
		//Bellom->ChangeAnimation("Left_Wake");
		//Bellom->SetRenderPos({ 1700, 380 });
		//Bellom->SetRenderScale({ 1024, 1024 });
		//BossStop = true;
	}

	if (BossStop == false)
	{
		StateUpdate(_Delta);
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

	if (AttackCount == 10)
	{
		DeathTime += _Delta;
		ChangeState(BossState::Death);
		if (DeathTime >= DeathLimitTime && true == Bellom->IsAnimationEnd())
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

void BellomBoss::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BossState::Summon():
		return SummonUpdate(_Delta);
		break;
	case BossState::Idle:
		return IdleUpdate(_Delta);
		break;
	case BossState::Ready:
		return ReadyUpdate(_Delta);
		break;
	case BossState::Wake:
		return WakeUpdate(_Delta);
		break;
	case BossState::Down:
		return DownUpdate(_Delta);
		break;
	case BossState::AttackReady:
		return AttackReadyUpdate(_Delta);
		break;
	case BossState::AttackBall:
		return AttackBallUpdate(_Delta);
		break;
	case BossState::AttackBallBomb:
		break;
	case BossState::Death:
		return DeathUpdate(_Delta);
		break;
	default:
		break;
	}
}

void BellomBoss::ChangeState(BossState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BossState::Summon:
			SummonStart();
			break;
		case BossState::Idle:
			IdleStart();
			break;
		case BossState::Ready:
			ReadyStart();
			break;
		case BossState::Wake:
			WakeStart();
			break;
		case BossState::Down:
			DownStart();
			break;
		case BossState::AttackReady:
			AttackReadyStart();
			break;
		case BossState::AttackBall:
			AttackBallStart();
			break;
		case BossState::AttackBallBomb:
			break;
		case BossState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void BellomBoss::ChangeAnimationState(const std::string& _StateName)
{
	AnimationName = "Left_";

	AnimationName += _StateName;
	CurState = _StateName;

	Bellom->ChangeAnimation(AnimationName);
}


void BellomBoss::SummonStart()
{
	ChangeAnimationState("Ready");
	GameEngineSound::SoundPlay("BellomAttack1.mp3");
	Bellom->On();
	Bellom->SetRenderPos({ 1700, 400 });
}

void BellomBoss::SummonUpdate(float _Delta)
{
	B_FWakeTime += _Delta;
	if (true == Bellom->IsAnimationEnd())
	{
		ChangeAnimationState("Wake");
	}

	if (true == Bellom->IsAnimationEnd())
	{
		ChangeAnimationState("Down");
	}

	if (B_FWakeTime >= 4.5f)
	{
		ChangeState(BossState::Down);
		B_FWakeTime = 0.0f;
	}
}

void BellomBoss::IdleStart()
{
	//ChangeAnimationState("Wake");
}

void BellomBoss::IdleUpdate(float _Delta)
{

}

void BellomBoss::DownStart()
{
	Bellom->Off();
}

void BellomBoss::DownUpdate(float _Delta)
{
	B_FDownTime += _Delta;

	if (B_FDownTime >= b_FDownLimitTime)
	{
		switch (Attack)
		{
		case 0:
			B_FDownTime = 0.0f;
			ChangeState(BossState::Ready);
			break;
		case 1:
			B_FDownTime = 0.0f;
			ChangeState(BossState::AttackReady);
			break;
		}
	}
}

void BellomBoss::ReadyStart()
{
	Bellom->On();
	Bellom->SetRenderPos({ Player::GetMainPlayer()->GetPos().X, 400.0f });
	GameEngineSound::SoundPlay("BellomAttack1.mp3");
	ChangeAnimationState("Ready");
	Attack += 1;
	BellomBody->SetCollisionPos({ Player::GetMainPlayer()->GetPos().X, 600.0f });
}
void BellomBoss::ReadyUpdate(float _Delta)
{
	B_FDownTime += _Delta;

	if (true == Bellom->IsAnimationEnd())
	{
		ChangeAnimationState("Wake");
		BellomBody->On();
	}

	if (true == Bellom->IsAnimationEnd())
	{
		ChangeAnimationState("Down");
		BellomBody->Off();
	}

	if (B_FDownTime >= 4.5f)
	{
		//BellomBody->Off();
		B_FDownTime = 0.0f;
		ChangeState(BossState::Down);
	}
}

void BellomBoss::WakeStart()
{

}
void BellomBoss::WakeUpdate(float _Delta)
{

}

void BellomBoss::AttackReadyStart()
{
	Attack = 0;
	Bellom->On();
	Bellom->SetRenderPos({ Player::GetMainPlayer()->GetPos().X + 500.0f, 400.0f });
	BellomSaveAttackPosX = Player::GetMainPlayer()->GetPos().X + 500.0f;
	BellomAttackReadyPosX = Player::GetMainPlayer()->GetPos().X - 180.0f;
	BellomAttackPosX = Player::GetMainPlayer()->GetPos().X - 80.0f;
	BellomAttackBallPosX = Player::GetMainPlayer()->GetPos().X - 180.0f;

	GameEngineSound::SoundPlay("BellomAttack9.mp3");
	ChangeAnimationState("Ready");
	BellomBody->SetCollisionPos({ Player::GetMainPlayer()->GetPos().X + 500.0f, 600.0f });
}
void BellomBoss::AttackReadyUpdate(float _Delta)
{
	B_FDownTime += _Delta;

	if (true == Bellom->IsAnimationEnd() && AttackCheck == 0)
	{
		ChangeAnimationState("Wake");
		AttackCheck += 1;
		BellomBody->On();
	}

	if (true == Bellom->IsAnimationEnd() && AttackCheck == 1)
	{
		ChangeAnimationState("AttackReady");
		Bellom->SetRenderPos({ BellomAttackPosX, 330.0f });
		//Bellom->SetRenderScale({ 1536, 1024 });
		Bellom->SetRenderScale({ 1792, 1024 });
		AttackCheck += 1;
	}

	if (true == Bellom->IsAnimationEnd() && AttackCheck == 2)
	{
		ChangeAnimationState("Attack");
		//Bellom->SetRenderScale({ 1280, 1024 });
		Bellom->SetRenderScale({ 1536, 1024 });
		Bellom->SetRenderPos({ BellomAttackPosX, 260.0f });
		AttackCheck += 1;
	}

	if (true == Bellom->IsAnimationEnd() && AttackCheck == 3)
	{
		ChangeAnimationState("AttackBall");
		Bellom->SetRenderPos({ BellomAttackPosX, 330.0f });
		Bellom->SetRenderScale({ 1792, 1024 });
		AttackCheck += 1;
	}

	if (true == Bellom->IsAnimationEnd() && AttackCheck == 4)
	{
		ChangeAnimationState("Down");
		Bellom->SetRenderPos({ BellomSaveAttackPosX, 400.0f });
		Bellom->SetRenderScale({ 1024, 1024 });
		BellomBody->Off();
	}

	if (B_FDownTime >= 7.2f)
	{
		//BellomBody->Off();
		B_FDownTime = 0.0f;
		AttackCheck = 0;
		ChangeState(BossState::Down);
	}
}

void BellomBoss::AttackBallStart()
{
}
void BellomBoss::AttackBallUpdate(float _Delta)
{
}

void BellomBoss::DeathStart()
{
	ChangeAnimationState("Death");
	GameEngineSound::SoundPlay("BellomDeath.mp3");
	Bellom->SetRenderScale({ 896, 896 });
	//Bellom->SetRenderPos({ 1700, 370 });

	if (true == Bellom->IsAnimationEnd())
	{
		Death();
	}
}
void BellomBoss::DeathUpdate(float _Delta)
{
	//if (true == Bellom->IsAnimationEnd())
	//{
	//	Death();
	//}
}
