#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <vector>

// Ό³Έν :
class NineNpc : public GameEngineActor
{
public:
	// constructer destructer
	NineNpc();
	~NineNpc();

	// delete Function
	NineNpc(const NineNpc& _Other) = delete;
	NineNpc(NineNpc&& _Other) noexcept = delete;
	NineNpc& operator = (const NineNpc& _Other) = delete;
	NineNpc& operator = (NineNpc&& _Other) noexcept = delete;

	void SetMouseObject(class MouseObject* _MObject)
	{
		MObject = _MObject;
	}

protected:
	void Start() override;

	void Update(float _Delta) override;

	GameEngineRenderer* NineQuest = nullptr;
	GameEngineCollision* NineQuestCollision = nullptr;


	GameEngineRenderer* ScriptRenderer = nullptr;
	GameEngineCollision* ScriptCollision = nullptr;

	bool Script;
	bool ScriptEnd;

private:
	class MouseObject* MObject;
};

