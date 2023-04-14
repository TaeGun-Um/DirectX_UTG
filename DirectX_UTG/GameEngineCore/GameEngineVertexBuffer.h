#pragma once
#include "GameEngineResource.h"
#include "GameEngineVertex.h"
#include "GameEngineDirectBuffer.h"

// ���� : GameEngineDirectBuffer�� ��ӹ޾ұ� ������ ID3D11Buffer, D3D11_BUFFER_DESC�� Ȱ���� �� �ִ�.
//        ���������������� �ܰ迡�� InputAssembler1 �ܰ踦 ����ϴ� Ŭ����
class GameEngineVertexBuffer : public GameEngineResource<GameEngineVertexBuffer>, public GameEngineDirectBuffer
{
	friend class GameEngineInputLayOut;

public:
	// constrcuter destructer
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer();

	// delete Function
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&& _Other) noexcept = delete;

	// ���ҽ��� Vertex�� �����Ͽ� �߰��Ѵ�.
	template<typename VertexType>
	static void Create(const std::string_view& _Name, const std::vector<VertexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineVertexBuffer> Res = GameEngineResource::Create(_Name);
		// ������ ���ÿ� GameEngineInputLayOutInfo�� ���ϵ��� �Ѵ�.
		Res->LayOutInfo = &VertexType::LayOut;
		Res->ResCreate(&_Vertexs[0], sizeof(VertexType), static_cast<UINT>(_Vertexs.size()));
	}

	void Setting() override;

protected:

private:
	GameEngineInputLayOutInfo* LayOutInfo = nullptr;

	// GEVertex�� Vertex �������, ���� Create, ������Ʈ
	void ResCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount);

	UINT Offset = 0;
	UINT VertexSize = 0;
	UINT VertexCount = 0;
};

