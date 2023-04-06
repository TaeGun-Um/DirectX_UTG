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

// 
// D3D11CreateDevice() 인자가 좀 많다.
// 1. 이 장치를 통해서 만들어줘 어댑터
// 2. 언노운 넣어도 상관없음. 이렇게 해서 어댑터를 기반으로 만들 땐, 어뎁터를 안넣어주면 (널로 넣어주면) 알아서 찾아서 만들어주긴 함.
//	  어댑터로 할 땐 SOFTWARE(CPU로 그려라)와 HARDWARE(그래픽카드로 그려라)가 나뉨.
// 3. 어댑터를 얻어왔기 때문에 0을 넣거나 널을 넣을 수 있는데, 함수 안에서 알아서 해줘가 된다.
// 4. iFlag는 디버그면 디버그로 만들어줘가 된다.
// 5. FeatureLevel을 가져오는건데, 널을 넣으면 다 가져와달라고 하는 것
// 6. 0을 넣으면 알아서 해준다.
// 7. 다이렉트도 SDK 버전이 있는데, D3D11_SDK_VERSION을 넣으면 그냥 해당 윈도우에서 지원하는 SDK 버전이 define 됨
//    SDK == 소프트웨어 디벨롭먼트 키트, 소프트웨어 개발자용 키트 (lib, header 등 총집합)
// 8. 디바이스
// 9. 레벨, 애초에 11이기 때문에 안넣어도 11됨
// 
// 최종적으로 결정된 다이렉트 레벨이 넘어온다.
// 
// 7, 8, 9는 동적할당 한것과 다름 없다. 릴리즈 구조를 만들어서 명시적으로 호출하는 인터페이스 구성->coreend에서 호출
// 
// 여기까지 하면 디바이스가 만들어진다.
// 이후 윈도우 (창)과 연결하는 작업을 해줘야한다.
// 즉, 백버퍼 만드는 작업을 해줘야 한다.
// 연결한 후, 그림(2차원 배열)은 GPU에 저장되고 그것을 가져와 쓰기 위해 swapchain을 만들어야 한다.
// 
// CreateSwapChain을 하려면
// 1. 창 크기 == 윈도우창 크기를 알아야함. 사이즈가 바뀌면 디바이스 지웠다가 다시 만들어야 한다.
//              게임에서 창 크기 변경하면 잠깐 멈추고 로드됨. 이건 디바이스 싹 다 지우고, 리소스 싹 다 지우고 다시 만들어서 로드하는 과정을 거쳐야한다.
// 	            이거 안할거임
// 
// 2. DXGI_SWAP_CHAIN_DESC == 대부분 0 넣으면 기본 설정으로 해줘라는 뜻이다.
//    BufferCount = 2; WinApi의 더블 버퍼링 방식과 같다. 구조는 다를 바 없지만 다렉은 글카를 끌어와 쓰는것만 도와주고 다를뿐.
//    BufferDexc.Width = unsigned int
//    BufferDesc.Height = unsigned
//    OutputWindow = 어떤 윈도우(창)에 띄울 것인가 == 핸들
//    BufferDesc.Refreshrate.Denominator = 최소 화면 갱신률
//    BufferDesc.Refreshrate. == 최대 화면 갱신률
//    BufferDesc.Format = DXGU_FORMAT_R8G8B8A8_UNORM (1byte, 1byte, 1byte, 1byte 포멧으로 만들어달라.)  // DXGI_FORMAT_420_OPAQUE(float인데, 32bit, 32bit, 32bit 4k용이다.)
//    BufferDesc.Scanline = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED == 이미지를 하나 그렸을 때, 놀랍게도 모니터 자체는 위에서 부터 아래로 스캔라인으로 그림. 그거 설정
//    BufferDesc.Sacling = 기억 안남
//    BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE+SHADER_INPUT   == 이 스왑체인은 단순히 특정 모니터에만 그리는 용도로 만드는게 아니라, 여러 종류를 옵션을 정해서 만들 수 있다.
//                                                                    윈도우가 하나니까 하나만? 아니다. 그 상태에서도 여러개를 만들 수 있다. 지금 용도는 특정 윈도우에 윈도우 
//                                                                    전용 옵션이 설정된 다이렉트를 설정하는 것이다. 쉐이더에서도 이걸 사용할 수 있도록 하겠다는 뜻.
//    SampleDesc.Quality = 0 // 자동으로 해달라는 뜻
//    SampleDesc.Count = 1   // 퀄리티 1짜리 만들어달라는 뜻이 아님.
// 
// 샘플링
// 
// 화면에 무언갈 그릴 때, 
//
// 안티얼라이어싱
// 부드럽게 보이도록 뭉게주는 것. MSAA는 안티얼라이어싱 알고리즘이다.
// 모니터는 이미 픽셀의 2차원 배열일 뿐이다.
// 픽셀이 여러개 존재.
// 점으로 이뤄진 곳에 도형을 그리고 싶다.
// 픽셀은 제자리에 존재할 뿐
// 도형과 닿은 부위가 적다 = 옅게
// 많다 = 많게
// 이런걸 픽셀 하나에 점을 배치한다. 점의 양이 많을 수록 색의 농도 표현이 많아지며, 닿는 부분 체크도 많아짐.
// 1초에 for문을 1280x720에 안티얼라이어싱 곱하기 만큼 돈다. (1280 x 720 x 8 = 720만)
//
// 연산량이 어마어마하기 때문에 꼼수를 많이 부름
// 엔비디아 FXAA 알고리즘
//
//
//
//
//
//
//
//