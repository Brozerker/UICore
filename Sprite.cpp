#include "Sprite.h"

Sprite::Sprite() 
	:mSprite(nullptr),
	mSpriteTex(nullptr),
	mSpritePosition(D3DXVECTOR3(0, 0, 0)),
	mSpriteVelocity(D3DXVECTOR3(0, 0, 0)),
	mSpriteAcceleration(D3DXVECTOR3(0, 0, 0)),
	mSpriteRotation(0)
{
	
}

Sprite::~Sprite()
{
	if (mSprite) mSprite->Release();
	if (mSpriteTex) mSpriteTex->Release();
}

bool Sprite::onInit(LPDIRECT3DDEVICE9 d3dDevice, LPCSTR suppliedTexturePath)
{
	HRESULT result = D3DXCreateSprite(d3dDevice, &mSprite);
	if (FAILED(result))
	{
		MessageBox(0, "Sprite::Sprite() - Failed to Create Sprite", "Compile Error", MB_OK);
		return false;
	}

	result = D3DXCreateTextureFromFile(d3dDevice, suppliedTexturePath, &mSpriteTex);
	if (FAILED(result))
	{
		MessageBox(0, "Sprite::Sprite() - Failed to create texture from file", "Compile Error", MB_OK);
		return false;
	}
}

void Sprite::onUpdate(float dt)
{
	//Virtual so that it can be overridden to handle particular update code when inherited from.
}

void Sprite::onDraw(LPDIRECT3DDEVICE9 d3dDevice)
{
	//d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0); 
	//d3dDevice->BeginScene(); 
	//mSprite->Begin(D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_DONOTMODIFY_RENDERSTATE);

	d3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	D3DXMATRIX R;
	D3DXMatrixRotationZ(&R, mSpriteRotation);

	mSprite->Draw(mSpriteTex, 0, NULL, 0, D3DCOLOR_XRGB(255, 255, 255));
	mSprite->Flush();
	d3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);

	//mSprite->End();
	//d3dDevice->EndScene();
	//d3dDevice->Present(0, 0, 0, 0);
}

const D3DXVECTOR3 Sprite::getPosition() const
{
	return mSpritePosition;
}

const D3DXVECTOR3 Sprite::getVelocity() const
{
	return mSpriteVelocity;
}

const D3DXVECTOR3 Sprite::getAcceleration() const
{
	return mSpriteAcceleration;
}

const float Sprite::getRotation() const
{
	return mSpriteRotation;
}


void Sprite::setPosition(const D3DXVECTOR3 suppliedPosition)
{
	mSpritePosition = suppliedPosition;
}

void Sprite::setVelocity(const D3DXVECTOR3 suppliedVelocity)
{
	mSpriteVelocity = suppliedVelocity;
}

void Sprite::setAcceleration(const D3DXVECTOR3 suppliedAcceleration)
{
	mSpriteAcceleration = suppliedAcceleration;
}

void Sprite::setRotation(const float suppliedRotation)
{
	mSpriteRotation = suppliedRotation;
}
