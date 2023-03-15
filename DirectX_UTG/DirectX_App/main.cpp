#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>

#pragma comment(lib, "GameEngineBase.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	std::string Str = "aaaaa bbbbb ccccc";
	GameEngineSerializer Data;
	Data.Write(Str);

	GameEngineFile NewFile = GameEngineFile("D:\\AAAA.txt");
	NewFile.Save(Data);

}

// 건너편은 헤더만 추가했기 때문에 모름
// 참조추가가 정석적인 방법은 아니다.
// 이걸 빌드하게 되면 정적 라이브러리가 Bin > x64 > GameEngine~.lib가 나온다.
// 이걸 복잡한 과정 없이 가져다 쓰겠다가 참조추가인 것이다.
// 실제로는 #pragma comment(lib, "경로")

// 라이브러리의 모든 바이너리코드는 Bin > x64 > debug 폴더 내 GameEngine~.lib에 존재한다
// 