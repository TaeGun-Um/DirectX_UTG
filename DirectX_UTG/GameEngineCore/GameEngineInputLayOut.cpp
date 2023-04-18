#include "PrecompileHeader.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineInputLayOut::GameEngineInputLayOut()
{
}

GameEngineInputLayOut::~GameEngineInputLayOut()
{
	Relase();
}

void GameEngineInputLayOut::Relase()
{
	if (nullptr != InputLayOut)
	{
		InputLayOut->Release();
		InputLayOut = nullptr;
	}
}

// 만들어진 버텍스 버퍼와 버텍스 쉐이더를 받고 그걸 기반으로 인풋 레이아웃 생성
void GameEngineInputLayOut::ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader)
{
	// 중간에 쉐이더나 버텍스버퍼 정보를 변경했어도, 지우고 시작하여 꼬이지 않도록 함
	Relase();

	if (nullptr == _Info->LayOutInfo)
	{
		MsgAssert("레이아웃 정보를 만들수 없는 버텍스 버퍼 입니다.");
	}

	const std::vector<D3D11_INPUT_ELEMENT_DESC>& LayOutInfos = _Info->LayOutInfo->GetDescs();

	// 버텍스버퍼와 버텍스쉐이더를 기반으로 인풋레이아웃 생성
	HRESULT Result = GameEngineDevice::GetDevice()->CreateInputLayout(
		&LayOutInfos[0],                         // 버텍스버퍼의 시작 주소값
		static_cast<UINT>(LayOutInfos.size()),   // 버텍스버퍼의 사이즈
		_Shader->BinaryCode->GetBufferPointer(), // 쉐이더의 바이너리 코드
		_Shader->BinaryCode->GetBufferSize(),    // 쉐이더의 바이너리 코드 사이즈
		&InputLayOut);                           // 여기로 생성된 값 복사

	if (S_OK != Result)
	{
		MsgAssert("인풋 레이아웃 생성에 실패했습니다.");
	}

}

// 생성된 인풋 레이아웃으로 세팅
void GameEngineInputLayOut::Setting()
{
	if (nullptr == InputLayOut)
	{
		MsgAssert("생성되지 않은 인풋레이아웃을 세팅하려고 했습니다.");
	}

	GameEngineDevice::GetContext()->IASetInputLayout(InputLayOut);
}