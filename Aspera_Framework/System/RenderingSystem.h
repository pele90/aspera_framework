#ifndef _RENDERINGSYSTEM_H_
#define _RENDERINGSYSTEM_H_

#include "../UI/userinterfaceclass.h"
#include "../Component/Transform.h"
#include "../Gameobject/Camera.h"
#include "..\Gameobject\DirectionalLight.h"
#include "../Component/ModelMesh.h"
#include "../Component/InstancingMesh.h"
#include "../Component/Renderer.h"
#include "../Component/TerrainMesh.h"
#include "..\Component\Light.h"
#include "../MISC/Enums.h"
#include "../D3D/D3D.h"
#include "../Base/GameObject.h"
#include "../Base/Mesh.h"
#include "../Manager/ShaderManager.h"
#include "../Manager/TextureManager.h"
#include "../Graphics/DebugWindow.h"
#include "../Graphics/RenderTexture.h"
#include <d3d11.h>
#include <vector>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 10000.0f;
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
	bool Frame(vector<GameObject*>, Camera*, int);
	
private:
	bool Render(Camera*);
	bool RenderScene(Camera*);
	bool RenderGameObjectsForShadowMap(DirectionalLight*);
	bool RenderToTexture(Camera*);
	bool RenderSceneToDepthMap(DirectionalLight*);
	bool RenderSceneToDepthMaps(vector<DirectionalLight*>);
	bool RenderDebugWindow(Camera*);
	bool LoadBuffersAndBind(Mesh*);

	bool LoadBuffer(Mesh*);
	bool BindBuffer(Mesh*);
	bool RenderWithShader(Mesh*, ShaderType, vector<string>);
	bool RenderWithShadows(Mesh*, vector<string>, DirectionalLight*);
	bool RenderWithMultipleLightsAndShadows(Mesh*, vector<string>, vector<DirectionalLight*>);
	bool RenderWithPointLight(Mesh*, vector<string>, DirectionalLight*[]);

private:
	D3D* m_direct3D;
	ShaderManager* m_ShaderManager;
	TextureManager* m_TextureManager;
	XMMATRIX m_worldMatrix, m_baseViewMatrix, m_viewMatrix, m_projectionMatrix, m_orthographicMatrix;
	UserInterfaceClass* m_userInterface;

	vector<RenderTexture*> m_renderToTextures;
	RenderTexture* m_RenderTexture;
	DebugWindow* m_DebugWindow;

	// Initialized meaning their vertex and index buffers are initialized
	vector<GameObject*> m_initializedGameObjects;
	vector<GameObject*> m_uninitializedGameObjects;
};

#endif // !_RENDERINGSYSTEM_H_

