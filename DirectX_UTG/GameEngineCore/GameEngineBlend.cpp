#include "PrecompileHeader.h"
#include "GameEngineBlend.h"

GameEngineBlend::GameEngineBlend()
{
}

GameEngineBlend::~GameEngineBlend()
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

void GameEngineBlend::Setting()
{
	if (nullptr == State)
	{
		MsgAssert("�������� ���� �����Ͷ����� ������Ʈ �Դϴ�.");
	}

	if (Desc.RenderTarget[0].SrcBlend == D3D11_BLEND_BLEND_FACTOR)
	{
		MsgAssert("���� ó�� ���� �ʴ� ���� ����Դϴ� ���� ���� �Է±���� ����� �ּ���.");
	}

	GameEngineDevice::GetContext()->OMSetBlendState(State, nullptr, Mask);
	// 1�� : ���� ����ũ
	// 2�� : ���͸� ���Ƿ� ������ �� �ִ�. 0.5f, 0.5f, 0.5f�� �ְ� �ʹٸ� �׷��� �� �� ����, ������ ���� �ÿ� ���� ó���� �� ���� ����̶�� assert�� (���߿� �սô�)
	// 3�� : 0xFFFFFFFF�� �� �ڸ��� ������, 1~2�� R, 3~4�� G, 5~6�� B, 7~8�� ���Ĵ�. Ư�� �ڸ����� 00�� ������ �ش� ���� �������� ����� ��. ������ ��� FFFFFFFF�� ������ ����
}

void GameEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Value)
{
	Desc = _Value;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBlendState(&Desc, &State))
	{
		MsgAssert("���� ������Ʈ ������ �����߽��ϴ�.");
	}
}