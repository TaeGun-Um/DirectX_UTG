#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"

// ���̴� ���ҽ� ���� Ŭ����
class GameEngineShaderResources
{
public:
	int BindPoint = -1;                     // b0, t0 ���� �� ��° ���Կ� ���õǾ�� �ϴ����� ���� ����.
	std::string Name;                       // ���̴� �̸�
	class GameEngineShader* ParentShader;   // �θ� ���̴�

	virtual void Setting() = 0;
};

// ��� ���� ���� Ŭ����
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res; // ��� ���� ���ҽ� ����
	const void* CPUData;
	size_t CPUDataSize;

	void Setting() override;
};

// �ؽ��� ���� ���� Ŭ����
class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;       // �ؽ��� ���� ���ҽ� ����
};

// �ؽ��ĳ� ��� ���� ��, ��� ���ҽ��� ���� ���� Ŭ����
class GameEngineShaderResHelper
{
private:
	// ��� ������ ���, �̸��� �ϳ����� Vertex�� ���Ǳ⵵ �ϰ� Shader�� ���Ǳ⵵ �Ѵ�. �̸� ���� multimap == key(first)�� �ߺ��� ������ map
	// ��� ���۴� ���̴��� ������ �Ǹ鼭 �̷� �������� ���±��� �ϴ� ������ ����� �� ��� ���۰� ���������(GameEngineShader::ShaderResCheck()�� �̵�)
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	// ������ ��� ���۸� ConstantBuffer�� �����Ѵ�.
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBuffer.insert(std::make_pair(_Buffer.Name, _Buffer));
	}

	bool IsConstantBuffer(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBuffer.find(UpperName);

		if (ConstantBuffer.end() == FindIter)
		{
			return false;
		}

		return true;
	}

	template<typename DataType>
	void SetConstantBufferLink(const std::string_view& _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, reinterpret_cast<const void*>(&_Data), sizeof(DataType));
	}

	void SetConstantBufferLink(const std::string_view& _Name, const void* _Data, size_t _Size);

	// ConstantBuffer�� ��ȸ�ϸ� �ʿ�� �ϴ� GameEngineShaderResHelper�� ����
	void Copy(const GameEngineShaderResHelper& _ResHelper);

	void Setting();
};
