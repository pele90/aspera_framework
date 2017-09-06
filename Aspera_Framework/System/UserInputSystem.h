#ifndef _USER_INPUT_SYSTEM_H_
#define _USER_INPUT_SYSTEM_H_

#include "..\MISC\Input.h"
#include "..\Base\GameObject.h"
#include <vector>

class UserInputSystem
{
public:
	UserInputSystem();
	UserInputSystem(const UserInputSystem&);
	~UserInputSystem();

	void Initialize();
	void Shutdown();

	void HandleUserInput(Input* input, vector<GameObject*> gameobjects);

};

#endif // !_USER_INPUT_SYSTEM_H_
