#pragma once
#include <GameEngineBase/GameEngineMath.h>

// ��ǲ���̾ƿ� ���¿����� �ذ��ϱ� ���� Vertex LayOut ����, Vertex�� ������ ��� �Ǿ� �ִ����� ���̴��� �ø�ƽ�ʿ� �� �˷���� �Ѵ�.
class GameEngineInputLayOut
{
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;  // LayOut ����ü

public:
	void AddInputLayOut(
		LPCSTR SemanticName,
		DXGI_FORMAT Format,
		D3D11_INPUT_CLASSIFICATION InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
		UINT InstanceDataStepRate = 0,
		UINT AlignedByteOffset = -1,
		UINT InputSlot = 0,
		UINT SemanticIndex = 0
	);
};

// ���� :
class GameEngineVertex
{
public:
	static GameEngineInputLayOut LayOut;

public:
	float4 POSITION;
	float4 COLOR;
};