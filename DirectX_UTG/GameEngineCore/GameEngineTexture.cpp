#include "PrecompileHeader.h"
#include "GameEngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Release\\DirectXTex.lib")
#endif

GameEngineTexture::GameEngineTexture()
{
}

// Texture�� RenderTarget�� �����Ҵ��̱� ������, �Ҹ��� ȣ�� �� Release�� �ǽ��ؾ� �Ѵ�.
GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != DSV)
	{
		DSV->Release();
		DSV = nullptr;
	}

	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

	if (nullptr != RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
		Texture2D = nullptr;
	}
}

// HDC�� Texture2D�� �Ҵ� �� CreateRenderTargetView() ȣ��
void GameEngineTexture::ResCreate(ID3D11Texture2D* _Create)
{
	Texture2D = _Create;
	Texture2D->GetDesc(&Desc);
	CreateRenderTargetView();
}

// Texture(HDC)�� ���� RenderTarget�� ����
void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("�ؽ�ó�� �������� �ʴ� ����Ÿ�ٺ��� ���� ���� �����ϴ�.");
		return;
	}

	// RenderTarget�� ���� �� ���� �� �ִ�.
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgAssert("����Ÿ�ٺ� ������ �����߽��ϴ�.");
		return;
	}
}

void GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("�ؽ�ó�� �������� �ʴµ� ���� ���ٽ� �� ���� ���� �����ϴ�.");
		return;
	}

	HRESULT Result = GameEngineDevice::GetDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);
	// 1�� : ����ü
	// 2�� : �ؽ��� ���� �� Ư���� �־��� ���� �ִ°�? ������ null
	// 3�� : ������ ���� ����ü, ID3D11DepthStencilView

	if (S_OK != Result)
	{
		MsgAssert("���� ���ٽ� �� ������ �����߽��ϴ�.");
		return;
	}
}

// ��θ� ���� �� ���ҽ��� �ε��Ѵ�.
void GameEngineTexture::ResLoad(const std::string_view& _Path)
{
	GameEnginePath NewPath(_Path);

	std::string Ext = GameEngineString::ToUpper(NewPath.GetExtension());

	// LoadFromWICFile�� 1�� ���ڰ� wchar�� �ش� �Լ� ȣ��� ��ȯ
	std::wstring Path = GameEngineString::AnsiToUniCode(NewPath.GetFullPath());

	if (Ext == ".TGA")
	{
		MsgAssert("���� �ε��� �� ���� �����Դϴ�." + std::string(_Path.data()));
	}
	else if (Ext == ".DDS")
	{
		MsgAssert("���� �ε��� �� ���� �����Դϴ�." + std::string(_Path.data()));
	}
	else if (S_OK != DirectX::LoadFromWICFile(Path.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgAssert("�ؽ�ó �ε忡 �����߽��ϴ�." + std::string(_Path.data()));
	}
	// 1�� ���� : wchar�� ��ȯ �� ����
	// 2�� ���� : �˾Ƽ� ����
	// 3�� ���� : �ؽ��� ������ ����
	// 4�� ���� : �ε�� ������ ���� ��´�.

	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineDevice::GetDevice(), // 1. ����̽� ����
		Image.GetImages(),             // 2. ���� �̹���
		Image.GetImageCount(),         // 3. �̹����� ������ ���ļ� ���� �� �ִ�. �װ��� ��(Count)
		Image.GetMetadata(),           // 4. ��Ÿ ������
		&SRV)                          // 5. ID3D11ShaderResourceView�� ���� ���޹���
	)
	{
		MsgAssert("���̴� ���ҽ� �� ������ �����߽��ϴ�." + std::string(_Path.data()));
	}

	// �ؽ��� �ʺ�� ���� ��������� ����
	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);
}

// CreateShaderResourceView()�� SRV�� ���� ���޹��� ��, �ش� ������ VSSetShaderResources(), PSSetShaderResources() �ǽ�
void GameEngineTexture::VSSetting(UINT _Slot)
{
	// 0�� ���Կ� SRV�� �ְڴ�.
	GameEngineDevice::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	// 0�� ���Կ� SRV�� �ְڴ�.
	GameEngineDevice::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Value)
{
	Desc = _Value;

	GameEngineDevice::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D);

	if (D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL == Desc.BindFlags)
	{
		CreateDepthStencilView();
	}

	if (nullptr == Texture2D)
	{
		MsgAssert("�ؽ�ó ������ �����߽��ϴ�.");
	}
}