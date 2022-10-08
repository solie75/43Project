#pragma once

struct tCamEffect
{
	CAMERA_EFFECT	m_eCurEffect;
	float			m_fAccTime;
	float			m_fMaxTime;
};


class CCameraMgr
{
	SINGLE(CCameraMgr);

private:
	Vec m_vLook;
	Vec m_vDiff;

	list<tCamEffect> m_CamEffectList;
	float m_fRatio;

public:
	void SetLook(Vec _vLook) { m_vLook = _vLook; }
	void FadeOut(float _fTerm);
	void FadeIn(float _fTerm);

public:
	void CameraMgrTick();

public:
	Vec GetRenderPos(Vec _vRealPos)
	{
		return _vRealPos - m_vDiff;
	}

	Vec GetRealPos(Vec _vRenderPos)
	{
		return _vRenderPos + m_vDiff;
	}


};

