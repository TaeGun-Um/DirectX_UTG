#include "PrecompileHeader.h"
#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\CupheadCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::Start(hInstance, CupheadCore::GameStart, CupheadCore::GameEnd, { 0, 0 });
}

// 
// 상수버퍼 이름은 하나인데, 버텍스에 사용되기도 하고 쉐이더에 사용되기도 한다면, 해결 방법이 multimap이다.
// 
// 상수버퍼는 언제 만들어지냐~ 쉐이더 컴파일 하면서 이런 쉐이더를 쓰는구나 하고(64바이트 짜리 상수버퍼를 쓰네) 상수 버퍼가 만들어지는 것
// 리소스는 텍스쳐를 쓰네, 상수버퍼를 쓰네를 들고 있는 것  
// 
// 상수버퍼는 메모리를 아끼기 위해서 복잡한 과정을 거친다.
// 다른 쉐이더를 새로 만들었는데, 이름만 똑같고 크기가 다를 수도 있음
// 
// switch문으로 돌아와서
// 상수버퍼 쓴다고 온 상황에, Create() 실시함.
// 문제는 쉐이더를 만들면 만들수록 상수버퍼는 계속 늘어날 것이다.
// 이름만 똑같고 크기가 다를 수 있지만, 완전히 똑같은 이름과 크기의 상수버퍼가 만들어질 수도 있음
// 기본적으로 상수버퍼는 이름이 중요한게 아니고 크기가 중요하다.
// 
// 현재 엔진은 리소스를 이름으로 관리하기로 했다.
// 상수버퍼는 이름이 중요하지 않아서 이름으로 관리 안할것임
// GameEngineResources는 상속 받을 것이다.
// 상수버퍼는 돌려쓸 수 있기 때문. 이름이 다르다고 상수 버퍼를 또 만들지는 않을 것임
// 크기가 같은 상수버퍼는 공유된다.
// 
// 상수버퍼 CreateAndFind는 조건에 합당한 것을 리턴해줌, 없으면 만들어서 리턴해줌
// 매개 변수를 byte, Name으로 하는 이유는
// 크기는 같지만 슬롯과 이름이 다르면 다른 상수 버퍼가 되기 위함.
// 
// CPU 클래그가 write, 행렬을 접근해서 써주기 위함
// 그래서 다이나믹으로 만들어지고
// GetDevice->CreateBuffer에서 2번째 인자가 필요없다.
// 
// 텍스쳐는 한장이고 돌려쓸 예정이라면
// 각자가 가지게될 리소스들을 랜더러마다 하나씩 가지게 하는 것
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
//