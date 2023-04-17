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
};

// ��� ���� ���� Ŭ����
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res; // ��� ���� ���ҽ� ����
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

	// ConstantBuffer�� ��ȸ�ϸ� �ʿ�� �ϴ� GameEngineShaderResHelper�� ����
	void Copy(const GameEngineShaderResHelper& _ResHelper);
};
