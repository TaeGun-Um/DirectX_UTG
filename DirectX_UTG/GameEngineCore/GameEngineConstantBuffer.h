#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

// (0417) 현재 우리의 엔진 구조는 하나의 랜더링 파이프라인을 모든 랜더러들이 공유하고 있는 형태이다.
// 이렇게 되면 랜더링 파이프라인 안에 있는 픽셀 쉐이더에서 텍스쳐를 한 장 세팅하는 상황에, 그 텍스쳐를 누가 들고있어야 하는지에 문제가 발생한다.

// 쉐이더의 리소스와 랜더링 파이프라인은 겹칠 수 없다.
// 기성 엔진의 경우(언리얼) 머터리얼 인스턴스라는 것을 만드는데, 이것은 랜더링 파이프라인을 복제해서(쉐이더의 내용을 복제해서) 랜더러가 들고 있도록 한다.
// 말 그대로 랜더러의 갯수만큼 만들어서 문제를 해결한다는 뜻이다.

// 100개의 나무가 존재한다고 가정해보자. 나무는 모두 똑같은 텍스쳐와 랜더링 파이프라인을 사용할 것이다.
// 이것들은 리소스를 공유하는 형태이기 때문에 분리하지 않는 형태이다.
// 우리도 분리 안할 예정
// 랜더러가 텍스쳐를 들고있는 형태는 텍스쳐 세팅이 많아질 경우 해결이 어려워진다(멤버 변수로 Texture1, Texture2, Texture3, ... 점점 늘어나면 어려워진다는 뜻).
// 이를 돕기 위해 GameEngineShaderResHelper를 만들어서 보조한다.
// 이러면 파이프라인과 리소스를 Renderer가 들고있는 형태가 된다.
// GameEngineRenderer와 GameEngineShaderResHelper로 이동

// 설명 : 상수 버퍼를 생성하기 위한 클래스
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

	// 상수 버퍼는 이름이 중요하지 않고, 사이즈가 중요하다.
	// 있는 상수 버퍼는 그대로 find 해서 가져오고, 없는 상수 버퍼는 만들어서 가져온다.
	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, const std::string_view& _Name, const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
	{
		// 동일한 사이즈(크기)의 상수 버퍼가 존재하지 않는다면
		if (ConstantBufferRes.end() == ConstantBufferRes.find(_Byte))
		{
			// 만든다.
			ConstantBufferRes[_Byte];
		}

		std::string UpperName = GameEngineString::ToUpper(_Name.data());

		// 동일한 사이즈(크기)의 상수 버퍼가 존재한다면
		if (ConstantBufferRes[_Byte].end() != ConstantBufferRes[_Byte].find(UpperName))
		{
			// 그걸 리턴해줌
			return ConstantBufferRes[_Byte][UpperName];
		}

		// 없는 상수버퍼를 만드는 단계
		// 매개 변수를 Byte와 Name으로 하는 이유 == 크기는 같지만 슬롯과 이름이 다를 경우 상수 버퍼를 만들기 위함이다.
		std::shared_ptr<GameEngineConstantBuffer> Buffer = CreateUnNamed(); // GameEngineResource의 UnNamedRes에 pushback 하여 값을 저장
		Buffer->SetName(UpperName);                                         // UnNamed이긴 하지만, 이름으로 구분하는 경우도 있기 때문에 일단 SetName으로 저장
		ConstantBufferRes[_Byte][UpperName] = Buffer;                       // 저장한 값도 해당 클래스의 multimap에 저장
		Buffer->ResCreate(_BufferDesc);                                     // GameEngineDevice::GetDevice()->CreateBuffer() 실시

		// 만들어서 리턴해준다.
		return Buffer;
	}

	// 세팅된 초기값에서 다른 값으로 변경할 경우 해당 함수 호출
	void ChangeData(const void* _Data, UINT _Size);

	// 리소스 클리어
	static void ResourcesClear();

protected:
	void ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc); // 인덱스 버퍼와 유사한 형태를 지닌 ResCreate

private:
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBufferRes; // 상수 버퍼를 저장하기 위한 multi-map

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
};
