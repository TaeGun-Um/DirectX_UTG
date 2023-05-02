#pragma once

#include <memory>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// 설명 : 현재(2023) 게임 시장은 DirectX11이 잡고 있다. 언리얼과 유니티도 내부에서는 DirectX를 활용함(안드로이드는 OpenGL)
//        DirectX9에서는 하나의 인터페이스(Id3D9Device)로 텍스쳐로드와 계산, 드로우 등을 실시했지만
//        DirctX11부터는 인터페이스가 ID3D11Device와 ID3D11DeviceContext로 분리됐다.
class GameEngineDevice
{
public:
	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

	// 디바이스 이니셜라이즈 (로드)
	static void Initialize();

	// 윈도우(창)과 생성된 Direct를 연결하는 과정
	static void CreateSwapChain();

	// 릴리즈 구조(알아서 되지만 명시적 확인을 위해 직접 호출)
	static void Release();

	static void RenderStart();

	static void RenderEnd();

	// 비디오용
	static void VidioRenderStart();

	// 비디오용
	static void VidioRenderEnd();

	static ID3D11Device* GetDevice()
	{
		return Device;
	}

	static ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

protected:

private:
	// 리소스는 Device가 로드해준다. 그래픽카드의 VRAM에 대한 권한 담당
	// 텍스쳐를 만들면 VRAM에 저장된다. 당연히 CPU에 저장할 수 있지만 GPU를 활용하는 데는 이유가 있다.
	// CPU와 GPU는 모두 연산 장치와 RAM을 가지고 있기 때문에 그림을 그릴 순 있지만 CPU는 순차 처리로 그림을 그리기도 하고, 그림 작업 이외에 할 일이 너무 많다.
	// GPU는 오직 그림을 그리기를 위한 연산만을 수행하기 위해 만들어진 연산 장치와 RAM을 가진다.
	// 픽셀의 병렬 연산만을 위한 전용 칩셋이라고 보면 됨 -> 2차원 배열(숫자) 연산이 굉장히 빠르다.
	// GPU는 하드웨어와 연결되어 있으며 이걸 사용하기 위해서는 Com 객체가 필요하다. Direct의 Device가 이 역할을 수행해준다.
	static ID3D11Device* Device;

	// 랜더링과 관련된 연산은 ID3D11DeviceContext가 담당한다.
	// 11부터는 DrawMesh를 컨텍스트가, TextureLoad를 Device가 담당한다.
	static ID3D11DeviceContext* Context;

	// 디바이스와 컨텍스트의 하위
	// 윈도우(창)처럼 설정만 한다면 Direct도 여러 개 띄울 수 있다.
	// 윈도우(창) 기준으로 본다면 스왑체인은 BackBuffer이다.
	static IDXGISwapChain* SwapChain;

	// 그래픽카드 Adapter를 얻어옴
	static IDXGIAdapter* GetHighPerformanceAdapter();

	static std::shared_ptr<class GameEngineRenderTarget> BackBufferTarget;

	// constrcuter destructer
	GameEngineDevice();
	~GameEngineDevice();
};

// GPU의 연산 능력
// 만약 MSAAX8 알고리즘을 활용할 경우, 픽셀 내부에는 8개의 점이 존재하게 된다.
// 그렇다면 1280x720의 화면에서 픽셀 하나 당 8개의 점이 존재한다면
// 초당 1280 * 720 * 8 = 7,200,000 회의 연산을 실시하는 것이다. 이게 순식간에 가능함

// +) FXAA 알고리즘은 엔비디아에서 만든 안티얼라이어싱 알고리즘입니다.