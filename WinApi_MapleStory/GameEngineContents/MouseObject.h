#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class MouseState
{
	Idle,
	Grab,
	GrabIdle,
	Max,
};

// 설명 : 카메라에 영향을 안받으려고 한애고
class MouseObject : public GameEngineActor
{
private:
	static MouseObject* MainMouse;

public:
	static MouseObject* GetMainMouse()
	{
		return MainMouse;
	}

public:
	// constructer destructer
	MouseObject();
	~MouseObject();

	// delete Function
	MouseObject(const MouseObject& _Other) = delete;
	MouseObject(MouseObject&& _Other) noexcept = delete;
	MouseObject& operator = (const MouseObject& _Other) = delete;
	MouseObject& operator = (MouseObject&& _Other) noexcept = delete;

	GameEngineCollision* GetCollision() 
	{
		return Collision;
	}

	void CursorGrab();

	//void ChangeState(MouseState _State);

	void ChangeAnimationState(const std::string& _StateName);

	GameEngineRenderer* CursorRenderer = nullptr;


protected:
	void StateUpdate(float _Delta);

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	//void IdleStart();
	//void IdleUpdate(float _Delta);

	//void GrabStart();
	//void GrabUpdate(float _Delta);

	//void GrabIdleStart();
	//void GrabIdleUpdate(float _Delta);

	MouseState State = MouseState::Max;
	std::string CurState = "";

private:
	GameEngineCollision* Collision;

};

