#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// (0417) ���� �츮�� ���� ������ �ϳ��� ������ ������������ ��� ���������� �����ϰ� �ִ� �����̴�.
// �̷��� �Ǹ� ������ ���������� �ȿ� �ִ� �ȼ� ���̴����� �ؽ��ĸ� �� �� �����ϴ� ��Ȳ��, �� �ؽ��ĸ� ���� ����־�� �ϴ����� ������ �߻��Ѵ�.

// ���̴��� ���ҽ��� ������ ������������ ��ĥ �� ����.
// �⼺ ������ ���(�𸮾�) ���͸��� �ν��Ͻ���� ���� ����µ�, �̰��� ������ ������������ �����ؼ�(���̴��� ������ �����ؼ�) �������� ��� �ֵ��� �Ѵ�.
// �� �״�� �������� ������ŭ ���� ������ �ذ��Ѵٴ� ���̴�.

// 100���� ������ �����Ѵٰ� �����غ���. ������ ��� �Ȱ��� �ؽ��Ŀ� ������ ������������ ����� ���̴�.
// �̰͵��� ���ҽ��� �����ϴ� �����̱� ������ �и����� �ʴ� �����̴�.
// �츮�� �и� ���� ����
// �������� �ؽ��ĸ� ����ִ� ���´� �ؽ��� ������ ������ ��� �ذ��� ���������(��� ������ Texture1, Texture2, Texture3, ... ���� �þ�� ��������ٴ� ��).
// �̸� ���� ���� GameEngineShaderResHelper�� ���� �����Ѵ�.
// �̷��� ���������ΰ� ���ҽ��� Renderer�� ����ִ� ���°� �ȴ�.
// GameEngineRenderer�� GameEngineShaderResHelper�� �̵�

// ���� : ��� ���۸� �����ϱ� ���� Ŭ����
class GameEngineConstantBuffer : public GameEngineResource<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
	friend class GameEngineConstantBufferSetter;

public:

	// constrcuter destructer
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

	// delete Function
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _Other) noexcept = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _Other) = delete;
	GameEngineConstantBuffer& operator=(GameEngineConstantBuffer&& _Other) noexcept = delete;

	// ��� ���۴� �̸��� �߿����� �ʰ�, ����� �߿��ϴ�.
	// �ִ� ��� ���۴� �״�� find �ؼ� ��������, ���� ��� ���۴� ���� �����´�.
	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, const std::string_view& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
	{
		// ������ ������(ũ��)�� ��� ���۰� �������� �ʴ´ٸ�
		if (ConstantBufferRes.end() == ConstantBufferRes.find(_Byte))
		{
			// �����.
			ConstantBufferRes[_Byte];
		}

		std::string UpperName = GameEngineString::ToUpper(_Name.data());

		// ������ ������(ũ��)�� ��� ���۰� �����Ѵٸ�
		if (ConstantBufferRes[_Byte].end() != ConstantBufferRes[_Byte].find(UpperName))
		{
			// �װ� ��������
			return ConstantBufferRes[_Byte][UpperName];
		}

		// ���� ������۸� ����� �ܰ�
		// �Ű� ������ Byte�� Name���� �ϴ� ���� == ũ��� ������ ���԰� �̸��� �ٸ� ��� ��� ���۸� ����� �����̴�.
		std::shared_ptr<GameEngineConstantBuffer> Buffer = CreateUnNamed(); // GameEngineResource�� UnNamedRes�� pushback �Ͽ� ���� ����
		Buffer->SetName(UpperName);                                         // UnNamed�̱� ������, �̸����� �����ϴ� ��쵵 �ֱ� ������ �ϴ� SetName���� ����
		ConstantBufferRes[_Byte][UpperName] = Buffer;                       // ������ ���� �ش� Ŭ������ multimap�� ����
		Buffer->ResCreate(_BufferDesc);                                     // GameEngineDevice::GetDevice()->CreateBuffer() �ǽ�

		// ���� �������ش�.
		return Buffer;
	}

	// ���õ� �ʱⰪ���� �ٸ� ������ ������ ��� �ش� �Լ� ȣ��
	void ChangeData(const void* _Data, UINT _Size);

	// ���ҽ� Ŭ����
	static void ResourcesClear();

protected:
	void ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc); // �ε��� ���ۿ� ������ ���¸� ���� ResCreate

private:
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBufferRes; // ��� ���۸� �����ϱ� ���� multi-map

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};
