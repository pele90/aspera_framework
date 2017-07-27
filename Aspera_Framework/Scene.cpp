#include "Scene.h"

Scene::Scene()
{
	m_name = "DEFAULT_SCENE";
	m_RenderingSystem = 0;
	m_cameraMovementSystem = 0;
	m_MainCamera = 0;
}

Scene::Scene(char* name)
{
	m_name = name;
	m_RenderingSystem = 0;
	m_cameraMovementSystem = 0;
	m_MainCamera = 0;
}

Scene::Scene(const Scene&) {}

Scene::~Scene() {}

bool Scene::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

#pragma region MESSAGE ALERT

	m_messageAlert = MessageAlert();
	m_messageAlert.Initialize(hwnd);

#pragma endregion

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
	m_MainCamera->GetComponent<Transform>()->SetPosition(0.0f, 0.0f, -10.0f);
	m_MainCamera->RenderBaseViewMatrix();

	// Set camera position in the world coordinates.
	m_MainCamera->GetComponent<Transform>()->SetPosition(0.0f, 10.0f, -10.0f);



#pragma endregion

#pragma region GAMEOBJECTS

	m_GameObjects = vector<GameObject*>();

	result = CreateSkydome();
	if (!result)
		return false;

	/*result = CreateTerrain();
	if (!result)
		return false;*/


	CreateGameObjects(1);

	if (!CreateCube(3.0f, 0.5f, -1.5f))
		return false;

	if (!CreateCube(1.0f, 0.5f, 0.0f))
		return false;

	if (!CreateCube(-1.5f, 0.5f, -3.0f))
		return false;

	// Create green light
	if (!CreateLight(-6.0f, 10.0f, 6.0f, XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f)))
		return false;

	// Create blue light
	if (!CreateLight(-6.0f, 20.0f, -6.0f, XMFLOAT4(0.0f, 0.0f, 1.0f, 0.0f)))
		return false;

	 //Create red light
	if (!CreateLight(6.0f, 5.0f, 6.0f, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f)))
		return false;


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

void Scene::Shutdown()
{
	if (m_MainCamera)
	{
		m_MainCamera->Shutdown();
		delete m_MainCamera;
		m_MainCamera = 0;
	}

	if (m_RenderingSystem)
	{
		m_RenderingSystem->Shutdown();
		delete m_RenderingSystem;
		m_RenderingSystem = 0;
	}
	
	if (m_cameraMovementSystem)
	{
		m_cameraMovementSystem->Shutdown();
		delete m_cameraMovementSystem;
		m_cameraMovementSystem = 0;
	}

	for (vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
		(*it)->Shutdown();

	m_GameObjects.clear();

}

bool Scene::Frame(Input* p_input, float p_frameTime, int p_fps)
{
	bool result;

	// Process systems

	// System for handling user input such as adding gameobjects or removing them
	// example: m_UserInputSystem->HandleUserInput(p_input, m_MainCamera); 

	m_cameraMovementSystem->HandleMovementInput(p_input, m_MainCamera, p_frameTime);

	result = m_RenderingSystem->Frame(m_GameObjects, m_MainCamera, p_fps);
	if (!result)
		return false;

	return true;
}

void Scene::AddGameObject(GameObject* gameobject)
{
	m_GameObjects.push_back(gameobject);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
	vector<GameObject*>::iterator iter = find_if(m_GameObjects.begin(), m_GameObjects.end(), [gameObject](GameObject* p)->bool { return gameObject->GetName() == p->GetName(); });

	if (iter != m_GameObjects.end())
	{
		(*iter)->Shutdown();
		m_GameObjects.erase(iter);
	}
}

void Scene::CreateGameObjects(int count)
{
	ModelMesh* mesh = new ModelMesh;
	mesh->Initialize("../Aspera_Framework/data/models/plane01.txt");
	Renderer* renderer = new Renderer;
	vector<string> textureIds = vector<string>{ "stone01d" };
	renderer->Initialize(ShaderType::TEXTURE, textureIds);

	for (int i = 1; i <= count; ++i) {
		Prefab* monkey = new Prefab;
		Transform* position = new Transform;
		position->SetPosition(0.0f, 0.0f, 0.0f);
		monkey->AddComponent(position);
		monkey->AddComponent(mesh);
		monkey->AddComponent(renderer);
		AddGameObject(monkey);
	}
}

bool Scene::CreateSkydome()
{
	bool result;

	Skydome* skydome = new Skydome;
	if (!skydome)
		return false;
	result = skydome->Initialize("../Aspera_Framework/data/skydome/skydome.txt");
	if (!result)
		return false;
	XMFLOAT3 cameraPosition;
	cameraPosition = m_MainCamera->GetComponent<Transform>()->GetPosition();
	skydome->GetComponent<Transform>()->SetPosition(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	AddGameObject(skydome);

	return true;
}

bool Scene::CreateTerrain()
{
	Terrain* terrain = new Terrain;
	terrain->Initialize("../Aspera_Framework/data/terrain/setup.txt");
	AddGameObject(terrain);

	return true;
}

bool Scene::CreateCube(float x, float y, float z)
{
	bool result;

	Prefab* prefab = new Prefab;

	ModelMesh* mesh = new ModelMesh;
	result = mesh->Initialize("../Aspera_Framework/data/models/cube.txt");
	if (!result) 
	{
		m_messageAlert.ShowMessage(L"ModelMesh could not be initialized in Scene::CreateCube", L"Error");
		return false;
	}
	
	prefab->AddComponent(mesh);

	Renderer* renderer = new Renderer;
	vector<string> textureIds = vector<string>{ "wall" };
	result = renderer->Initialize(ShaderType::TEXTURE, textureIds);
	if (!result)
		return false;
	prefab->AddComponent(renderer);


	Transform* position = new Transform;
	position->SetPosition(x, y, z);
	prefab->AddComponent(position);

	AddGameObject(prefab);

	return true;

}

bool Scene::CreateLight(float x, float y, float z, XMFLOAT4 color)
{
	bool result;

	DirectionalLight* light;

	light = new DirectionalLight;
	result = light->Initialize();
	if (!result)
		return false;

	light->GetComponent<Transform>()->SetPosition(x, y, z);
	light->GetComponent<Light>()->SetDiffuseColor(color);
	light->GetComponent<Light>()->SetAmbientColor(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f));
	AddGameObject(light);

	return true;

}