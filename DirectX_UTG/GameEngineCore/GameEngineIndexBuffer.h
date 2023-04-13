#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// ���� : ���������������� �ܰ迡�� InputAssembler2 �ܰ踦 ����ϴ� Ŭ����, Index�� int�� �����̴�(���� ������ int�� ����).
class GameEngineIndexBuffer : public GameEngineResource<GameEngineIndexBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();

	// delete Function
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _Other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer& operator=(GameEngineIndexBuffer&& _Other) noexcept = delete;

	// ������ �մ� ������ �����Ͽ� ���ҽ��� �߰�
	template<typename IndexType>
	static void Create(const std::string_view& _Name, const std::vector<IndexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineIndexBuffer> Res = GameEngineResource::Create(_Name);

		Res->ResCreate(&_Vertexs[0], sizeof(IndexType), static_cast<UINT>(_Vertexs.size()));
	}

	void Setting() override;

	// IndexCount �������� (Draw���� ���)
	inline UINT GetIndexCount()
	{
		return IndexCount;
	}

protected:

private:
	// ID3D11Buffer* Buffer = nullptr;         // ��� Buffer �迭�� ID3D11Buffer�� ��� ������ ������ �ִ�. << ��ӹ���
	// D3D11_BUFFER_DESC BufferInfo = { 0, };  // �׸��� D3D11_BUFFER_DESC�� ������ �޾Ƽ� Ȱ���Ѵ�.         << ��ӹ���

	void ResCreate(const void* _Data, UINT _IndexSize, UINT _IndexCount);

	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;

	UINT Offset = 0;
	UINT IndexSize = 0;   // ������ ũ��
	UINT IndexCount = 0;  // ������ ����
	UINT VertexCount = 0;
};

