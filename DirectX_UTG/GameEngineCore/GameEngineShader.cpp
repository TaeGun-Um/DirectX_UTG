#include "PrecompileHeader.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"

GameEngineShader::GameEngineShader()
{
}

GameEngineShader::~GameEngineShader()
{
	if (nullptr != BinaryCode)
	{
		BinaryCode->Release();
		BinaryCode = nullptr;
	}
}

void GameEngineShader::CreateVersion(const std::string_view& _ShaderType, UINT _VersionHigt /*= 5*/, UINT _VersionLow /*= 0*/)
{
	// vs_5_0
	Version += _ShaderType;
	Version += "_";
	Version += std::to_string(_VersionHigt);
	Version += "_";
	Version += std::to_string(_VersionLow);
}

// 쉐이더 컴파일 시 상수 버퍼를 만들고 적용하기 위한 단계
// 쉐이더 리소스 조사를 실시하여 그 정보를 가져와 사용한다.
void GameEngineShader::ShaderResCheck()
{
	if (nullptr == BinaryCode)
	{
		MsgAssert("쉐이더가 컴파일 되지 않아서 쉐이더의 리소스를 조사할 수 없습니다.");
		return;
	}

	// Reflection == RTTI와 비슷한 개념으로, 쉐이더 안에서 상수 버퍼 몇 개 사용했는지, 리턴값이 뭔지 등을 알아낼 수 있다.
	ID3D11ShaderReflection* CompileInfo = nullptr;

	// D3DReflect()
	// 1번 인자 : 바이너리 코드
	// 2번 인자 : 바이너리 코드의 버퍼 사이즈
	// 3번 인자 : GUID
	// 4번 인자 : 정보를 전달받을 ID3D11ShaderReflection 포인터 변수
	if (S_OK != D3DReflect(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgAssert("쉐이더 리플렉션에 실패했습니다.");
		return;
	}

	D3D11_SHADER_DESC Info;                // 컴파일 후 저장된 정보를 가져오기 위한 것
	CompileInfo->GetDesc(&Info);           // D3DReflect()을 통해 정보를 받은 변수로부터 GetDesc() 하여 D3D11_SHADER_DESC 변수가 쉐이더 정보들을 받는다.
	D3D11_SHADER_INPUT_BIND_DESC ResDesc;  // 또 정보를 얻어오기 위한 변수

	// Info.BoundResources == 내부에 있는 사용한 상수 버퍼와 텍스처 샘플러 등의 총합
	// 해당 갯수만큼 for문을 돈다.
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResDesc); // D3D11_SHADER_INPUT_BIND_DESC에게 정보 복사
		std::string Name = ResDesc.Name;                  // 쉐이더 코드 내에서 사용한 상수 버퍼의 이름(cbuffer TransformData : register(b0) 중 "TransformData" 부분)을 string으로 받을 수 있다.
		                                                  // 선언만 한 것은 사용할 수 없으며, 선언 후 실제로 쉐이더 코드 내에서 사용해야 한다.
		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;        // D3D_SHADER_INPUT_TYPE이 뭔지에 따라 상수 버퍼의 생성 조건이 달라진다.

		// 해당 리소스 Type은 무엇인가요~?
		switch (Type)
		{
		case D3D_SIT_CBUFFER: // 이 리소스는 상수 버퍼입니다.
		{
			std::string UpperName = GameEngineString::ToUpper(ResDesc.Name);

			// GetConstantBufferByName() 에서 ResDesc.Name(상수 버퍼 함수의 이름)을 통해 정보를 가져와 ID3D11ShaderReflectionConstantBuffer 포인터 변수에 저장
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResDesc.Name);
			
			D3D11_SHADER_BUFFER_DESC BufferDesc;

			// ID3D11ShaderReflectionConstantBuffer에 대해 GetDesc(D3D11_SHADER_BUFFER_DESC)로 정보를 얻어옴
			CBufferPtr->GetDesc(&BufferDesc);

			// GameEngineConstantBuffer의 CreateAndFind() 실시, 있으면 그대로 가져오고, 없으면 만들어서 가져옴
			// 이름만 똑같고 크기가 다를 수 있지만, 이름도 크기도 완전히 똑같은 상수 버퍼를 또 만들 수도 있다.
			// 처음에는 문제 없지만, 쉐이더를 계속 만들면 메모리가 부족해지는 문제가 발생하게 된다. 이를 방지하기 위해 Create를 하거나 Find를 하는 것이다.
			// 기본적으로 같은 슬롯의 상수 버퍼는 크기가 동일할 경우 공유하여 사용할 수 있기 때문에 이 형태를 취한다.
			// 1번 인자 : 상수 버퍼 크기 전달
			// 2번 인자 : 상수 버퍼의 이름 전달
			// 3번 인자 : 상수 버퍼 정보(Desc) 전달
			std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, UpperName, BufferDesc);
			// 상수 버퍼는 여러 개 만들어지면 메모리가 부족해진다.
			// 따라서 되도록이면 같은 사이즈의 버퍼는 돌려쓰는 형태가 좋음

			// 만들어진 상수 버퍼를 CreateConstantBufferSetter로 저장하기 위한 객체 선언
			GameEngineConstantBufferSetter Setter;

			Setter.ParentShader = this;           // 부모(쉐이더) 설정
			Setter.Name = UpperName;              // 상수버퍼 이름(ResDesc.Name) 설정
			Setter.BindPoint = ResDesc.BindPoint; // 슬롯 번호 설정
			Setter.Res = Buffer;                  // 상수버퍼 정보

			// GameEngineShaderResHelper의 멀티맵 자료형 ConstantBuffer에 만들어진 버퍼 입력
			ResHelper.CreateConstantBufferSetter(Setter);

			break;
		}
		case D3D_SIT_TEXTURE: // 이 리소스는 텍스쳐입니다.
		{
			break;
		}
		case D3D_SIT_SAMPLER: // 이 리소스는 샘플러입니다.
		{
			break;
		}
		default:
			break;
		}

	}

	// CompileInfo
}