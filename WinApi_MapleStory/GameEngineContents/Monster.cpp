#include "Monster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Player.h"

#include "Enum.h"

std::list<Monster*> Monster::AllMonster;


Monster::Monster()
{
	AllMonster.push_back(this);
}

Monster::~Monster()
{

}

void Monster::AllMonsterDeath()
{
	for (Monster* Monster : AllMonster)
	{
		Monster->Death();
	}

	AllMonster.clear();
}

void Monster::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("BlueSnailStand.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\BlueSnail\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("BlueSnailStand.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BlueSnailStand.bmp"), 2, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BlueSnailMove.bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BlueSnailDeath.bmp"), 6, 2);
	}

	{
		BlueSnailRenderer = CreateRenderer(RenderOrder::Monster);
		BlueSnailRenderer->CreateAnimation("Left_Idle", "BlueSnailStand.bmp", 0, 0, 0.1f, true);
		BlueSnailRenderer->CreateAnimation("Right_Idle", "BlueSnailStand.bmp", 1, 1, 0.1f, true);
		BlueSnailRenderer->CreateAnimation("Left_Run", "BlueSnailMove.bmp", 0, 4, 0.3f, true);
		BlueSnailRenderer->CreateAnimation("Right_Run", "BlueSnailMove.bmp", 5, 9, 0.3f, true);
		BlueSnailRenderer->CreateAnimation("Left_Death", "BlueSnailDeath.bmp", 0, 5, 0.2f, true);
		BlueSnailRenderer->CreateAnimation("Right_Death", "BlueSnailDeath.bmp", 6, 11, 0.2f, true);
		BlueSnailRenderer->ChangeAnimation("Right_Idle");
		ChangeState(MonsterState::Idle);
	}

	if (nullptr == GameEngineSound::FindSound("Die.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");

		GameEngineSound::SoundLoad(FilePath.PlusFilePath("Die.mp3"));
	}

	{
		MonsterBodyCol = CreateCollision(CollisionOrder::MonsterBody);
		MonsterBodyCol->SetCollisionScale({ 50, 50 });
		MonsterBodyCol->SetCollisionType(CollisionType::Rect);
	}

}

void Monster::Update(float _Delta)
{
	//float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	//Dir.Normalize();

	//AddPos(Dir * _Delta * 100.0f);

	// Dir *= 0.1f;


	//float Speed = 30.0f;
	//BlueSnailMovePos;

	//Dir = MonsterDir::Right;
	//ChangeAnimationState("Run");
	M_FMoveTime += _Delta;

	//DirCheck();

	//if (M_FStopTime <= M_FMoveTime)
	//{
	//	BlueSnailMovePos = { -Speed * _Delta, 0.0f };
	//	Dir = MonsterDir::Left;
	//	ChangeAnimationState("Run");
	//	AddPos(BlueSnailMovePos);

	//	if (M_FMoveTime >= 7.0f)
	//	{
	//		M_FMoveTime = M_FMoveLimitTime;
	//	}
	//}
	//else
	//{
	//	Dir = MonsterDir::Right;
	//	BlueSnailMovePos = { Speed * _Delta, 0.0f };
	//	AddPos(BlueSnailMovePos);
	//}

	StateUpdate(_Delta);

	std::vector<GameEngineCollision*> _Col;
	if (true == MonsterBodyCol->Collision(CollisionOrder::PlayerAttack, _Col
		, CollisionType::Rect // 
		, CollisionType::Rect // 
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			ChangeState(MonsterState::Death);
			//BlueSnailRenderer->ChangeAnimation("Right_Death");

			//if (BlueSnailRenderer->IsAnimationEnd())
			//{
			//	Actor->Death();
			//}
		}
	}

	//std::string StrPos ="";
	//swprintf_s(StrPos, L"Move : %.2f / %.2f", M_FMoveTime, m_fMoveLimitTime);
	//TextOut(hDC, x, y + 60, strPos, lstrlen(strPos));
}

void Monster::Render(float _Delta)
{
	//HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	//std::string StrPos = "";
	//StrPos += "MoveTime : ";
	//StrPos += std::to_string(M_FMoveTime);
	//TextOutA(dc, BlueSnailX + BlueSnailMovePos.X, BlueSnailY + BlueSnailMovePos.Y, StrPos.c_str(), static_cast<int>(StrPos.size()));
}

void Monster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	case MonsterState::Run:
		return RunUpdate(_Delta);
	case MonsterState::Death:
		return DeathUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Monster::ChangeState(MonsterState _State)
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
		case MonsterState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Monster::DirCheck()
{
	//int idx = rand() % 2;
	//Dir = idx ? MonsterDir::Right : MonsterDir::Left;
}

void Monster::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName;

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

	BlueSnailRenderer->ChangeAnimation(AnimationName);
}


void Monster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Monster::IdleUpdate(float _Delta)
{
	if (M_FStopTime <= M_FMoveTime)
	{
		Dir = MonsterDir::Right;
		ChangeState(MonsterState::Run);
		M_FMoveTime = 0.0f;
	}
}

void Monster::RunStart()
{
	ChangeAnimationState("Run");
	idx = rand() % 2;
	Dir = idx ? MonsterDir::Right : MonsterDir::Left;
	int a = 0;
}

void Monster::RunUpdate(float _Delta)
{

	float Speed = 30.0f;
	BlueSnailMovePos;

	//ChangeAnimationState("Run");
	//AddPos(BlueSnailMovePos);
	if (M_FStopTime <= M_FMoveTime && idx == 0)
	{
		BlueSnailMovePos = { -Speed * _Delta, 0.0f };
		//Dir = MonsterDir::Left;
		ChangeAnimationState("Run");
		AddPos(BlueSnailMovePos);

		if (M_FMoveTime >= 7.0f)
		{
			M_FMoveTime = M_FMoveLimitTime;
			ChangeState(MonsterState::Idle);
		}
	}
	else
	{
		//Dir = MonsterDir::Right;
		BlueSnailMovePos = { Speed * _Delta, 0.0f };
		AddPos(BlueSnailMovePos);
	}
}

void Monster::DeathStart()
{
	ChangeAnimationState("Death");
	GameEngineSound::SoundPlay("Die.mp3");
}

void Monster::DeathUpdate(float _Delta)
{
	if (true == BlueSnailRenderer->IsAnimationEnd())
	{
		BlueSnailRenderer->Off();
	}
}