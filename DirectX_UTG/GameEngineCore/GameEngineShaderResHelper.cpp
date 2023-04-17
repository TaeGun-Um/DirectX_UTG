#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"

// ConstantBuffer�� ��ȸ�ϸ� �ʿ�� �ϴ� GameEngineShaderResHelper�� ����
void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBuffer)
	{
		ConstantBuffer.insert(Setter);
	}
}