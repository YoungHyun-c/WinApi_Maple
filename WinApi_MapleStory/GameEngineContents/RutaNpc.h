#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class RutaNpc : public GameEngineActor
{
public:
	// constructer destructer
	RutaNpc();
	~RutaNpc();

	// delete Function
	RutaNpc(const RutaNpc& _Other) = delete;
	RutaNpc(RutaNpc&& _Other) noexcept = delete;
	RutaNpc& operator = (const RutaNpc& _Other) = delete;
	RutaNpc& operator = (RutaNpc&& _Other) noexcept = delete;

	void  SetMouseObject(class MouseObject* _MObject)
	{
		MObject = _MObject;
	}

protected:
	void Start() override;

	void Update(float _Delat) override;

	GameEngineRenderer* RutaQuest = nullptr;
	GameEngineCollision* RutaQuestCollision = nullptr;

	GameEngineRenderer* ScriptRenderer = nullptr;
	GameEngineCollision* ScriptCollision = nullptr;

	bool RutaScript = false;
	bool ScriptEnd = false;
	int RutaScripti = 0;

private:

	class MouseObject* MObject;
};

