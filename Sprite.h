#include "Graphic.h"

#include <d3d9.h>
#include <d3dx9.h>
class Sprite : public Graphic {
	
public:
	Sprite();
	virtual ~Sprite();

	bool onInit(LPDIRECT3DDEVICE9 d3dDevice, LPCSTR suppliedTexturePath);
	virtual void onUpdate(float dt);
	virtual void onDraw(LPDIRECT3DDEVICE9 d3dDevice);

	const D3DXVECTOR3 getPosition() const;
	const D3DXVECTOR3 getVelocity() const;
	const D3DXVECTOR3 getAcceleration() const;
	const float getRotation() const;


	void setPosition(const D3DXVECTOR3 suppliedPosition);
	void setVelocity(const D3DXVECTOR3 suppliedVelocity);
	void setAcceleration(const D3DXVECTOR3 suppliedAcceleration);
	void setRotation(const float suppliedRotation);


private:
	ID3DXSprite* mSprite;
	IDirect3DTexture9* mSpriteTex;
	D3DXVECTOR3 mSpritePosition;
	D3DXVECTOR3 mSpriteVelocity;
	D3DXVECTOR3 mSpriteAcceleration;
	float mSpriteRotation;
	
};