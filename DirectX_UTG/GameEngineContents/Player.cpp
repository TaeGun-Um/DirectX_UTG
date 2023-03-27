#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Update(float _Delta)
{

}

void Player::Render(float _Delta)
{
	HDC Dc = GameEngineWindow::GetWindowBackBufferHdc();

	// Rectangle(Dc, 0, 0, 100, 100);

	const int VertexCount = 24;

	float4 Pos = { 640, 360 };

	// 최초의 버텍스의 위치를 로컬공간이라고 부릅니다.
	float4 ArrVertex[VertexCount];
	// 앞면
	ArrVertex[0] = { -0.5f, -0.5f, 0.5f };
	ArrVertex[1] = { 0.5f, -0.5f,0.5f };
	ArrVertex[2] = { 0.5f, 0.5f,0.5f };
	ArrVertex[3] = { -0.5f, 0.5f,0.5f };

	// 뒷면
	ArrVertex[4] = ArrVertex[0].RotaitonXDegReturn(180.0f);
	ArrVertex[5] = ArrVertex[1].RotaitonXDegReturn(180.0f);
	ArrVertex[6] = ArrVertex[2].RotaitonXDegReturn(180.0f);
	ArrVertex[7] = ArrVertex[3].RotaitonXDegReturn(180.0f);

	// 왼쪽면
	ArrVertex[8] = ArrVertex[0].RotaitonYDegReturn(90.0f);
	ArrVertex[9] = ArrVertex[1].RotaitonYDegReturn(90.0f);
	ArrVertex[10] = ArrVertex[2].RotaitonYDegReturn(90.0f);
	ArrVertex[11] = ArrVertex[3].RotaitonYDegReturn(90.0f);

	// 오른쪽
	ArrVertex[12] = ArrVertex[0].RotaitonYDegReturn(-90.0f);
	ArrVertex[13] = ArrVertex[1].RotaitonYDegReturn(-90.0f);
	ArrVertex[14] = ArrVertex[2].RotaitonYDegReturn(-90.0f);
	ArrVertex[15] = ArrVertex[3].RotaitonYDegReturn(-90.0f);

	ArrVertex[16] = ArrVertex[0].RotaitonXDegReturn(90.0f);
	ArrVertex[17] = ArrVertex[1].RotaitonXDegReturn(90.0f);
	ArrVertex[18] = ArrVertex[2].RotaitonXDegReturn(90.0f);
	ArrVertex[19] = ArrVertex[3].RotaitonXDegReturn(90.0f);

	ArrVertex[20] = ArrVertex[0].RotaitonXDegReturn(-90.0f);
	ArrVertex[21] = ArrVertex[1].RotaitonXDegReturn(-90.0f);
	ArrVertex[22] = ArrVertex[2].RotaitonXDegReturn(-90.0f);
	ArrVertex[23] = ArrVertex[3].RotaitonXDegReturn(-90.0f);


	POINT ArrPoint[VertexCount];

	float4x4 ScaleMat;
	ScaleMat.Scale({ 100, 100, 100 });

	float4x4 PosMat;
	PosMat.Pos(Pos);

	float4x4 WorldMat = ScaleMat * PosMat;

	// 크자이공부

	// 크기를 키우고
	// 회전시킨다음
	// 이동하고
	// 공전시키고
	// 부모의 변환을 적용시킨다.
	// 공간변환의 순서.

	// 벡터의 외적에 대해서 알아봅시다.

	for (size_t i = 0; i < VertexCount; i++)
	{
		ArrVertex[i] = ArrVertex[i] * WorldMat;
		ArrPoint[i] = ArrVertex[i].ToWindowPOINT();
	}

	for (size_t i = 0; i < 6; i++)
	{
		size_t Index = i * 4;

		float4 Vector0 = ArrVertex[Index + 0];
		float4 Vector1 = ArrVertex[Index + 1];
		float4 Vector2 = ArrVertex[Index + 2];

		float4 Dir0 = Vector0 - Vector1;
		float4 Dir1 = Vector1 - Vector2;

		float4 Cross = float4::Cross3DReturn(Dir0, Dir1);
		if (0 <= Cross.z)
		{
			continue;
		}

		Polygon(Dc, &ArrPoint[i * 4], 4);
	}
};