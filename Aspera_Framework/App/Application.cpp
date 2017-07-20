#include "Application.h"

Application::Application()
{
	m_input = 0;
	m_timer = 0;
	m_fps = 0;
	m_scene = 0;
}

Application::Application(const Application& other) {}

Application::~Application() {}

bool Application::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	#pragma region INPUT

	// Create the input object.
	m_input = new Input;
	if (!m_input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	#pragma endregion

	#pragma region SCENE

	m_scene = new Scene("Level_1");
	if (!m_scene)
	{
		return false;
	}

	result = m_scene->Initialize(hwnd, screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	#pragma endregion

	#pragma region TIMER

	// Create the timer object.
	m_timer = new Timer;
	if (!m_timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	#pragma endregion

	#pragma region FPS

	// Create the fps object.
	m_fps = new Fps;
	if (!m_fps)
	{
		return false;
	}

	// Initialize the fps object.
	m_fps->Initialize();

	#pragma endregion

	return true;
}

void Application::Shutdown()
{
	// Release the scene object.
	if (m_scene)
	{
		m_scene->Shutdown();
		delete m_scene;
		m_scene = 0;
	}

	// Release the fps object.
	if (m_fps)
	{
		delete m_fps;
		m_fps = 0;
	}

	// Release the timer object.
	if (m_timer)
	{
		delete m_timer;
		m_timer = 0;
	}

	// Release the input object.
	if (m_input)
	{
		m_input->Shutdown();
		delete m_input;
		m_input = 0;
	}

	return;
}

bool Application::Frame()
{
	bool result;

	// Update the system stats.
	m_fps->Frame();
	m_timer->Frame();

	// Do the input frame processing.
	result = m_input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the scene processing.
	result = m_scene->Frame(m_input, m_timer->GetTime(), m_fps->GetFps());
	if (!result)
	{
		return false;
	}

	return result;
}

