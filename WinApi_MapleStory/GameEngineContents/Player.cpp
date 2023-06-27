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
//int Player::BackGroundSizeforCamY = -1082;
int Player::BackGroundSizeforCamX = 0;
int Player::BackGroundSizeforCamY = 0;

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

		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Player.bmp"));

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

		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Pl11ayer.bmp"), 5, 17);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Playrrer.bmp"), 5, 17);


		//FolderPath.MoveChild("ContentsResources\\Texture\\Player\\FolderPlayer\\");
		//ResourcesManager::GetInst().CreateSpriteFolder("Stand", FolderPath.PlusFilePath("Stand"));


		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));

	}

	// �̹��� ũ��(������)��ŭ �޾ƿ���
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
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({ 50, 50 });
		BodyCollsion->SetCollisionType(CollisionType::Rect);
	}
	
	
	ChangeState(PlayerState::Idle);
	Dir = PlayerDir::Right;
}

void Player::Update(float _Delta)
{

	//std::vector<GameEngineCollision*> _Col;
	//if (true == BodyCollsion->Collision(CollisionOrder::MonsterBody, _Col
	//	, CollisionType::Rect // 
	//	, CollisionType::CirCle // 
	//))
	//{
	//	for (size_t i = 0; i < _Col.size(); i++)
	//	{
	//		GameEngineCollision* Collison = _Col[i];

	//		GameEngineActor* Actor = Collison->GetActor();

	//		Actor->Death();
	//	}
	//}

	if (true == GameEngineInput::IsDown('R'))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}


	StateUpdate(_Delta);

	CameraFocus();

	//if(FindImage = ResourcesManager::GetInst().FindTexture("RUTAMAP_NPC.bmp"))
	//{
	//	//GetLevel()->GetMainCamera()->SetPos({ GetPos() });
	//	GetLevel()->GetMainCamera()->SetPos({ GetPos() - GameEngineWindow::MainWindow.GetScale().Half() });

	//	//�����̵��� �ص� ī�޶��� y���� �ȹٲ�� ����
	//	// 260 -> GetLevel()->GetMainCamera()->GetPos().hY()
	//	// Cam X�� 0���� �۰�, Y�� 260 �̻��̸�
	//	if (0 > GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	//	{
	//		//ī�޶� ���� ��ǥ�̸�, 0,0�� ī�޶� ����
	//		//GetLevel()->GetMainCamera()->SetPos({ 0, GameEngineWindow::MainWindow.GetScale().hY()});
	//		GetLevel()->GetMainCamera()->SetPos({ 0, 0 });
	//	}
	//	if (0 > GetLevel()->GetMainCamera()->GetPos().X)
	//	{
	//		//ī�޶� ���� ��ǥ�̸�, 0,0�� ī�޶� ����
	//		//GetLevel()->GetMainCamera()->SetPos({ 0, GameEngineWindow::MainWindow.GetScale().hY()});
	//		GetLevel()->GetMainCamera()->SetPos({ 0, 260 });
	//	}
	//	//&& 1082 > GetLevel()->GetMainCamera()->GetPos().Y

	//	// Cam X�� 0���� Ŀ����
	//	if (0 < GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	//	{
	//		GetLevel()->GetMainCamera()->SetPos({ GetPos().X - GameEngineWindow::MainWindow.GetScale().hX() ,0 }); 
	//	}
	//
	//	if ((BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X) < GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	//	{
	//		GetLevel()->GetMainCamera()->SetPos({ (BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X), 0 });
	//	}
	//	// Cam X�� �̹����� X���� Ŀ����
	//	if ((BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X) < GetLevel()->GetMainCamera()->GetPos().X)
	//	{
	//		float Value = GetLevel()->GetMainCamera()->GetPos().X;
	//		Value;
	//		//ī�޶� ��ǥ�� ��� �̹���ũ�� - ȭ��ũ�⸦ �Ѿ�ٸ� ī�޶� ����
	//		//��Ÿ��� �̹��� ���� -> 2498
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
	//	//ī�޶� ��ǥ�� ��� �̹���ũ�� - ȭ��ũ�⸦ �Ѿ�ٸ� ī�޶� ����
	//	//��Ÿ��� �̹��� ���� -> 1082
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
	case PlayerState::Run:
		return RunUpdate(_Delta);
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

	// �ڵ���� ���������� ����Ǳ� ������ 
	// D�� �������·� A������������ ������ȯ�� ����������
	// A�� �������·� D�� ������������ A�� ó���� ���� �̷������ ������ȯ�� �����ʱ⶧���� ������ �߻��ߴ�.

	// ������ �����ϴ� Ű���� ��� ������� �׻��� �״�� ����. �Ʒ��� D�� �����϶� Left�� �Ǵ� ���� ����.
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A�� ���Ȱų� D�� �����̶�� Left�� ������ȯ �ε� �������־ Left�� �ٶ󺸴� ������ ����.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D�� ���Ȱų� A�� �����̸� Right�� ���� ��ȯ.
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
		Text += "�÷��̾� �׽�Ʈ �� : ";
		Text += std::to_string(TestValue);
		//Text += std::to_string(1.0f / _Delta);
		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
	}

	{
		float4 PlayerPos = GameEngineWindow::MainWindow.GetScale().Half();
		float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
		float4 Dir = PlayerPos - MousePos;

		//std::string Text = "";
		//Text += "���콺 �ޱ� �� : ";
		//Text += std::to_string(Dir.AngleDeg());
		//TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));
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

	Data.Pos = ActorCameraPos() + PotalCheck;
}
