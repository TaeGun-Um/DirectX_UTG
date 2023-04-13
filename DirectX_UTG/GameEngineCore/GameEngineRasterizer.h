#pragma once
#include "GameEngineResource.h"

// ���� : ������ ���������� �ܰ迡�� Resterizer �ܰ踦 ����ϴ� Ŭ����
class GameEngineRasterizer : public GameEngineResource<GameEngineRasterizer>
{
public:
	// constrcuter destructer
	GameEngineRasterizer();
	~GameEngineRasterizer();

	// delete Function
	GameEngineRasterizer(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer(GameEngineRasterizer&& _Other) noexcept = delete;
	GameEngineRasterizer& operator=(const GameEngineRasterizer& _Other) = delete;
	GameEngineRasterizer& operator=(GameEngineRasterizer&& _Other) noexcept = delete;

	// �����Ͷ������� Create�� �� ���ҽ��� Ǫ����
	static std::shared_ptr<GameEngineRasterizer> Create(const std::string_view& _Name, const D3D11_RASTERIZER_DESC& _Desc)
	{
		std::shared_ptr<GameEngineRasterizer> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting() override;

	// ResCreate()���� �ΰ� �� ���������, �⺻�� �ϴ� �ָ���� ����. ���߿� �ٲٰ������ ȣ���ϸ� �ȴ�.
	inline void SetFILL_MODE(D3D11_FILL_MODE _Value)
	{
		switch (_Value)
		{
		case D3D11_FILL_WIREFRAME:
			CurState = WireframeState;
			break;
		case D3D11_FILL_SOLID:
			CurState = SolidState;
			break;
		default:
			break;
		}
	}

	// �����Ͷ������� CULL�� ���ϴ� ��. Cull�� ����Ǹ� �ٽ� ����� �������̽�(ResCreate(Desc))
	inline void SetCULL_MODE(D3D11_CULL_MODE _Value)
	{
		Desc.CullMode = _Value;
		ResCreate(Desc);
	}

protected:
	void ResCreate(const D3D11_RASTERIZER_DESC& _Value);

private:
	D3D11_RASTERIZER_DESC Desc = {};                  // �����͸����� ��û���� ������ DESC ����
	ID3D11RasterizerState* CurState = nullptr;        // ������� �ܰ�� ���� State�� �Ѱܴ޶�� ��û�Ѵ�. ������ State
	ID3D11RasterizerState* SolidState = nullptr;      // FILL�� �ָ��� State, �� �� ������ ������ �� �� ���� ���̱� ����
	ID3D11RasterizerState* WireframeState = nullptr;  // FILL�� ���̾������� State, �� �� ������ ������ �� �� ���� ���̱� ����

	void Release();

};

