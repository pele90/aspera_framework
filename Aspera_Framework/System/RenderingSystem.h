#ifndef _RENDERINGSYSTEM_H_
#define _RENDERINGSYSTEM_H_

#include "../UI/userinterfaceclass.h"
#include "../Component/Transform.h"
#include "../Gameobject/Camera.h"
#include "../Component/ModelMesh.h"
#include "../Component/InstancingMesh.h"
#include "../Component/Renderer.h"
#include "../Component/TerrainMesh.h"
#include "../MISC/Enums.h"
#include "../D3D/D3DClass.h"
#include "../Base/GameObject.h"
#include "../Base/Mesh.h"
#include "../Manager/ShaderManagerClass.h"
#include "../Manager/TextureManagerClass.h"
#include <d3d11.h>
#include <vector>

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 10000.0f;
const float SCREEN_NEAR = 0.1f;


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
	bool LoadBuffersAndBind(Mesh*);

	bool LoadBuffer(Mesh*);
	bool BindBuffer(Mesh*);
	bool RenderWithShader(Mesh*, ShaderType);

private:
	D3DClass* m_Direct3D;
	ShaderManagerClass* m_ShaderManager;
	TextureManagerClass* m_TextureManager;
	XMMATRIX m_worldMatrix, m_baseViewMatrix, m_viewMatrix, m_projectionMatrix, m_orthographicMatrix;
	UserInterfaceClass* m_userInterface;

	vector<GameObject*> m_initializedGameObjects;
	vector<GameObject*> m_uninitializedGameObjects;
};

#endif // !_RENDERINGSYSTEM_H_

