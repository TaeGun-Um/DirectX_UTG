#pragma once

#include <math.h>
#include <cmath>
#include <string>
#include <Windows.h>
#include <vector>

// final 더이상 상속 내리지 못하도록 하는 문법
class GameEngineMath final
{
public:
	static std::vector<unsigned int> GetDigits(int _Value);
	static unsigned int GetLenth(int _Value);
	static const float PIE;
	static const float PIE2;
	static const float DegToRad;
	static const float RadToDeg;

private:
	virtual ~GameEngineMath() = 0;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Forward;
	static const float4 Back;
	static const float4 One;
	static const float4 Zero;
	static const float4 Null;

	static float4 AngleToDirection2DToDeg(float _Deg)
	{
		return AngleToDirection2DToRad(_Deg * GameEngineMath::DegToRad);
	}

	static float4 AngleToDirection2DToRad(float _Rad)
	{
		return float4(cosf(_Rad), sinf(_Rad), 0.0f, 1.0f);
	}

	static float GetAngleVectorToVectorDeg(const float4& _Left, const float4& _Right)
	{
		return GetAngleVectorToVectorRad(_Left, _Right) * GameEngineMath::RadToDeg;
	}

	static float GetAngleVectorToVectorRad(const float4& _Left, const float4& _Right)
	{
		float4 Left = _Left;
		float4 Right = _Right;

		Left.Normalize();
		Right.Normalize();

		float CosSeta = DotProduct3D(Left, Right);

		float Angle = acosf(CosSeta);

		return Angle;
	}

	static float4 Cross3DReturnNormal(const float4& _Left, const float4& _Right)
	{
		return Cross3DReturn(_Left.NormalizeReturn(), _Right.NormalizeReturn()).NormalizeReturn();
	}

	static float4 Cross3DReturn(const float4& _Left, const float4& _Right)
	{
		float4 ReturnValue;
		ReturnValue.x = (_Left.y * _Right.z) - (_Left.z * _Right.y);
		ReturnValue.y = (_Left.z * _Right.x) - (_Left.x * _Right.z);
		ReturnValue.z = (_Left.x * _Right.y) - (_Left.y * _Right.x);
		return ReturnValue;
	}

	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		//            1         1          1          0          0          0
		float Value = _Left.x * _Right.x + _Left.y * _Right.y + _Left.z * _Right.z;
		return Value;
	}

public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float Arr1D[4];
	};

	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}

	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	int hiw() const
	{
		return static_cast<int>(w * 0.5f);
	}

	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	float hw() const
	{
		return w * 0.5f;
	}

	float GetAnagleDegZ()
	{
		return GetAnagleRadZ() * GameEngineMath::RadToDeg;
	}

	float4 RotaitonXDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonXRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	float4 RotaitonYDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonYRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	float4 RotaitonZDegReturn(float _Deg)
	{
		float4 ReturnValue = *this;
		ReturnValue.RotaitonZRad(_Deg * GameEngineMath::DegToRad);
		return ReturnValue;
	}

	void RotaitonXDeg(float _Deg)
	{
		RotaitonXRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotaitonYDeg(float _Deg)
	{
		RotaitonYRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotaitonZDeg(float _Deg)
	{
		RotaitonZRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotaitonXRad(float _Rad);
	void RotaitonYRad(float _Rad);
	void RotaitonZRad(float _Rad);

	float GetAnagleRadZ()
	{
		float4 AngleCheck = (*this);
		AngleCheck.Normalize();

		float Result = acosf(AngleCheck.x);

		if (AngleCheck.y > 0)
		{
			Result = GameEngineMath::PIE2 - Result;
		}
		return Result;

	}

	POINT ToWindowPOINT()
	{
		return POINT(ix(), iy());
	}

	float4 half() const
	{
		return { x * 0.5f,y * 0.5f,z * 0.5f,w };
	}

	bool IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	float Size() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float SizeValue = Size();
		x /= SizeValue;
		y /= SizeValue;
		z /= SizeValue;
	}

	float4 NormalizeReturn() const
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	static float4 Lerp(const float4& Start, const float4& End, float Ratio)
	{
		return Start * (1.0f - Ratio) + (End * Ratio);
	}

	static float4 LerpClamp(const float4& Start, const float4& End, float Ratio)
	{
		if (0 >= Ratio)
		{
			Ratio = 0.0f;
		}

		if (1.0f <= Ratio)
		{
			Ratio = 1.0f;
		}

		return Lerp(Start, End, Ratio);
	}

	float4 operator *(const float _Value) const
	{
		float4 Return;
		Return.x = x * _Value;
		Return.y = y * _Value;
		Return.z = z * _Value;
		return Return;
	}

	bool operator ==(const float4& _Value) const
	{
		return _Value.x == x && _Value.y == y && _Value.z == z;
	}


	float4 operator +(const float4& _Value) const
	{
		float4 Return;
		Return.x = x + _Value.x;
		Return.y = y + _Value.y;
		Return.z = z + _Value.z;
		return Return;
	}

	float4 operator -(const float4& _Value) const
	{
		float4 Return;
		Return.x = x - _Value.x;
		Return.y = y - _Value.y;
		Return.z = z - _Value.z;
		return Return;
	}

	float4 operator *(const float4& _Value) const
	{
		float4 Return;
		Return.x = x * _Value.x;
		Return.y = y * _Value.y;
		Return.z = z * _Value.z;
		return Return;
	}

	float4 operator /(const float4& _Value) const
	{
		float4 Return;
		Return.x = x / _Value.x;
		Return.y = y / _Value.y;
		Return.z = z / _Value.z;
		return Return;
	}

	float4 operator -() const
	{
		return { -x, -y, -z, 1.0f };
	}

	float4& operator +=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;
		return *this;
	}

	float4& operator *=(const float _Value)
	{
		x *= _Value;
		y *= _Value;
		z *= _Value;
		return *this;
	}

	float4& operator *=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;
		return *this;
	}

	float4& operator -=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;
		return *this;
	}

	float4& operator /=(const float4& _Other)
	{
		x /= _Other.x;
		y /= _Other.y;
		z /= _Other.z;
		return *this;
	}

	float4 operator*(const class float4x4& _Other);
	float4& operator*=(const class float4x4& _Other);

	std::string ToString()
	{
		char ArrReturn[256];

		sprintf_s(ArrReturn, "x: %f, y: %f, z: %f, w: %f", x, y, z, w);

		return std::string(ArrReturn);
	}
};

class CollisionData
{
public:
	float4 Position;
	float4 Scale; // x만 원의 반지름으로 보겠습니다.

	float Left() const
	{
		return Position.x - Scale.hx();
	}

	float Right() const
	{
		return Position.x + Scale.hx();
	}

	float Top() const
	{
		return Position.y - Scale.hy();
	}

	float Bot() const
	{
		return Position.y + Scale.hy();
	}

	float4 LeftTop() const
	{
		return float4{ Left(), Top() };
	}

	float4 RightTop() const
	{
		return float4{ Right(), Top() };
	}

	float4 LeftBot() const
	{
		return float4{ Left(), Bot() };
	}

	float4 RightBot() const
	{
		return float4{ Right(), Bot() };
	}
};

class float4x4
{
public:
	static const float4x4 Zero;
	static const int YCount = 4;
	static const int XCount = 4;

public:
	union
	{
		float Arr1D[16];
		float Arr2D[4][4];
		float4 ArrVector[4];

		struct
		{
			float _00;
			float _01;
			float _02;
			float _03;
			float _10;
			float _11;
			float _12;
			float _13;
			float _20;
			float _21;
			float _22;
			float _23;
			float _30;
			float _31;
			float _32;
			float _33;
		};
	};

	void Identity()
	{
		memset(Arr1D, 0, sizeof(float) * 16);
		Arr2D[0][0] = 1.0f;
		Arr2D[1][1] = 1.0f;
		Arr2D[2][2] = 1.0f;
		Arr2D[3][3] = 1.0f;
	}


	// 뷰 행렬을 만들기 위해선 Z(앞, Dir)와 Y(위, Up)가 필요하다.
	// LookAtLH 함수는 외적과 내적이 필요하다.
	// 외적을 통해서 회전해야 하는 방향을 구하고, 내적을 통해서 얼마만큼 돌아야하는지 구하는 것이다.
	void LookAtLH(const float4& _EyePos, const float4& _EyeDir, const float4& _EyeUp)
	{
		Identity();

		float4 EyePos = _EyePos;

		// Up과 Dir를 알기 때문에, Right를 알 수 있다(외적)
		// 셋을 노말라이즈 하기 때문에, 회전행렬이 된다고 할 수 있다.
		float4 EyeDir = _EyeDir.NormalizeReturn();
		float4 EyeUp = _EyeUp;
		float4 Right = float4::Cross3DReturn(EyeUp, EyeDir);
		Right.Normalize();

		float4 UpVector = float4::Cross3DReturn(_EyeDir, Right);
		Right.Normalize();

		float4 NegEyePos = -_EyePos;

		// 플레이어가 원점(0, 0, 0)에 존재한다면, 카메라는 그보다 조금 떨어진 위치(0, 0, -100)에서 플레이어를 바라본다.
		// 뷰 행렬의 원칙은 다른 위치(0, 0, -100)에 존재하는 카메라를 원점(0, 0, 0)으로 이동 회전 시킨 값의 반대값을 액터들에게 적용하는 것이다.

		float D0Value = float4::DotProduct3D(Right, NegEyePos);     // DXValue == 카메라가 이동한 만큼 이동해야하는 액터들의 이동값, D0Value == X값
		float D1Value = float4::DotProduct3D(UpVector, NegEyePos);  // D1Value == Y값
		float D2Value = float4::DotProduct3D(EyeDir, NegEyePos);    // D2Value == Z값

		// 그냥 차이를 구하면 안되는 것인가(NegEyePos만큼 이동시키면 되지 않나?)에 대해서 생각한다면, 여기까지는 이동 과정이기 때문이다. 아직 회전을 적용하지 않았다.
		// 회전을 적용하기 위해선 내적을 통해 벡터의 정사영 값들 (D0Value, D1Value, D2Value)을 구해야 한다.

		ArrVector[0] = { 1, 0, 0, 0 };
		ArrVector[1] = { 0, 1, 0, 0 };
		ArrVector[2] = { 0, 0, 1, 0 };
		ArrVector[3] = { D0Value, D1Value, D2Value, 0 };
	}

	void Scale(const float4& _Value)
	{
		//100, 0 , 0 , 0
		// 0 ,100, 0 , 0
		// 0 , 0 ,100, 0
		// 0 , 0 , 0 , 1

		Identity();
		Arr2D[0][0] = _Value.x;
		Arr2D[1][1] = _Value.y;
		Arr2D[2][2] = _Value.z;
	}

	void Pos(const float4& _Value)
	{
		//  0   1   2   3
		//0 0,  0 , 0 , 0
		//1 0 , 0,  0 , 0
		//2 0 , 0 , 0 , 0
		//3 200, 200 , 200 , 1

		Identity();
		Arr2D[3][0] = _Value.x;
		Arr2D[3][1] = _Value.y;
		Arr2D[3][2] = _Value.z;
	}

	void RotationDeg(const float4& _Deg)
	{
		// 짐벌락 현상이라는 것이 있습니다.
		// 축이 겹치는 이상한 현상이 있는데 그 현상을 해결하려면
		// 곱하는 순서를 바꿔야 해결이 된다.
		// Rot = RotX * RotY * RotZ;

		// 기본적으로 쿼터니온 회전이라는걸 사용하는데 
		// 짐벌락 해결함.
		float4x4 RotX = float4x4::Zero;
		float4x4 RotY = float4x4::Zero;
		float4x4 RotZ = float4x4::Zero;
		RotX.RotationXDeg(_Deg.x);
		RotY.RotationYDeg(_Deg.y);
		RotZ.RotationZDeg(_Deg.z);

		*this = RotX * RotY * RotZ;
	}

	void RotationXDeg(const float _Deg)
	{
		RotationXRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationXRad(const float _Rad)
	{
		Identity();
		Arr2D[1][1] = cosf(_Rad);
		Arr2D[1][2] = sinf(_Rad);
		Arr2D[2][1] = -sinf(_Rad);
		Arr2D[2][2] = cosf(_Rad);
	}

	void RotationYDeg(const float _Deg)
	{
		RotationYRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationYRad(const float _Rad)
	{
		Identity();
		Arr2D[0][0] = cosf(_Rad);
		Arr2D[0][2] = -sinf(_Rad);
		Arr2D[2][0] = sinf(_Rad);
		Arr2D[2][2] = cosf(_Rad);
	}

	void RotationZDeg(const float _Deg)
	{
		RotationZRad(_Deg * GameEngineMath::DegToRad);
	}

	void RotationZRad(const float _Rad)
	{
		Identity();
		Arr2D[0][0] = cosf(_Rad);
		Arr2D[0][1] = sinf(_Rad);
		Arr2D[1][0] = -sinf(_Rad);
		Arr2D[1][1] = cosf(_Rad);
	}

	float4x4 operator*(const float4x4& _Other)
	{
		//  0   0   0   0			   		  0   0   0   0	    0   0   0   0
		//  0,  0 , 0 , 0			   		  0,  0 , 0 , 0	    0,  0 , 0 , 0
		//  0 , 0,  0 , 0          *   		  0 , 0,  0 , 0  =  0 , 0,  0 , 0
		//  0 , 0 , 0 , 0			   		  0 , 0 , 0 , 0	    0 , 0 , 0 , 0

		this->Arr2D;
		_Other.Arr2D;

		float4x4 Return = Zero;
		for (size_t y = 0; y < YCount; y++)
		{
			for (size_t x = 0; x < XCount; x++)
			{
				for (size_t j = 0; j < 4; j++)
				{
					Return.Arr2D[y][x] += Arr2D[y][j] * _Other.Arr2D[j][x];
				}
			}
		}

		return Return;
	}

	float4x4()
	{
		Identity();
	}

	float4x4(float4 _x, float4 _y, float4 _z, float4 _w)
	{
		ArrVector[0] = _x;
		ArrVector[1] = _y;
		ArrVector[2] = _z;
		ArrVector[3] = _w;
	}
};

