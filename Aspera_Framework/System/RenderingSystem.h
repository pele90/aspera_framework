#ifndef _RENDERINGSYSTEM_H_
#define _RENDERINGSYSTEM_H_

#include "..\MISC\Input.h"
#include "../UI/UserInterface.h"
#include "../Component/Transform.h"
#include "../Gameobject/Camera.h"
#include "..\Gameobject\DirectionalLight.h"
#include "../Component/ModelMesh.h"
#include "../Component/InstancingMesh.h"
#include "../Component/Renderer.h"
#include "../Component/TerrainCell.h"
#include "../Gameobject/Terrain.h"
#include "..\Component\Light.h"
#include "../MISC/Enums.h"
#include "../D3D/D3D.h"
#include "../Base/GameObject.h"
#include "../Base/Mesh.h"
#include "../Manager/ShaderManager.h"
#include "../Manager/TextureManager.h"
#include "../Graphics/DebugWindow.h"
#include "../Graphics/RenderTexture.h"
#include "../Graphics/Frustum.h"
#include <d3d11.h>
#include <vector>
#include <chrono>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1500.0f;
const float SCREEN_NEAR = 0.1f;
const int SHADOWMAP_WIDTH = 2048;
const int SHADOWMAP_HEIGHT = 2048;


class RenderingSystem
{

public:
	RenderingSystem();
	~RenderingSystem();

	bool Initialize(HWND, int, int, vector<GameObject*>);
	void Shutdown();
	bool InitializeGameObjects();
	bool Frame(vector<GameObject*> gameobjects, Camera* camera, Input* input, int fps);
	
private:
	bool Render(Camera*);
	bool RenderScene(Camera*);
	bool RenderSceneToTexture(Camera*);
	bool RenderSceneToDepthMap(DirectionalLight*);
	bool RenderSceneToDepthMaps();
	bool RenderDebugWindow(Camera*);

	bool BindBuffer(Mesh*);
	bool RenderWithShader(Mesh*, ShaderType, vector<string>);
	bool RenderGameObjectsForShadowMap(DirectionalLight*);
	bool RenderWithMultipleLightsAndShadows(Mesh*, vector<string>);

	void HandleInputs(Input* input);
	void HandleGameObjects(vector<GameObject*> gameobjects, Camera* camera);

private:
	D3D* m_direct3D;
	ShaderManager* m_ShaderManager;
	TextureManager* m_TextureManager;
	XMMATRIX m_worldMatrix, m_baseViewMatrix, m_viewMatrix, m_projectionMatrix, m_orthographicMatrix;
	UserInterface* m_userInterface;
	RenderTexture* m_RenderTexture;
	DebugWindow* m_DebugWindow;
	Frustum* m_frustum;
	vector<DirectionalLight*> m_lights;

	bool m_displayUI = true;
	bool m_wireFrame = false;
	bool m_cellLines = false;

	vector<RenderTexture*> m_renderToTextures;
	// Initialized meaning their vertex and index buffers are initialized
	vector<GameObject*> m_initializedGameObjects;
	vector<GameObject*> m_uninitializedGameObjects;
};

#endif // !_RENDERINGSYSTEM_H_

