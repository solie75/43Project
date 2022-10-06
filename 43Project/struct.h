#pragma once

struct Vec
{
	float x;
	float y;

public:

	void Normalize()// 정규화
	{
		float fDist = sqrtf(x * x + y * y);
		x /= fDist;
		y /= fDist;
	}

	Vec operator + (Vec _vOther)
	{
		return Vec(x + _vOther.x, y + _vOther.y);
	}
	
	Vec operator - (Vec _vOther)
	{
		return Vec(x - _vOther.x, y - _vOther.y);
	}

	void operator += (Vec _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}


	Vec operator / (float _f)
	{
		return Vec(x / _f, y / _f);
	}

	void operator -= (Vec _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
	}

	void operator /= (float _f)
	{
		x /= _f;
		y /= _f;
	}

public:
	Vec()
		: x(0.f)
		, y(0.f)
	{}

	Vec(float _x, float _y)
		: x(_x), y(_y)
	{}

	Vec(UINT _x, UINT _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{

	}

	~Vec()
	{}
};

struct tEvent
{
	EVENT_TYPE eType;
	DWORD_PTR wPARAM;
	DWORD_PTR lPARAM;
};

struct tAnimFrame
{
	Vec vLeftTop; // Atlas 내에서 가져올 이미지의 최상단 좌표 
	Vec vSize; // 프레임 사이즈
	Vec vOffset; // 추가 이동
	float fDuration; // 해당 프레임 노출 시간
};