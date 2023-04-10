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
// 
// 다이렉트X의 랜더링 파이프라인 
// 
// 모니터는 픽셀의 집합이다.
// 전혀 보이진 않지만 개념상 월드라는 세상을 만든다. x y (z)로 이뤄진 세상
// 어떤 세상에 존재가 있다는 것을 표현하려고 함, 이걸 도와주는게 transform
// 어떤 점이 있다. 이 점은 바라보는 방향, 위치, 회전 값들의 집합을 가지고 있음
// 이것 만으로는 화면에 도형이 나오게 하진 못함
// 점(정점)들을 모아서(연결해서) 삼각형을 만든다.
// 이 삼각형의 각 점들이 우리가 만들어낸 worldmatrix에 영향을 받는 것이다.
// 
// 삼각형이 가운데 있다고 가정해보자. 이게 worldmatrix에 영향을 받으면 크자이공부가 적용된다.
// 근데 이게 어떻게 화면에 어떻게 뜨는 걸까
// 먼저 카메라를 만든다.
// 카메라는 화각을 갖는다.
// 카메라가 0,0의 위치에 오고 나머지가 그만큼 밀려남
// 그리고 projection을 하여 프로스텀을 만들어낸다.
// 프로스텀 안에 매쉬를 가진 존재가 들어오면 뷰포트가 곱해지면서 화면에 위치하게 된다.
// 
// 그리고 삼각형과 닿은 픽셀들에 따라 걸러냄
// 
// 이게 일반적인 랜더링 파이프라인임
// 근데 다렉은 좀 다르다.
// 
// input assembler : 점을 준비하라
// 오른쪽 구조체들
// 왼쪽 리소스들
// 
// 최초에 화면에 위치하게 하면 점은 위치만 있음
// 색은? 점 안에 들어있어야 함
// 점은 위치와 색깔 정보값을 다 가지고 있어야함
// 이 점을 만들어서 DirectX한테 보내야 한다.
// 
// 지금까지는 점의 위치만 보낸 것임(위치는 물론 필수)
// 점에는 위치 뿐만 아니라 여러 정보를 담을 수 있다.
// 
// 리소스에 GameEngineVertex 추가
// 인스턴스 버퍼 == 다이렉트X에 자신이 넣은 점들의 갯수와, 그걸 어떤 순서로 그릴 지 정보를 넘겨줘야함
// 매쉬는 버텍스와 인스턴스 버퍼로 이뤄짐
// 초반에는 사실 버텍스랑 인스턴스 두개 합쳐진 상태를 매쉬라고 부르지도 않음
// 사람들끼리 매쉬라고 부르기로 약속한 단어임
// 다렉에서는 버텍스버퍼라고 부른다. 점만 놓고 보면
// 이 점을 그리는 건 인스턴스 버퍼라고 한다.
// 
// DirectBuffer에서
// Id3D11Buffer << 인덱스를 넣어도, 상수를 넣어도 이걸 줌
// 어떤 데이터에 대한 사용 권한을 주기 위한 것
// 다이렉트 X가 보기엔 그래픽카드 램에 몇 바이트 공간 만들어주면 되는거지? 라고 하는 것
// 이 공간을 어떻게 쓸 지는 너가 알려줭~ 식으로 처리함
// 
// 모든 버퍼 계열들은 모두 ID3D11Buffer를 들고 있게 된다.
// 그리고 D3D11_BUFFER_DESC 에서 정보를 받아 사용
// 
// vertexvbuffer에 이중 상속을 걸어
// 
// 그러면 위의 두 멤버 변수 사용 가능
// 
// 어차피 할당될 것이기 때문에 Buffer의 릴리즈 구조를 DirectBuffer의 소멸자에서 구현
// 
// Bufferinfo.BindFlag << 램 안에 공간 만들건데, 용도를 알려주는 것
// D3D11_BIND_VERTEX_BUFFER
// 용도가 버텍스 버퍼임
// 
// bufferinfo.ByteWidth 얼마난 크기인지 크기 지정
// 	   다렉 관점에선 갯수 관심 없어서 곱해서 들어감
// 
// CPUACCESFLAGE = 0;
// 이게 0이면 접근 안하겠다는 뜻
// 0이 아니면 다이나믹 으로~
// 
// Usage 메모리 어디에 둘 것인지, 디폴트는 그래픽카드임 GPU에서 읽고 수정 가능. cpu에선 불가
// 1 : 읽을 수만 있음, 한 번 올리고 나면 안바뀜
// 다이나믹 : GPU와 CPU 모두에서 액세스 가능, 글카에 올려도 수정하려면 cpu에서 수정 가능 안가능
// 3 : gpu에 있는 값을 받아보고싶다 (뭔가 그린거를 받아오는거임) 이게 비트코인. 기본적으로는 안된다.
// 
// 이제 디바이스에 리소스를 만드는 작업을 요청
// CreateBuffer(&Bufferinfo, &Data, &Buffer)
// Data = 이 데이터대로 만들어줭
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