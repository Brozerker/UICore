//Created by Darrell Smith, taken from his Applied Development II "Dart"
#include "DirectInput.h"

#include "../D3D9Graphics/GFX.h"//for AppInst and MainWnd
#include "Logger.h"

DirectInput* DirectInput::Singleton = NULL;

DirectInput* DirectInput::Instance()
{
	if (!Singleton)
		Singleton = new DirectInput;
	return Singleton;
}

void DirectInput::init(DWORD keyboardCoopFlags, DWORD  mouseCoopFlags)
{
	//reset mouse and keyboard states
	ZeroMemory(KeyboardState, sizeof(KeyboardState));
	ZeroMemory(&MouseState, sizeof(MouseState));
	//create direct3d object
	if (FAILED(DirectInput8Create(GFX->getAppInstance(), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&DInput, 0)))
	{
		LOGGER->Write(L"Input:Input: Could not create Direct Input 8 Device");
	}
	//create keyboard device
	if (FAILED(DInput->CreateDevice(GUID_SysKeyboard, &Keyboard, 0)))
	{
		LOGGER->Write(L"Input: Input: Could not create Keyboard Device");
	}
	if (FAILED(Keyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		LOGGER->Write(L"Input: Input: Could not set Keyboard Data Format");
	}
	if (FAILED(Keyboard->SetCooperativeLevel(GFX->getHWND(), keyboardCoopFlags)))
	{
		LOGGER->Write(L"Input: Input: Could not set Keyboard Cooperative Level");
	}
	if (FAILED(Keyboard->Acquire()))
	{
		LOGGER->Write(L"Input: Input: Could not acquire Keyboard");
	}
	//create mouse device
	if (FAILED(DInput->CreateDevice(GUID_SysMouse, &Mouse, 0)))
	{
		LOGGER->Write(L"Input: Input: Could not Create Mouse Device");
	}
	if (FAILED(Mouse->SetDataFormat(&c_dfDIMouse2)))
	{
		LOGGER->Write(L"Input: Input: Could not Set Mouse Date Format");
	}
	if (FAILED(Mouse->SetCooperativeLevel(GFX->getHWND(), mouseCoopFlags)))
	{
		LOGGER->Write(L"Input: Input: Could not Set Mouse Cooperative Level");
	}
	if (FAILED(Mouse->Acquire()))
	{
		LOGGER->Write(L"Input: Input: Could not Acquire Mouse");
	}
	//ShowCursor(false);//hide default cursor in window
}

void DirectInput::shutdown()
{
	//release  components
	DInput->Release();
	Keyboard->Unacquire();
	Mouse->Unacquire();
	Keyboard->Release();
	Mouse->Release();
}

void DirectInput::Poll()
{
	// Poll keyboard.
	if (FAILED(Keyboard->GetDeviceState(sizeof(KeyboardState), (void**)&KeyboardState)))
	{
		LOGGER->Write(L"Input: Poll: Keyboard State lost, attempting to reaquire");
		// Keyboard lost, zero out keyboard data structure.
		ZeroMemory(KeyboardState, sizeof(KeyboardState));
		// Try to acquire for next time we poll.
		if (FAILED(Keyboard->Acquire()))
		{
			LOGGER->Write(L"Input : Poll: Could not Reaquire Keyboard");
		}
	}
	// Poll mouse.
	if (FAILED(Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&MouseState)))
	{
		LOGGER->Write(L"Input: Poll: Mouse State lost, attempting to reaquire");
		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&MouseState, sizeof(MouseState));
		// Try to acquire for next time we poll.
		if (FAILED(Mouse->Acquire()))
		{
			LOGGER->Write(L"Input: Poll: Could not Reaquire Mouse");
		}
	}
}
//a key is pressed
bool DirectInput::KeyDown(unsigned char key)
{
	return (KeyboardState[key] & 0x80) != 0;
}
//a mouse button is clicked
bool DirectInput::MouseButtonDown(int button)
{
	return (MouseState.rgbButtons[button] & 0x80) != 0;
}
//the amount the mouse moved in the x direction this frame
float DirectInput::MouseDX()
{
	return (float)MouseState.lX;
}
//the amount the mouse moved in the y direction this frame
float DirectInput::MouseDY()
{
	return (float)MouseState.lY;
}
//the amount the mouse moved in the z direction this frame
float DirectInput::MouseDZ()
{
	return (float)MouseState.lZ;
}

