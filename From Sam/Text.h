#pragma once
#include <vector>
#include "D3DUtils.h"

using std::vector;

namespace GFXCore
{
	struct FontData{
		RECT			textBoxDimens;
		wchar_t		strFontName[64];
		D3DCOLOR	textColor;
		int		nFontHeight;
		int		nFontWidth;
		ID3DXFont* pFont;
		bool	bItalics;
	};

	class Text
	{
	public:
		void init(const int startNumFonts = 5);
		int createFont(IDirect3DDevice9* device, const FontData& textCreationInfo);
		void render(const int fontId, const wchar_t* displayText);
		void shutdown();
		inline void onLostDevice();
		inline void onResetDevice();

		Text();
		~Text();

	protected:
		vector<FontData>		fontList;

	private:
		static int	nInternalFontId;
	};

	void Text::onLostDevice() {
		for (unsigned int i = 0; i < fontList.size(); ++i)
			HR(fontList[i].pFont->OnLostDevice());
	}

	void Text::onResetDevice() {
		for (unsigned int i = 0; i < fontList.size(); ++i)
			HR(fontList[i].pFont->OnResetDevice());
	}

}