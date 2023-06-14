#include "Player.h"
#pragma region Headers

#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include "Bullet.h"
#include "Monster.h"
#include "PlayUIManager.h"
#include <GameEnginePlatform/GameEngineInput.h>

#pragma endregion

Player* Player::MainPlayer = nullptr;

Player::Player() 
{
}

Player::~Player() 
{
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Player.bmp"));

		GameEngineWindowTexture* T = ResourcesManager::GetInst().TextureCreate("Fade", {1280, 720});
		T->FillTexture(RGB(255, 0 , 0));


		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 17);
		
		
		FolderPath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().CreateSpriteFolder("FolderPlayer", FolderPath.PlusFilePath("FolderPlayer"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Test.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
	}

	{

		MainRenderer = CreateRenderer(200);
		MainRenderer->CreateAnimation("Test", "FolderPlayer");
		MainRenderer->CreateAnimation("Left_Idle", "Left_Player.bmp", 0, 2, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Right_Player.bmp", 0, 2, 1.0f, true);
		MainRenderer->CreateAnimation("Left_Run", "Left_Player.bmp", 3, 6, 0.1f, true);
		// MainRenderer->CreateAnimation("Right_Run", "Right_Player.bmp", 20, 0, 0.1f, true);

		MainRenderer->CreateAnimationToFrame("Right_Run", "Right_Player.bmp", {20, 19, 18, 17, 16, 15}, 0.1f, true);
		MainRenderer->ChangeAnimation("Test");
		MainRenderer->SetRenderScaleToTexture();
	}

	{
		GameEngineRenderer* Ptr = CreateRenderer("HPBar.bmp", RenderOrder::Play);
		Ptr->SetRenderPos({ 0, -100 });
		Ptr->SetRenderScale({ 200, 40 });
		Ptr->SetTexture("HPBar.bmp");
		Ptr->SetText("か神格たびかし葛ったびかし葛ったびかし葛った顕し葛君たびしけい稽っ原閑", 40);
	}

	{
		/*GameEngineRenderer* Ptr = CreateRenderer("Fade", 6000);
		Ptr->SetRenderScale({ 1280, 720 });*/
	}

	{
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({100, 100});
		BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}


	// SetGroundTexture("StageTestPixel.bmp");

	

	// State = PlayerState::Idle;

	ChanageState(PlayerState::Idle);
	Dir = PlayerDir::Right;
}

void Player::Update(float _Delta)
{

	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::MonsterBody, _Col
		, CollisionType::Rect // 蟹研 紫唖莫生稽 坐操
		, CollisionType::CirCle // 雌企亀 紫唖莫生稽 坐操
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->Death();
		}
		// 蟹澗 佼什斗櫛 中宜廃暗醤.
	}

	if (true == GameEngineInput::IsPress('L'))
	{
		// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
		// GameEngineSound::SoundPlay("AAA.Mp3");
		// GameEngineSound::PlayBgm("AAA.Mp3");
		// GameEngineSound::StopBgm("AAA.Mp3");

		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

		// Monster::AllMonsterDeath();
	}

	if (true == GameEngineInput::IsPress('Y'))
	{
		// GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	StateUpdate(_Delta);

	CameraFocus();

	// Gravity();
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
		break;
	default:
		break;
	}

}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}


void Player::DirCheck()
{

	// 坪球級戚 授託旋生稽 叔楳鞠奄 凶庚拭 
	// D研 刊献雌殿稽 A研喚袈聖凶税 号狽穿発精 亜管馬走幻
	// A研 刊献雌殿稽 D研 喚袈聖凶拭澗 A税 坦軒亜 胡煽 戚欠嬢閃辞 号狽穿発戚 鞠走省奄凶庚拭 庚薦亜 降持梅陥.

	// 号狽聖 衣舛馬澗 徹級戚 乞砧 覗軒虞檎 益雌殿 益企稽 政走. 焼掘税 D亜 覗軒析凶 Left亜 鞠澗 依聖 号走.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A亜 喚携暗蟹 D亜 覗軒戚虞檎 Left稽 号狽穿発 昔汽 亜幻備赤嬢亀 Left研 郊虞左澗 薄雌戚 持沿.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D亜 喚携暗蟹 A亜 覗軒戚檎 Right稽 号狽 穿発.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;
	}


	// 据掘 赤揮 坪球.
	/*PlayerDir CheckDir = PlayerDir::Left;

	if (true == GameEngineInput::IsDown('A'))
	{
		CheckDir = PlayerDir::Left;
	}
	else if (true == GameEngineInput::IsDown('D'))
	{
		CheckDir = PlayerDir::Right;
	}

	bool ChangeDir = false;

	if (CheckDir != PlayerDir::Max)
	{
		Dir = CheckDir;
		ChangeDir = true;
	}

	if (CheckDir != PlayerDir::Max && true == ChangeDir)
	{
		ChangeAnimationState(CurState);
	}*/

}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName

	std::string AnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}



void Player::LevelStart() 
{
	MainPlayer = this;
}

void Player::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	{
		std::string Text = "";
		Text += "巴傾戚嬢 砺什闘 葵 : ";
		Text += std::to_string(1.0f / _Delta);
		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
	}

	{
		float4 PlayerPos = GameEngineWindow::MainWindow.GetScale().Half();
		float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
		float4 Dir = PlayerPos - MousePos;

		std::string Text = "";
		Text += "原酔什 賞越 葵 : ";
		Text += std::to_string(Dir.AngleDeg());
		TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));
	}

	CollisionData Data;

	Data.Pos = ActorCameraPos();
	Data.Scale = { 5,5 };
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	Data.Pos = ActorCameraPos() + LeftCheck;
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	Data.Pos = ActorCameraPos() + RightCheck;
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}
