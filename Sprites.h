#pragma once
#include <vector>
#include "D3DUtils.h"
#include "Textures.h"


namespace GFXCore
{
	struct SpriteData {
		D3DXVECTOR3	center;
		D3DXVECTOR3	position;
		RECT					clipRect;
		D3DCOLOR			color;
		int						nTextureId;
		bool					bHasClipRect;
	};

	class Sprites 
	{
	public:
		void init(IDirect3DDevice9* device, const int startNumSprites = 15);
		int loadSprite(IDirect3DDevice9* device, const wchar_t* fileName, 
							Textures& textures, 
							const D3DXVECTOR3& initPos, 
							const D3DCOLOR initColor = D3DCOLOR_RGBA(255, 255, 0, 255),
							RECT* clipRect = NULL);
		void update(const int id, const D3DXVECTOR3& newPos);
		void shutdow();
		void render(Textures& textures);

		inline SpriteData&	getSprite(const int id);

		Sprites();
		~Sprites();

	protected:
		std::vector<SpriteData>	spriteList;

		ID3DXSprite*		pSprite;

	private:
		static int nIdGenerator;
	};

	SpriteData& Sprites::getSprite(const int id)		{ return spriteList[id]; }
}