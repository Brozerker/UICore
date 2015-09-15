// Wraps initialization of immediate mode Direct Input, and provides 
// information for querying the state of the keyboard and mouse.
#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
//#include <d3d9.h>
//#include <d3dx9.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Graphics;


namespace GSP420
{
	//make it easier for others to refer to the input. They can use INPUT-> instead of
	//DirectInput::Instance()->
#define INPUT DirectInput::Instance()

	class DirectInput
	{
	public:
		static DirectInput* Instance();
		void init(Graphics& graphics, DWORD keyboardCoopFlags, DWORD  mouseCoopFlags);
		void shutdown();

		void Poll();//poll for any keys or mouse activated
		bool KeyDown(unsigned char key);//a key has been pressed
		bool MouseButtonDown(int button);//a mouse button was clicked
		//the amount that the mouse moves this frame
		float MouseDX();
		float MouseDY();
		float MouseDZ();
	private:
		static DirectInput* Singleton;
		// Make private to prevent copying of members of this class.
		DirectInput() {}
		DirectInput(const DirectInput&) {}
		DirectInput& operator=(const DirectInput&) {}
		//D3D devices needed	
		IDirectInput8*			DInput;
		//for keyboard
		IDirectInputDevice8*	Keyboard;
		char					KeyboardState[256];
		//for mouse
		IDirectInputDevice8*	Mouse;
		DIMOUSESTATE2			MouseState;
	};

}