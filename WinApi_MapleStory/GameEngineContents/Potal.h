#pragma once

// Ό³Έν :
class Potal
{
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

};

