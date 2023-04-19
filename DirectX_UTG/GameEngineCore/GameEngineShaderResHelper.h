#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"

// ���̴� ���ҽ� ���� Ŭ����
class GameEngineShaderResources
{
public:
	int BindPoint = -1;                     // b0, t0 ���� �� ��° ���������� ���� ����
	std::string Name;                       // ���̴� �̸�
	class GameEngineShader* ParentShader;   // ���̴� Ÿ��(���ؽ��� �ȼ��̳�)

	virtual void Setting() = 0;             // ���͵鿡�� Setting�� �����ϵ��� virtual �ǽ�
};

// ��� ���� ���� Ŭ����
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res; // ��� ���� ���ҽ� ����
	const void* CPUData;
	UINT CPUDataSize;

	// ��� ���۴� ��� ���̴����� ����ϱ� ������, ������ ���� switch �ǽ�
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
	// ������ �Ȱ��Ƶ�, ���̴� Ÿ���� �ٸ���(���ؽ�, �ȼ�) ������ ���ĵ� ����� ����.
	// �̰� ���ļ� ������ �ƴ� �Ŷ��, ���ʿ� VSSetting, PSSetting �̷��� ���� �ʿ䰡 ������.
	// ������ �Ǵ� ���� ���� ���̴� ���� ���� ������ ���ٰ� �����ϴ� �� ���̴�.
	// ���� ���� ���� �ڵ� ����������, �̸��� ��ġ�� ��� ���۰� ���Ը� �ٸ� ��쿡�� map�� ���� �� �ֵ���(Key���� �Ȱ��Ƶ� insert �ǵ���) ��Ƽ���� Ȱ���� ���̴�.
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

	void SetConstantBufferLink(const std::string_view& _Name, const void* _Data, UINT _Size);

	// ConstantBuffer�� ��ȸ�ϸ� �ʿ�� �ϴ� GameEngineShaderResHelper�� ����
	void Copy(const GameEngineShaderResHelper& _ResHelper);

	// ��� ���� ������ ParentShader�� �����ϰ�, Type�� �´� ���̴� ���� �ǽ�
	void Setting();
};
