#include "Monster.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "Player.h"

#include <iostream>
#include <cmath>
using namespace std;
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
		BlueSnailRenderer->CreateAnimation("Left_Death", "BlueSnailDeath.bmp", 0, 5, 0.2f, false);
		BlueSnailRenderer->CreateAnimation("Right_Death", "BlueSnailDeath.bmp", 6, 11, 0.2f, false);
		BlueSnailRenderer->ChangeAnimation("Right_Idle");
		ChangeState(MonsterState::Idle);
	}

	GameEngineSound::SetGlobalVolume(0.3f);
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
	StateUpdate(_Delta);

	//std::vector<GameEngineCollision*> _Col;
	if (true == MonsterBodyCol->Collision(CollisionOrder::PlayerAttack, _Col
		, CollisionType::Rect // 
		, CollisionType::Rect // 
	))
	{
		ChangeState(MonsterState::Death);
	}

	if (GameEngineInput::IsDown(VK_F2))
	{
		MonsterStatus = !MonsterStatus;
	}
}

void Monster::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	//std::string StrPos = "";
	//StrPos += "MoveTime : ";
	//StrPos += std::to_string(M_FMoveTime);
	//TextOutA(dc, BlueSnailX + BlueSnailMovePos.X, BlueSnailY + BlueSnailMovePos.Y, StrPos.c_str(), static_cast<int>(StrPos.size()));


	if (MonsterStatus)
	{
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
			std::string MonsterPosX = "";
			float X = GetPos().X;
			MonsterPosX += "몬스터 X 위치 : ";
			MonsterPosX += std::to_string(X);
			TextOutA(dc, ActorCameraPos().X, ActorCameraPos().Y -80, MonsterPosX.c_str(), static_cast<int>(MonsterPosX.size()));
		}

		{
			float4 Pos;
			std::string MonsterPosY = "";
			float Y = GetPos().Y;
			MonsterPosY += ("몬스터 Y 위치 : ");
			MonsterPosY += std::to_string(Y);
			TextOutA(dc, ActorCameraPos().X, ActorCameraPos().Y -60, MonsterPosY.c_str(), static_cast<int>(MonsterPosY.size()));
		}

		{
			float4 Pos;
			std::string MonsterPosY = "";
			MonsterPosY += ("MoveTime : ");
			MonsterPosY += std::to_string(M_FMoveTime);
			MonsterPosY += ("/");
			MonsterPosY += std::to_string(static_cast<int>(M_FMoveLimitTime));
			TextOutA(dc, ActorCameraPos().X, ActorCameraPos().Y - 40, MonsterPosY.c_str(), static_cast<int>(MonsterPosY.size()));
		}

		{
			float4 Pos;
			std::string MonsterPosY = "";
			MonsterPosY += ("StopTime : ");
			MonsterPosY += std::to_string(static_cast<int>(M_FStopTime));
			MonsterPosY += ("/");
			MonsterPosY += std::to_string(static_cast<int>(M_FStopLimitTime));
			TextOutA(dc, ActorCameraPos().X, ActorCameraPos().Y - 20, MonsterPosY.c_str(), static_cast<int>(MonsterPosY.size()));
		}
	}
}

void Monster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
		break;
	case MonsterState::Run:
		return RunUpdate(_Delta);
		break;
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
	M_FStopTime += _Delta;
	if (M_FStopTime >= M_FStopLimitTime)
	{
		ChangeState(MonsterState::Run);
		M_FStopTime = 0.0f;
	}
}

void Monster::RunStart()
{
	idx = GameEngineRandom::MainRandom.RandomInt(0, 2);
	Dir = idx ? MonsterDir::Left : MonsterDir::Right;
}

void Monster::RunUpdate(float _Delta)
{
	M_FMoveTime += _Delta;
	BlueSnailMovePos;

	//if (M_FStopTime <= M_FMoveTime)
	//{
	if (Dir == MonsterDir::Left && M_FMoveTime < M_FMoveLimitTime)
	{
		BlueSnailMovePos = { -Speed * _Delta, 0.0f };
		ChangeAnimationState("Run");
		CheckPos = LeftCheck;
	}
	if (Dir == MonsterDir::Right && M_FMoveTime < M_FMoveLimitTime)
	{
		BlueSnailMovePos = { Speed * _Delta, 0.0f };
		ChangeAnimationState("Run");
		CheckPos = RightCheck;
	}

	if (M_FMoveTime >= M_FMoveLimitTime)
	{
		M_FMoveTime = 0.0f;
		ChangeState(MonsterState::Idle);
	}

	unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), CheckPos);
	if (RGB(0, 0, 128) != CheckColor)
	{
		AddPos(BlueSnailMovePos);
	}
	if (RGB(0, 0, 128) == CheckColor)
	{
		//ChangeState(MonsterState::Idle);
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
		MonsterBodyCol->Off();
	}
}