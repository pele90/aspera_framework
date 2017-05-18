#ifndef _SCENECLASS_H_
#define _SCENECLASS_H_

#include <vector>
#include <algorithm>

#include "D3D/D3DClass.h"

#include "BASE/GameObject.h"
#include "BASE/Prefab.h"

#include "MANAGER/ShaderManagerClass.h"
#include "MANAGER/TextureManagerClass.h"

#include "GAMEOBJECT/Camera.h"
#include "GAMEOBJECT/Cube.h"
#include "GAMEOBJECT/InstancedCube.h"
#include "GAMEOBJECT/Terrain.h"
#include "GAMEOBJECT/Skydome.h"

#include "SYSTEM/RenderingSystem.h"
#include "SYSTEM/CameraMovementSystem.h"

#include "MISC/InputClass.h"


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

