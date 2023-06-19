#pragma once

// Ό³Έν :
class UIPanel
{
public:
	// constructer destructer
	UIPanel();
	~UIPanel();

	// delete Function
	UIPanel(const UIPanel& _Other) = delete;
	UIPanel(UIPanel&& _Other) noexcept = delete;
	UIPanel& operator = (const UIPanel& _Other) = delete;
	UIPanel& operator = (UIPanel&& _Other) noexcept = delete;

protected:

private:

};

