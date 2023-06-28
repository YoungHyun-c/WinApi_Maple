#pragma once

// Ό³Έν :
class RutaNpc
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

protected:

private:

};

