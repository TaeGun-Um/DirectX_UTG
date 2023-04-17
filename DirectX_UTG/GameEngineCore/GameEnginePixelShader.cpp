#include "PrecompileHeader.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::GameEnginePixelShader()
{
	Type = ShaderType::Pixel;
}

GameEnginePixelShader::~GameEnginePixelShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

// 쉐이더 로드 방식에서 엔트리포인트 이름만 PS인 것 이외에
// 버텍스 쉐이더와 생성 방식이 동일하다.
void GameEnginePixelShader::ShaderLoad(const std::string_view& _Path
	, const std::string_view& _EntryPoint
	, UINT _VersionHigh /*= 5*/
	, UINT _VersionLow /*= 0*/)
{
	CreateVersion("ps", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG

	Flag = D3D10_SHADER_DEBUG;

#endif

	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error;

	std::wstring UniCodePath = GameEngineString::AnsiToUniCode(_Path);

	if (S_OK != D3DCompileFromFile
	(
		UniCodePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryPoint.c_str(),
		Version.c_str(),
		Flag,
		0,
		&BinaryCode,
		&Error
	)
		)
	{

		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgAssert(ErrorString);
		return;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader
	(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),
		nullptr,
		&ShaderPtr
	)
		)
	{
		MsgAssert("버텍스 쉐이더 핸들 생성에 실패했습니다");
	}
}

void GameEnginePixelShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않습니다 세팅에 실패했습니다.");
	}

	GameEngineDevice::GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
	// 전달 인자 방식이 버텍스쉐이더와 동일하다
}