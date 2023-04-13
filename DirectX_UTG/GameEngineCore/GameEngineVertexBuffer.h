#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// 설명 : GameEngineDirectBuffer를 상속받았기 때문에 ID3D11Buffer, D3D11_BUFFER_DESC를 활용할 수 있다.
//        랜더링파이프라인 단계에서 InputAssembler1 단계를 담당하는 클래스
class GameEngineVertexBuffer : public GameEngineResource<GameEngineVertexBuffer>, public GameEngineDirectBuffer
{
public:
	// constrcuter destructer
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer();

	// delete Function
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&& _Other) noexcept = delete;

	// 리소스에 Vertex를 생성하여 추가한다.
	template<typename VertexType>
	static void Create(const std::string_view& _Name, const std::vector<VertexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineVertexBuffer> Res = GameEngineResource::Create(_Name);

		Res->ResCreate(&_Vertexs[0], sizeof(VertexType), static_cast<UINT>(_Vertexs.size()));
	}

	void Setting() override;

protected:

private:
	// GEVertex의 Vertex 기반으로, 정보 Create, 업데이트
	void ResCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount);

	UINT Offset;
	UINT VertexSize;
	UINT VertexCount;
};

