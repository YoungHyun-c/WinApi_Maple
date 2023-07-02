#pragma once

// Ό³Έν :
class ImpMonster
{
public:
	// constructer destructer
	ImpMonster();
	~ImpMonster();

	// delete Function
	ImpMonster(const ImpMonster& _Other) = delete;
	ImpMonster(ImpMonster&& _Other) noexcept = delete;
	ImpMonster& operator = (const ImpMonster& _Other) = delete;
	ImpMonster& operator = (ImpMonster&& _Other) noexcept = delete;

protected:

private:

};

