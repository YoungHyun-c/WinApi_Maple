#pragma once

// Ό³Έν :
class BellomTail
{
public:
	// constructer destructer
	BellomTail();
	~BellomTail();

	// delete Function
	BellomTail(const BellomTail& _Other) = delete;
	BellomTail(BellomTail&& _Other) noexcept = delete;
	BellomTail& operator = (const BellomTail& _Other) = delete;
	BellomTail& operator = (BellomTail&& _Other) noexcept = delete;

protected:

private:

};

