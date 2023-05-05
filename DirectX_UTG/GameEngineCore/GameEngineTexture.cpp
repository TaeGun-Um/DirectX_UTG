#include "PrecompileHeader.h"
#include "GameEngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Release\\DirectXTex.lib")
#endif

GameEnginePixelColor GameEnginePixelColor::Black = { 0, 0, 0, 0 };

GameEngineTexture::GameEngineTexture()
{
}

// Texture와 RenderTarget은 동적할당이기 때문에, 소멸자 호출 시 Release를 실시해야 한다.
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

// HDC를 Texture2D에 할당 후 CreateRenderTargetView() 호출
void GameEngineTexture::ResCreate(ID3D11Texture2D* _Create)
{
	Texture2D = _Create;
	Texture2D->GetDesc(&Desc);
	CreateRenderTargetView();
}

// Texture(HDC)를 통해 RenderTarget을 만듬
void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처가 존재하지 않는 랜더타겟뷰을 만들 수는 없습니다.");
		return;
	}

	// RenderTarget은 여러 개 만들 수 있다.
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgAssert("랜더타겟뷰 생성에 실패했습니다.");
		return;
	}
}

void GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처가 존재하지 않는데 뎁스 스텐실 뷰 만들 수는 없습니다.");
		return;
	}

	HRESULT Result = GameEngineDevice::GetDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);
	// 1번 : 구조체
	// 2번 : 텍스쳐 만들 때 특별히 넣어줄 것이 있는가? 없으니 null
	// 3번 : 정보를 받을 구조체, ID3D11DepthStencilView

	if (S_OK != Result)
	{
		MsgAssert("뎁스 스텐실 뷰 생성에 실패했습니다.");
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

	// 텍스쳐 너비와 높이 멤버변수에 저장
	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);
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
		MsgAssert("텍스처 생성에 실패했습니다.");
	}
}

// 바깥에 나갔다면 무슨색깔 리턴할지에 대한 컬러도 넣어줘야 한다.
GameEnginePixelColor GameEngineTexture::GetPixel(int _X, int _Y, GameEnginePixelColor DefaultColor)
{
	if (0 > _X)
	{
		return DefaultColor;
	}

	if (0 > _Y)
	{
		return DefaultColor;
	}

	if (_X >= GetWidth())
	{
		return DefaultColor;
	}

	if (_Y >= GetHeight())
	{
		return DefaultColor;
	}

	DXGI_FORMAT Fmt = Image.GetMetadata().format;

	// Image.GetImages()->pixels;

	unsigned char* ColorPtr = Image.GetPixels();

	switch (Fmt)
	{
	case DXGI_FORMAT_UNKNOWN:
		break;
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32B32A32_UINT:
		break;
	case DXGI_FORMAT_R32G32B32A32_SINT:
		break;
	case DXGI_FORMAT_R32G32B32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32B32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32B32_UINT:
		break;
	case DXGI_FORMAT_R32G32B32_SINT:
		break;
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
		break;
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
		break;
	case DXGI_FORMAT_R16G16B16A16_UNORM:
		break;
	case DXGI_FORMAT_R16G16B16A16_UINT:
		break;
	case DXGI_FORMAT_R16G16B16A16_SNORM:
		break;
	case DXGI_FORMAT_R16G16B16A16_SINT:
		break;
	case DXGI_FORMAT_R32G32_TYPELESS:
		break;
	case DXGI_FORMAT_R32G32_FLOAT:
		break;
	case DXGI_FORMAT_R32G32_UINT:
		break;
	case DXGI_FORMAT_R32G32_SINT:
		break;
	case DXGI_FORMAT_R32G8X24_TYPELESS:
		break;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		break;
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
		break;
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
		break;
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
		break;
	case DXGI_FORMAT_R10G10B10A2_UNORM:
		break;
	case DXGI_FORMAT_R10G10B10A2_UINT:
		break;
	case DXGI_FORMAT_R11G11B10_FLOAT:
		break;
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
		break;
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		break;
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_R8G8B8A8_UINT:
		break;
	case DXGI_FORMAT_R8G8B8A8_SNORM:
		break;
	case DXGI_FORMAT_R8G8B8A8_SINT:
		break;
	case DXGI_FORMAT_R16G16_TYPELESS:
		break;
	case DXGI_FORMAT_R16G16_FLOAT:
		break;
	case DXGI_FORMAT_R16G16_UNORM:
		break;
	case DXGI_FORMAT_R16G16_UINT:
		break;
	case DXGI_FORMAT_R16G16_SNORM:
		break;
	case DXGI_FORMAT_R16G16_SINT:
		break;
	case DXGI_FORMAT_R32_TYPELESS:
		break;
	case DXGI_FORMAT_D32_FLOAT:
		break;
	case DXGI_FORMAT_R32_FLOAT:
		break;
	case DXGI_FORMAT_R32_UINT:
		break;
	case DXGI_FORMAT_R32_SINT:
		break;
	case DXGI_FORMAT_R24G8_TYPELESS:
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
		break;
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
		break;
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
		break;
	case DXGI_FORMAT_R8G8_TYPELESS:
		break;
	case DXGI_FORMAT_R8G8_UNORM:
		break;
	case DXGI_FORMAT_R8G8_UINT:
		break;
	case DXGI_FORMAT_R8G8_SNORM:
		break;
	case DXGI_FORMAT_R8G8_SINT:
		break;
	case DXGI_FORMAT_R16_TYPELESS:
		break;
	case DXGI_FORMAT_R16_FLOAT:
		break;
	case DXGI_FORMAT_D16_UNORM:
		break;
	case DXGI_FORMAT_R16_UNORM:
		break;
	case DXGI_FORMAT_R16_UINT:
		break;
	case DXGI_FORMAT_R16_SNORM:
		break;
	case DXGI_FORMAT_R16_SINT:
		break;
	case DXGI_FORMAT_R8_TYPELESS:
		break;
	case DXGI_FORMAT_R8_UNORM:
		break;
	case DXGI_FORMAT_R8_UINT:
		break;
	case DXGI_FORMAT_R8_SNORM:
		break;
	case DXGI_FORMAT_R8_SINT:
		break;
	case DXGI_FORMAT_A8_UNORM:
		break;
	case DXGI_FORMAT_R1_UNORM:
		break;
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
		break;
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
		break;
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
		break;
	case DXGI_FORMAT_BC1_TYPELESS:
		break;
	case DXGI_FORMAT_BC1_UNORM:
		break;
	case DXGI_FORMAT_BC1_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC2_TYPELESS:
		break;
	case DXGI_FORMAT_BC2_UNORM:
		break;
	case DXGI_FORMAT_BC2_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC3_TYPELESS:
		break;
	case DXGI_FORMAT_BC3_UNORM:
		break;
	case DXGI_FORMAT_BC3_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC4_TYPELESS:
		break;
	case DXGI_FORMAT_BC4_UNORM:
		break;
	case DXGI_FORMAT_BC4_SNORM:
		break;
	case DXGI_FORMAT_BC5_TYPELESS:
		break;
	case DXGI_FORMAT_BC5_UNORM:
		break;
	case DXGI_FORMAT_BC5_SNORM:
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		break;
	case DXGI_FORMAT_B5G5R5A1_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	{
		int Index = _Y * static_cast<int>(GetWidth()) + _X;
		ColorPtr = ColorPtr + (Index * 4);
		GameEnginePixelColor Return;
		Return.r = ColorPtr[2];
		Return.g = ColorPtr[1];
		Return.b = ColorPtr[0];
		Return.a = ColorPtr[3];
		return Return;
	}
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM:
	{
		int Index = _Y * static_cast<int>(GetWidth()) + _X;
		ColorPtr = ColorPtr + (Index * 4);
		GameEnginePixelColor Return;
		Return.r = ColorPtr[2];
		Return.g = ColorPtr[1];
		Return.b = ColorPtr[0];
		Return.a = ColorPtr[3];
		return Return;
	}
		break;
	case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
		break;
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	{
		// 컬러1개에 4바이트인 100 * 100
		// 10, 10
		int Index = _Y * static_cast<int>(GetWidth()) + _X;
		ColorPtr = ColorPtr + (Index * 4);
		GameEnginePixelColor Return;
		Return.r = ColorPtr[2];
		Return.g = ColorPtr[1];
		Return.b = ColorPtr[0];
		Return.a = ColorPtr[3];
		return Return;
	}
	case DXGI_FORMAT_B8G8R8X8_TYPELESS:
		break;
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
		break;
	case DXGI_FORMAT_BC6H_TYPELESS:
		break;
	case DXGI_FORMAT_BC6H_UF16:
		break;
	case DXGI_FORMAT_BC6H_SF16:
		break;
	case DXGI_FORMAT_BC7_TYPELESS:
		break;
	case DXGI_FORMAT_BC7_UNORM:
		break;
	case DXGI_FORMAT_BC7_UNORM_SRGB:
		break;
	case DXGI_FORMAT_AYUV:
		break;
	case DXGI_FORMAT_Y410:
		break;
	case DXGI_FORMAT_Y416:
		break;
	case DXGI_FORMAT_NV12:
		break;
	case DXGI_FORMAT_P010:
		break;
	case DXGI_FORMAT_P016:
		break;
	case DXGI_FORMAT_420_OPAQUE:
		break;
	case DXGI_FORMAT_YUY2:
		break;
	case DXGI_FORMAT_Y210:
		break;
	case DXGI_FORMAT_Y216:
		break;
	case DXGI_FORMAT_NV11:
		break;
	case DXGI_FORMAT_AI44:
		break;
	case DXGI_FORMAT_IA44:
		break;
	case DXGI_FORMAT_P8:
		break;
	case DXGI_FORMAT_A8P8:
		break;
	case DXGI_FORMAT_B4G4R4A4_UNORM:
		break;
	case DXGI_FORMAT_P208:
		break;
	case DXGI_FORMAT_V208:
		break;
	case DXGI_FORMAT_V408:
		break;
	case DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE:
		break;
	case DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE:
		break;
	case DXGI_FORMAT_FORCE_UINT:
		break;
	default:
		break;
	}

	return DefaultColor;
}