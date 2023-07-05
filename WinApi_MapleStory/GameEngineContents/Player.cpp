#include "Player.h"
#pragma region Headers

#include "Enum.h"
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
//#include "Bullet.h"
//#include "Monster.h"
#include "UIPanel.h"
#include <GameEnginePlatform/GameEngineInput.h>

#include "UIQuest.h"

#pragma endregion

Player* Player::MainPlayer = nullptr;
int Player::BackGroundSizeforCamX = 0;
int Player::BackGroundSizeforCamY = 0;

bool Player::DebugMode = false;

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Stand.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");


		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Stand.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Walk.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Walk.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Alert.bmp"), 3, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Attack.bmp"), 3, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Attack.bmp"), 3, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Jump.bmp"), 2, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Prone.bmp"), 2, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Prone_Attack.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Rope.bmp"), 2, 1);

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LeftSkill0.bmp"), 4, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RightSkill0.bmp"), 4, 1);

		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Bellom.bmp"), 5, 5);

		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Pl11ayer.bmp"), 5, 17);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Playrrer.bmp"), 5, 17);


		//FolderPath.MoveChild("ContentsResources\\Texture\\Player\\FolderPlayer\\");
		//ResourcesManager::GetInst().CreateSpriteFolder("Stand", FolderPath.PlusFilePath("Stand"));

		GameEngineSound::SetGlobalVolume(0.3f);
		if (nullptr == GameEngineSound::FindSound("Attack.mp3"))
		{
			GameEnginePath FilePath;
			FilePath.SetCurrentPath();
			FilePath.MoveParentToExistsChild("ContentsResources");
			FilePath.MoveChild("ContentsResources\\Sound\\");

			GameEngineSound::SoundLoad(FilePath.PlusFilePath("Attack.mp3"));
			GameEngineSound::SoundLoad(FilePath.PlusFilePath("Jump.mp3"));
		}
		
	}

	// 이미지 크기(사이즈)만큼 받아오기
	//if (false == ResourcesManager::GetInst().IsLoadTexture("RUTAMAP_NPC"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");
	//	FilePath.MoveChild("ContentsResources\\Texture\\");
	//	GameEngineWindowTexture* FindImage = ResourcesManager::GetInst().FindTexture("RUTAMAP_NPC.bmp");
	//	BackGroundSizeforCamX = FindImage->GetScale().iX();
	//	BackGroundSizeforCamY = FindImage->GetScale().iY();
	//}

	//if (false == ResourcesManager::GetInst().IsLoadTexture("Garden_Test"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");
	//	FilePath.MoveChild("ContentsResources\\Texture\\");
	//	GameEngineWindowTexture* FindImage = ResourcesManager::GetInst().FindTexture("Garden_Test.bmp");
	//	BackGroundSizeforCamX = FindImage->GetScale().iX();
	//	BackGroundSizeforCamY = FindImage->GetScale().iY();
	//}

	//{
	//	GameEngineRenderer* Bellom = CreateRenderer(RenderOrder::Play);
	//	Bellom->CreateAnimation("Left_Idle", "Bellom.bmp", 0, 23, 0.2f);
	//	//Bellom->SetRenderPos({ 500, 500 });
	//	Bellom->ChangeAnimation("Left_Idle");
	//}


	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		MainRenderer->CreateAnimation("Left_Idle", "Stand.bmp", 0, 2, 0.3f);
		MainRenderer->CreateAnimation("Right_Idle", "Stand.bmp", 3, 5, 0.3f);
	
		MainRenderer->CreateAnimation("Left_Run", "Left_Walk.bmp", 0, 3, 0.3f, true);
		MainRenderer->CreateAnimation("Right_Run", "Right_Walk.bmp", 0, 3, 0.3f, true);

		MainRenderer->CreateAnimation("Left_Alert", "Alert.bmp", 0, 2, 0.3f);
		MainRenderer->CreateAnimation("Right_Alert", "Alert.bmp", 3, 5, 0.3f);

		MainRenderer->CreateAnimation("Left_Attack0", "Left_Attack.bmp", 0, 2, 0.2f);
		MainRenderer->CreateAnimation("Left_Attack1", "Left_Attack.bmp", 3, 5, 0.2f);
		MainRenderer->CreateAnimation("Left_Attack2", "Left_Attack.bmp", 6, 8, 0.2f);
		
		MainRenderer->CreateAnimation("Right_Attack0", "Right_Attack.bmp", 0, 2, 0.2f);
		MainRenderer->CreateAnimation("Right_Attack1", "Right_Attack.bmp", 3, 5, 0.2f);
		MainRenderer->CreateAnimation("Right_Attack2", "Right_Attack.bmp", 6, 8, 0.2f);
		
		MainRenderer->CreateAnimation("Left_Jump", "Jump.bmp", 0, 0, 0.3f, false);
		MainRenderer->CreateAnimation("Right_Jump", "Jump.bmp", 1, 1, 0.3f, false);

		MainRenderer->CreateAnimation("Left_Prone", "Prone.bmp", 0, 0, 0.3f);
		MainRenderer->CreateAnimation("Right_Prone", "Prone.bmp", 1, 1, 0.3f);

		MainRenderer->CreateAnimation("Left_Prone_Attack", "Prone_Attack.bmp", 0, 1, 0.3f);
		MainRenderer->CreateAnimation("Right_Prone_Attack", "Prone_Attack.bmp", 2, 3, 0.3f);
		
		MainRenderer->CreateAnimation("Left_Rope", "Rope.bmp", 0, 1, 0.3f);
		MainRenderer->CreateAnimation("Right_Rope", "Rope.bmp", 0 , 1, 0.3f);

		MainRenderer->GetActor()->SetPos({ 500, 500 });
		MainRenderer->SetRenderScale({ 128, 128 });
		
		MainRenderer->ChangeAnimation("Right_Idle");
	}


	{
		BodyCollision = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollision->SetCollisionScale({ 50,50 });
	}

	{
		AttackRenderer0 = CreateRenderer(RenderOrder::Play);
		AttackRenderer0->CreateAnimation("Left_Skill0", "LeftSkill0.bmp", 0, 3, 0.075f);
		AttackRenderer0->CreateAnimation("Right_Skill0", "RightSkill0.bmp", 0, 3, 0.075f);
		//AttackRenderer0->SetRenderPos({ 100, -30 });
		AttackRenderer0->SetRenderScale({ 768, 512 });
		AttackRenderer0->ChangeAnimation("Right_Skill0");
		//AttackRenderer0->ChangeAnimation("Left_Skill0");
		AttackRenderer0->Off();
	}

	{
		AttackCollsion = CreateCollision(CollisionOrder::PlayerAttack);
		AttackCollsion->SetCollisionScale({ 300, 200 });
		AttackCollsion->SetCollisionType(CollisionType::Rect);
		AttackCollsion->Off();
	}
	
	ChangeState(PlayerState::Idle);
	Dir = PlayerDir::Right;
}

void Player::Update(float _Delta)
{

	//std::vector<GameEngineCollision*> _Col;
	//if (true == AttackCollsion->Collision(CollisionOrder::MonsterBody, _Col
	//	, CollisionType::Rect // 나를 사각형으로 봐줘
	//	, CollisionType::CirCle // 상대도 사각형으로 봐줘
	//))
	//{
	//	for (size_t i = 0; i < _Col.size(); i++)
	//	{
	//		GameEngineCollision* Collison = _Col[i];

	//		GameEngineActor* Actor = Collison->GetActor();

	//		Collison->GetActor()->Death();
	//	}
	//}


	//std::vector<GameEngineCollision*> _BellomBodyCol;
	//if (true == AttackCollsion->Collision(CollisionOrder::MonsterBody, _BellomBodyCol
	//	, CollisionType::Rect
	//	, CollisionType::Rect) && GameEngineInput::IsDown(VK_SHIFT))
	//{
	//	GameEngineSoundPlayer BellomDamage = GameEngineSound::SoundPlay("BellomDamage.mp3");
	//	//AttackCount += 1;
	//	return;
	//}

	//std::vector<GameEngineCollision*> _BellomBodyC;
	//if (true == AttackCollsion->Collision(CollisionOrder::MonsterBody, _BellomBodyC
	//	, CollisionType::Rect
	//	, CollisionType::Rect) && GameEngineInput::IsUp(VK_SHIFT))
	//{
	//	GameEngineSoundPlayer BellomDamage = GameEngineSound::SoundPlay("BellomDamage.mp3");
	//	//AttackCount += 1;
	//	return;
	//}

	if (true == GameEngineInput::IsDown('R'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}

	if (true == GameEngineInput::IsDown(VK_F1))
	{
		DebugMode = !DebugMode;
	}


	StateUpdate(_Delta);

	CameraFocus();

	//if(FindImage = ResourcesManager::GetInst().FindTexture("RUTAMAP_NPC.bmp"))
	//{
	//	//GetLevel()->GetMainCamera()->SetPos({ GetPos() });
	//	GetLevel()->GetMainCamera()->SetPos({ GetPos() - GameEngineWindow::MainWindow.GetScale().Half() });

	//	//상하이동을 해도 카메라의 y축은 안바뀌게 제한
	//	// 260 -> GetLevel()->GetMainCamera()->GetPos().hY()
	//	// Cam X가 0보다 작고, Y가 260 이상이면
	//	if (0 > GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	//	{
	//		//카메라가 음수 좌표이면, 0,0에 카메라를 고정
	//		//GetLevel()->GetMainCamera()->SetPos({ 0, GameEngineWindow::MainWindow.GetScale().hY()});
	//		GetLevel()->GetMainCamera()->SetPos({ 0, 0 });
	//	}
	//	if (0 > GetLevel()->GetMainCamera()->GetPos().X)
	//	{
	//		//카메라가 음수 좌표이면, 0,0에 카메라를 고정
	//		//GetLevel()->GetMainCamera()->SetPos({ 0, GameEngineWindow::MainWindow.GetScale().hY()});
	//		GetLevel()->GetMainCamera()->SetPos({ 0, 260 });
	//	}
	//	//&& 1082 > GetLevel()->GetMainCamera()->GetPos().Y

	//	// Cam X가 0보다 커지면
	//	if (0 < GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	//	{
	//		GetLevel()->GetMainCamera()->SetPos({ GetPos().X - GameEngineWindow::MainWindow.GetScale().hX() ,0 }); 
	//	}
	//
	//	if ((BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X) < GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	//	{
	//		GetLevel()->GetMainCamera()->SetPos({ (BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X), 0 });
	//	}
	//	// Cam X가 이미지의 X보다 커지면
	//	if ((BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X) < GetLevel()->GetMainCamera()->GetPos().X)
	//	{
	//		float Value = GetLevel()->GetMainCamera()->GetPos().X;
	//		Value;
	//		//카메라 좌표가 배경 이미지크기 - 화면크기를 넘어간다면 카메라를 고정
	//		//루타배경 이미지 넓이 -> 2498
	//	
	//		GetLevel()->GetMainCamera()->SetPos({(BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X), 260});
	//	}

	//	if (260 < GetLevel()->GetMainCamera()->GetPos().Y)
	//	{
	//		GetLevel()->GetMainCamera()->SetPos({ GetPos().X - GameEngineWindow::MainWindow.GetScale().hX(), 260});
	//		//GetLevel()->GetMainCamera()->SetPos({ (BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X) , 260 });
	//		float Value = GetLevel()->GetMainCamera()->GetPos().Y;
	//		Value;
	//	}

	//	int a = 0;

	//}

	//if ((BackGroundSizeforCamY - GameEngineWindow::MainWindow.GetScale().Y) < GetLevel()->GetMainCamera()->GetPos().Y)
	//{
	//	float Value = GetLevel()->GetMainCamera()->GetPos().Y;
	//	Value;
	//	//카메라 좌표가 배경 이미지크기 - 화면크기를 넘어간다면 카메라를 고정
	//	//루타배경 이미지 높이 -> 1082
	//	GetLevel()->GetMainCamera()->SetPos({ 0, 260 });
	//	//GetLevel()->GetMainCamera()->SetPos({ 0, (BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().Y)});
	//}

}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
		break;
	case PlayerState::Run:
		return RunUpdate(_Delta);
		break;
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
		break;
	case PlayerState::DoubleJump:
		return DoubleJumpUpdate(_Delta);
		break;
	case PlayerState::Prone:
		return ProneUpdate(_Delta);
		break;
	case PlayerState::ProneAttack:
		return ProneAttackUpdate(_Delta);
		break;
	case PlayerState::Attack:
		return AttackUpdate(_Delta);
		break;
	case PlayerState::Rope:
		RopeUpdate(_Delta);
		break;
	default:
		break;
	}

}

void Player::ChangeState(PlayerState _State)
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
		case PlayerState::Rope:
			RopeStart();
			break;
		case PlayerState::Prone:
			ProneStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::ProneAttack:
			ProneAttackStart();
			break;
		case PlayerState::DoubleJump:
			DoubleJumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}


void Player::DirCheck()
{

	// 코드들이 순차적으로 실행되기 때문에 
	// D를 누른상태로 A를눌렀을때의 방향전환은 가능하지만
	// A를 누른상태로 D를 눌렀을때에는 A의 처리가 먼저 이루어져서 방향전환이 되지않기때문에 문제가 발생했다.

	// 방향을 결정하는 키들이 모두 프리라면 그상태 그대로 유지. 아래의 D가 프리일때 Left가 되는 것을 방지.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A가 눌렸거나 D가 프리이라면 Left로 방향전환 인데 가만히있어도 Left를 바라보는 현상이 생김.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D가 눌렸거나 A가 프리이면 Right로 방향 전환.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
		return;
	}

}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	// "Idle"
	// _StateName


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
		Text += "플레이어 디버그 모드: F1";
		TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));
	}

	{
		std::string Text = "";
		Text += "몬스터 디버그 모드: F2";
		TextOutA(dc, 2, 40, Text.c_str(), static_cast<int>(Text.size()));
	}

	{
		std::string Text = "";
		Text += "픽셀 확인: B";
		TextOutA(dc, 2, 60, Text.c_str(), static_cast<int>(Text.size()));
	}

	{
		std::string Text = "";
		Text += "충돌 확인 : R";
		TextOutA(dc, 2, 80, Text.c_str(), static_cast<int>(Text.size()));
	}

	if (DebugMode)
	{
		{
			std::string PlayerStateText = "";
			PlayerStateText = "플레이어 상태 : " + AnimationName;
			TextOutA(dc, ActorCameraPos().X + 30, ActorCameraPos().Y - 100, PlayerStateText.c_str(), static_cast<int>(PlayerStateText.size()));
		}

		{
			float4 Pos;
			std::string PlayerPosX = "";
			float X = MainPlayer->GetPos().X;
			PlayerPosX += "플레이어 X위치 : ";
			PlayerPosX += std::to_string(X);
			TextOutA(dc, ActorCameraPos().X + 30, ActorCameraPos().Y - 80, PlayerPosX.c_str(), static_cast<int>(PlayerPosX.size()));
		}

		{
			float4 Pos;
			std::string PlayerPosY = "";
			float Y = MainPlayer->GetPos().Y;
			PlayerPosY += "플레이어 Y위치 : ";
			PlayerPosY += std::to_string(Y);
			TextOutA(dc, ActorCameraPos().X + 30, ActorCameraPos().Y - 60, PlayerPosY.c_str(), static_cast<int>(PlayerPosY.size()));
		}

		{
			float4 Pos;
			std::string PlayerHP = "";
			int Hp = GetMainPlayer()->GetMainPlayerHpValue();
			PlayerHP += "플레이어 HP : ";
			PlayerHP += std::to_string(Hp);
			TextOutA(dc, ActorCameraPos().X + 30, ActorCameraPos().Y - 40, PlayerHP.c_str(), static_cast<int>(PlayerHP.size()));
		}

		{
			float4 Pos;
			std::string PlayerMP = "";
			int MP = GetMainPlayer()->GetMainPlayerMpValue();
			PlayerMP += "플레이어 MP : ";
			PlayerMP += std::to_string(MP);
			TextOutA(dc, ActorCameraPos().X + 30, ActorCameraPos().Y - 20, PlayerMP.c_str(), static_cast<int>(PlayerMP.size()));
		}

		{
			std::string Text = "";
			Text += "플레이어 공격 횟수 : ";
			Text += std::to_string(TestValue);
			TextOutA(dc, ActorCameraPos().X + 30, ActorCameraPos().Y, Text.c_str(), static_cast<int>(Text.size()));
		}

		{
			float4 Pos;
			std::string PlayerHP = "";
			int Hp = GetMainPlayer()->GetMainPlayerHpValue();
			//PlayerHP += "플레이어 HP : ";
			PlayerHP += std::to_string(Hp);
			TextOutA(dc, 500, 700, PlayerHP.c_str(), static_cast<int>(PlayerHP.size()));
		}

		{
			float4 Pos;
			std::string PlayerMP = "";
			int MP = GetMainPlayer()->GetMainPlayerMpValue();
			//PlayerMP += "플레이어 MP : ";
			PlayerMP += std::to_string(MP);
			TextOutA(dc, 500, 715, PlayerMP.c_str(), static_cast<int>(PlayerMP.size()));
		}

		CollisionData Data;
		Data.Pos = ActorCameraPos() + GroundCheck;
		Data.Scale = { 5, 5 };
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + LeftCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + RightCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

		Data.Pos = ActorCameraPos() + RopeCheck;
		Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	}

	//{
	//	float4 PlayerPos = GameEngineWindow::MainWindow.GetScale().Half();
	//	float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
	//	float4 Dir = PlayerPos - MousePos;

	//	std::string Text = "";
	//	Text += "마우스 위치 X값 : ";
	//	//Text += std::to_string(Dir.AngleDeg());
	//	Text += std::to_string(MousePos.X);
	//	Text += "마우스 위치 Y값 : ";
	//	Text += std::to_string(MousePos.Y);
	//	TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));
	//}

}

