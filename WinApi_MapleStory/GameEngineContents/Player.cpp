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
//#include "PlayUIManager.h"
#include <GameEnginePlatform/GameEngineInput.h>

#pragma endregion

Player* Player::MainPlayer = nullptr;
int Player::BackGroundSizeforCamX = 0;
//int Player::BackGroundSizeforCamY = -1082;
int Player::BackGroundSizeforCamY = 0;

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Player.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		//ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Player.bmp"));

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 17);


		FolderPath.MoveChild("ContentsResources\\Texture\\Player\\FolderPlayer\\");
		//ResourcesManager::GetInst().CreateSpriteFolder("Left", FolderPath.PlusFilePath("Left"));
		//FolderPath.MoveChild("ContentsResources\\Texture\\Player\\FolderPlayer\\Stand\\");
		ResourcesManager::GetInst().CreateSpriteFolder("Stand", FolderPath.PlusFilePath("Stand"));
		ResourcesManager::GetInst().CreateSpriteFolder("Walk", FolderPath.PlusFilePath("Walk"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HPBar.bmp"));
		
	}

	// 이미지 크기(사이즈)만큼 받아오기
	if (false == ResourcesManager::GetInst().IsLoadTexture("RUTAMAP_NPC"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\");
		GameEngineWindowTexture* FindImage = ResourcesManager::GetInst().FindTexture("RUTAMAP_NPC.bmp");
		BackGroundSizeforCamX = FindImage->GetScale().iX();
		BackGroundSizeforCamY = FindImage->GetScale().iY();
	}
	//GameEngineImage* FindImage = GH_ResourcesManager::GH_GetInst().GH_FindGameImage("1-1_big.bmp");
	//BackGroundSizeforCamX = FindImage->GH_GetSize().ix();

	{

		MainRenderer = CreateRenderer(RenderOrder::Play);
		MainRenderer->CreateAnimation("Left_Idle", "Stand", 0, 2, 0.5f);
		MainRenderer->CreateAnimation("Right_Idle", "Stand", 3, 5, 0.5f);
	}

	{
		MainRenderer->CreateAnimation("Left_Run", "Walk", 0, 3, 0.3f);
		MainRenderer->CreateAnimation("Right_Run", "Walk", 4, 7, 0.3f);

		//MainRenderer->CreateAnimationToFrame("Right_Run", "Right_Player.bmp", { 20, 19, 18, 17, 16, 15 }, 0.1f, true);
		//MainRenderer->SetRenderPos({ 100 , 700 });
		//MainRenderer->SetRenderPos({ 0, -34 });
		MainRenderer->SetRenderPos({ 0, 0 });
		//MainRenderer->SetRenderScale({ 66, 69 });
		MainRenderer->ChangeAnimation("Right_Idle");
	}


	{
		//BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		//BodyCollsion->SetCollisionScale({ 100, 100 });
		//BodyCollsion->SetCollisionType(CollisionType::CirCle);
	}

	// SetGroundTexture("StageTestPixel.bmp");


	ChanageState(PlayerState::Idle);
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

	if (true == GameEngineInput::IsPress('L'))
	{
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);
		// Monster::AllMonsterDeath();
	}

	if (true == GameEngineInput::IsPress('Y'))
	{
		// GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}


	StateUpdate(_Delta);

	//CameraFocus();

	//GetLevel()->GetMainCamera()->SetPos({ GetPos() });
	GetLevel()->GetMainCamera()->SetPos({ GetPos() - GameEngineWindow::MainWindow.GetScale().Half() });

	//상하이동을 해도 카메라의 y축은 안바뀌게 제한
	// 260 -> GetLevel()->GetMainCamera()->GetPos().hY()
	// Cam X가 0보다 작고, Y가 260 이상이면
	if (0 > GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	{
		//카메라가 음수 좌표이면, 0,0에 카메라를 고정
		//GetLevel()->GetMainCamera()->SetPos({ 0, GameEngineWindow::MainWindow.GetScale().hY()});
		GetLevel()->GetMainCamera()->SetPos({ 0, 0 });
	}
	if (0 > GetLevel()->GetMainCamera()->GetPos().X)
	{
		//카메라가 음수 좌표이면, 0,0에 카메라를 고정
		//GetLevel()->GetMainCamera()->SetPos({ 0, GameEngineWindow::MainWindow.GetScale().hY()});
		GetLevel()->GetMainCamera()->SetPos({ 0, 260 });
	}
	//&& 1082 > GetLevel()->GetMainCamera()->GetPos().Y

	// Cam X가 0보다 커지면
	if (0 < GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	{
		GetLevel()->GetMainCamera()->SetPos({ GetPos().X - GameEngineWindow::MainWindow.GetScale().hX() ,0 }); 
	}
	
	if ((BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X) < GetLevel()->GetMainCamera()->GetPos().X && 260 > GetLevel()->GetMainCamera()->GetPos().Y)
	{
		GetLevel()->GetMainCamera()->SetPos({ (BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X), 0 });
	}
	// Cam X가 이미지의 X보다 커지면
	if ((BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X) < GetLevel()->GetMainCamera()->GetPos().X)
	{
		float Value = GetLevel()->GetMainCamera()->GetPos().X;
		Value;
		//카메라 좌표가 배경 이미지크기 - 화면크기를 넘어간다면 카메라를 고정
		//루타배경 이미지 넓이 -> 2498
		
		GetLevel()->GetMainCamera()->SetPos({(BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X), 260});
	}

	if (260 < GetLevel()->GetMainCamera()->GetPos().Y)
	{
		GetLevel()->GetMainCamera()->SetPos({ GetPos().X - GameEngineWindow::MainWindow.GetScale().hX(), 260});
		//GetLevel()->GetMainCamera()->SetPos({ (BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().X) , 260 });
		float Value = GetLevel()->GetMainCamera()->GetPos().Y;
		Value;
	}

	int a = 0;

	//if ((BackGroundSizeforCamY - GameEngineWindow::MainWindow.GetScale().Y) < GetLevel()->GetMainCamera()->GetPos().Y)
	//{
	//	float Value = GetLevel()->GetMainCamera()->GetPos().Y;
	//	Value;
	//	//카메라 좌표가 배경 이미지크기 - 화면크기를 넘어간다면 카메라를 고정
	//	//루타배경 이미지 높이 -> 1082
	//	GetLevel()->GetMainCamera()->SetPos({ 0, 260 });
	//	//GetLevel()->GetMainCamera()->SetPos({ 0, (BackGroundSizeforCamX - GameEngineWindow::MainWindow.GetScale().Y)});
	//}



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
		Text += "플레이어 테스트 값 : ";
		Text += std::to_string(1.0f / _Delta);
		TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));
	}

	{
		float4 PlayerPos = GameEngineWindow::MainWindow.GetScale().Half();
		float4 MousePos = GameEngineWindow::MainWindow.GetMousePos();
		float4 Dir = PlayerPos - MousePos;

		std::string Text = "";
		Text += "마우스 앵글 값 : ";
		Text += std::to_string(Dir.AngleDeg());
		TextOutA(dc, 2, 20, Text.c_str(), static_cast<int>(Text.size()));
	}

	CollisionData Data;

	Data.Pos = (ActorCameraPos() + float4{ 0.0f, 30.0f });
	Data.Scale = { 5,5 };
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	Data.Pos = ActorCameraPos() + LeftCheck;
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	Data.Pos = ActorCameraPos() + RightCheck;
	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}
