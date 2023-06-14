#include <iostream>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/ContentCore.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineRandom.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 함수 f(x) => 3

	// 함수 g(3) => x

	// sin(각도) cos(각도) => float4(x, y)
	// float4(x, y) => 각도

	//while (true)
	//{
	//	int Test = GameEngineRandom::MainRandom.RandomInt(-100, 100);
	//	std::string Text = std::to_string(Test);
	//	Text += "\n";
	//	OutputDebugString(Text.c_str());
	//	Sleep(100);
	//}

	GameEngineCore::EngineStart<ContentCore>("MyWindow", hInstance);
	return 0;
}