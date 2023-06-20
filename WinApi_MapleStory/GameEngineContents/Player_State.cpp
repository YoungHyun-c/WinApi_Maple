#include "Player.h"
#include "Enum.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}

// 가만히 있는 중일 때
void Player::IdleUpdate(float _Delta)
{
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), GroundCheck);
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck + float4::UP);

			while (CheckColor != RGB(255, 255, 255) && CheckColor != RGB(0, 255, 0))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck + float4::UP);
				AddPos(float4::UP);
			}
			GravityReset();
		}
	}

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_SPACE))
	{
		ChangeState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeState(PlayerState::Prone);
		return;
	}

	unsigned int CheckColor = GetGroundColor(RGB(0, 255, 0), RopeCheck);
	if (true == GameEngineInput::IsPress('W') && CheckColor == RGB(0, 255, 0))
	{
		ChangeState(PlayerState::Rope);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT))
	{
		ChangeState(PlayerState::Attack);
		return;
	}
}


// 움직이는 중일 때
void Player::RunUpdate(float _Delta)
{
	DirCheck();
	// 중력 적용 
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), GroundCheck);
		if (Color == RGB(255, 255, 255))
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck + float4::UP);

			while (CheckColor == RGB(255, 0, 0)) //&& CheckColor != (0, 255, 0))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck + float4::UP);
				AddPos(float4::UP);
			}


			if (true == GameEngineInput::IsPress(VK_SPACE))
			{
				ChangeState(PlayerState::Jump);
				return;
			}

			GravityReset();
		}
	}


	unsigned int CheckColor = GetGroundColor(RGB(0, 255, 0), RopeCheck);
	if (true == GameEngineInput::IsPress('W') && CheckColor == RGB(0, 255, 0))
	{
		ChangeState(PlayerState::Rope);
		return;
	}

	float Speed = 300.0f;

	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		CheckPos = LeftCheck;
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		CheckPos = RightCheck;
		MovePos = { Speed * _Delta, 0.0f };
	}

	// 공격
	if (true == GameEngineInput::IsDown(VK_SHIFT))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
		return;
	}

	{
		//unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		//if (Color == RGB(255, 255, 255) || Color == RGB(0, 255, 0))
		//{
		//	AddPos(MovePos);
		//	GetLevel()->GetMainCamera()->AddPos(MovePos);
		//}

		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255) || Color == RGB(0, 255, 0))
		{
			if (RGB(255, 255, 255) == GetGroundColor(RGB(255, 255, 255), GroundCheck + MovePos))
			{
				float4 XPos = float4::ZERO;
				float4 Dir = MovePos.X <= 0.0f ? float4::RIGHT : float4::LEFT;

				while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), GroundCheck + MovePos + XPos))
				{
					XPos += Dir;

					if (abs(XPos.X) > 50.0f)
					{
						break;
					}
				}

				float4 YPos = float4::ZERO;
				while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), GroundCheck + MovePos + YPos))
				{
					YPos.Y += 1;

					if (YPos.Y > 60.0f)
					{
						break;
					}
				}

				if (abs(XPos.X) >= YPos.Y)
				{
					while (RGB(255, 0, 0) != GetGroundColor(RGB(255, 255, 255), GroundCheck + MovePos))
					{
						MovePos.Y += 1;
					}
				}

			}

			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}

}

void Player::JumpStart()
{
	SetGravityVector(float4::UP * 400.0f);
	Jump = true;
	DoubleJump = true;
	ChangeAnimationState("Jump");
}

void Player::DoubleJumpStart()
{
	if (Dir == PlayerDir::Right)
	{
		SetGravityVector(float4{ 400.0f, -300.0f });
	}
	if (Dir == PlayerDir::Left)
	{
		SetGravityVector(float4{ -400.0f, -300.0f });
	}
	Jump = false;
	ChangeAnimationState("Jump");
}

void Player::DoubleJumpUpdate(float _Delta)
{
	DirCheck();
	Gravity(_Delta);

	unsigned int CheckColor = GetGroundColor(RGB(0, 255, 0), RopeCheck);
	if (true == GameEngineInput::IsPress('W') && CheckColor == RGB(0, 255, 0))
	{
		ChangeState(PlayerState::Rope);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	//float Speed = 100.0f;
	//float4 MovePos = float4::ZERO;
	//float4 CheckPos = float4::ZERO;
	//if (true == GameEngineInput::IsPress('A'))
	//{
	//	CheckPos = LeftCheck;
	//	MovePos += float4::LEFT * Speed * _Delta;
	//}
	//else if (true == GameEngineInput::IsPress('D'))
	//{
	//	CheckPos = RightCheck;
	//	MovePos += float4::RIGHT * Speed * _Delta;
	//}

	//AddPos(MovePos);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), GroundCheck);
		if (RGB(255, 255, 255) != Color && Color != RGB(0, 255, 0))
		{
			ChangeState(PlayerState::Run);
			return;
		}
	}
}

// 점프중 일 때
void Player::JumpUpdate(float _Delta)
{
	Gravity(_Delta);
	DirCheck();

	if (DoubleJump == true && true == GameEngineInput::IsDown(VK_SPACE))
	{
		ChangeState(PlayerState::DoubleJump);
	}

	unsigned int CheckColor = GetGroundColor(RGB(0, 255, 0), RopeCheck);
	if (true == GameEngineInput::IsPress('W') && CheckColor == RGB(0, 255, 0))
	{
		ChangeState(PlayerState::Rope);
		return;
	}


	float Speed = 250.0f;
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A'))
	{
		CheckPos = LeftCheck;
		MovePos += float4::LEFT * Speed * _Delta;
	}
	else if (true == GameEngineInput::IsPress('D'))
	{
		CheckPos = RightCheck;
		MovePos += float4::RIGHT * Speed * _Delta;
	}


	// 공격
	if (true == GameEngineInput::IsDown(VK_SHIFT))
	{
		ChangeState(PlayerState::Attack);
		return;
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), GroundCheck);
		if (RGB(255, 255, 255) != Color && Color != RGB(0, 255, 0))
		{
			ChangeState(PlayerState::Run);
			return;
		}
	}
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255) || Color == RGB(0, 255, 0))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}

}

void Player::ProneStart()
{
	ChangeAnimationState("Prone");
}

// 엎드려있는 중일 때
void Player::ProneUpdate(float _Delta)
{
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), GroundCheck);
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck + float4::UP);

			while (CheckColor != RGB(255, 255, 255) && CheckColor != RGB(0, 255, 0))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck + float4::UP);
				AddPos(float4::UP);
			}
			GravityReset();
		}
	}

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SHIFT))
	{
		ChangeState(PlayerState::ProneAttack);
		return;
	}
}

void Player::RopeStart()
{
	ChangeAnimationState("Rope");
	SetGravityVector(float4::UP * 100.0f);
}

// 로프(줄)타는 중일 때
void Player::RopeUpdate(float _Delta)
{
	float Speed = 100.0f;
	float4 MovePos = float4::ZERO;
	float4 CheckPos = float4::ZERO;

	unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), RopeCheck);
	if (true == GameEngineInput::IsPress('W') && CheckColor == RGB(0, 255, 0))
	{
		CheckPos = RopeCheck;
		MovePos = { 0.0f, -Speed * _Delta };
	}
	if (true == GameEngineInput::IsPress('S') && CheckColor == RGB(0, 255, 0))
	{
		CheckPos = RopeCheck;
		MovePos = { 0.0f, Speed * _Delta };
	}

	AddPos(MovePos);


	unsigned int GroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck);
	if (CheckColor == RGB(255, 255, 255))
	{
		while (GroundCheckColor == RGB(0, 255, 0))
		{
			GroundCheckColor = GetGroundColor(RGB(0, 255, 0), GroundCheck);
			AddPos(float4::UP);
		}
		ChangeState(PlayerState::Run);
		return;

	}

	if (GroundCheckColor == RGB(255, 0, 0))
	{
		ChangeState(PlayerState::Run);
		return;
	}


	unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
	if (Color == RGB(0, 255, 0))
	{
		AddPos(MovePos);
		GetLevel()->GetMainCamera()->AddPos(MovePos);
	}

}

void Player::AttackStart()
{
	int Value = GameEngineRandom::MainRandom.RandomInt(0, 2);

	switch (Value)
	{
	case(0):
		ChangeAnimationState("Attack0");
		break;
	case(1):
		ChangeAnimationState("Attack1");
		break;
	case(2):
		ChangeAnimationState("Attack2");
		break;
	default:
		break;
	}
}

void Player::ProneAttackStart()
{
	ChangeAnimationState("Prone_Attack");
}

// 엎드려서 공격중일 때
void Player::ProneAttackUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		++TestValue;
		ChangeState(PlayerState::Prone);
		return;
	}

	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Run);
		return;
	}

}

void Player::AttackUpdate(float _Delta)
{

	if (Jump == true)
	{
		float Speed = 300.0f;
		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;
		if (true == GameEngineInput::IsPress('A'))
		{
			CheckPos = LeftCheck;
			MovePos += float4::LEFT * _Delta * Speed;
		}
		else if (true == GameEngineInput::IsPress('D'))
		{
			CheckPos = RightCheck;
			MovePos += float4::RIGHT * _Delta * Speed;
		}

		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);
		if (Color == RGB(255, 255, 255) || Color == RGB(0, 255, 0))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}

	if (DoubleJump == true)
	{
		float Speed = 300.0f;
		float4 MovePos = float4::ZERO;
		float4 CheckPos = float4::ZERO;
		if (true == GameEngineInput::IsPress('A'))
		{
			CheckPos = LeftCheck;
		}
		else if (true == GameEngineInput::IsPress('D'))
		{
			CheckPos = RightCheck;
		}
	}

	unsigned int Color = GetGroundColor(RGB(255, 255, 255), GroundCheck);
	if (RGB(255, 255, 255) == Color || Color == RGB(0, 255, 0))
	{
		Gravity(_Delta);
	}
	else
	{
		unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck + float4::UP);

		while (CheckColor != RGB(255, 255, 255) && CheckColor == RGB(0, 255, 0))
		{
			CheckColor = GetGroundColor(RGB(255, 255, 255), GroundCheck + float4::UP);
			AddPos(float4::UP);
		}

		Jump = false;
		GravityReset();
	}


	if (true == MainRenderer->IsAnimationEnd())
	{
		++TestValue;
		ChangeState(PlayerState::Run); // Alert
		return;
	}

}