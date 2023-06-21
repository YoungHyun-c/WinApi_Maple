#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MouseObjectPlay : public GameEngineActor
{
public:
	// constructer destructer
	MouseObjectPlay();
	~MouseObjectPlay();

	// delete Function
	MouseObjectPlay(const MouseObjectPlay& _Other) = delete;
	MouseObjectPlay(MouseObjectPlay&& _Other) noexcept = delete;
	MouseObjectPlay& operator = (const MouseObjectPlay& _Other) = delete;
	MouseObjectPlay& operator = (MouseObjectPlay&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:
	GameEngineCollision* Collision;
};

