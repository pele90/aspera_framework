#include "RenderingSystem.h"

RenderingSystem::RenderingSystem()
{
	m_Direct3D = 0;
	m_ShaderManager = 0;
	m_TextureManager = 0;
	m_userInterface = 0;
}

RenderingSystem::~RenderingSystem()
{
}

bool RenderingSystem::Initialize(HWND hwnd, int screenWidth, int screenHeight, vector<GameObject*> gameObjects)
{
	bool result;

#pragma region D3D

	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

#pragma endregion

#pragma region SHADER MANAGER

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

#pragma endregion

#pragma region TEXTURE MANAGER

	// Create the texture manager object.
	m_TextureManager = new TextureManagerClass;
	if (!m_TextureManager)
	{
		return false;
	}

	// TODO: make function to load all needed textures
	// Initialize the texture manager object.
	/*result = m_TextureManager->Initialize(10);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture manager object.", L"Error", MB_OK);
		return false;
	}*/

	// Load textures into the texture manager.
	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../Aspera_Framework/data/textures/tga/dirt01d.tga", "dirt01d");
	if (!result)
	{
		return false;
	}

	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../Aspera_Framework/data/textures/tga/dirt01n.tga", "dirt01n");
	if (!result)
	{
		return false;
	}

	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../Aspera_Framework/data/textures/tga/test.tga", "test");
	if (!result)
	{
		return false;
	}

#pragma endregion

#pragma region USERINTERFACE

	m_userInterface = new UserInterfaceClass;
	if (!m_userInterface)
		return false;

	result = m_userInterface->Initialize(m_Direct3D, screenHeight, screenWidth);
	if (!result)
		return false;

#pragma endregion

	for (auto gameobject : gameObjects)
	{
		m_uninitializedGameObjects.push_back(gameobject);
	}

	InitializeGameObjects();

	return true;
}

bool RenderingSystem::InitializeGameObjects()
{
	bool result;

	for (int i = 0; i < m_uninitializedGameObjects.size(); ++i)
	{
		GameObject* go = m_uninitializedGameObjects.at(i);
		if (go->GetComponent<ModelMesh>("MODEL_MESH") != NULL)
		{
			result = go->GetComponent<ModelMesh>("MODEL_MESH")->InitializeBuffers(m_Direct3D->GetDevice());
			m_initializedGameObjects.push_back(go);
		}
		else if (go->GetComponent<TerrainMesh>("TERRAIN_MESH") != NULL)
		{
			result = go->GetComponent<TerrainMesh>("TERRAIN_MESH")->InitializeBuffers(m_Direct3D->GetDevice());
			m_initializedGameObjects.push_back(go);
		}
	}

	m_uninitializedGameObjects.clear();

	return true;
}

void RenderingSystem::Shutdown()
{
	// Release the texture manager object.
	if (m_TextureManager)
	{
		m_TextureManager->Shutdown();
		delete m_TextureManager;
		m_TextureManager = 0;
	}

	// Release the shader manager object.
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the userinterface object.
	if (m_userInterface)
	{
		m_userInterface->Shutdown();
		delete m_userInterface;
		m_userInterface = 0;
	}
}

bool RenderingSystem::Frame(vector<GameObject*> gameobjects, Camera* camera, int p_fps)
{
	bool result;

	camera->RenderViewMatrix();

	m_Direct3D->GetWorldMatrix(m_worldMatrix);
	camera->GetViewMatrix(m_viewMatrix);
	m_Direct3D->GetProjectionMatrix(m_projectionMatrix);
	camera->GetBaseViewMatrix(m_baseViewMatrix);
	m_Direct3D->GetOrthoMatrix(m_orthographicMatrix);

	Transform* cameraTransform = camera->GetComponent<Transform>("TRANSFORM");

	for (auto go : gameobjects) {
		if(go->GetName() == "SkydomeGO")
			go->GetComponent<Transform>("TRANSFORM")->SetTransform(*cameraTransform);
	}

	// process user interface frame
	m_userInterface->Frame(m_Direct3D->GetDeviceContext(), p_fps, cameraTransform->GetPosition());

	result = Render(camera);
	if (!result)
		return false;

	return true;
}

bool RenderingSystem::Render(Camera* camera)
{
	bool result;

	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// render gameobjects
	for (vector<GameObject*>::iterator iter = m_initializedGameObjects.begin(); iter != m_initializedGameObjects.end(); ++iter)
	{
		XMFLOAT3 position = (*iter)->GetComponent<Transform>("TRANSFORM")->GetPosition();
		Renderer* renderer = (*iter)->GetComponent<Renderer>("RENDERER");
		Mesh* mesh = (*iter)->GetComponent<Mesh>();

		switch (mesh->GetMeshType())
		{
		case MeshType::TERRAIN_MESH:

			// Translate the model to be custom position.
			m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

			// Turn the Z buffer back and back face culling on.
			m_Direct3D->TurnZBufferOn();
			m_Direct3D->TurnOnCulling();

			BindBuffer(mesh);

			if (!RenderWithShader(mesh, ShaderType::TERRAIN, renderer->GetTextureIds()))
				return false;

			if (!RenderWithShader(mesh, ShaderType::TEXTURE, renderer->GetTextureIds()))
				return false;

			m_Direct3D->GetWorldMatrix(m_worldMatrix);

			// Turn the Z buffer back and back face culling off.
			m_Direct3D->TurnZBufferOn();
			m_Direct3D->TurnOnCulling();
			break;
		case MeshType::D3INSTANCE_MESH:

			break;
		default:

			if (renderer->GetShaderType() == ShaderType::SKYDOME)
			{
				// Turn off back face culling and turn off the Z buffer if skybox.
				m_Direct3D->TurnOffCulling();
				m_Direct3D->TurnZBufferOff();
			}

			// Translate the model to be custom position.
			m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

			BindBuffer(mesh);

			if (!RenderWithShader(mesh, renderer->GetShaderType(), renderer->GetTextureIds()))
				return false;

			// Reset world matrix
			m_Direct3D->GetWorldMatrix(m_worldMatrix);

			if (renderer->GetShaderType() == ShaderType::SKYDOME)
			{
				// Turn the Z buffer back and back face culling off.
				m_Direct3D->TurnZBufferOn();
				m_Direct3D->TurnOnCulling();
			}

			break;
		}

		if ((*iter)->GetName() == "InstancedCubeGO")
		{
			InstancingMesh* mesh = (*iter)->GetComponent<InstancingMesh>("INSTANCING_MESH");
			if (mesh != NULL)
			{
				// Load buffers and bind to the device context (GPU)
				if (!LoadBuffersAndBind(mesh))
					return false;

				if (!RenderWithShader(mesh, renderer->GetShaderType(), renderer->GetTextureIds()))
					return false;
			}
		}

	}

	// render user interface
	result = m_userInterface->Render(m_Direct3D, m_ShaderManager, m_worldMatrix, m_baseViewMatrix, m_orthographicMatrix);
	if (!result)
		return false;

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

bool RenderingSystem::LoadBuffersAndBind(Mesh* mesh)
{
	bool result;

	result = mesh->InitializeBuffers(m_Direct3D->GetDevice());
	if (!result)
		return false;

	mesh->Render(m_Direct3D->GetDeviceContext());

	return true;
}

bool RenderingSystem::RenderWithShader(Mesh* mesh, ShaderType shaderType, vector<string> textureIds)
{
	bool result;

	switch (shaderType)
	{
	case COLOR:
		result = m_ShaderManager->RenderColorShader(m_Direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix);
		if (!result)
			return false;
		break;

	case TEXTURE:
		result = m_ShaderManager->RenderTextureShader(m_Direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(textureIds.at(0)));
		if (!result)
			return false;
		break;

	case TEXTURE_INSTANCED:
		result = m_ShaderManager->RenderTextureShaderInstanced(m_Direct3D->GetDeviceContext(), mesh->GetVertexCount(), mesh->GetInstanceCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(textureIds.at(0)));
		if (!result)
			return false;
		break;

	case LIGHT:
		//result = m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(0));
		//if (!result)
			//return false;
		break;

	case TERRAIN:
		result = m_ShaderManager->RenderTerrainShader(m_Direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(textureIds.at(0)), m_TextureManager->GetTexture(textureIds.at(1)), XMFLOAT3(0.0f, -1.0f, 0.0), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		if (!result)
			return false;
		break;

	case SKYDOME:
		result = m_ShaderManager->RenderSkyDomeShader(m_Direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, XMFLOAT4(0.0f, 0.05f, 0.6f, 1.0f), XMFLOAT4(0.0f, 0.5f, 0.8f, 1.0f));
		if (!result)
			return false;
		break;

	case FONT:
		/*result = m_ShaderManager->RenderFontShader(m_Direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(textureIds.at(0)));
		if (!result)
			return false;*/
		break;
	}

	return true;
}

bool RenderingSystem::BindBuffer(Mesh *mesh)
{
	bool result;

	mesh->Render(m_Direct3D->GetDeviceContext());

	return true;
}

bool RenderingSystem::LoadBuffer(Mesh *mesh)
{
	bool result;

	result = mesh->InitializeBuffers(m_Direct3D->GetDevice());
	if (!result)
		return false;

	return true;
}