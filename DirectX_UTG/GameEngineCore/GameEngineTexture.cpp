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

// Texture와 RenderTarget은 동적할당이기 때문에, 소멸자 호출 시 Release를 실시해야 한다.
GameEngineTexture::~GameEngineTexture()
{
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

// HDC를 Texture2D에 할당 후 CreateRenderTargetView() 호출
void GameEngineTexture::ResCreate(ID3D11Texture2D* _Create)
{
	Texture2D = _Create;
	CreateRenderTargetView();
}

// Texture(HDC)를 통해 RenderTarget을 만듬
void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처가 존재하지 않는 랜더타겟을 만들 수는 없습니다.");
		return;
	}

	// RenderTarget은 여러 개 만들 수 있다.
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgAssert("랜더타겟 생성에 실패했습니다.");
		return;
	}
}

// 경로를 받은 뒤 리소스를 로드한다.
void GameEngineTexture::ResLoad(const std::string_view& _Path)
{
	GameEnginePath NewPath(_Path);

	std::string Ext = GameEngineString::ToUpper(NewPath.GetExtension());

	// LoadFromWICFile의 1번 인자가 wchar라서 해당 함수 호출로 변환
	std::wstring Path = GameEngineString::AnsiToUniCode(NewPath.GetFullPath());

	if (Ext == ".TGA")
	{
		MsgAssert("아직 로드할 수 없는 포맷입니다." + std::string(_Path.data()));
	}
	else if (Ext == ".DDS")
	{
		MsgAssert("아직 로드할 수 없는 포맷입니다." + std::string(_Path.data()));
	}
	else if (S_OK != DirectX::LoadFromWICFile(Path.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}
	// 1번 인자 : wchar로 변환 후 전달
	// 2번 인자 : 알아서 해줘
	// 3번 인자 : 텍스쳐 정보를 전달
	// 4번 인자 : 로드된 정보를 여기 담는다.

	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineDevice::GetDevice(), // 1. 디바이스 전달
		Image.GetImages(),             // 2. 넣을 이미지
		Image.GetImageCount(),         // 3. 이미지는 여러개 겹쳐서 넣을 수 있다. 그것의 수(Count)
		Image.GetMetadata(),           // 4. 메타 데이터
		&SRV)                          // 5. ID3D11ShaderResourceView로 정보 전달받음
	)
	{
		MsgAssert("쉐이더 리소스 뷰 생성에 실패했습니다." + std::string(_Path.data()));
	}

}

// CreateShaderResourceView()로 SRV에 값을 전달받은 후, 해당 값으로 VSSetShaderResources(), PSSetShaderResources() 실시
void GameEngineTexture::VSSetting(UINT _Slot)
{
	// 0번 슬롯에 SRV로 넣겠다.
	GameEngineDevice::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	// 0번 슬롯에 SRV로 넣겠다.
	GameEngineDevice::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}
