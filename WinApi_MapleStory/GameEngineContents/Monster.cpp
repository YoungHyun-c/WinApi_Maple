#include "Monster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>

#include "Enum.h"
#include "Player.h"

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
	if (false == ResourcesManager::GetInst().IsLoadTexture("BlueSnialStand.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\BlueSnail\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BlueSnailStand.bmp"), 2, 1);
	}

	{
		BlueSnailRenderer = CreateRenderer(RenderOrder::Play);
		BlueSnailRenderer->CreateAnimation("Left_Idle", "BlueSnailStand.bmp", 0, 0, 0.1f, true);
		BlueSnailRenderer->CreateAnimation("Right_Idle", "BlueSnailStand.bmp", 1, 1, 0.1f, true);
		BlueSnailRenderer->SetRenderPos({ 300, 300 });
		BlueSnailRenderer->ChangeAnimation("Left_Idle");
	}
}

void Monster::Update(float _Delta)
{
	//float4 Dir = Player::GetMainPlayer()->GetPos() - GetPos();

	//Dir.Normalize();

	// Dir <= 거리가 일정하지 않다는 게 문제에요.

	// Dir *= 0.1f;

	
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