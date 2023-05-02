#pragma once

#include <memory>

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>

// ���� : ����(2023) ���� ������ DirectX11�� ��� �ִ�. �𸮾�� ����Ƽ�� ���ο����� DirectX�� Ȱ����(�ȵ���̵�� OpenGL)
//        DirectX9������ �ϳ��� �������̽�(Id3D9Device)�� �ؽ��ķε�� ���, ��ο� ���� �ǽ�������
//        DirctX11���ʹ� �������̽��� ID3D11Device�� ID3D11DeviceContext�� �и��ƴ�.
class GameEngineDevice
{
public:
	// delete Function
	GameEngineDevice(const GameEngineDevice& _Other) = delete;
	GameEngineDevice(GameEngineDevice&& _Other) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice& _Other) = delete;
	GameEngineDevice& operator=(GameEngineDevice&& _Other) noexcept = delete;

	// ����̽� �̴ϼȶ����� (�ε�)
	static void Initialize();

	// ������(â)�� ������ Direct�� �����ϴ� ����
	static void CreateSwapChain();

	// ������ ����(�˾Ƽ� ������ ����� Ȯ���� ���� ���� ȣ��)
	static void Release();

	static void RenderStart();

	static void RenderEnd();

	// ������
	static void VidioRenderStart();

	// ������
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
	// ���ҽ��� Device�� �ε����ش�. �׷���ī���� VRAM�� ���� ���� ���
	// �ؽ��ĸ� ����� VRAM�� ����ȴ�. �翬�� CPU�� ������ �� ������ GPU�� Ȱ���ϴ� ���� ������ �ִ�.
	// CPU�� GPU�� ��� ���� ��ġ�� RAM�� ������ �ֱ� ������ �׸��� �׸� �� ������ CPU�� ���� ó���� �׸��� �׸��⵵ �ϰ�, �׸� �۾� �̿ܿ� �� ���� �ʹ� ����.
	// GPU�� ���� �׸��� �׸��⸦ ���� ���길�� �����ϱ� ���� ������� ���� ��ġ�� RAM�� ������.
	// �ȼ��� ���� ���길�� ���� ���� Ĩ���̶�� ���� �� -> 2���� �迭(����) ������ ������ ������.
	// GPU�� �ϵ����� ����Ǿ� ������ �̰� ����ϱ� ���ؼ��� Com ��ü�� �ʿ��ϴ�. Direct�� Device�� �� ������ �������ش�.
	static ID3D11Device* Device;

	// �������� ���õ� ������ ID3D11DeviceContext�� ����Ѵ�.
	// 11���ʹ� DrawMesh�� ���ؽ�Ʈ��, TextureLoad�� Device�� ����Ѵ�.
	static ID3D11DeviceContext* Context;

	// ����̽��� ���ؽ�Ʈ�� ����
	// ������(â)ó�� ������ �Ѵٸ� Direct�� ���� �� ��� �� �ִ�.
	// ������(â) �������� ���ٸ� ����ü���� BackBuffer�̴�.
	static IDXGISwapChain* SwapChain;

	// �׷���ī�� Adapter�� ����
	static IDXGIAdapter* GetHighPerformanceAdapter();

	static std::shared_ptr<class GameEngineRenderTarget> BackBufferTarget;

	// constrcuter destructer
	GameEngineDevice();
	~GameEngineDevice();
};

// GPU�� ���� �ɷ�
// ���� MSAAX8 �˰����� Ȱ���� ���, �ȼ� ���ο��� 8���� ���� �����ϰ� �ȴ�.
// �׷��ٸ� 1280x720�� ȭ�鿡�� �ȼ� �ϳ� �� 8���� ���� �����Ѵٸ�
// �ʴ� 1280 * 720 * 8 = 7,200,000 ȸ�� ������ �ǽ��ϴ� ���̴�. �̰� ���İ��� ������

// +) FXAA �˰����� �����ƿ��� ���� ��Ƽ����̾�� �˰����Դϴ�.