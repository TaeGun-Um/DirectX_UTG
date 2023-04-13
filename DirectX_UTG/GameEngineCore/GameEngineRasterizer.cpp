#include "PrecompileHeader.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer()
{
}

GameEngineRasterizer::~GameEngineRasterizer()
{
	Release();
}

void GameEngineRasterizer::Release()
{
	if (nullptr != SolidState)
	{
		SolidState->Release();
		SolidState = nullptr;
	}

	if (nullptr != WireframeState)
	{
		WireframeState->Release();
		WireframeState = nullptr;
	}
}

void GameEngineRasterizer::Setting()
{
	if (nullptr == CurState)
	{
		MsgAssert("�������� ���� �����Ͷ����� ������Ʈ �Դϴ�.");
	}

	GameEngineDevice::GetContext()->RSSetState(CurState);
	// ���� ����� State�� �����Ͷ����� RSSetState() �ǽ�
}

// GameEngineCore_Resources �� Desc Ȯ��
void GameEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Value)
{
	Release();     // ���⿡ ����� �־ �ǹ��� �� �ְ�����, ResCreate()�� ��ȣ��Ǹ� �� ����� �ٽ� ����� ������ �ص� ������� ����
	               // �׷��� �ص� ������ ������ ������ ���̴�. �׸��� ���� ���߿� ȣ��� �������̽��� �ƴϱ� ������ ������ ��.
	               // ����� �����̶� ������.

	Desc = _Value;

	// �츮�� ���� ������ FILLMode�� �� �� ����� ������, ���⼭ �� �� CreateRasterizerState()�� �ǽ��Ѵ�.
	// CreateRasterizerState(���̾�������)
	Desc.FillMode = D3D11_FILL_WIREFRAME; 
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc, &WireframeState))
	{
		MsgAssert("���̾� ������ �����Ͷ����� ������Ʈ ������ �����߽��ϴ�.");
	}

	// CreateRasterizerState(�ָ���)
	Desc.FillMode = D3D11_FILL_SOLID;
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc, &SolidState))
	{
		MsgAssert("�ָ��� �����Ͷ����� ������Ʈ ������ �����߽��ϴ�.");
	}

	// �� �� ���������, �⺻�� �ָ���� ����
	SetFILL_MODE(D3D11_FILL_SOLID);
}
