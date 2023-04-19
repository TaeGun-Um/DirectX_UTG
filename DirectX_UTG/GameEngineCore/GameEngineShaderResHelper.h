#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"

// 쉐이더 리소스 헬퍼 클래스
class GameEngineShaderResources
{
public:
	int BindPoint = -1;                     // b0, t0 같은 몇 번째 슬롯인지에 대한 정보
	std::string Name;                       // 쉐이더 이름
	class GameEngineShader* ParentShader;   // 쉐이더 타입(버텍스냐 픽셀이냐)

	virtual void Setting() = 0;             // 세터들에게 Setting을 강요하도록 virtual 실시
};

// 상수 버퍼 헬퍼 클래스
class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res; // 상수 버퍼 리소스 집합
	const void* CPUData;
	UINT CPUDataSize;

	// 상수 버퍼는 모든 쉐이더에서 사용하기 때문에, 구분을 위한 switch 실시
	void Setting() override;
};

// 텍스쳐 세팅 헬퍼 클래스
class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;       // 텍스쳐 세팅 리소스 집합
};

// 텍스쳐나 상수 버퍼 등, 모든 리소스를 위한 헬퍼 클래스
class GameEngineShaderResHelper
{
private:
	// 슬롯이 똑같아도, 쉐이더 타입이 다르면(버텍스, 픽셀) 슬롯이 겹쳐도 상관이 없다.
	// 이게 겹쳐서 문제가 됐던 거라면, 애초에 VSSetting, PSSetting 이렇게 나눌 필요가 없었지.
	// 문제가 되는 것은 같은 쉐이더 내에 같은 슬롯을 쓴다고 선언하는 것 뿐이다.
	// 물론 좋지 않은 코딩 습관이지만, 이름이 겹치는 상수 버퍼가 슬롯만 다를 경우에도 map에 넣을 수 있도록(Key값이 똑같아도 insert 되도록) 멀티맵을 활용한 것이다.
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBuffer;

public:
	// 생성된 상수 버퍼를 ConstantBuffer에 저장한다.
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

	// ConstantBuffer를 순회하며 필요로 하는 GameEngineShaderResHelper를 복사
	void Copy(const GameEngineShaderResHelper& _ResHelper);

	// 상수 버퍼 세팅을 ParentShader로 구분하고, Type에 맞는 쉐이더 세팅 실시
	void Setting();
};
