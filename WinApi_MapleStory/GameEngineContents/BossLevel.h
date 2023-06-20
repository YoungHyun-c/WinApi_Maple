#pragma once

// Ό³Έν :
class BossLevel
{
public:
	// constructer destructer
	BossLevel();
	~BossLevel();

	// delete Function
	BossLevel(const BossLevel& _Other) = delete;
	BossLevel(BossLevel&& _Other) noexcept = delete;
	BossLevel& operator = (const BossLevel& _Other) = delete;
	BossLevel& operator = (BossLevel&& _Other) noexcept = delete;

protected:

private:

};

