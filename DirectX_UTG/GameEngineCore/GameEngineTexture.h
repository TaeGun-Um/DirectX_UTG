#pragma once

#include "GameEngineResource.h"
#include <GameEngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>

// GetPixel용 클래스
class GameEnginePixelColor
{
public:
	static GameEnginePixelColor Black;

	union
	{
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		unsigned char ColorChar[4];
		int Color;
	};

	bool operator==(GameEnginePixelColor _Color)
	{
		return Color == _Color.Color;
	}

	float4 Tofloat4()
	{

	}

	GameEnginePixelColor()
	{

	}

	GameEnginePixelColor(char _r, char _g, char _b, char _a)
		: r(_r), g(_g), b(_b), a(_a)
	{

	}
};

// 설명 : WinAPI에서 GameEngineImage와 동일한 구조 (이름만 GameEngineTexture일 뿐)
class GameEngineTexture : public GameEngineResource<GameEngineTexture>
{
	friend GameEngineDevice;
	friend class GameEngineTextureSetter;

public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	// 경로를 찾아서 로드(밑에 함수로 이동)
	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path)
	{
		GameEnginePath NewPath(_Path);
		return Load(_Path, NewPath.GetFileName());
	}

	// 로드한 리소스(이미지)를 저장하고 ResLoad(경로) 실시
	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResLoad(_Path);
		return NewTexture;
	}

	// Resource에 Texture 추가
	static std::shared_ptr<GameEngineTexture> Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		return NewTexture;
	}

	static std::shared_ptr<GameEngineTexture> Create(const std::string_view& _Name, ID3D11Texture2D* _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResCreate(_Value);
		return NewTexture;
	}

	// (0426) 깊이버퍼 텍스쳐 생성
	static std::shared_ptr<GameEngineTexture> Create(const D3D11_TEXTURE2D_DESC& _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::CreateUnNamed();
		NewTexture->ResCreate(_Value);
		return NewTexture;
	}

	// ShaderResourceView 가져오기
	ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}

	// RenderTarget 가져오기
	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	// 깊이버퍼 텍스쳐 가져오기
	ID3D11DepthStencilView* GetDSV()
	{
		return DSV;
	}

	// D3D11_TEXTURE2D_DESC의 너비 가져오기
	int GetWidth()
	{
		return Desc.Width;
	}

	// D3D11_TEXTURE2D_DESC의 깊이 가져오기
	int GetHeight()
	{
		return Desc.Height;
	}

	// 픽셀 충돌용
	GameEnginePixelColor GetPixel(int _X, int _Y, GameEnginePixelColor DefaultColor = GameEnginePixelColor::Black);

protected:

private:
	
	ID3D11Texture2D* Texture2D = nullptr;    // HDC
	ID3D11RenderTargetView* RTV = nullptr;   // BackBuffer
	ID3D11ShaderResourceView* SRV = nullptr; // 쉐이더리소스뷰
	ID3D11DepthStencilView* DSV = nullptr;   // 댑스스탠실뷰

	D3D11_TEXTURE2D_DESC Desc;               // 텍스쳐 구조체
	DirectX::TexMetadata Data;               // LoadFromWICFile()에 텍스쳐 정보 담을 곳
	DirectX::ScratchImage Image;             // LoadFromWICFile() 후 로드된 정보가 여기 담김

	// HDC를 Texture2D에 할당 후 CreateRenderTargetView() 호출
	void ResCreate(ID3D11Texture2D* _Value);
	void ResCreate(const D3D11_TEXTURE2D_DESC& _Value);

	// 경로를 받은 뒤 리소스를 로드한다.
	void ResLoad(const std::string_view& _Path);

	void CreateRenderTargetView();
	void CreateDepthStencilView();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

