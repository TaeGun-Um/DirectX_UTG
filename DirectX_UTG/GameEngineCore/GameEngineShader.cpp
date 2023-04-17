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

// ���̴� ������ �� ��� ���۸� ����� �����ϱ� ���� �ܰ�
// ���̴� ���ҽ� ���縦 �ǽ��Ͽ� �� ������ ������ ����Ѵ�.
void GameEngineShader::ShaderResCheck()
{
	if (nullptr == BinaryCode)
	{
		MsgAssert("���̴��� ������ ���� �ʾƼ� ���̴��� ���ҽ��� ������ �� �����ϴ�.");
		return;
	}

	// Reflection == RTTI�� ����� ��������, ���̴� �ȿ��� ��� ���� �� �� ����ߴ���, ���ϰ��� ���� ���� �˾Ƴ� �� �ִ�.
	ID3D11ShaderReflection* CompileInfo = nullptr;

	// D3DReflect()
	// 1�� ���� : ���̳ʸ� �ڵ�
	// 2�� ���� : ���̳ʸ� �ڵ��� ���� ������
	// 3�� ���� : GUID
	// 4�� ���� : ������ ���޹��� ID3D11ShaderReflection ������ ����
	if (S_OK != D3DReflect(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgAssert("���̴� ���÷��ǿ� �����߽��ϴ�.");
		return;
	}

	D3D11_SHADER_DESC Info;                // ������ �� ����� ������ �������� ���� ��
	CompileInfo->GetDesc(&Info);           // D3DReflect()�� ���� ������ ���� �����κ��� GetDesc() �Ͽ� D3D11_SHADER_DESC ������ ���̴� �������� �޴´�.
	D3D11_SHADER_INPUT_BIND_DESC ResDesc;  // �� ������ ������ ���� ����

	// Info.BoundResources == ���ο� �ִ� ����� ��� ���ۿ� �ؽ�ó ���÷� ���� ����
	// �ش� ������ŭ for���� ����.
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResDesc); // D3D11_SHADER_INPUT_BIND_DESC���� ���� ����
		std::string Name = ResDesc.Name;                  // ���̴� �ڵ� ������ ����� ��� ������ �̸�(cbuffer TransformData : register(b0) �� "TransformData" �κ�)�� string���� ���� �� �ִ�.
		                                                  // ���� �� ���� ����� �� ������, ���� �� ������ ���̴� �ڵ� ������ ����ؾ� �Ѵ�.
		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;        // D3D_SHADER_INPUT_TYPE�� ������ ���� ��� ������ ���� ������ �޶�����.

		// �ش� ���ҽ� Type�� �����ΰ���~?
		switch (Type)
		{
		case D3D_SIT_CBUFFER: // �� ���ҽ��� ��� �����Դϴ�.
		{
			std::string UpperName = GameEngineString::ToUpper(ResDesc.Name);

			// GetConstantBufferByName() ���� ResDesc.Name(��� ���� �Լ��� �̸�)�� ���� ������ ������ ID3D11ShaderReflectionConstantBuffer ������ ������ ����
			ID3D11ShaderReflectionConstantBuffer* CBufferPtr = CompileInfo->GetConstantBufferByName(ResDesc.Name);
			
			D3D11_SHADER_BUFFER_DESC BufferDesc;

			// ID3D11ShaderReflectionConstantBuffer�� ���� GetDesc(D3D11_SHADER_BUFFER_DESC)�� ������ ����
			CBufferPtr->GetDesc(&BufferDesc);

			// GameEngineConstantBuffer�� CreateAndFind() �ǽ�, ������ �״�� ��������, ������ ���� ������
			// �̸��� �Ȱ��� ũ�Ⱑ �ٸ� �� ������, �̸��� ũ�⵵ ������ �Ȱ��� ��� ���۸� �� ���� ���� �ִ�.
			// ó������ ���� ������, ���̴��� ��� ����� �޸𸮰� ���������� ������ �߻��ϰ� �ȴ�. �̸� �����ϱ� ���� Create�� �ϰų� Find�� �ϴ� ���̴�.
			// �⺻������ ���� ������ ��� ���۴� ũ�Ⱑ ������ ��� �����Ͽ� ����� �� �ֱ� ������ �� ���¸� ���Ѵ�.
			// 1�� ���� : ��� ���� ũ�� ����
			// 2�� ���� : ��� ������ �̸� ����
			// 3�� ���� : ��� ���� ����(Desc) ����
			std::shared_ptr<GameEngineConstantBuffer> Buffer = GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, UpperName, BufferDesc);
			// ��� ���۴� ���� �� ��������� �޸𸮰� ����������.
			// ���� �ǵ����̸� ���� �������� ���۴� �������� ���°� ����

			// ������� ��� ���۸� CreateConstantBufferSetter�� �����ϱ� ���� ��ü ����
			GameEngineConstantBufferSetter Setter;

			Setter.ParentShader = this;           // �θ�(���̴�) ����
			Setter.Name = UpperName;              // ������� �̸�(ResDesc.Name) ����
			Setter.BindPoint = ResDesc.BindPoint; // ���� ��ȣ ����
			Setter.Res = Buffer;                  // ������� ����

			// GameEngineShaderResHelper�� ��Ƽ�� �ڷ��� ConstantBuffer�� ������� ���� �Է�
			ResHelper.CreateConstantBufferSetter(Setter);

			break;
		}
		case D3D_SIT_TEXTURE: // �� ���ҽ��� �ؽ����Դϴ�.
		{
			break;
		}
		case D3D_SIT_SAMPLER: // �� ���ҽ��� ���÷��Դϴ�.
		{
			break;
		}
		default:
			break;
		}

	}

	// CompileInfo
}