#pragma once

#include "GameEngineResource.h"
#include <GameEngineCore/ThirdParty/DirectXTex/inc/DirectXTex.h>

// ���� : WinAPI���� GameEngineImage�� ������ ���� (�̸��� GameEngineTexture�� ��)
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

	// ��θ� ã�Ƽ� �ε�(�ؿ� �Լ��� �̵�)
	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path)
	{
		GameEnginePath NewPath(_Path);
		return Load(_Path, NewPath.GetFileName());
	}

	// �ε��� ���ҽ�(�̹���)�� �����ϰ� ResLoad(���) �ǽ�
	static std::shared_ptr<GameEngineTexture> Load(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::Create(_Name);
		NewTexture->ResLoad(_Path);
		return NewTexture;
	}

	// Resource�� Texture �߰�
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

	// (0426) ���̹��� �ؽ��� ����
	static std::shared_ptr<GameEngineTexture> Create(const D3D11_TEXTURE2D_DESC& _Value)
	{
		std::shared_ptr<GameEngineTexture> NewTexture = GameEngineResource::CreateUnNamed();
		NewTexture->ResCreate(_Value);
		return NewTexture;
	}

	// RenderTarget ��������
	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	// ���̹��� �ؽ��� ��������
	ID3D11DepthStencilView* GetDSV()
	{
		return DSV;
	}

	// D3D11_TEXTURE2D_DESC�� �ʺ� ��������
	unsigned int GetWidth()
	{
		return Desc.Width;
	}

	// D3D11_TEXTURE2D_DESC�� ���� ��������
	unsigned int GetHeight()
	{
		return Desc.Height;
	}

protected:

private:
	
	ID3D11Texture2D* Texture2D = nullptr;    // HDC
	ID3D11RenderTargetView* RTV = nullptr;   // BackBuffer
	ID3D11ShaderResourceView* SRV = nullptr; // ���̴����ҽ���
	ID3D11DepthStencilView* DSV = nullptr;   // �𽺽��ĽǺ�

	D3D11_TEXTURE2D_DESC Desc;               // �ؽ��� ����ü
	DirectX::TexMetadata Data;               // LoadFromWICFile()�� �ؽ��� ���� ���� ��
	DirectX::ScratchImage Image;             // LoadFromWICFile() �� �ε�� ������ ���� ���

	// HDC�� Texture2D�� �Ҵ� �� CreateRenderTargetView() ȣ��
	void ResCreate(ID3D11Texture2D* _Value);
	void ResCreate(const D3D11_TEXTURE2D_DESC& _Value);

	// ��θ� ���� �� ���ҽ��� �ε��Ѵ�.
	void ResLoad(const std::string_view& _Path);

	void CreateRenderTargetView();
	void CreateDepthStencilView();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};

