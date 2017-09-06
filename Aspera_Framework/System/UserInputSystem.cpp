#include "UserInputSystem.h"

UserInputSystem::UserInputSystem(){}

UserInputSystem::UserInputSystem(const UserInputSystem &){}

UserInputSystem::~UserInputSystem(){}

void UserInputSystem::Initialize()
{
}

void UserInputSystem::Shutdown()
{
}

void UserInputSystem::HandleUserInput(Input* input, vector<GameObject*> gameobjects)
{
	for (auto go : gameobjects)
	{
		if (go->IsSelected())
			if (input->IsF4Toggled())
				go->SetActive(!go->IsActive());
	}
}