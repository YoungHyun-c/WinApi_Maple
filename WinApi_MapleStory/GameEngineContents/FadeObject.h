#pragma once
#include "PlayActor.h"

// ���� :
class FadeObject : public PlayActor
{
public:
	// constrcuter destructer
	FadeObject();
	~FadeObject();

	// delete Function
	FadeObject(const FadeObject& _Other) = delete;
	FadeObject(FadeObject&& _Other) noexcept = delete;
	FadeObject& operator=(const FadeObject& _Other) = delete;
	FadeObject& operator=(FadeObject&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
};

