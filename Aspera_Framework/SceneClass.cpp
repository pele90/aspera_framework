#include "SceneClass.h"

SceneClass::SceneClass()
{
	m_RenderingSystem = 0;
	m_cameraMovementSystem = 0;
	m_MainCamera = 0;
}

SceneClass::SceneClass(char* name)
{
	m_name = name;
	m_RenderingSystem = 0;
	m_MainCamera = 0;
}

SceneClass::SceneClass(const SceneClass&) {}

SceneClass::~SceneClass() {}

bool SceneClass::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

#pragma region CAMERA MOVEMENT SYSTEM

	m_cameraMovementSystem = new CameraMovementSystem;
	if (!m_cameraMovementSystem)
	{
		return false;
	}

	result = m_cameraMovementSystem->Initialize();
	if (!result)
	{
		return false;
	}

#pragma endregion

#pragma region MAIN CAMERA

	m_MainCamera = new Camera;
	if (!m_MainCamera)
		return false;

	result = m_MainCamera->Initialize();
	if (!result)
		return false;

	// Set camera position for UI.
	m_MainCamera->GetComponent<Transform>("TRANSFORM")->SetPosition(0.0f, 0.0f, -10.0f);
	m_MainCamera->RenderBaseViewMatrix();

	// Set camera position in the world coordinates.
	m_MainCamera->GetComponent<Transform>("TRANSFORM")->SetPosition(0.0f, 10.0f, -10.0f);



#pragma endregion

#pragma region GAMEOBJECTS

	m_GameObjects = vector<GameObject*>();

	Skydome* skydome = new Skydome;
	if (!skydome)
		return false;
	result = skydome->Initialize("../Aspera_Framework/data/skydome/skydome.txt");
	if (!result)
		return false;
	XMFLOAT3 cameraPosition;
	cameraPosition = m_MainCamera->GetComponent<Transform>("TRANSFORM")->GetPosition();
	skydome->GetComponent<Transform>("TRANSFORM")->SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	AddGameObject(skydome);

	Terrain* terrain = new Terrain;
	terrain->Initialize("../Aspera_Framework/data/terrain/setup.txt");
	AddGameObject(terrain);

	/*InstancedCube *cube = new InstancedCube;
	cube->Initialize("../Rastertek/data/cube.txt");
	AddGameObject(cube);*/

	//CreateGameObjects(5);

#pragma endregion

#pragma region RENDERING SYSTEM

	m_RenderingSystem = new RenderingSystem;
	if (!m_RenderingSystem)
	{
		return false;
	}

	result = m_RenderingSystem->Initialize(hwnd, screenWidth, screenHeight, m_GameObjects);
	if (!result)
	{
		return false;
	}

#pragma endregion

	return true;
}

void SceneClass::Shutdown()
{
	m_MainCamera->Shutdown();
	delete m_MainCamera;
	m_MainCamera = 0;

	m_RenderingSystem->Shutdown();
	delete m_RenderingSystem;
	m_RenderingSystem = 0;

	m_cameraMovementSystem->Shutdown();
	delete m_cameraMovementSystem;
	m_cameraMovementSystem = 0;

	for (vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		(*it)->Shutdown();

	m_GameObjects.clear();

}

bool SceneClass::Frame(InputClass* p_input, int p_frameTime, int p_fps)
{
	bool result;

	m_cameraMovementSystem->HandleMovementInput(p_input, m_MainCamera, p_frameTime);

	// Process rendering 
	result = m_RenderingSystem->Frame(m_GameObjects, m_MainCamera, p_fps);
	if (!result)
	{
		return false;
	}

	return true;
}

void SceneClass::AddGameObject(GameObject* gameobject)
{
	m_GameObjects.push_back(gameobject);
}

void SceneClass::RemoveGameObject(GameObject* gameObject)
{
	vector<GameObject*>::iterator iter = find_if(m_GameObjects.begin(), m_GameObjects.end(), [gameObject](GameObject* p)->bool { return gameObject->GetName() == p->GetName(); });

	if (iter != m_GameObjects.end())
	{
		(*iter)->Shutdown();
		m_GameObjects.erase(iter);
	}
}

void SceneClass::CreateDummyObjects(int count)
{
	for (int i = 0; i < count; ++i) {
		Cube* monkey = new Cube;
		monkey->Initialize("../Aspera_Framework/data/models/cube.txt");
		monkey->GetComponent<Transform>("TRANSFORM")->SetPosition(i * 3.0f, 8.0f, 0.0f);
		AddGameObject(monkey);
	}
}

void SceneClass::CreateGameObjects(int count)
{
	ModelMesh* mesh = new ModelMesh;
	mesh->Initialize("../Aspera_Framework/data/models/teapot.txt");
	Renderer* renderer = new Renderer;
	vector<string> textureIds = vector<string>{ "dirt01d" };
	renderer->Initialize(ShaderType::TEXTURE, textureIds);

	for (int i = 0; i < count; ++i) {
		Prefab* monkey = new Prefab;
		Transform* position = new Transform;
		position->SetPosition(i * 200.0f, 50.0f, i * 200.0f);
		//position->SetPosition(512.0f, 50.0f, 512.0f);
		monkey->AddComponent(position);
		monkey->AddComponent(mesh);
		monkey->AddComponent(renderer);
		AddGameObject(monkey);
	}
}
