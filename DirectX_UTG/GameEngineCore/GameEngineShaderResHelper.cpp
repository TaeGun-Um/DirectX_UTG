#include "PrecompileHeader.h"
#include "GameEngineShaderResHelper.h"

// ConstantBuffer를 순회하며 필요로 하는 GameEngineShaderResHelper를 복사
void GameEngineShaderResHelper::Copy(const GameEngineShaderResHelper& _ResHelper)
{
	for (const std::pair<std::string, GameEngineConstantBufferSetter>& Setter : _ResHelper.ConstantBuffer)
	{
		ConstantBuffer.insert(Setter);
	}
}