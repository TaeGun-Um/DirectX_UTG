#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// 설명 : 랜더링파이프라인 단계에서 InputAssembler2 단계를 담당하는 클래스, Index는 int의 집합이다(순서 정보를 int로 담음).
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

	// 정점을 잇는 순서를 생성하여 리소스에 추가
	template<typename IndexType>
	static void Create(const std::string_view& _Name, const std::vector<IndexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineIndexBuffer> Res = GameEngineResource::Create(_Name);

		Res->ResCreate(&_Vertexs[0], sizeof(IndexType), static_cast<UINT>(_Vertexs.size()));
	}

	void Setting() override;

	// IndexCount 가져오기 (Draw에서 사용)
	inline UINT GetIndexCount()
	{
		return IndexCount;
	}

protected:

private:
	// ID3D11Buffer* Buffer = nullptr;         // 모든 Buffer 계열은 ID3D11Buffer를 멤버 변수로 가지고 있다. << 상속받음
	// D3D11_BUFFER_DESC BufferInfo = { 0, };  // 그리고 D3D11_BUFFER_DESC로 정보를 받아서 활용한다.         << 상속받음

	void ResCreate(const void* _Data, UINT _IndexSize, UINT _IndexCount);

	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;

	UINT Offset = 0;
	UINT IndexSize = 0;   // 공간의 크기
	UINT IndexCount = 0;  // 정점의 갯수
	UINT VertexCount = 0;
};

