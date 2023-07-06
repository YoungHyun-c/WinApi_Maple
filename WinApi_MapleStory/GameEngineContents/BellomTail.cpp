#include "BellomTail.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>"
#include <GameEnginePlatform/GameEngineWindow.h>


#include "Player.h"
#include "PlayActor.h"
#include "Enum.h"
#include "BellomBoss.h"

BellomTail* BellomTail::MainTail = nullptr;

BellomTail::BellomTail()
{

}

BellomTail::~BellomTail()
{

}

void BellomTail::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("BellomTails.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\Bellom\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BellomTails.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("BellomTailsDown.bmp"), 8, 1);
	}

	GameEngineSound::SetGlobalVolume(0.3f);
	if (nullptr == GameEngineSound::FindSound("BellomAttack8.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomAttack6.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BellomAttack8.mp3"));
	}

	{
		BellomTails = CreateRenderer(RenderOrder::Monster);
		BellomTails->CreateAnimation("Left_Ready", "Bellom1.bmp", 0, 7, 0.2f, false);
		BellomTails->CreateAnimation("Left_Wake", "BellomTails.bmp", 0, 9, 0.1f, false);
		BellomTails->CreateAnimation("Left_Down", "BellomTailsDown.bmp", 0, 7, 0.1f, false);
		BellomTails->SetRenderPos({ 1700, 400 });
		BellomTails->ChangeAnimation("Left_Ready");
		BellomTails->Off();
	}
}

void BellomTail::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('7'))
	{
		BellomTails->ChangeAnimation("Left_Ready");
		BellomTails->SetRenderPos({ 1630, 400 });
		BellomTails->SetRenderScale({ 1024,1024 });
	}

	if (true == GameEngineInput::IsDown('8'))
	{
		BellomTails->ChangeAnimation("Left_Wake");
		BellomTails->SetRenderPos({ 1700, 420 });
		BellomTails->SetRenderScale({ 923, 717 });
	}

	if (true == GameEngineInput::IsDown('9'))
	{
		BellomTails->ChangeAnimation("Left_Down");
		BellomTails->SetRenderPos({ 1700, 420 });
		BellomTails->SetRenderScale({ 923, 717 });
	}

	if (BellomTailSummon == false && true == BellomBoss::GetMainBoss()->BellomSummoner())
	{
		BellomTails->ChangeAnimation("Left_Wake");
		BellomTailSummon = true;
		ChangeState(TailState::Ready);
	}
	
	if (BellomTailSummon == true)
	{
		StateUpdate(_Delta);
	}

	if (true == BellomBoss::GetMainBoss()->BellomDeath())
	{
		Death();
	}
}

void BellomTail::LevelStart()
{
	MainTail = this;
}


void BellomTail::StateUpdate(float _Delta)
{
	switch (State)
	{
	case TailState::Ready:
		return ReadyUpdate(_Delta);
		break;
	case TailState::Down:
		return DownUpdate(_Delta);
		break;
	default:
		break;
	}
}

void BellomTail::ChangeState(TailState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case TailState::Ready:
			ReadyStart();
			break;
		case TailState::Down:
			DownStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void BellomTail::ChangeAnimationState(const std::string& _StateName)
{
	AnimationName = "Left_";

	AnimationName += _StateName;
	CurState = _StateName;

	BellomTails->ChangeAnimation(AnimationName);
}

void BellomTail::ReadyStart()
{
	GameEngineSound::SoundPlay("BellomAttack9.mp3");
	BellomTails->On();
	BellomTails->SetRenderPos({ Player::GetMainPlayer()->GetPos().X, 400.0f });
	BellomTailesSavePosX = Player::GetMainPlayer()->GetPos().X + 70;
	BellomTails->SetRenderScale({ 1024,1024 });
	ChangeAnimationState("Ready");
}
void BellomTail::ReadyUpdate(float _Delta)
{
	BT_FWakeTime += _Delta;

	if (true == BellomTails->IsAnimationEnd())
	{
		//GameEngineSound::SoundPlay("BellomAttack6.mp3");
		BellomTails->ChangeAnimation("Left_Wake");
		BellomTails->SetRenderPos({ BellomTailesSavePosX, 420 });
		BellomTails->SetRenderScale({ 923, 717 });
	}

	if (true == BellomTails->IsAnimationEnd())
	{
		GameEngineSound::SoundPlay("BellomAttack6.mp3");
		BellomTails->ChangeAnimation("Left_Down");
		BellomTails->SetRenderPos({ BellomTailesSavePosX, 420 });
		BellomTails->SetRenderScale({ 923, 717 });
	}

	if (BT_FWakeTime >= BT_FWakeLimitTime)
	{
		BT_FWakeTime = 0.0f;
		ChangeState(TailState::Down);
	}
}
void BellomTail::DownStart()
{
	BellomTails->Off();
}
void BellomTail::DownUpdate(float _Delta)
{
	BT_FDownTime += _Delta;
	if (BT_FDownTime >= BT_FDownLimitTime)
	{
		BT_FDownTime = 0.0f;
		ChangeState(TailState::Ready);
	}
}
