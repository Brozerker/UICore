#include "Graphic.h"
#include <string>

class UIObject : public Graphic {
	Graphic parent;
	int width, height;
	bool enable;
	std::string text;
	//font

public:
	void Render();
};