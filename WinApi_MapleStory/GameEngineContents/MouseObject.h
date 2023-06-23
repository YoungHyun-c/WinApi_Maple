#pragma once
#include <GameEngineCore/GameEngineActor.h>

// CreateActor<MouseObject>()

// ���� : ī�޶� ������ �ȹ������� �Ѿְ�
class MouseObject : public GameEngineActor
{
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

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	GameEngineCollision* Collision;
};

