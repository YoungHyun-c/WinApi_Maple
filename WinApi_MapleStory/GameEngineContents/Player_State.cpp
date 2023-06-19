#include "Player.h"
#include "Enum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
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

void Player::IdleUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		++TestValue;
	}

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255) && CheckColor != RGB(0, 255, 0))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			GravityReset();
		}
	}


	if (true == GameEngineInput::IsDown('A')
		//|| true == GameEngineInput::IsDown('W')
		//|| true == GameEngineInput::IsDown('S')
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

	if (true == GameEngineInput::IsPress('W'))
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


void Player::RunUpdate(float _Delta)
{
	// �߷� ���� 
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255) && CheckColor != RGB(0, 255, 0))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
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


	DirCheck();

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

	//if (true == GameEngineInput::IsPress('W'))
	//{
	//	MovePos = { 0.0f, -Speed * _Delta };
	//}
	//if (true == GameEngineInput::IsPress('S'))
	//{
	//	MovePos = { 0.0f, Speed * _Delta };
	//}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
		return;
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

void Player::JumpStart()
{
	ChangeAnimationState("Jump");
	SetGravityVector(float4::UP * 400.0f);
}


void Player::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

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

	AddPos(MovePos);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) != Color && Color != RGB(0, 255, 0))
		{
			ChangeState(PlayerState::Idle);
			return;
		}
	}
}

void Player::ProneStart()
{
	ChangeAnimationState("Prone");
}

void Player::ProneUpdate(float _Delta)
{

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255) && CheckColor != RGB(0, 255, 0))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
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
}

void Player::AttackStart()
{
	ChangeAnimationState("Attack");
}

void Player::ProneAttackStart()
{
	ChangeAnimationState("Prone_Attack");
}

void Player::AttackUpdate(float _Delta)
{

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255) && CheckColor != RGB(0, 255, 0))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}


			GravityReset();
		}
	}
	if (true == MainRenderer->IsAnimationEnd())
	{
		++TestValue;
		ChangeState(PlayerState::Idle);

		//if (true == GameEngineInput::IsDown('A')
		//	|| true == GameEngineInput::IsDown('D'))
		//{
		//	DirCheck();
		//	ChangeState(PlayerState::Run);
		//	return;
		//}
	}

}