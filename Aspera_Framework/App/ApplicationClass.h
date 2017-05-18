#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_

/////////////
// GLOBALS //
/////////////

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../MISC/Inputclass.h"
#include "../MISC/TimerClass.h"
#include "../MISC/FpsClass.h"
#include "../SceneClass.h"

class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	InputClass* m_Input;
	TimerClass* m_Timer;
	FpsClass* m_Fps;
	SceneClass* m_Scene;
};

#endif "_APPLICATIONCLASS_H_"