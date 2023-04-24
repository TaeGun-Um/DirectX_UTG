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

// 침습형 shared ptr
// 
// 레퍼런스는 지금 shared ptr이 관리중
// 이게 안좋은게 있음
// 
// 레퍼런스 카운트를 부모가 가지고 있으면 좋음
// 방식의 문제점은 부모 클래스가 들고 있어야 한다.
// 내부에 들고있는건 동적할당을 실시하기 때문에 부모가 그냥 값으로 들고있는게 좋다는 뜻
// 
// std에서는 이걸 std::enable_shared_from_this로 지원
// 이건 다중 상속할 때만 가능
// 
// 블랜드
// 2번 : factor 넣을때가 있는데 지금은 널
//       필터를 임의로 넣을 수 있다. 0.5 0.5 0.5 넣고싶으면 지정해서 넣을 수 있다는 뜻
//       SrcBlend 내가 직접 넣은 거면, 아직 처리할 수 없는 블랜드 방식이라고 팅굴 예정.
//       
// 3번 : 16진수, 0xFFFFFFFF
//       두 자리씩 나눠서, 1번 2번이면 R, 3번 4번이면 G, 5번 6번이면 B, 7번 8번이면 A
//       00을 넣으면 블랜드를 하지 마라라는 뜻. 근데 써본적 없음.
// 
// 코어리소스에서
// 
// 처음에 아무것도 없을 때. 기본 세팅이 1111블랜드임.
// 어떤 랜더타겟에 이미 그려진 컬러를 데스크컬러라고 한다.
// 그리고 그려져야 하는(픽셀이 건져진) 컬러를 소스컬러라고 한다.
// 데스크컬러가 0011이고, 소스컬러가 1001일때, 이걸 어떻게 합칠지 결정하는게 블랜더다.
// 더할거냐 뺄거냐~
//
// 1 0 0 1 * 필터 (옵션) 0 0 1 1 * 필터
// 
// 1번 : false, 자동으로 알파부분을 제거해서 출력해주는 것. True 개느리니까 false
// 2번 : 블랜드를 여러 개 넣을 것이냐, true면 여러 개 넣는다. 랜더타겟(SVTarget)을 한 번에 10개 세팅하고 동시에 10개 출력할 수 있는데, 이러면 블랜드 세팅 개수는 그 갯수만큼 필요함
//       이게 false면, 0번으로 다 해라,
// 3번 : 2번 셋팅에 몇 번 블랜드로 할 지 정하는 것
// 4번 : 
// 5번 : 더할거냐 뺄거냐 max와 min은 최종 색을 결정. 
//       1001 0011을 더하면, 최종 색은 max일 때 1 0 1 1 min이면 0 0 0 1
// 6번 : 필터를 뭐로 할거냐, 네 번째 숫자를 세 개의 수로 나눔, 이것도 r g b
// 7번 : 1 - 알파, 위쪽에 덮는 알파가 쌔면 옅어지게 만드는 것.
// 8번 : 8 ~ 10번은, 알파쪽에서만 따로 설정할 수 있는 옵션, rgb랑 똑같음
// 9번
// 10번 : 
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