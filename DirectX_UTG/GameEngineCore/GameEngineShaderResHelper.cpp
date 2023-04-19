#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBuffer.h"

// ConstantBuffer�� ��ȸ�ϸ� �ʿ�� �ϴ� GameEngineShaderResHelper�� ����
void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBuffer)
	{
		ConstantBuffer.insert(Setter);
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

// ~Setter�� ���õ� ���ҽ�(��� ����, �ؽ��� ��)�� ������ �ִ�.
// ���⼭ ��� ���۴� ������ ���� �ִµ�, ��� ���̴����� ����ϱ� �����̴�.
// �̸� �����ϱ� ����, ��Ƽ�ʿ��� � ���̴����� �����ϰ�, �׿� ���� Setting�� �ǵ��� switch�� �ǽ�
void GameEngineShaderResHelper::Setting()
{
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator StartIter = ConstantBuffer.begin();
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator EndIter = ConstantBuffer.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		GameEngineConstantBufferSetter& Setter = StartIter->second;
		Setter.Setting();
	}
}

// �̸��� ��ũ�� ������, ����� �������� ResHelper ���� �ʱⰪ�� ����(�������� ���!)�ƴٰ� �ص�, ���Ŀ� ���� �����ϸ� ����Ǳ� ������ ��ũ��� �������ϴ�.
void GameEngineShaderResHelper::SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = GameEngineString::ToUpper(_Name);

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBuffer.find(UpperName);

	if (ConstantBuffer.end() == FindIter)
	{
		MsgAssert("�������� �ʴ� ������۸� �����Ϸ��� �߽��ϴ�." + UpperName);
		return;
	}

	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameStartIter = ConstantBuffer.lower_bound(UpperName); // ���� �̸� ��(Key ��) ���� �տ� �ִ� ��
	std::multimap<std::string, GameEngineConstantBufferSetter>::iterator NameEndIter = ConstantBuffer.upper_bound(UpperName);   // ���� �̸� ��(Key ��) ���� �ڿ� �ִ� ��

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