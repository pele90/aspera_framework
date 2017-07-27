#ifndef _SYSTEM_H_
#define _SYSTEM_H_

// PRE-PROCESSING DIRECTIVES //
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "Application.h"

class System 
{
public:
	System();
	System(const System&);
	~System();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	Application* m_application;
};

// FUNCTION PROTOTYPES //
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// GLOBALS //
static System* ApplicationHandle = 0;

#endif // !_SYSTEM_H_

