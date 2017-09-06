#ifndef _SCENECLASS_H_
#define _SCENECLASS_H_

#pragma region INCLUDES

#include <vector>
#include <algorithm>

#include "D3D\D3D.h"

#include "Base\GameObject.h"
#include "Base\Prefab.h"
#include "Manager\ShaderManager.h"
#include "Manager\TextureManager.h"
#include "Gameobject\Camera.h"
#include "Gameobject\Cube.h"
#include "Gameobject\InstancedCube.h"
#include "Gameobject\Terrain.h"
#include "Gameobject\Skydome.h"
#include "Gameobject\DirectionalLight.h"
#include "System\RenderingSystem.h"
#include "System\CameraMovementSystem.h"
#include "MISC\Input.h"
#include "MISC\MessageAlert.h"
#include "System\UserInputSystem.h"

#pragma endregion

using namespace std;

class Scene
{
public:
	Scene();
	Scene(char*);
	Scene(const Scene&);
	~Scene();

	bool Initialize(HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	bool Frame(Input*,float, int);

	void AddGameObject(GameObject*);
	void RemoveGameObject(GameObject*);
	bool CreateSkydome();
	bool CreateTerrain();
	bool CreateCube(float, float, float);
	bool CreateLight(float x, float y, float z, XMFLOAT4 color, char* name);
	bool CreateTree(float, float, float);

private:
	void CreateGameObjects(int);

private:
	char* m_name;
	vector<GameObject*> m_gameObjects;
	RenderingSystem* m_RenderingSystem;
	CameraMovementSystem* m_cameraMovementSystem;
	UserInputSystem* m_userInputSystem;
	Camera* m_MainCamera;
	MessageAlert m_messageAlert;
};

#endif // !_SCENECLASS_H_

