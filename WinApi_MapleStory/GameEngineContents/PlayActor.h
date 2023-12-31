#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class PlayActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayActor();
	~PlayActor();

	// delete Function
	PlayActor(const PlayActor& _Other) = delete;
	PlayActor(PlayActor&& _Other) noexcept = delete;
	PlayActor& operator=(const PlayActor& _Other) = delete;
	PlayActor& operator=(PlayActor&& _Other) noexcept = delete;

	void Gravity(float _Delta);

	void CameraFocus();

	void GravityReset()
	{
		GravityVector = float4::ZERO;
	}


	void GravityOff()
	{
		IsGravity = false;
	}

	void SetGroundTexture(const std::string& _GroundTextureName);

	// 내 위치에서 
	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);
	//int GetGroundColor(unsigned int _DefaultColor, const float4 _Pos = { 0.0f, 30.0f });
	//int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4{ 200.0f, 530.0f });

	float4 ActorCameraPos();

	void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}

	float4 GetGravityVector()
	{
		// GravityVector.y > 0.0f
		return GravityVector;
	}

protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool IsGravity = true;

	float GravityPower = 900.0f;
	float4 GravityVector = float4::ZERO;

};

