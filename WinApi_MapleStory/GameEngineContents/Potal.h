#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Potal : public GameEngineActor
{
private:
	static std::list<Potal*> AllPotal;
public:
	// constructer destructer
	Potal();
	~Potal();

	// delete Function
	Potal(const Potal& _Other) = delete;
	Potal(Potal&& _Other) noexcept = delete;
	Potal& operator = (const Potal& _Other) = delete;
	Potal& operator = (Potal&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	void Update(float _Delta) override;
};

