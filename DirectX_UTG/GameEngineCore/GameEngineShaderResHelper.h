#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

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
	std::shared_ptr<GameEngineTexture> Res; // �ؽ��� ���� ���ҽ� ����

	// �ؽ��� ������ ParentShader�� �����ϰ�, Type�� �´� ���̴� ���� �ǽ�
	void Setting() override;
};

// ���÷� ���� ���� Ŭ����
class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineSampler> Res; // ���÷� ���� ���ҽ� ����

	// ���÷� ������ ParentShader�� �����ϰ�, Type�� �´� ���̴� ���� �ǽ�
	void Setting() override;
};

// �ؽ��ĳ� ��� ���� ��, ��� ���ҽ��� ���� ���� Ŭ����
class GameEngineShaderResHelper
{
private:
	// ������ �Ȱ��Ƶ�, ���̴� Ÿ���� �ٸ���(���ؽ�, �ȼ�) ������ ���ĵ� ����� ����.
	// �̰� ���ļ� ������ �ƴ� �Ŷ��, ���ʿ� VSSetting, PSSetting �̷��� ���� �ʿ䰡 ������.
	// ������ �Ǵ� ���� ���� ���̴� ���� ���� ������ ���ٰ� �����ϴ� �� ���̴�.
	// ���� ���� ���� �ڵ� ����������, �̸��� ��ġ�� ��� ���۰� ���Ը� �ٸ� ��쿡�� map�� ���� �� �ֵ���(Key���� �Ȱ��Ƶ� insert �ǵ���) ��Ƽ���� Ȱ���� ���̴�.
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;

public:
	// ������ ��� ���۸� ConstantBuffer�� �����Ѵ�.
	void CreateConstantBufferSetter(const GameEngineConstantBufferSetter& _Buffer)
	{
		ConstantBufferSetters.insert(std::make_pair(_Buffer.Name, _Buffer));
	}

	void CreateTextureSetter(const GameEngineTextureSetter& _Setter)
	{
		TextureSetters.insert(std::make_pair(_Setter.Name, _Setter));
	}

	void CreateSamplerSetter(const GameEngineSamplerSetter& _Setter)
	{
		SamplerSetters.insert(std::make_pair(_Setter.Name, _Setter));
	}

	bool IsConstantBuffer(const std::string_view& _Name)
	{
		std::string UpperName = GameEngineString::ToUpper(_Name);

		std::multimap<std::string, GameEngineConstantBufferSetter>::iterator FindIter = ConstantBufferSetters.find(UpperName);

		if (ConstantBufferSetters.end() == FindIter)
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
	
	// �ؽ��ĸ� �̸����� �����ϴ� �Լ�
	void SetTexture(const std::string_view& _SettingName, const std::string_view& _ImageName);

	// �ؽ��ĸ� �̸����� �����ϴ� �Լ�
	void SetTexture(const std::string_view& _SettingName, std::shared_ptr<GameEngineTexture> _Texture);

	// ���̴��� ���ҽ� ������ �������� ī��
	void Copy(const GameEngineShaderResHelper& _ResHelper);

	// ��� ���� ������ ParentShader�� �����ϰ�, Type�� �´� ���̴� ���� �ǽ�
	void Setting();
};
