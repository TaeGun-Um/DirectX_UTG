#pragma once
#include "GameEngineResource.h"

// ID3D11Buffer 
// 
// � �����Ϳ� ���� ��� ������ �ֱ� ���� ���̴�.
// DirectX�� ���⿣ VRAM�� �� ����Ʈ�� ������ ������ָ� �Ǵ°���? ��� �ϴ� ��
// �ش� ������ ��� ����� ���� ����ڰ� ��������� �Ѵ�. ==> D3D11_BUFFER_DESC�� Ȱ��

// ���� : DirectX���� ���� �׸��� ���� �ν��Ͻ� ���ۿ� Ŭ����
class GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineDirectBuffer();
	~GameEngineDirectBuffer();

	// delete Function
	GameEngineDirectBuffer(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer(GameEngineDirectBuffer&& _Other) noexcept = delete;
	GameEngineDirectBuffer& operator=(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer& operator=(GameEngineDirectBuffer&& _Other) noexcept = delete;

protected:
	ID3D11Buffer* Buffer = nullptr;         // ��� Buffer �迭�� ID3D11Buffer�� ��� ������ ������ �ִ�.
	D3D11_BUFFER_DESC BufferInfo = { 0, };  // �׸��� D3D11_BUFFER_DESC�� ������ �޾Ƽ� Ȱ���Ѵ�.

private:
};

