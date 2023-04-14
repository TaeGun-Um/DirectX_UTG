#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 인풋레이아웃 낫셋오류를 해결하기 위한 Vertex LayOut 생성, Vertex의 구성이 어떻게 되어 있는지를 쉐이더의 시멘틱쪽에 다 알려줘야 한다.
// 인풋 레이아웃은 랜더링 파이프라인에서 세팅되는 쉐이더마다 달라질 수 있다.
// 우리의 엔진 구조는 인풋레이아웃 자체를 GameEngineRenderingPipeLine 에서 만드는 구조로 구성
class GameEngineInputLayOutInfo
{
public:
	static UINT FormatSize(DXGI_FORMAT _Format);

	inline const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetDescs()
	{
		return Descs;
	}

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;  // LayOut 구조체
	int Offset = 0;

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

// 설명 :
class GameEngineVertex
{
public:
	static GameEngineInputLayOutInfo LayOut;

public:
	float4 POSITION;
	float4 COLOR;
};