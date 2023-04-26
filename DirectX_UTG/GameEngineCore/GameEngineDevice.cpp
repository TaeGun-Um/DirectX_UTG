#include "PrecompileHeader.h"
#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineRenderTarget.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

ID3D11Device* GameEngineDevice::Device = nullptr;
ID3D11DeviceContext* GameEngineDevice::Context = nullptr;
IDXGISwapChain* GameEngineDevice::SwapChain = nullptr;
std::shared_ptr<GameEngineRenderTarget> GameEngineDevice::BackBufferTarget = nullptr;

GameEngineDevice::GameEngineDevice()
{
}

GameEngineDevice::~GameEngineDevice()
{
}

// GDI+, DXGI�� Ȯ���ϸ� DrawTexture�� �����Ѵ�.
// DC�� ������, ��θ� ä���ְ�.. �ڵ����� �ǽ����ش�.
// �ٵ� �Ϲ� ���α׷��Ӱ� �̷� ������ ����� �Ű澲�� ����� ��ƴ�.
// �׷��� �����.
IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// __uuidof(IDXGIFactory) == Direct������ �ڽ��� ���̺귯���� Ȱ���� ��, Factory �������̽��� Ȱ���Ͽ� �������� �ߴ�.
	// �̸� Ȱ���ϸ� == GUID MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")�� ������ �ȴ�.
	// �̰��� ���� ��ġ�� �ʴ� ���� ���̴�.
	// ���α׷��� ��Ʋ� �� �ϳ��� ������ �� �ִ� Ű�� ����� ���, __uuidof(IDXGIFactory) �ߴµ� ���̵� ���� ���ɼ��� ������ ��.
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	// ���⼭���ʹ� �������� �ۼ��� �ڵ�, VRAM�� ���� ���� �׷���ī�尡 ���ٴ� ������ ����
	if (nullptr == Factory)
	{
		MsgAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
		return nullptr;
	}

	size_t prevAdapterVideoMemory = 0;

	for (UINT Adapterindex = 0; ; Adapterindex++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		// ��ǻ�Ϳ� ����� �׷���ī�带 �����ͼ� Ȯ��
		Factory->EnumAdapters(Adapterindex, &CurAdapter);
		if (nullptr == CurAdapter)
		{
			break;
		}

		// GetDesc(&Desc) �׷��� ī�� ���� ȣ��
		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		// VRAM ��, DedicatedVideoMemory == VRAM ũ��
		if (prevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			prevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			// Adapter�� Ȱ���� �����ٸ� ������ ���ش�.
			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	// Factory�� ������ ���ش�.
	Factory->Release();

	// ���� ���� �׷���ī�� ������ �������ش�.
	return Adapter;
}

// Direct�� ������ ������(â)�� ã�Ƽ� ����
// WinAPI�� ���� ���ڸ�, BackBuffer ����� �۾��̶�� ���� ��
void GameEngineDevice::CreateSwapChain()
{
	// ������ â ũ�⸦ �������ش�. ����� �ٲ�� ����̽� �ʱ�ȭ�� �ǽ��ؾ� �ϴµ�, �װ� ���� ���� ����
	// ���� �ɼǿ��� �ػ󵵸� ������ ��� ������ ��� ���߰� �ε��Ǵµ�, �̰� ����̽��� �ʱ�ȭ�ǰ� �ٽ� �����Ǵ� �������� �߻��ϴ� ���̴�.
	// ����̽� �� �� �����, ���ҽ� �� �� ����� �ٽ� ���� �ε��ϴϱ� �����ɸ��� ����
	float4 ScreenSize = GameEngineWindow::GetScreenSize();

	// ��κ� 0�̳� null�� ������ �˾Ƽ� �ش޶�� ���̴�.
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0, };
	 
	SwapChainDesc.BufferCount = 2;                                                           // WinAPI���� �ߴ� ���� ���۸� ��İ� ����. ������ �ٸ� �� ����. �׳� �׷���ī�带 Ȱ���Ͽ� ������ ��. ��� �����൵ ������ �����̱� �ϴ�
	SwapChainDesc.BufferDesc.Width = ScreenSize.uix();                                       // unsigned int�� ȭ�� �ʺ� ����
	SwapChainDesc.BufferDesc.Height = ScreenSize.uiy();                                      // unsigned int�� ȭ�� ���� ����
	SwapChainDesc.OutputWindow = GameEngineWindow::GetHWnd();                                // ������ ������(â)�� �ڵ�
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;                                    // �ּ� ȭ�� ������(�ּ� ������)
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;                                     // �ִ� ȭ�� ������(�ִ� ������)
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                            // 1byte, 1byte, 1byte, 1byte �������� �׸��� �׷��޶�� ���̴�. DXGI_FORMAT_420_OPAQUE�� �ִµ�, �̰� 32bit, 32bit, 32bit, 32bit�� �׷��޶�� ��, 4K���̴�)
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;        // �̹��� �ϳ��� �׷��� ��, SCANLINE���� �׸��� �ʵ��� ����. (SCANLINE == CPU�� ���� ó�� �����ϸ� ��)
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                        // ��� �ȳ���
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;   // Ư�� �����쿡�� ������ ���� �ɼ��� ������ ���̷�Ʈ ����ü���� ����ϰڴٴ� �ǹ�. ���̴������� �̰� �����ϰڴٴ� �ǹ�
	SwapChainDesc.SampleDesc.Quality = 0;                                                    // ���ø� ����Ƽ 0�� �ڵ����� �ش޶�� ��
	SwapChainDesc.SampleDesc.Count = 1;                                                      // ����Ƽ 0¥���� �Ѱ� ������ ���� �ƴϴ�. ��κ��� ���α׷��Ӵ� ���̴��� ��Ƽ����̾���� ���� ����. �⺻ ����� �ʹ� ������ �����̴�.
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;								 // �̹����� ���������� ȭ�鿡 ��µǾ�� �Ѵ�. ȭ�鿡 ����ϱ� �� �ʿ��� �̹����� ������� ���۸� �ΰ� ����ٴ� ��.
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                            // ȭ�� ũ�⸦ �ٲٰų� ����͸� �ٲ� �� �ʿ��� ������, ���ӿ��� �ػ� ���� ���ɼ��� ����� �ִ� �ɼ��ε�, �̴� �����Ѵٴ� ���̴�. �ƹ��͵� ������ �˾Ƽ� �Ѵ�.
	SwapChainDesc.Windowed = true;                                                           // false�� ��üȭ�� �Դϴ�.

	// SwapChainDesc.BufferUsage == �ܼ��� Ư�� ����Ϳ��� �׸��� �뵵�� ����� ���� �ƴ϶�, ���� ������ �ɼ����� ���ؼ� ���� �� �ִ�.
	// �����찡 �ϳ��ϱ� �ϳ��� ���� �� �ִ� ���� �ƴ϶�, ���� �� ���� �� �ִ�.

	// ���ø��̶�, ȭ�鿡 ���𰡸� �׸� ���� ����~
	// ��Ƽ����̾��(��Ƽ�������)�� �ִ�.
	// ����Ϳ��� ��µǴ� �׸��� ���Լ� �ε巴�� ���̵��� ���ִ� �˰��� (MSAA, FXAA �˰���)
	// �ȼ��� ����Ϳ� ������ ��ġ�� ������ ��, ���а� �̵����� �ʴ´�.
	// �̶�, �ȼ� �ڽſ� Ư�� ��ü�� ���� ���, �ڽ��� ���� ���� ������ ���� ���� ���ϰ�, �帮�� ������ �� �ִ�.
	// ���� 2�� �����µ�, �ϳ��� ��Ҵٸ� �ణ �帮��, �ΰ� �� ��Ҵٸ� ���� ������ �̷� ��
	// �ȼ� �ϳ��� ���ϴ� ���� ������ ���� ���� ���� ���԰� �帲�� ���� ����ȭ�Ͽ� ǥ���Ѵ�.

	// SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	// Direct�� �⺻������ ������ ����� ���ϱ� ������ ������� ȭ�鿡 ������ �ϱ� ���ؼ� ȭ�鿡 �̹����� ���� �ð����� ������ �ʰ� ��ǲ�� ���� �ʾҴٸ� �ٸ� ���۸� �̿��Ѵ�.
	// �ٸ� ���۸� �̿��ϴ� ����, ������ ���۴� �ٽ� ��� ���¿� ���δ�.

	IDXGIDevice* SwapDevice = nullptr;
	IDXGIAdapter* SwapAdapter = nullptr;
	IDXGIFactory* SwapFactory = nullptr;

	// static IDXGIAdapter* GetHighPerformanceAdapter();�� ���� ���� ����͸� Ȱ���� �� �ֱ� �ѵ�, D3D11CreateDevice()�� ���� Device�� ���������.
	// SwapDevice���� Device ������ ����
	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&SwapDevice));
	if (nullptr == SwapDevice)
	{
		MsgAssert("DXGI ����̽��� DirectX����̽����� ������ ���߽��ϴ�.");
		return;
	}

	// �� ������� SwapDevice�� ���� SwapAdapter�� ������ ���� �� �ִ�. (��ġ WinAPI�� GetLevel() ���� ����)
	SwapDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&SwapAdapter));
	if (nullptr == SwapAdapter)
	{
		MsgAssert("DXGI ����̽��� DirectX����̽����� ������ ���߽��ϴ�.");
		return;
	}

	// ������ GetHighPerformanceAdapter()�� ���� Adapter�� Factory�� ���Դ�.
	// ���⼱ ������ SwapAdapter�� ���� SwapFactory ������ �����´�.
	SwapAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&SwapFactory));

	// ������ SwapFactory�� SwapChain�� �����.
	if (S_OK != SwapFactory->CreateSwapChain(Device, &SwapChainDesc, &SwapChain))
	{
		MsgAssert("����ü�� ������ �����߽��ϴ�.");
		return;
	}

	// SwapChain ������ �Ϸ�ƴٸ� SwapDevice, SwapAdapter, SwapFactory�� Release�� �ǽ��Ѵ�.
	SwapDevice->Release();
	SwapAdapter->Release();
	SwapFactory->Release();

	ID3D11Texture2D* SwapBackBufferTexture = nullptr;

	// SwapChain�� �����ߴٸ�, ���ο� Texture�� ���ϰ� �ִ�. ID3D11Texture2D* SwapBackBufferTexture���� �װ��� ������ ���̴�.
	HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&SwapBackBufferTexture));
	if (S_OK != Result)
	{
		MsgAssert("����ü�� ������ �����߽��ϴ�.");
		return;
	}

	// �׸����� RenderTarget�� �����.
	// �׷���ī������ �� �ؽ��ĸ� ������ �� �ִ� ������ ����� �޶�� �ϴ� ���̴�.
	// �̶�, SwapChain���� ���� Texture�� �������� �ڵ�� ����� Direct�� Texture�̴�.
	// �̰� ������ ������ ���� ������ Device->CreateTargetview(�����, ����Ÿ��)�� �ǽ�������, �̰� GameEngineTextuer, GameEngineRenderTarget �� ���� ������.

	std::shared_ptr<GameEngineTexture> BackBufferTexture = std::make_shared<GameEngineTexture>();
	BackBufferTexture->ResCreate(SwapBackBufferTexture);

	// RenderTarget�� HDC��� �����ϸ� �ȴ�. HDC�� �̹����� ������ �� �ִ� ����(�ڵ�)�̴�.
	BackBufferTarget = GameEngineRenderTarget::Create("MainBackBufferTarget", BackBufferTexture, { 0.0f, 0.0f, 1.0f, 1.0f });

	// WinAPI������ �̹����� �ε��� ������ HDC�� ���Ա� ������, �츮�� �� ��, �� õ���� HDC�� ��Ʈ�� �ߴ�. �̹����� �ε��� ��ŭ HDC�� �����ϱ� �����̴�.
	// �׷��� HDC�� ������ �̹����� ȭ�鿡 ��� ���� ������.
	// HDC�� ȭ�鿡 �׸��� ���� �� �����ϴ� ���̴�. �̰� ������ ȭ�鿡 ������ �ص� ������, �̰͸� �ؼ� ������.
	// �̰� RenderTarget�� �׷��ִ� ���̴�.

	// ��� : ������ Window�� ���� HWND�� ���� -> �̰ɷ� SwapChain�� ���� -> SwapChain�� Texture�� ���� -> Texture�� �׸� �׸� ������ RenderTarget�� ����

	// �𽺿� ���� ���� �ؽ��� ����
	BackBufferTarget->CreateDepthTexture();
}

// ����� Ŭ����
void GameEngineDevice::RenderStart()
{
	BackBufferTarget->Clear();   // ����� Ŭ����
	BackBufferTarget->Setting(); // �ƿ�ǲ���� ����
	// ���⿡ �ƿ�ǲ���� ������ �ִٰ� �����ϸ� �ȵǴ� ����, ������ ������� �ؾ��Ѵٰ� �����ϴ� ���̴�.
	// ������ ������������ ���� ������ ��, Draw ������ ������ ������ ����� ����. ������ ���ܰ踦 ���ߴٰ� �����ܰ踦 ���ϴ°� �ƴ�
}

// ����ۿ� �̹��� ����(HDC�� ������ �̹��� ȭ�鿡 ����)
void GameEngineDevice::RenderEnd()
{
	// ������(â)�� ������ ���(�ػ� ����) �� �κп��� ������.
	// �ٵ� ũ�⸦ �����ϴ� ����� ����̽� �ʱ�ȭ, ���ҽ� ���� �� �ٽ� ����̽� �����ϴ� ������ ��ġ�µ� << �̰� �ȸ����� ������ �����ϸ� ���⼭ ����.
	HRESULT Result = SwapChain->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		// ����̽� �ٽø����
		MsgAssert("����Ÿ�� ������ �����߽��ϴ�.");
		return;
	}
}

// ���̷�Ʈ �ε�� �ڵ�(HWND)�� �ʿ��ϴ�.
void GameEngineDevice::Initialize()
{
	if (nullptr == GameEngineWindow::GetHWnd())
	{
		MsgAssert("�����찡 ��������� �ʾҴµ� ����̽��� �ʰ�ȭ �Ҽ��� �����ϴ�.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// ����� ����� ���� iFalg�� D3D11_CREATE_DEVICE_DEBUG�� �Ҵ��ϰ� HRESULT�� �������ش�.
	// �׷��� 
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	// ������ ����� ��, ������ ��ǻ�Ͱ� ���̷�Ʈ11�� �����ϴ��� Ȯ���ϱ� ����
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// IDXGIAdapter ������ �׷���ī��� ���� ����Ǵ� �������̽��̴�.
	// GetHighPerformanceAdapter()�� �ڽ��� ��ǻ�Ϳ��� ���� ���� �׷���ī�� ���� �����´�.
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("�׷���ī�� ��ġ ��� �������̽��� �����µ� �����߽��ϴ�.");
		return;
	}

	HRESULT Result = D3D11CreateDevice(
		Adapter,                                     // �׷���ī�� ����, �ش� ��ġ�� ���� �����޶�.
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,    // UNKNOWN�� �־ �������. ����͸� �ȳ־��൵(null �Է�) �Լ� ���ο��� �˾Ƽ� ã�Ƴ� �� ������ش�.
		nullptr,                                     // Adapter�� ���Ա� ������ 0�� �ְų� null�� �־��� �� �ִµ�, �̸� ������ �Լ� �ȿ��� �˾Ƽ� �ش޶�� ���̴�.
		iFlag,                                       // ������ ����� ����� �� iFlag�� ����� ���� �Ҵ��ߴµ�, �̴� ����� ����� ����׷� �׷��޶�� ���� �ȴ�.
		nullptr,                                     // FeatureLevel�� �������� ���̴�. null�� ������ ��� ���ҽ��� ��������� ���̴�.
		0,                                           // 0�� ������ �Լ� ���ο��� �˾Ƽ� ���ش�.
		D3D11_SDK_VERSION,                           // Direct�� SDK ������ �����ϴµ�, D3D11_SDK_VERSION�� ������ �����찡 �����ϴ� SDK(Software Development Kit; lib, header�����̺귯��) ������ defined �ȴ�.
		&Device,                                     // �� ����̽��� �� �־���
		&Level,                                      // ���ʿ� 11�̱� ������ �ȳ־ 11�� �ȴ�.
		&Context                                     // �� ���ؽ�Ʈ�� �� �־���
	);

	// 7, 8, 9���� �����ߴٸ�, ���ο��� �����Ҵ��� �߻��� ���̴�.
	// ������ ������ ���� �ڽ��� ��������� Ȯ���� �� �ֵ��� �Ѵ�.
	// (23.04.06) GECore�� Start()�� End() �п��� ȣ��������

	// 2�� ���� +) Adapter�� �� �� D3D_DRIVER_TYPE_SOFTWARE�� D3D_DRIVER_TYPE_HARDWARE�� ������.
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_SOFTWARE == CPU�� �׷���
	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE == GPU�� �׷���

	if (S_OK != Result)
	{
		MsgAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	// Adapter ������ �����ٸ� ������
	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	// ���������� ������ Direct�� ������ 11�� �ƴ϶�� ��� (���� 11 ���� ���ϴ� �׷���ī����... ���һ�)
	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		MsgAssert("���̷�Ʈ 11�� �������� �ʴ� �׷���ī�� �Դϴ�");
		return;
	}

	// ���̷�Ʈ x���� ��Ƽ������ ���� 
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	// ����ü�� == ������(â)������ BackBuffer�� ���� ����
	// ������(â)�� �����ϴ� �۾��� �ǽ��ϴ� ���̴�.
	CreateSwapChain();
}

// ������ ���� (End���� ȣ��)
void GameEngineDevice::Release()
{
	BackBufferTarget = nullptr;

	if (nullptr != SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}
}