#pragma once
#include "GameEngineResource.h"

// ID3D11Buffer 
// 
// 어떤 데이터에 대한 사용 권한을 주기 위한 것이다.
// DirectX가 보기엔 VRAM에 몇 바이트의 공간을 만들어주면 되는거지? 라고 하는 것
// 해당 공간을 어떻게 사용할 지는 사용자가 전달해줘야 한다. ==> D3D11_BUFFER_DESC를 활용

// 설명 : DirectX에서 점을 그리기 위한 인스턴스 버퍼용 클래스
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
	ID3D11Buffer* Buffer = nullptr;         // 모든 Buffer 계열은 ID3D11Buffer를 멤버 변수로 가지고 있다.
	D3D11_BUFFER_DESC BufferInfo = { 0, };  // 그리고 D3D11_BUFFER_DESC로 정보를 받아서 활용한다.

private:
};

