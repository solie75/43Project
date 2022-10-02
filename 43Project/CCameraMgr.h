#pragma once
class CCameraMgr
{
	SINGLE(CCameraMgr);

private:
	Vec m_vLook;
	Vec m_vDiff;

public:
	void SetLook(Vec _vLook) { m_vLook = _vLook; }

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

