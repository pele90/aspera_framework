#ifndef _SCENECLASS_H_
#define _SCENECLASS_H_

#pragma region INCLUDES

#include <vector>
#include <algorithm>

#include "D3D\D3DClass.h"

#include "Base\GameObject.h"
#include "Base\Prefab.h"

#include "Manager\ShaderManagerClass.h"
#include "Manager\TextureManagerClass.h"

#include "Gameobject\Camera.h"
#include "Gameobject\Cube.h"
#include "Gameobject\InstancedCube.h"
#include "Gameobject\Terrain.h"
#include "Gameobject\Skydome.h"
#include "Gameobject\DirectionalLight.h"

#include "System\RenderingSystem.h"
#include "System\CameraMovementSystem.h"

#include "MISC\InputClass.h"

#pragma endregion

using namespace std;

class SceneClass
{
public:
	SceneClass();
	SceneClass(char*);
	SceneClass(const SceneClass&);
	~SceneClass();

	bool Initialize(HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	bool Frame(InputClass*,int, int);

	void AddGameObject(GameObject*);
	void RemoveGameObject(GameObject*);
	void CreateDummyObjects(int);
	bool CreateSkydome();
	bool CreateTerrain();
	bool CreateCube(float, float, float);
	bool CreateLight(float, float, float, XMFLOAT4);

private:
	void CreateGameObjects(int);

private:
	char* m_name;
	vector<GameObject*> m_GameObjects;
	RenderingSystem* m_RenderingSystem;
	CameraMovementSystem* m_cameraMovementSystem;
	Camera* m_MainCamera;
	
};

#endif // !_SCENECLASS_H_

