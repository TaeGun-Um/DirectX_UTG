#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

// 설명 :
class GameEngineDebug
{
public:

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;

	static void LeakCheck();
	static void LeakPointBreak(int _Point);

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

};


#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);

// 단순히 메세지를 출력하는 함수, assert가 제거된 형태
#define MsgTextBox(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Text", MB_OK);