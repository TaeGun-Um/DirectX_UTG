#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

ID3D11Device* GameEngineDevice::Device = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain = nullptr;

GameEngineDevice::GameEngineDevice()
{
}

GameEngineDevice::~GameEngineDevice()
{
}

// GDI+, DXGI를 확인하면 DrawTexture가 존재한다.
// DC를 얻어오고, 경로를 채워주고.. 자동으로 실시해준다.
// 근데 일반 프로그래머가 이런 세세한 기능을 신경쓰긴 힘들고 어렵다.
// 그래도 써봐라.
IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// __uuidof(IDXGIFactory) == c++에서 지원하는 클래스를 구분하기 위한 GUI를 얻어오는 것이다.
	// 내부로 들어가서 확인하면 절대 겹치지 않는 고유 값을 받아온다. == MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	// 여기서부터는 선생님이 작성한 코드, VRAM이 가장 높은 그래픽카드가 좋다는 기준을 세움
	if (nullptr == Factory)
	{
		MsgAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다.");
		return nullptr;
	}

	size_t prevAdapterVideoMemory = 0;

	for (UINT Adapterindex = 0; ; Adapterindex++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		// 컴퓨터에 연결된 그래픽카드를 가져와서 확인
		Factory->EnumAdapters(Adapterindex, &CurAdapter);
		if (nullptr == CurAdapter)
		{
			break;
		}

		// GetDesc(&Desc) 그래픽 카드 정보 호출
		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		// VRAM 비교, DedicatedVideoMemory == VRAM 크기
		if (prevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			prevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			// Adapter의 활용이 끝났다면 릴리즈 해준다.
			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	// Factory도 릴리즈 해준다.
	Factory->Release();

	// 가장 좋은 그래픽카드 정보를 리턴해준다.
	return Adapter;
}

// Direct를 연결할 윈도우(창)을 찾아서 연결
// WinAPI를 예로 들자면, BackBuffer 만드는 작업이라고 보면 됨
void GameEngineDevice::CreateSwapChain()
{
	// 윈도우 창 크기를 설정해준다. 사이즈가 바뀌면 디바이스 초기화를 실시해야 하는데, 그건 구현 안할 것임
	// 게임 옵션에서 해상도를 변경할 경우 게임이 잠시 멈추고 로딩되는데, 이게 디바이스가 초기화되고 다시 생성되는 과정에서 발생하는 것이다.
	// 디바이스 싹 다 지우고, 리소스 싹 다 지우고 다시 만들어서 로드하니까 오래걸리는 것임
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	// 대부분 0이나 null을 넣으면 알아서 해달라는 뜻이다.
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0, };
	 
	SwapChainDesc.BufferCount = 2;                                                           // WinAPI에서 했던 더블 버퍼링 방식과 같다. 구조가 다를 바 없음. 그냥 그래픽카드를 활용하여 연산할 뿐. 사실 안해줘도 못느낄 수준이긴 하다
	SwapChainDesc.BufferDesc.Width = ScreenSize.uix();                                       // unsigned int로 화면 너비 전달
	SwapChainDesc.BufferDesc.Height = ScreenSize.uiy();                                      // unsigned int로 화면 높이 전달
	SwapChainDesc.OutputWindow = GameEngineWindow::GetHWnd();                                // 연결할 윈도우(창)의 핸들
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;                                    // 최소 화면 갱신율(최소 프레임)
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;                                     // 최대 화면 갱신율(최대 프레임)
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                            // 1byte, 1byte, 1byte, 1byte 포멧으로 그림을 그려달라는 뜻이다. DXGI_FORMAT_420_OPAQUE이 있는데, 이건 32bit, 32bit, 32bit, 32bit로 그려달라는 뜻, 4K용이다)
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;        // 이미지 하나를 그렸을 때, SCANLINE으로 그리지 않도록 설정. (SCANLINE == CPU의 순차 처리 생각하면 됨)
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                        // 기억 안나심
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;   // 특정 윈도우에서 윈도우 전용 옵션이 설정된 다이렉트 스왑체인을 사용하겠다는 의미. 쉐이더에서도 이걸 적용하겠다는 의미
	SwapChainDesc.SampleDesc.Quality = 0;                                                    // 샘플링 퀄리티 0은 자동으로 해달라는 뜻
	SwapChainDesc.SampleDesc.Count = 1;                                                      // 퀄리티를 1짜리로 만들어달라는 뜻이 아님

	// SwapChainDesc.BufferUsage == 단순히 특정 모니터에만 그리는 용도로 만드는 것이 아니라, 여러 종류를 옵션으로 정해서 만들 수 있다.
	// 윈도우가 하나니까 하나만 만들 수 있는 것이 아니라, 여러 개 만들 수 있다.

	// 샘플링이란, 화면에 무언가를 그릴 때의 설정~
	// 안티얼라이어싱(안티엘리어싱)이 있다.
	// 모니터에서 출력되는 그림을 뭉게서 부드럽게 보이도록 해주는 알고리즘 (MSAA, FXAA 알고리즘)
	// 픽셀은 모니터에 정해진 위치에 존재할 뿐, 어디론가 이동하지 않는다.
	// 이때, 픽셀 자신에 특정 물체가 들어올 경우, 자신이 가진 점의 갯수에 따라서 색을 진하게, 흐리게 조절할 수 있다.
	// 점을 2개 가졌는데, 하나에 닿았다면 약간 흐리게, 두개 다 닿았다면 원래 색으로 이런 뜻
	// 픽셀 하나가 지니는 점의 갯수가 많을 수록 색의 진함과 흐림에 대해 세분화하여 표현한다.
}





// 다이렉트 로드는 핸들(HWND)이 필요하다.
void GameEngineDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetHWnd())
	{
		MsgAssert("윈도우가 만들어지지 않았는데 디바이스를 초가화 할수는 없습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// 디버그 모드일 때는 iFalg에 D3D11_CREATE_DEVICE_DEBUG를 할당하고 HRESULT에 전달해준다.
	// 그러면 
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	// 릴리즈 모드일 때, 본인의 컴퓨터가 다이렉트11을 지원하는지 확인하기 위함
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// IDXGIAdapter 변수는 그래픽카드와 직접 연결되는 인터페이스이다.
	// GetHighPerformanceAdapter()로 자신의 컴퓨터에서 가장 좋은 그래픽카드 값을 가져온다.
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("그래픽카드 장치 어뎁터 인터페이스를 얻어오는데 실패했습니다.");
		return;
	}

	HRESULT Result = D3D11CreateDevice(
		Adapter,                                     // 그래픽카드 정보, 해당 장치를 통햇 만들어달라.
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,    // UNKNOWN을 넣어도 상관없다. 어댑터를 안넣어줘도(null 입력) 함수 내부에서 알아서 찾아낸 뒤 만들어준다.
		nullptr,                                     // Adapter를 얻어왔기 때문에 0을 넣거나 null을 넣어줄 수 있는데, 이를 넣으면 함수 안에서 알아서 해달라는 뜻이다.
		iFlag,                                       // 위에서 디버그 모드일 시 iFlag에 디버그 값을 할당했는데, 이는 디버그 모드라면 디버그로 그려달라는 뜻이 된다.
		nullptr,                                     // FeatureLevel을 가져오는 것이다. null을 넣으면 모든 리소스를 가져오라는 뜻이다.
		0,                                           // 0을 넣으면 함수 내부에서 알아서 해준다.
		D3D11_SDK_VERSION,                           // Direct도 SDK 버전이 존재하는데, D3D11_SDK_VERSION을 넣으면 윈도우가 지원하는 SDK(Software Development Kit; lib, headerㄹ라이브러리) 버전이 defined 된다.
		&Device,                                     // 이 디바이스에 값 넣어줘
		&Level,                                      // 애초에 11이기 때문에 안넣어도 11이 된다.
		&Context                                     // 이 컨텍스트에 값 넣어줘
	);

	// 7, 8, 9번을 전달했다면, 내부에서 동적할당이 발생한 것이다.
	// 릴리즈 구조를 만들어서 자신이 명시적으로 확인할 수 있도록 한다.
	// (23.04.06) GECore의 Start()와 End() 분에서 호출해줬음

	// 2번 인자 +) Adapter로 할 땐 D3D_DRIVER_TYPE_SOFTWARE와 D3D_DRIVER_TYPE_HARDWARE로 나뉜다.
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_SOFTWARE == CPU로 그려라
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE == GPU로 그려라

	if (S_OK != Result)
	{
		MsgAssert("디바이스 생성에 실패했습니다.");
		return;
	}

	// Adapter 설정이 끝났다면 릴리즈
	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	// 최종적으로 결정된 Direct의 레벨이 11이 아니라면 경고 (요즘에 11 지원 안하는 그래픽카드라면... 맙소사)
	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		MsgAssert("다이렉트 11을 지원하지 않는 그래픽카드 입니다");
		return;
	}

	// 스왑체인 == 윈도우(창)에서의 BackBuffer와 같은 역할
	// 윈도우(창)과 연결하는 작업을 실시하는 것이다.
	CreateSwapChain();
}

// 릴리즈 구조 (End에서 호출)
void GameEngineDevice::Release()
{
	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}

	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}


}