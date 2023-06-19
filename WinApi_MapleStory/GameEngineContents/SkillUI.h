#pragma once

// Ό³Έν :
class SkillUI
{
public:
	// constructer destructer
	SkillUI();
	~SkillUI();

	// delete Function
	SkillUI(const SkillUI& _Other) = delete;
	SkillUI(SkillUI&& _Other) noexcept = delete;
	SkillUI& operator = (const SkillUI& _Other) = delete;
	SkillUI& operator = (SkillUI&& _Other) noexcept = delete;

protected:

private:

};

