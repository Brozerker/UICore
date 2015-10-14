#pragma once
#include <vector>
#include "D3DUtils.h"

using std::vector;

namespace GFXCore
{
	struct TexureData {
		IDirect3DTexture9* pTex;
		int		nWidth;
		int		nHeight;
	};
	
	class Textures
	{
	public:
		void init(const int startNumTex = 20);
		int loadTexture(IDirect3DDevice9* device, const wchar_t* fileName);
		void shutdown();
		
		inline IDirect3DTexture9* getTexture(const int id);

		Textures();
		~Textures();

	protected:
		vector<TexureData>	texList;

	private:
		static int nIdGenerator;
	};


	IDirect3DTexture9* GFXCore::Textures::getTexture(const int id)	{ return texList[id].pTex; }
}