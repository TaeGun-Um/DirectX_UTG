#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"

// ���̴��� ���ҽ� ������ �������� ī��
void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	// ��� ���� ���ҽ� ī��
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBufferSetters)
	{
		ConstantBufferSetters.insert(Setter);
	}
	// �ؽ��� ���ҽ� ī��
	for (const std::pair<std::string, GameEngineTextureSetter>& Setter : _ResHelper.TextureSetters)
	{
		TextureSetters.insert(Setter);
	}
	// ���÷� ���ҽ� ī��
	for (const std::pair<std::string, GameEngineSamplerSetter>& Setter : _ResHelper.SamplerSetters)
	{
		SamplerSetters.insert(Setter);
	}
}

// ��� ���� ������ ParentShader�� �����ϰ�, Type�� �´� ���̴� ���� �ǽ�
void GameEngineConstantBufferSetter::Setting()
{
	// ���⼭ ���� ó���� �̰� �ǽ�(GPU���� Map�ϰ� �� �����ϰ� Umap�ϴ� �ൿ)�ϰ� Type�� ���� ���̴� �����Ѵ�.
	Res->ChangeData(CPUData, CPUDataSize);

	ShaderType Type = ParentShader->GetType();  // � ���̴����� �����ϱ� ���� GetType

	switch (Type)
	{
	case ShaderType::None:   // �θ�(���̴�)�� �ƹ��͵� �ƴ� ��� (����)
	{
		MsgAssert("� ���̴��� ���õ��� �˼����� ������� �Դϴ�.");
		break;
	}
	case ShaderType::Vertex: // �θ�(���̴�)�� ���ؽ��� ���
	{
		Res->VSSetting(BindPoint);
		break;
	}
	case ShaderType::Pixel:  // �θ�(���̴�)�� �ȼ��� ���
	{
		Res->PSSetting(BindPoint);
		break;
	}
	default:
		break;
	}

}

// �ؽ��� ������ ParentShader�� �����ϰ�, Type�� �´� ���̴� ���� �ǽ�
// �ؽ��Ĵ� �̹� �ִ� ���� ����ϱ� ������, ChangeData�� �ǽ����� �ʴ´�.
void GameEngineTextureSetter::Setting()
{
	ShaderType Type = ParentShader->GetType();

	switch (Type)
	{
	case ShaderType::None:   // �θ�(���̴�)�� �ƹ��͵� �ƴ� ��� (����)
	{
		MsgAssert("� ���̴��� ���õ��� �˼����� ������� �Դϴ�.");
		break;
	}
	case ShaderType::Vertex: // �θ�(���̴�)�� ���ؽ��� ���
	{
		Res->VSSetting(BindPoint);
		break;
	}
	case ShaderType::Pixel:  // �θ�(���̴�)�� �ȼ��� ���
	{
		Res->PSSetting(BindPoint);
		break;
	}
	default:
		break;
	}
}

// ���÷� ������ ParentShader�� �����ϰ�, Type�� �´� ���̴� ���� �ǽ�
// ���÷��� �̹� �ִ� ���� ����ϱ� ������, ChangeData�� �ǽ����� �ʴ´�.
void GameEngineSamplerSetter::Setting()
{
	ShaderType Type = ParentShader->GetType();

	switch (Type)
	{
	case ShaderType::None:   // �θ�(���̴�)�� �ƹ��͵� �ƴ� ��� (����)
	{
		MsgAssert("� ���̴��� ���õ��� �˼����� ������� �Դϴ�.");
		break;
	}
	case ShaderType::Vertex: // �θ�(���̴�)�� ���ؽ��� ���
	{
		Res->VSSetting(BindPoint);
		break;
	}
	case ShaderType::Pixel:  // �θ�(���̴�)�� �ȼ��� ���
	{
		Res->PSSetting(BindPoint);
		break;
	}
	default:
		break;
	}
}

// ~Setter�� ���õ� ���ҽ�(��� ����, �ؽ��� ��)�� ������ �ִ�.
// ���⼭ ��� ���۴� ������ ���� �ִµ�, ��� ���̴����� ����ϱ� �����̴�.
// �̸� �����ϱ� ����, ��Ƽ�ʿ��� � ���̴����� �����ϰ�, �׿� ���� Setting�� �ǵ��� switch�� �ǽ�
void GameEngineShaderResHelper::Setting()
{
	// ���̴� ��� ���� ����
	{
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator StartIter = ConstantBufferSetters.begin();
		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator EndIter = ConstantBufferSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineConstantBufferSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}
	// ���̴� �ؽ��� ����
	{
		std::multimap<std::string, GameEngineTextureSetter>::iterator StartIter = TextureSetters.begin();
		std::multimap<std::string, GameEngineTextureSetter>::iterator EndIter = TextureSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineTextureSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}
	// ���̴� ���÷� ����
	{
		std::multimap<std::string, GameEngineSamplerSetter>::iterator StartIter = SamplerSetters.begin();
		std::multimap<std::string, GameEngineSamplerSetter>::iterator EndIter = SamplerSetters.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			GameEngineSamplerSetter& Setter = StartIter->second;
			Setter.Setting();
		}
	}
}

// �̸��� ��ũ�� ������, ����� �������� ResHelper ���� �ʱⰪ�� ����(�������� ���!)�ƴٰ� �ص�, ���Ŀ� ���� �����ϸ� ����Ǳ� ������ ��ũ��� �������ϴ�.
void GameEngineShaderResHelper::SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBufferSetters.find(UpperName);

	if (ConstantBufferSetters.end() == FindIter)
	{
		MsgAssert("�������� �ʴ� ������۸� �����Ϸ��� �߽��ϴ�." + UpperName);
		return;
	}

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter = ConstantBufferSetters.lower_bound(UpperName); // ���� �̸� ��(Key ��) ���� �տ� �ִ� ��
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter = ConstantBufferSetters.upper_bound(UpperName);   // ���� �̸� ��(Key ��) ���� �ڿ� �ִ� ��

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		GameEngineConstantBufferSetter& Setter = NameStartIter->second;

		if (Setter.Res->GetBufferSize() != _Size)
		{
			MsgAssert("������ۿ� �����Ϸ��� �������� ũ�Ⱑ �ٸ��ϴ�.\n ������� : " + std::to_string(Setter.Res->GetBufferSize()) + "\n������ ������ ������ : " + std::to_string(_Size) + UpperName);
			return;
		}

		Setter.CPUData = _Data;      // ��ũ�� �Լ� ȣ���ϸ� CPUData�� �ڷ��� �Է�
		Setter.CPUDataSize = _Size;  // �̷��� ����� �ڷ��� ������ ũ��� ��� ���� ������ ũ�Ⱑ �ٸ��� ������ ����
	}

}