#include "PrecompileHeader.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::GameEngineVertexShader()
{
	Type = ShaderType::Vertex;
}

GameEngineVertexShader::~GameEngineVertexShader()
{
	if (nullptr != ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

// 쉐이더 컴파일 실시
void GameEngineVertexShader::ShaderLoad(const std::string_view& _Path ,const std::string_view& _EntryPoint ,UINT _VersionHigh /*= 5*/ ,UINT _VersionLow /*= 0*/)
{
	CreateVersion("vs", _VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);

	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;

#endif
	// 상수버퍼 할때 이옵션이 관련이 있다. 나중에 상수 버퍼할 때 알려달라고 얘기
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// ID3DBlob 선언 필요, 에러발생 시 해당 포인터에 에러 메세지가 전달됨(하단의 if 구현부 확인)
	ID3DBlob* Error;

	// 경로는 유니코드화 하여 전달받아야 한다.
	std::wstring UniCodePath = GameEngineString::AnsiToUniCode(_Path);

	if (S_OK != D3DCompileFromFile          // 쉐이더의 경로를 알려주면 컴파일을 해주는 함수이다.
	(
		UniCodePath.c_str(),                // 유니코드화된 경로 wstring에 경로 복사
		nullptr,                            // 널포인터, #defined을 활용하지 않음, 종종 쉐이더는 4만줄 이상 코딩하고 #defined을 통해 경우에 따라 이 선언부, 저 선언부로 바꿔가며 쉐이더 함수를 호출하지만, 아직 안쓸 예정(아마 계속 안쓸 수도 있음, 그래서 널포인터)
		D3D_COMPILE_STANDARD_FILE_INCLUDE,  // 해당 쉐이더 내의 #include를 따르라는 뜻, 어쩔 땐 include 하고 어쩔 땐 안하는 경우가 있긴 한데, 그냥 쉐이더 코드 안에서 #include하고 사용할 예정이다.
		EntryPoint.c_str(),                 // EntryPoint 전달
		Version.c_str(),                    // Version 전달
		Flag,                               // 디버깅 모드일 떄 Flag(D3D10_SHADER_DEBUG)로 해달라는 뜻, D11은 없고 D10만 있다. 다이렉트가 D11로 안바꿨음
		0,                                  // 알아서 하라는 뜻
		&BinaryCode,                        // 이중 포인터는 넣으면 값이 변경된다. 쉐이더 코드를 그래픽카드에게 전달했을 때, 넘겨받는 바이너리코드를 저장
		&Error                              // 에러나면 여기에 값 전달
	)
		)
	{
		// S_OK가 아닐 경우, reinterpret_cast<char*>(Error->GetBufferPointer())를 string으로 받으면
		// 어떤 에러가 발생했는지 알 수 있다. 이것을 우리의 MsgAssert의 인자로 전달 후 Assert 실시
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgAssert(ErrorString);
		return;
	}

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader
	(
		BinaryCode->GetBufferPointer(),  // 바이너리코드의 버퍼포인터 가져오기
		BinaryCode->GetBufferSize(),     // 바이너리코드의 버퍼사이즈 가져오기
		nullptr,                         // 변경사항 없이 넣어준 대로 만들어달라는 뜻
		&ShaderPtr                       // ShaderPtr에 값 저장
	)
		)
	{
		MsgAssert("버텍스 쉐이더 핸들 생성에 실패했습니다");
		return;
	}

	// GameEngineConstantBuffer의 ShaderResCheck 실행
	ShaderResCheck();
}

// VertexShader Setting 단계, Load 후 값을 저장한 ShaderPtr을 활용
void GameEngineVertexShader::Setting()
{
	if (nullptr == ShaderPtr)
	{
		MsgAssert("버텍스 쉐이더가 존재하지 않습니다 세팅에 실패했습니다.");
		return;
	}

	GameEngineDevice::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
	// 1번 : Load로 값 저장된 버텍스포인터
	// 2번 : 필요없기 때문에 널포인터
	// 3번 : 필요없기 때문에 0
}