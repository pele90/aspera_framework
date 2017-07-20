#ifndef _APPLICATION_H_
#define _APPLICATION_H_

/////////////
// GLOBALS //
/////////////

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../MISC/Input.h"
#include "../MISC/Timer.h"
#include "../MISC/Fps.h"
#include "../Scene.h"

class Application
{
public:
	Application();
	Application(const Application&);
	~Application();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	Input* m_input;
	Timer* m_timer;
	Fps* m_fps;
	Scene* m_scene;
};

#endif "_APPLICATION_H_"