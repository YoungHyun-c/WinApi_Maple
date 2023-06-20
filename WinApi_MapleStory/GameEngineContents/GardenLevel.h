#pragma once

// Ό³Έν :
class GardenLevel
{
public:
	// constructer destructer
	GardenLevel();
	~GardenLevel();

	// delete Function
	GardenLevel(const GardenLevel& _Other) = delete;
	GardenLevel(GardenLevel&& _Other) noexcept = delete;
	GardenLevel& operator = (const GardenLevel& _Other) = delete;
	GardenLevel& operator = (GardenLevel&& _Other) noexcept = delete;

protected:

private:

};

