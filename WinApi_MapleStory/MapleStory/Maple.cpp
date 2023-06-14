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
	// �Լ� f(x) => 3

	// �Լ� g(3) => x

	// sin(����) cos(����) => float4(x, y)
	// float4(x, y) => ����

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