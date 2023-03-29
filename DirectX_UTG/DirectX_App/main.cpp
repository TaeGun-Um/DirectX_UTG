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
	GameEngineCore::Start(hInstance, ContentsCore::GameStart, ContentsCore::GameEnd);
}

// 뷰 행렬
// 
// 기하구조 관리 클래스는 굉장히 중요한 클래스이다.
// 뭐가 바뀌어도 TransfomUpdata()를 돌린다.
// 행렬의 낭비가 있을 수 있지만, 특정 오브젝트는 아닐 수 있음
// 대부분의 오브젝트는 움직이지 않기 때문에, TransformUpdate를 돌린다.
// 
// MainCamera를 만들었으니, Getmaincamera를 만들었음.
// 액터에서 바로 사용 가능.
// 
// 자신이 속한 레벨을 들고오는 class GameEngineLevel* Level 멤버 변수 생성
// ActorInit 과정에서 Level->This로 연결
// 
// 매크로함수와 인라인함수의 차이
// 매크로 함수는 #define으로 만듬
// 디버깅을 걸기 어려움
// 완전 치환형이기 때문에 자료형을 체크해주는 컴파일러가 체크해도 알아보기 어렵
// 접근제한지정자도 안된다.
// 그래서 인라인이 안정적인 코딩에 사용하는 것이 좋다.
// 
// 함수에 Local을 붙이는 이유는 추후에 알려줌
// 
// 뷰 행렬을 만들기 위해선 Z와 Y가 필요하다.
// 
// LookAtLH 함수 내부에는 내적이 들어간다.
// 
// 외적을 통해서 돌아야하는 방향을 구하고, 내적을 통해서 얼만큼 돌아야하는지 값을 구하는 것이다.
// 
// 다시 뷰 행렬
// 
// 플레이어가 원점에 있으면 나는(카메라) -100에 있는 상태
// 뷰행렬을 위해서 카메라를 원점으로 이동시키면 다른 액터들은 모두 그만큼 앞으로 이동
// 그래서 float D2Value의 값은 그만큼 이동한 값이 입력됨.
// 
// D0, D1은 X, Y값이 나옴
// 
// 이렇게 어렵게(?) 구하는 이유는 아직 회전을 안했기 때문임.
// 그래서 가운데로 간 다음 정사영 값들이 나와야하기 때문에 어렵게(?) 구하는중
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