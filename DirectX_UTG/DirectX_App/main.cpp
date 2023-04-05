#include <Windows.h>
#include <GameEngineBase\GameEngineFile.h>
#include <GameEngineBase\GameEngineDirectory.h>
#include <GameEngineCore\GameEngineCore.h>
#include <GameEngineContents\ContentsCore.h>

#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd, { 0, 0 });
}

// 사원수
// 
// 복소수 기반의 행렬 식 = 쿼터니온
// 회전행렬은 4x4인데
// 이걸 x y z w를 통해서 줄일 수 있음. (1x4로 줄임)
// 그걸 식으로 사용하면 회전행렬이 된다는 것
// 
// 쿼터니온은 4x4가 아닌 1x4를 지니고 있기 때문에 메모리적으로 이득
// 그리고 짐벌락 현상이 안생기게 된다.
// 
// 근데 왜 사원수가 나오냐 얘기하자면
// 월드 스페이스에 존재하는 무언가를 바꾸려고 가정해보자.
// 여기에는 이미 크자이가 적용되어 있다.
// 이 행렬을 역으로 분리하는 건 굉장히 짜증나고 힘들다.
// 근데 다이렉트에서 이걸 지원해줌
// XMMatrixDecompose(크, 자, 이)
// 
// 일단 한 번에 오일러로(원래 걸로) 이뤄진 행렬을 뽑아낼 수 없다.
// 
// 다중상속
// 다중상속을 가장 잘 사용하는 것은 인터페이스만 제공하는 것이다.
// 멤버변수는 항상 문제를 일으키기 때문에.
// 사실 풀네임으로 선언하면 알아낼 수 있음(모호성이 사라진다.)
// 
// 메쉬는 CreateLevel 전에 만들어져 있어야 한다.
// 보통 엔진에서 박스나 구, 렉트 정도는 지원해줘야 한다.
// 이것들은 Mesh에 존재.
// 
// 릭은 안남지만 내가 원하는 타이밍에 제거된다ㅡㄴ 것을 명시하기 위해 CoreResourcesEnd에서 삭제
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