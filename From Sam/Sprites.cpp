#include "Sprites.h"

using std::vector;
using namespace GFXCore;

int Sprites::nIdGenerator = -1;

Sprites::Sprites()
{
}


Sprites::~Sprites()
{
}

void GFXCore::Sprites::init(IDirect3DDevice9* device, const int startNumSprites /*= 15*/)
{
	spriteList.reserve(startNumSprites);

	HR(D3DXCreateSprite(device, &pSprite));
}

int GFXCore::Sprites::loadSprite(IDirect3DDevice9* device, const wchar_t* fileName, Textures& textures, const D3DXVECTOR3& initPos, const D3DCOLOR initColor /*= D3DCOLOR_ARGB(255, 255, 255, 255)*/, RECT* clipRect /*= NULL*/)
{
	SpriteData newSprite;
	memset(&newSprite, NULL, sizeof(SpriteData));

	newSprite.nTextureId = textures.loadTexture(device, fileName);
	if (-1 == newSprite.nTextureId)
		return -1;

	newSprite.position = initPos;
	newSprite.color = initColor;
 	newSprite.center.x = (float)textures.getTextureWidth(newSprite.nTextureId) * 0.5f;
 	newSprite.center.y = (float)textures.getTextureHeight(newSprite.nTextureId) * 0.5f;
	if (NULL != clipRect) {
		newSprite.clipRect = *clipRect;
		newSprite.bHasClipRect = true;
	}

	spriteList.push_back(newSprite);

	return ++nIdGenerator;
}

void Sprites::shutdow()
{
	ReleaseCom(pSprite);

	spriteList.clear();
	spriteList.resize(0);
}

void GFXCore::Sprites::render(Textures& textures)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (unsigned int i = 0; i < spriteList.size(); ++i) {
		HRESULT hr = pSprite->Draw(textures.getTexture(spriteList[i].nTextureId),
												spriteList[i].bHasClipRect == true ? &spriteList[i].clipRect : NULL,
												NULL/*&spriteList[i].center*/,
												NULL/*&spriteList[i].position*/,
												spriteList[i].color);

		if (FAILED(hr))
			ErrorMsg(L"Sprite Draw Failure!", L"Sprites::render()");
	}
	pSprite->End();
}

void GFXCore::Sprites::update(const int id, const D3DXVECTOR3& newPos)
{
	spriteList[id].position = newPos;
}
