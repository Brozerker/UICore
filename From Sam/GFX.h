#pragma once
#include <list>
#include "D3DCore.h"
#include "Textures.h"
#include "Models.h"
#include "Camera.h"
#include "Text.h"
#include "Sprites.h"
//#include "ABC.h"
// TODO: remove later
#include "DirectInput.h"

#pragma comment (lib, "E:\\School Materials\\GSP420\\Week 3\\GraphicsCore\\Debug\\D3D9GraphicsD.lib")

#define GFX		GFXCore::Graphics::get()

namespace GFXCore
{
	class Graphics
	{
	public:
		bool initGFX(const HINSTANCE hInst, const wchar_t* wndCaption,
						  const int width = 1024, const int height = 768,
						  const D3DDEVTYPE requestedDevtype = D3DDEVTYPE_HAL,
						  const DWORD requestedVP = D3DCREATE_HARDWARE_VERTEXPROCESSING);
		void initLists(const int numStartTexs = 20, const int numStartModels = 10, const int numStartFonts = 5, const int numStartSprites = 15);
		void onLostDevice();
		void onResetDevice();
		void shutdown();

		int loadTexture(const wchar_t* fileName);
		int loadModel(const wchar_t* fileName, 
							const D3DXVECTOR3& initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							const D3DXVECTOR3& initRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							const D3DXVECTOR3& initScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f),
							DWORD options = D3DXMESH_MANAGED);
		int loadFont(const FontData& fontData);
		int loadSprite(const wchar_t* fileName, 
							const D3DXVECTOR3& initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
							D3DCOLOR initColor = D3DCOLOR_RGBA(255, 255, 255, 255),
							RECT* clipRect = NULL);

		inline D3DCore* d3d();
		inline Textures& textures();
		inline Models& models();
		inline Camera& camera();
		inline Text& text();
		inline Sprites& sprites();

		static inline Graphics* get();

	protected:
		Textures		texs;
		Models		modls;
		Camera		cam;
		Text			words;
		Sprites		images;

	private:
		static Graphics*	pInstance;

		static inline void del();

		Graphics() {}
		Graphics(const Graphics&);
		~Graphics() {}
	};

	
	D3DCore* Graphics::d3d()				{ return D3DCore::get(); }
	Textures& Graphics::textures()		{ return texs; }
	Models& Graphics::models() 			{ return modls; }
	Camera& Graphics::camera() 		{ return cam; }
	Text& Graphics::text() 					{ return words; }
	Sprites& Graphics::sprites()			{ return images; }
	Graphics* Graphics::get()	{
		if (NULL == pInstance) 
			pInstance = new Graphics;
		return pInstance;
	}
	void Graphics::del() {
		if (pInstance) {
			delete pInstance;
			pInstance = NULL;
		}
	}
}