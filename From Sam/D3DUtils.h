#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>

#include <tchar.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxerr.lib")

#define ReleaseCom(p) { if(p) { p->Release(); p = NULL; }}
#define ErrorMsg(s, c)	MessageBox(NULL, s, c, MB_ICONERROR)

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                      \
		{                                                  \
		HRESULT hr = x;                                \
		if (FAILED(hr))                                 \
				{                                              \
			DXTrace(__FILE__, __LINE__, hr, _T(#x), TRUE); PostQuitMessage(0);\
				}                                              \
		}
#endif

#else
#ifndef HR
#define HR(x) x;
#endif
#endif 

namespace GFXCore
{
	//===============================================================
	// randomness
	inline float getRandomFloat(const float min, const float max);
	inline void getRandomVec(D3DXVECTOR3& vOut);

	//===============================================================
	// Colors 
	const D3DXCOLOR WHITE(1.0f, 1.0f, 1.0f, 1.0f);
	const D3DXCOLOR BLACK(0.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR RED(1.0f, 0.0f, 0.0f, 1.0f);
	const D3DXCOLOR GREEN(0.0f, 1.0f, 0.0f, 1.0f);
	const D3DXCOLOR BLUE(0.0f, 0.0f, 1.0f, 1.0f);

	float getRandomFloat(const float min, const float max)
	{
		if (min >= max) // bad input
			return min;

		// Get random float in [0, 1] interval.
		float f = (rand() % 10001) * 0.0001f;

		return (f * (max - min)) + min;
	}

	void getRandomVec(D3DXVECTOR3& vOut)
	{
		vOut.x = getRandomFloat(-1.0f, 1.0f);
		vOut.y = getRandomFloat(-1.0f, 1.0f);
		vOut.z = getRandomFloat(-1.0f, 1.0f);

		// Project onto unit sphere.
		D3DXVec3Normalize(&vOut, &vOut);
	}
}