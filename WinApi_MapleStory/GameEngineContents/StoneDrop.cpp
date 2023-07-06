#include "StoneDrop.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineInput.h>"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "Player.h"
#include "PlayActor.h"
#include "Enum.h"
#include "BellomBoss.h"

StoneDrop* StoneDrop::MainStone = nullptr;

StoneDrop::StoneDrop()
{

}

StoneDrop::~StoneDrop()
{

}

void StoneDrop::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("StoneDrop.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\Bellom\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("StoneWarning.bmp"), 8, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("StoneDrop.bmp"), 10, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("StoneEnd.bmp"), 4, 1);
	}
	if (nullptr == GameEngineSound::FindSound("StoneStart.mp3"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("StoneStart.mp3"));
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("StoneEnd.mp3"));
	}

	{
		StonDrop = CreateRenderer(RenderOrder::Play);
		StonDrop->CreateAnimation("StoneWarning", "StoneWarning.bmp", 0, 7, 0.3f, false);
		StonDrop->CreateAnimation("StoneDrop", "StoneDrop.bmp", 0, 9, 0.1f, false);
		StonDrop->CreateAnimation("StoneEnd", "StoneEnd.bmp", 0, 3, 0.1f, false);
		StonDrop->SetRenderPos({ 1700, 420 });
		StonDrop->ChangeAnimation("StoneDrop");
		StonDrop->Off();
	}

}
void StoneDrop::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('7'))
	{
		StonDrop->ChangeAnimation("StoneWarning");
		StonDrop->SetRenderPos({ 1700, 420 });
		StonDrop->SetRenderScale({ 120, 600 });
	}

	if (true == GameEngineInput::IsDown('8'))
	{
		StonDrop->ChangeAnimation("StoneDrop");
		StonDrop->SetRenderPos({ 1700, 420 });
		StonDrop->SetRenderScale({ 120, 600 });
	}

	if (true == GameEngineInput::IsDown('9'))
	{
		StonDrop->ChangeAnimation("StoneEnd");
		StonDrop->SetRenderPos({ 1720, 650 });
		StonDrop->SetRenderScale({ 120, 130 });
	}

	if (BellomStoneSummon == false && true == BellomBoss::GetMainBoss()->BellomSummoner())
	{
		BellomStoneSummon = true;
		ChangeState(StoneState::Down);
	}

	if (BellomStoneSummon == true)
	{
		StateUpdate(_Delta);
	}

	if (true == BellomBoss::GetMainBoss()->BellomDeath())
	{
		Death();
	}
}

void StoneDrop::LevelStart()
{
	MainStone = this;
}

void StoneDrop::StateUpdate(float _Delta)
{
	switch (State)
	{
	case StoneState::Ready:
		ReadyUpdate(_Delta);
		break;
	case StoneState::Down:
		DownUpdate(_Delta);
		break;
	case StoneState::Max:
		break;
	default:
		break;
	}
}

void StoneDrop::ChangeState(StoneState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case StoneState::Ready:
			ReadyStart();
			break;
		case StoneState::Down:
			DownStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void StoneDrop::ChangeAnimationState(const std::string& _StateName)
{
	AnimationName = _StateName;
	CurState = _StateName;

	StonDrop->ChangeAnimation(AnimationName);
}

void StoneDrop::ReadyStart()
{
	StonDrop->On();
	StonDrop->SetRenderPos({ Player::GetMainPlayer()->GetPos().X, 420.0f });
	BellomStoneSavePosX = Player::GetMainPlayer()->GetPos().X;
	StonDrop->SetRenderScale({ 120.0f, 600.0f });
	ChangeAnimationState("StoneWarning");
	GameEngineSoundPlayer BgmPlay = GameEngineSound::SoundPlay("StoneStart.mp3");
	BgmPlay.SetVolume(0.2);
}
void StoneDrop::ReadyUpdate(float _Delta)
{
	BS_FWakeTime += _Delta;

	if (true == StonDrop->IsAnimationEnd())
	{
		StonDrop->ChangeAnimation("StoneDrop");
		StonDrop->SetRenderPos({ BellomStoneSavePosX, 420.0f });
		StonDrop->SetRenderScale({ 120.0f, 600.0f });
	}

	if (true == StonDrop->IsAnimationEnd())
	{
		GameEngineSoundPlayer BgmPlay = GameEngineSound::SoundPlay("StoneEnd.mp3");
		BgmPlay.SetVolume(0.2);
		StonDrop->ChangeAnimation("StoneEnd");
		StonDrop->SetRenderPos({ BellomStoneSavePosX + 20.0f, 650.0f });
		StonDrop->SetRenderScale({ 120.0f, 130.0f });
	}

	if (BS_FWakeTime >= BS_FWakeLimitTime)
	{
		BS_FWakeTime = 0.0f;
		ChangeState(StoneState::Down);
	}
}
void StoneDrop::DownStart()
{
	StonDrop->Off();
}
void StoneDrop::DownUpdate(float _Delta)
{
	BS_FDownTime += _Delta;
	if (BS_FDownTime >= BS_FDownLimitTime)
	{
		BS_FDownTime = 0.0f;
		ChangeState(StoneState::Ready);
	}
}
