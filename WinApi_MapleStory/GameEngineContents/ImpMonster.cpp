#include "ImpMonster.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Player.h"

#include "Enum.h"
#include <math.h>

std::list<ImpMonster*> ImpMonster::AllMonster;

ImpMonster::ImpMonster()
{
	AllMonster.push_back(this);
}

ImpMonster::~ImpMonster()
{

}

void ImpMonster::AllMonsterDeath()
{
	for (ImpMonster* Monster : AllMonster)
	{
		Monster->Death();
	}
	AllMonster.clear();
}


void ImpMonster::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("LeftImpStand.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("LeftImpStand.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LeftImpStand.bmp"), 6, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LeftImpAttack.bmp"),10 , 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LeftImpDeath.bmp"), 8, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RightImpStand.bmp"), 6, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RightImpAttack.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RightImpDeath.bmp"), 8, 1);
	}

	{
		ImpMonsterRenderer = CreateRenderer(RenderOrder::Monster);
		ImpMonsterRenderer->CreateAnimation("Left_Idle", "LeftImpStand.bmp", 0, 4, 0.2f, true);
		ImpMonsterRenderer->CreateAnimation("Left_Run", "LeftImpStand.bmp", 5, 11, 0.2f, true);
		ImpMonsterRenderer->CreateAnimation("Left_Attack", "LeftImpAttack.bmp", 0, 9, 0.2f, false);
		ImpMonsterRenderer->CreateAnimation("Left_Death", "LeftImpDeath.bmp", 0, 7, 0.2f, false);

		ImpMonsterRenderer->CreateAnimation("Right_Idle", "RightImpStand.bmp", 0, 4, 0.2f, true);
		ImpMonsterRenderer->CreateAnimation("Right_Run", "RightImpStand.bmp", 5, 11, 0.2f, true);
		ImpMonsterRenderer->CreateAnimation("Right_Attack", "RightImpAttack.bmp", 0, 9, 0.2f, false);
		ImpMonsterRenderer->CreateAnimation("Right_Death", "RightImpDeath.bmp", 0, 7, 0.2f, false);
		ImpMonsterRenderer->ChangeAnimation("Left_Idle");
		ChangeState(MonsterState::Idle);
	}

	if (nullptr == GameEngineSound::FindSound("ImpAttack.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("ImpAttack.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("ImpDie.mp3"));
	}

	{
		ImpBodyCollision = CreateCollision(CollisionOrder::MonsterBody);
		ImpBodyCollision->SetCollisionPos(ImpCollisionPosL);
		ImpBodyCollision->SetCollisionScale({ 40, 80 });
		ImpBodyCollision->SetCollisionType(CollisionType::Rect);
	}

	{
		ImpLeftAttackCollision = CreateCollision(CollisionOrder::MonsterAttack);
		ImpLeftAttackCollision->SetCollisionPos(LeftAttackCheck);
		ImpLeftAttackCollision->SetCollisionScale({ 180, 100 });
		ImpLeftAttackCollision->SetCollisionType(CollisionType::Rect);
	}

	{
		ImpRightAttackCollision = CreateCollision(CollisionOrder::MonsterAttack);
		ImpRightAttackCollision->SetCollisionPos(RightAttackCheck);
		ImpRightAttackCollision->SetCollisionScale({ 180, 100 });
		ImpRightAttackCollision->SetCollisionType(CollisionType::Rect);
	}
}

void ImpMonster::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_F2))
	{
		MonsterStatus = !MonsterStatus;
	}

	StateUpdate(_Delta);

	std::vector<GameEngineCollision*> _ImpBodyCol;
	if (true == ImpBodyCollision->Collision(CollisionOrder::PlayerAttack, _ImpBodyCol
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		ImpMonsterRenderer->SetRenderScale({ 192, 192 });
		ImpMonsterRenderer->SetRenderPos({ 0.0f, -10.0f });
		ChangeState(MonsterState::Death);
		return;
	}

	std::vector<GameEngineCollision*> _LefAttacktCol;
	if (Dir == MonsterDir::Left && true == ImpLeftAttackCollision->Collision(CollisionOrder::PlayerBody, _LefAttacktCol
		, CollisionType::Rect // 
		, CollisionType::Rect // 
	))
	{
		Dir = MonsterDir::Left;
		ImpBodyCollision->SetCollisionPos(ImpCollisionPosL);
		ImpMonsterRenderer->SetRenderScale({ 288, 128 });
		ImpMonsterRenderer->SetRenderPos({ -60.0f, -10.0f });
		ChangeState(MonsterState::Attack);
	}
	std::vector<GameEngineCollision*> _RightAttackCol;
	if (Dir == MonsterDir::Right &&	true == ImpRightAttackCollision->Collision(CollisionOrder::PlayerBody, _RightAttackCol
		, CollisionType::Rect // 
		, CollisionType::Rect // 
	))
	{
		Dir = MonsterDir::Right;
		ImpBodyCollision->SetCollisionPos(ImpCollisionPosR);
		ImpMonsterRenderer->SetRenderScale({ 288, 128 });
		ImpMonsterRenderer->SetRenderPos({ 60.f, -10.0f });
		ChangeState(MonsterState::Attack);
	}
}

void ImpMonster::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	

	if (MonsterStatus)
	{
		if (MonsterLeftAttack)
		{
			CollisionData Data;

			Data.Scale = { 180, 5 };
			Data.Pos = ActorCameraPos() + LeftAttackCheckTop;
			Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

			Data.Pos = ActorCameraPos() + LeftAttackCheckBot;
			Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
		}

		if (MonsterRightAttack)
		{
			CollisionData Data;

			Data.Scale = { 180, 5 };
			Data.Pos = ActorCameraPos() + RightAttackCheckTop;
			Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

			Data.Pos = ActorCameraPos() + RightAttackCheckBot;
			Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
		}

		{
			CollisionData Data;

			Data.Scale = { 5, 5 };
			Data.Pos = ActorCameraPos() + LeftCheck;
			Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

			Data.Pos = ActorCameraPos() + RightCheck;
			Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		}

		{
			float4 Pos;
			std::string MonsterState = "";
			MonsterState += "몬스터 상태 : " + AnimationName;
			TextOutA(dc, ActorCameraPos().X, ActorCameraPos().Y - 100, MonsterState.c_str(), static_cast<int>(MonsterState.size()));
		}

		{
			float4 Pos;
			std::string MonsterPosY = "";
			MonsterPosY += ("MoveTime : ");
			MonsterPosY += std::to_string(M_FMoveTime);
			MonsterPosY += ("/");
			MonsterPosY += std::to_string(static_cast<int>(M_FMoveLimitTime));
			TextOutA(dc, ActorCameraPos().X, ActorCameraPos().Y - 80, MonsterPosY.c_str(), static_cast<int>(MonsterPosY.size()));
		}

		{
			float4 Pos;
			std::string MonsterPosY = "";
			MonsterPosY += ("StopTime : ");
			MonsterPosY += std::to_string(static_cast<int>(M_FStopTime));
			MonsterPosY += ("/");
			MonsterPosY += std::to_string(static_cast<int>(M_FStopLimitTime));
			TextOutA(dc, ActorCameraPos().X, ActorCameraPos().Y - 60, MonsterPosY.c_str(), static_cast<int>(MonsterPosY.size()));
		}
	}
}

void ImpMonster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
		break;
	case MonsterState::Run:
		return RunUpdate(_Delta);
		break;
	case MonsterState::Attack:
		return AttackUpdate(_Delta);
		break;
	case MonsterState::Death:
		return DeathUpdate(_Delta);
		break;
	default:
		break;
	}
}

void ImpMonster::ChangeState(MonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Run:
			RunStart();
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		case MonsterState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ImpMonster::ChangeAnimationState(const std::string& _StateName)
{
	switch (Dir)
	{
	case MonsterDir::Right:
		AnimationName = "Right_";
		break;
	case MonsterDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;
	CurState = _StateName;

	ImpMonsterRenderer->ChangeAnimation(AnimationName);
}

void ImpMonster::IdleStart()
{
	ChangeAnimationState("Idle");
	ImpMonsterRenderer->SetRenderScale({ 256, 256 });
	ImpMonsterRenderer->SetRenderPos({ 0.0f, 0.0f });
}

void ImpMonster::IdleUpdate(float _Delta)
{
	M_FStopTime += _Delta;
	if (M_FStopTime >= M_FStopLimitTime)
	{
		ChangeState(MonsterState::Run);
		M_FStopTime = 0.0f;
	}
}

void ImpMonster::RunStart()
{
	idx = GameEngineRandom::MainRandom.RandomInt(0, 2);
	Dir = idx ? MonsterDir::Left : MonsterDir::Right;

	ImpMonsterRenderer->SetRenderScale({ 256, 256 });
	ImpMonsterRenderer->SetRenderPos({ 0.0f, 0.0f });
}

void ImpMonster::RunUpdate(float _Delta)
{
	M_FMoveTime += _Delta;
	IMPMovePos;

	if (Dir == MonsterDir::Left && M_FMoveTime < M_FMoveLimitTime)
	{
		IMPMovePos = { -Speed * _Delta, 0.0f };
		ChangeAnimationState("Run");
		ImpBodyCollision->SetCollisionPos(ImpCollisionPosL);
		CheckPos = LeftCheck;
	}
	if (Dir == MonsterDir::Right && M_FMoveTime < M_FMoveLimitTime)
	{
		IMPMovePos = { Speed * _Delta, 0.0f };
		ChangeAnimationState("Run");
		ImpBodyCollision->SetCollisionPos(ImpCollisionPosR);
		CheckPos = RightCheck;
	}

	if (M_FMoveTime >= M_FMoveLimitTime)
	{
		M_FMoveTime = 0.0f;
		ChangeState(MonsterState::Idle);
	}

	unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	if (RGB(255, 0, 0) != CheckColor)
	{
		AddPos(IMPMovePos);
	}
	if (RGB(255, 0, 0) == CheckColor)
	{
		if (Dir == MonsterDir::Right)
		{
			Dir = MonsterDir::Left;
		}
		if (Dir == MonsterDir::Left)
		{
			Dir = MonsterDir::Right;
		}
	}
}

void ImpMonster::AttackStart()
{
	GameEngineSound::SoundPlay("ImpAttack.mp3");
	ChangeAnimationState("Attack");
	if (Dir == MonsterDir::Left)
	{
		MonsterLeftAttack = !MonsterLeftAttack;
	}

	if (Dir == MonsterDir::Right)
	{
		MonsterRightAttack = !MonsterRightAttack;
	}
}

void ImpMonster::AttackUpdate(float _Delta)
{
	if (true == ImpMonsterRenderer->IsAnimationEnd())
	{
		M_FMoveTime = 0.0f;
		M_FStopTime = 0.0f;
		MonsterLeftAttack = false;
		MonsterRightAttack = false;
		ChangeState(MonsterState::Idle);
	}
}

void ImpMonster::DeathStart()
{
	GameEngineSound::SoundPlay("ImpDie.mp3");
	ChangeAnimationState("Death");
	ImpDeath = true;
	ImpRightAttackCollision->Off();
	ImpLeftAttackCollision->Off();
}
void ImpMonster::DeathUpdate(float _Delta)
{
	if (true == ImpMonsterRenderer->IsAnimationEnd())
	{
		ImpMonsterRenderer->Off();
		ImpBodyCollision->Off();
	}
}