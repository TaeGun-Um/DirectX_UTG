#pragma once

#include "GameEngineComponent.h"
#include "GameEngineShader.h"

// ���� :
class GameEngineRenderer : public GameEngineComponent
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// ��� ������ DirectX ���������� ������ ��ģ �� ��µȴ�.
	// ���⼭ �߿��Ѱ�, ���̴��� �˰� �ִ� ���� �� �� ���Կ� �����ؾ� �Ѵٴ� �� ���̴�. �ؽ��ĸ� �ε��Ѵٰ� �ڵ����� �̷����� �ʴ´�.
	// ������������ ���õǾ� �ְ�, � ���̴��� ���õǾ� �ְ�, �� ���̴��� � �ؽ��ĸ� ����߰�, � ���÷� � ��� ���۸� ����ߴ����� �˾ƾ� �Ѵ�.
	// �츮 ������ �������̽��� ���̴��� ������ �ϰ� ���� ShaderResCheck() �Լ��� ���� Reflection�� �̿��ϴ� ��
	// GameEngineVertexShader���� ShaderLoad() ���� �������� ShaderResCheck()�� �ǽ���
	void SetPipeLine(const std::string_view& _Name);

	inline GameEngineShaderResHelper& GetShaderResHelper()
	{
		return ShaderResHelper;
	}

protected:
	void Render(float _Delta) override;

private:
	// �츮�� ���� ������ �������� ���ҽ� ���۰� �������� �������Ǵ� ������ �� ���̴�.
	// "������ ������ � ���̴��� �Ἥ �׸��ž�"�� ����
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe; // ������ ������������ ��� ���� shared_ptr
	GameEngineShaderResHelper ShaderResHelper;               // �ؽ��ĸ� ���� ���ҽ�����

};
