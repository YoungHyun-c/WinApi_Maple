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
	}

	{
		BlueSnailRenderer = CreateRenderer(RenderOrder::Monster);
		BlueSnailRenderer->CreateAnimation("Left_Idle", "BlueSnailStand.bmp", 0, 0, 0.1f, true);
		BlueSnailRenderer->CreateAnimation("Right_Idle", "BlueSnailStand.bmp", 1, 1, 0.1f, true);
		BlueSnailRenderer->CreateAnimation("Left_Run", "BlueSnailMove.bmp", 0, 4, 0.3f, true);
		BlueSnailRenderer->CreateAnimation("Right_Run", "BlueSnailMove.bmp", 5, 9, 0.3f, true);
		BlueSnailRenderer->ChangeAnimation("Right_Idle");
	}

	{
		GameEngineCollision* MonsterBodyCol = CreateCollision(CollisionOrder::MonsterBody);
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
	float Speed = 30.0f;
	BlueSnailMovePos;

	Dir = MonsterDir::Right;
	ChangeAnimationState("Run");
	M_FMoveTime += _Delta;

	if (M_FStopTime <= M_FMoveTime)
	{
		BlueSnailMovePos = { -Speed * _Delta, 0.0f };
		Dir = MonsterDir::Left;
		ChangeAnimationState("Run");
		AddPos(BlueSnailMovePos);

		if (M_FMoveTime >= 7.0f)
		{
			M_FMoveTime = M_FMoveLimitTime;
		}
	}
	else
	{
		Dir = MonsterDir::Right;
		BlueSnailMovePos = { Speed * _Delta, 0.0f };
		AddPos(BlueSnailMovePos);
	}


	//std::string StrPos ="";
	//swprintf_s(StrPos, L"Move : %.2f / %.2f", M_FMoveTime, m_fMoveLimitTime);
	//TextOut(hDC, x, y + 60, strPos, lstrlen(strPos));
	//
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

}

void Monster::ChangeState(MonsterState _State)
{

}

//void Monster::DirCheck()
//{
//	if ()
//}

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
