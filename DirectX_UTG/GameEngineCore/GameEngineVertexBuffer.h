#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// 설명 : GameEngineDirectBuffer를 상속받았기 때문에 ID3D11Buffer, D3D11_BUFFER_DESC를 활용할 수 있다.
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

	template<typename VertexType>
	static void Create(const std::string_view& _Name, const std::vector<VertexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineVertexBuffer> Res = GameEngineResource::Create(_Name);

		Res->Create(&_Vertexs[0], sizeof(VertexType), static_cast<UINT>(_Vertexs.size()));
	}

	void Setting();

protected:

private:
	void Create(const void* _Data, UINT _VertexSize, UINT _VertexCount);

	UINT Offset;
	UINT VertexSize;
	UINT VertexCount;
};

