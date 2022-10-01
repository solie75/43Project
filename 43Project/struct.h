#pragma once

struct Vec
{
	float x;
	float y;

public:

	void Normalize()// ����ȭ
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

	void operator -= (Vec _vOther)
	{
		x -= _vOther.x;
		y -= _vOther.y;
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

	~Vec()
	{}
};

struct tEvent
{
	EVENT_TYPE eType;
	DWORD_PTR wPARAM;
	DWORD_PTR lPARAM;
};