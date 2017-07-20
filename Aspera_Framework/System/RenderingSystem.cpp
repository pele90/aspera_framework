#include "RenderingSystem.h"

RenderingSystem::RenderingSystem()
{
	m_direct3D = 0;
	m_ShaderManager = 0;
	m_TextureManager = 0;
	m_userInterface = 0;
	m_RenderTexture = 0;
	m_DebugWindow = 0;
}

RenderingSystem::~RenderingSystem() {}

bool RenderingSystem::Initialize(HWND hwnd, int screenWidth, int screenHeight, vector<GameObject*> gameObjects)
{
	bool result;

#pragma region D3D

	// Create the Direct3D object.
	m_direct3D = new D3D;
	if (!m_direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

#pragma endregion

#pragma region SHADER MANAGER

	// Create the shader manager object.
	m_ShaderManager = new ShaderManager;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

#pragma endregion

#pragma region TEXTURE MANAGER

	// Create the texture manager object.
	m_TextureManager = new TextureManager;
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
	result = m_TextureManager->LoadTexture(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), "../Aspera_Framework/data/textures/tga/stone01.tga", "stone01d");
	if (!result)
	{
		return false;
	}

	result = m_TextureManager->LoadTexture(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), "../Aspera_Framework/data/textures/tga/dirt01d.tga", "dirt01d");
	if (!result)
	{
		return false;
	}

	result = m_TextureManager->LoadTexture(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), "../Aspera_Framework/data/textures/tga/dirt01n.tga", "dirt01n");
	if (!result)
	{
		return false;
	}

	result = m_TextureManager->LoadTexture(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), "../Aspera_Framework/data/textures/tga/test.tga", "test");
	if (!result)
	{
		return false;
	}

	result = m_TextureManager->LoadTexture(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), "../Aspera_Framework/data/textures/tga/wall.tga", "wall");
	if (!result)
	{
		return false;
	}

#pragma endregion

#pragma region USERINTERFACE

	m_userInterface = new UserInterface;
	if (!m_userInterface)
		return false;

	result = m_userInterface->Initialize(m_direct3D, screenHeight, screenWidth);
	if (!result)
		return false;

#pragma endregion

#pragma region RENDER TEXTURE

	// Create the render to texture object.
	m_RenderTexture = new RenderTexture;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_direct3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		return false;
	}

#pragma endregion

#pragma region DEBUG WINDOW

	// Create the debug window object.
	m_DebugWindow = new DebugWindow;
	if (!m_DebugWindow)
	{
		return false;
	}

	// Initialize the debug window object.
	result = m_DebugWindow->Initialize(m_direct3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

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
			result = go->GetComponent<ModelMesh>("MODEL_MESH")->InitializeBuffers(m_direct3D->GetDevice());
			m_initializedGameObjects.push_back(go);
		}
		else if (go->GetComponent<TerrainCell>("TERRAIN_CELL") != NULL)
		{
			((Terrain*)go)->LoadTerrainCells(m_direct3D->GetDevice());
			((Terrain*)go)->ShutdownTerrainModel();
			m_initializedGameObjects.push_back(go);
		}
		else if (go->GetName() == "DIRECTIONAL_LIGHT") {
			m_initializedGameObjects.push_back(go);

			RenderTexture* rt = new RenderTexture;
			result = rt->Initialize(m_direct3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
			if (!result)
				return false;
			m_renderToTextures.push_back(rt);
		}
	}

	m_uninitializedGameObjects.clear();

	return true;
}

void RenderingSystem::Shutdown()
{
	// Release the debug window object.
	if (m_DebugWindow)
	{
		m_DebugWindow->Shutdown();
		delete m_DebugWindow;
		m_DebugWindow = 0;
	}

	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

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
	if (m_direct3D)
	{
		m_direct3D->Shutdown();
		delete m_direct3D;
		m_direct3D = 0;
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
	vector<DirectionalLight*> lights;

	camera->RenderViewMatrix();

	m_direct3D->GetWorldMatrix(m_worldMatrix);
	camera->GetViewMatrix(m_viewMatrix);
	m_direct3D->GetProjectionMatrix(m_projectionMatrix);
	camera->GetBaseViewMatrix(m_baseViewMatrix);
	m_direct3D->GetOrthoMatrix(m_orthographicMatrix);

	Transform* cameraTransform = camera->GetComponent<Transform>("TRANSFORM");

	// Set skydome position to camera position and extract all lights in the scene
	for (auto go : gameobjects) {
		if (go->GetName() == "SkydomeGO")
			go->GetComponent<Transform>("TRANSFORM")->SetTransform(*cameraTransform);
		else if (go->GetName() == "DIRECTIONAL_LIGHT")
		{
			lights.push_back(dynamic_cast<DirectionalLight*>(go));
		}
	}

	// process user interface frame
	result = m_userInterface->Frame(m_direct3D->GetDeviceContext(), p_fps, cameraTransform->GetPosition());
	if (!result)
		return false;

	//result = RenderSceneToDepthMaps(lights);

	result = Render(camera);
	if (!result)
		return false;

	return true;
}

bool RenderingSystem::Render(Camera* camera)
{
	bool result;

	// Clear the buffers to begin the scene.
	m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	result = RenderScene(camera);

	result = RenderDebugWindow(camera);

	// render user interface
	result = m_userInterface->Render(m_direct3D, m_ShaderManager, m_worldMatrix, m_baseViewMatrix, m_orthographicMatrix);
	if (!result)
		return false;

	// Present the rendered scene to the screen.
	m_direct3D->EndScene();

	return result;
}

bool RenderingSystem::LoadBuffersAndBind(Mesh* mesh)
{
	bool result;

	result = mesh->InitializeBuffers(m_direct3D->GetDevice());
	if (!result)
		return false;

	mesh->Render(m_direct3D->GetDeviceContext());

	return true;
}

bool RenderingSystem::RenderWithShader(Mesh* mesh, ShaderType shaderType, vector<string> textureIds)
{
	bool result;
	XMFLOAT3 lightDirection = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	XMFLOAT4 diffuseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	switch (shaderType)
	{
	case COLOR:
		result = m_ShaderManager->RenderColorShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix);
		if (!result)
			return false;
		break;

	case TEXTURE:
		result = m_ShaderManager->RenderTextureShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(textureIds.at(0)));
		if (!result)
			return false;
		break;

	case TEXTURE_INSTANCED:
		result = m_ShaderManager->RenderTextureShaderInstanced(m_direct3D->GetDeviceContext(), mesh->GetVertexCount(), mesh->GetInstanceCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(textureIds.at(0)));
		if (!result)
			return false;
		break;

	case LIGHT:
		result = m_ShaderManager->RenderLightShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(textureIds.at(0)), lightDirection, diffuseColor);
		if (!result)
			return false;
		break;

	case TERRAIN:
		result = m_ShaderManager->RenderTerrainShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(textureIds.at(0)), m_TextureManager->GetTexture(textureIds.at(1)), XMFLOAT3(-1.0f, -1.0f, 0.0), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		if (!result)
			return false;
		break;

	case SKYDOME:
		result = m_ShaderManager->RenderSkyDomeShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, XMFLOAT4(0.0f, 0.05f, 0.6f, 1.0f), XMFLOAT4(0.0f, 0.5f, 0.8f, 1.0f));
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
	mesh->Render(m_direct3D->GetDeviceContext());

	return true;
}

bool RenderingSystem::LoadBuffer(Mesh *mesh)
{
	bool result;

	result = mesh->InitializeBuffers(m_direct3D->GetDevice());
	if (!result)
		return false;

	return true;
}

bool RenderingSystem::RenderToTexture(Camera* camera)
{
	bool result;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_direct3D->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = RenderScene(camera);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_direct3D->ResetViewport();

	return true;
}

bool RenderingSystem::RenderScene(Camera* camera) {

	DirectionalLight* light = NULL;
	vector<DirectionalLight*> lights;
	int i = 0;

	bool m_cellLines = false;

	for (vector<GameObject*>::iterator iter = m_initializedGameObjects.begin(); iter != m_initializedGameObjects.end(); ++iter)
	{
		if ((*iter)->GetName() == "DIRECTIONAL_LIGHT") {
			light = dynamic_cast<DirectionalLight*>((*iter));
			lights.push_back(dynamic_cast<DirectionalLight*>((*iter)));
			i++;
		}
	}

	// render gameobjects
	for (vector<GameObject*>::iterator iter = m_initializedGameObjects.begin(); iter != m_initializedGameObjects.end(); ++iter)
	{
		XMFLOAT3 position = (*iter)->GetComponent<Transform>("TRANSFORM")->GetPosition();
		Renderer* renderer = (*iter)->GetComponent<Renderer>("RENDERER");
		Mesh* mesh = (*iter)->GetComponent<Mesh>();
		Terrain* terrain = nullptr;

		if (mesh != NULL) {
			switch (mesh->GetMeshType())
			{
			case MeshType::TERRAIN_CELL:

				terrain = (Terrain*)(*iter);

				// Translate the model to be custom position.
				m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

				// Turn the Z buffer back and back face culling on.
				m_direct3D->TurnZBufferOn();
				m_direct3D->TurnOnCulling();

				//Render the terrain cells (and cell lines if needed).
				for (int i = 0; i < terrain->GetCellCount(); i++)
				{
					// Put the terrain cell buffers on the pipeline.
					if(!terrain->RenderCell(m_direct3D->GetDeviceContext(), i))
						return false;

					m_ShaderManager->RenderTerrainShader(m_direct3D->GetDeviceContext(), terrain->GetCellIndexCount(i), m_worldMatrix, m_viewMatrix, m_projectionMatrix, m_TextureManager->GetTexture(renderer->GetTextureIds().at(0)), m_TextureManager->GetTexture(renderer->GetTextureIds().at(1)), XMFLOAT3(-1.0f, -1.0f, 0.0), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

					// If needed then render the bounding box around this terrain cell using the color shader. 
					if (m_cellLines)
					{
						terrain->RenderCellLines(m_direct3D->GetDeviceContext(), i);
						if (!m_ShaderManager->RenderColorShader(m_direct3D->GetDeviceContext(), terrain->GetCellLinesIndexCount(i), m_worldMatrix, m_viewMatrix, m_projectionMatrix))
							return false;
					}
				}


				/*if (!RenderWithShader(mesh, ShaderType::TERRAIN, renderer->GetTextureIds()))
					return false;*/

					//if (lights.size() != 0)
					//{
					//	if (!RenderWithMultipleLightsAndShadows(mesh, renderer->GetTextureIds(), lights))
					//		return false;
					//} 
					//else
					//{
					//	// render with normal map texture
					//	if (!RenderWithShader(mesh, ShaderType::LIGHT, renderer->GetTextureIds()))
					//		return false;
					//}



				m_direct3D->GetWorldMatrix(m_worldMatrix);

				// Turn the Z buffer back and back face culling off.
				m_direct3D->TurnZBufferOn();
				m_direct3D->TurnOnCulling();
				break;
			case MeshType::D3INSTANCE_MESH:

				break;
			default:

				if (renderer->GetShaderType() == ShaderType::SKYDOME)
				{
					// Turn off back face culling and turn off the Z buffer if skybox.
					m_direct3D->TurnOffCulling();
					m_direct3D->TurnZBufferOff();

					// Translate the model to be custom position.
					m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

					BindBuffer(mesh);

					if (!RenderWithShader(mesh, renderer->GetShaderType(), renderer->GetTextureIds()))
						return false;

					// Reset world matrix
					m_direct3D->GetWorldMatrix(m_worldMatrix);

					// Turn the Z buffer back and back face culling off.
					m_direct3D->TurnZBufferOn();
					m_direct3D->TurnOnCulling();
				}
				else
				{
					// Translate the model to be custom position.
					m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

					BindBuffer(mesh);

					if (lights.size() != 0)
					{
						if (!RenderWithMultipleLightsAndShadows(mesh, renderer->GetTextureIds(), lights))
							return false;
					}
					else
					{
						if (!RenderWithShader(mesh, renderer->GetShaderType(), renderer->GetTextureIds()))
							return false;
					}

					// Reset world matrix
					m_direct3D->GetWorldMatrix(m_worldMatrix);
				}

				break;
			}
		}
	}

	return true;
}

bool RenderingSystem::RenderDebugWindow(Camera* camera)
{
	bool result;

	if (m_renderToTextures.size() != 0)
	{

		// Turn off the Z buffer to begin all 2D rendering.
		m_direct3D->TurnZBufferOff();

		// Get the world, view, and ortho matrices from the camera and d3d objects.
		m_direct3D->GetWorldMatrix(m_worldMatrix);
		camera->GetViewMatrix(m_viewMatrix);
		m_direct3D->GetOrthoMatrix(m_orthographicMatrix);

		// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
		result = m_DebugWindow->Render(m_direct3D->GetDeviceContext(), 690, 10);
		if (!result)
		{
			return false;
		}

		// Render the debug window using the texture shader.
		result = m_ShaderManager->RenderTextureShader(m_direct3D->GetDeviceContext(), m_DebugWindow->GetIndexCount(), m_worldMatrix, m_baseViewMatrix,
			m_orthographicMatrix, m_renderToTextures.at(0)->GetShaderResourceView());
		if (!result)
		{
			return false;
		}

		// Turn the Z buffer back on now that all 2D rendering has completed.
		m_direct3D->TurnZBufferOn();
	}

	return true;
}

bool RenderingSystem::RenderSceneToDepthMap(DirectionalLight* light)
{
	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// render gameobjects to depth map (shadow map)
	for (vector<GameObject*>::iterator iter = m_initializedGameObjects.begin(); iter != m_initializedGameObjects.end(); ++iter)
	{
		XMFLOAT3 position = (*iter)->GetComponent<Transform>("TRANSFORM")->GetPosition();
		Renderer* renderer = (*iter)->GetComponent<Renderer>("RENDERER");
		Mesh* mesh = (*iter)->GetComponent<Mesh>();
		Terrain* terrain = nullptr;

		if (mesh != NULL) {
			switch (mesh->GetMeshType())
			{
			case MeshType::TERRAIN_CELL:

				terrain = (Terrain*)(*iter);

				// Translate the model to be custom position.
				m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

				// Turn the Z buffer back and back face culling on.
				m_direct3D->TurnZBufferOn();
				m_direct3D->TurnOnCulling();

				for (int i = 0; i < terrain->GetCellCount(); i++)
				{
					// Put the terrain cell buffers on the pipeline.
					if (!terrain->RenderCell(m_direct3D->GetDeviceContext(), i))
						return false;

					if (!m_ShaderManager->RenderDepthShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, light->GenerateViewMatrix(), light->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH)))
						return false;

				}

				m_direct3D->GetWorldMatrix(m_worldMatrix);

				// Turn the Z buffer back and back face culling off.
				m_direct3D->TurnZBufferOn();
				m_direct3D->TurnOnCulling();

				break;
			case MeshType::D3INSTANCE_MESH:

				break;

			default:

				if (renderer->GetShaderType() != ShaderType::SKYDOME)
				{
					// Translate the model to be custom position.
					m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

					BindBuffer(mesh);

					if (!m_ShaderManager->RenderDepthShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, light->GenerateViewMatrix(), light->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH)))
						return false;

					// Reset world matrix
					m_direct3D->GetWorldMatrix(m_worldMatrix);
				}

				break;
			}
		}
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_direct3D->ResetViewport();

	return true;
}

bool RenderingSystem::RenderSceneToDepthMaps(vector<DirectionalLight*> lights)
{
	int i = 0;
	vector<RenderTexture*> temp_renderTextures;

	for (vector<DirectionalLight*>::iterator iter = lights.begin(); iter != lights.end(); ++iter)
	{
		RenderTexture* rt = m_renderToTextures.back();
		m_renderToTextures.pop_back();

		rt->SetRenderTarget(m_direct3D->GetDeviceContext());
		rt->ClearRenderTarget(m_direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

		RenderGameObjectsForShadowMap((*iter));

		// Reset the render target back to the original back buffer and not the render to texture anymore.
		m_direct3D->SetBackBufferRenderTarget();

		// Reset the viewport back to the original.
		m_direct3D->ResetViewport();

		temp_renderTextures.push_back(rt);

		i++;
	}

	m_renderToTextures = temp_renderTextures;

	return true;
}

bool RenderingSystem::RenderWithShadows(Mesh* mesh, vector<string> textureIds, DirectionalLight* light)
{
	bool result;

	Transform* transform = light->GetComponent<Transform>("TRANSFORM");
	Light* lightInfo = light->GetComponent<Light>("LIGHT");

	result = m_ShaderManager->RenderShadowShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, light->GenerateViewMatrix(), light->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH), m_TextureManager->GetTexture(textureIds.at(0)), m_renderToTextures.at(0)->GetShaderResourceView(), transform->GetPosition(), lightInfo->GetAmbientColor(), lightInfo->GetDiffuseColor());

	if (!result)
		return false;

	return true;
}

bool RenderingSystem::RenderWithPointLight(Mesh* mesh, vector<string> textureIds, DirectionalLight* lights[])
{
	bool result;
	XMVECTOR diffuseColor[4];
	XMVECTOR lightPosition[4];

	for (int i = 0; i < 4; i++) {
		diffuseColor[i] = XMLoadFloat4(&(lights[i]->GetComponent<Light>("LIGHT")->GetDiffuseColor()));
		lightPosition[i] = XMLoadFloat3(&(lights[i]->GetComponent<Transform>("TRANSFORM")->GetPosition()));
	}

	// Render the model using the light shader and the light arrays.
	result = m_ShaderManager->RenderLightShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix,
		m_TextureManager->GetTexture(textureIds.at(0)), diffuseColor, lightPosition);
	if (!result)
	{
		return false;
	}

	return false;
}

bool RenderingSystem::RenderGameObjectsForShadowMap(DirectionalLight * light)
{
	for (vector<GameObject*>::iterator iter = m_initializedGameObjects.begin(); iter != m_initializedGameObjects.end(); ++iter)
	{
		XMFLOAT3 position = (*iter)->GetComponent<Transform>("TRANSFORM")->GetPosition();
		Renderer* renderer = (*iter)->GetComponent<Renderer>("RENDERER");
		Mesh* mesh = (*iter)->GetComponent<Mesh>();
		Terrain* terrain = nullptr;

		if (mesh != NULL) {
			switch (mesh->GetMeshType())
			{
			case MeshType::TERRAIN_CELL:

				terrain = (Terrain*)(*iter);

				// Translate the model to be custom position.
				m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

				// Turn the Z buffer back and back face culling on.
				m_direct3D->TurnZBufferOn();
				m_direct3D->TurnOnCulling();

				//for (int i = 0; i < 10; i++)
				//{
				//	// Put the terrain cell buffers on the pipeline.
				//	if (!terrain->RenderCell(m_direct3D->GetDeviceContext(), i))
				//		return false;

				//	if (!m_ShaderManager->RenderDepthShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, light->GenerateViewMatrix(), light->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH)))
				//		return false;
				//}

				m_direct3D->GetWorldMatrix(m_worldMatrix);

				// Turn the Z buffer back and back face culling off.
				m_direct3D->TurnZBufferOn();
				m_direct3D->TurnOnCulling();
				break;

			case MeshType::D3INSTANCE_MESH:

				break;

			default:
				if (renderer->GetShaderType() != ShaderType::SKYDOME)
				{
					// Translate the model to be custom position.
					m_worldMatrix = XMMatrixTranslation(position.x, position.y, position.z);

					BindBuffer(mesh);

					if (!m_ShaderManager->RenderDepthShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, light->GenerateViewMatrix(), light->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH)))
						return false;

					// Reset world matrix
					m_direct3D->GetWorldMatrix(m_worldMatrix);
				}

				break;
			}
		}
	}

	return true;
}

bool RenderingSystem::RenderWithMultipleLightsAndShadows(Mesh* mesh, vector<string> textureIds, vector<DirectionalLight*> lights)
{
	bool result;

	vector<XMMATRIX> viewMatrices, projectionMatrices;
	vector<ID3D11ShaderResourceView*> renderTextures;

	for (int i = 0; i < lights.size(); i++)
	{
		viewMatrices.push_back(lights[i]->GenerateViewMatrix());
		projectionMatrices.push_back(lights[i]->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH));
		renderTextures.push_back(m_renderToTextures.at(i)->GetShaderResourceView());
	}

	result = m_ShaderManager->RenderMultipleShadowShader(m_direct3D->GetDeviceContext(), mesh->GetIndexCount(), m_worldMatrix, m_viewMatrix, m_projectionMatrix, viewMatrices, projectionMatrices, m_TextureManager->GetTexture(textureIds.at(0)), renderTextures, lights);

	if (!result)
		return false;

	return true;
}

D3D* RenderingSystem::GetDirect3D()
{
	return m_direct3D;
}