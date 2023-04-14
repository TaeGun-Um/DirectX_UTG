#pragma once
#include "GameEngineResource.h"

// ���� : GameEngineRenderingPipeLine���� ��ǲ���̾ƿ��� ���� �� Ȱ���ϴ� Ŭ����
class GameEngineInputLayOut : public GameEngineResource<GameEngineInputLayOut>
{
public:
	// constrcuter destructer
	GameEngineInputLayOut();
	~GameEngineInputLayOut();

	// delete Function
	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void Relase();

	// ������� ���ؽ� ���ۿ� ���ؽ� ���̴��� �ް� �װ� ������� ��ǲ ���̾ƿ� ����
	void ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader);

	// ������ ��ǲ ���̾ƿ����� ����
	void Setting() override;

protected:

private:
	ID3D11InputLayout* InputLayOut = nullptr;

};

