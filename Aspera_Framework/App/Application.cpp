#include "Application.h"

Application::Application()
{
	m_Input = 0;
	m_Timer = 0;
	m_Fps = 0;
	m_Scene = 0;
}

Application::Application(const Application& other) {}

Application::~Application() {}

bool Application::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	#pragma region INPUT

	// Create the input object.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	#pragma endregion

	#pragma region SCENE

	m_Scene = new SceneClass("Level_1");
	if (!m_Scene)
	{
		return false;
	}

	result = m_Scene->Initialize(hwnd, screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	#pragma endregion

	#pragma region TIMER

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	#pragma endregion

	#pragma region FPS

	// Create the fps object.
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_Fps->Initialize();

	#pragma endregion

	return true;
}

void Application::Shutdown()
{
	if (m_Scene)
	{
		m_Scene->Shutdown();
		delete m_Scene;
		m_Scene = 0;
	}

	// Release the fps object.
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}

bool Application::Frame()
{
	bool result;

	// Update the system stats.
	m_Fps->Frame();
	m_Timer->Frame();

	// Do the input frame processing.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the scene processing.
	result = m_Scene->Frame(m_Input, m_Timer->GetTime(), m_Fps->GetFps());
	if (!result)
	{
		return false;
	}

	return result;
}

