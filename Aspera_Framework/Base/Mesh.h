#ifndef _MESH_H_
#define _MESH_H_

#include "Component.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
#include "../MISC/Enums.h"
using namespace DirectX;
using namespace std;

class Mesh : public Component
{

public:
	Mesh();
	Mesh(unsigned, char*);
	~Mesh();

	virtual bool Initialize();
	virtual bool Initialize(char*) = 0;
	virtual void Shutdown() = 0;
	virtual bool InitializeBuffers(ID3D11Device*) = 0;
	virtual void Render(ID3D11DeviceContext*);
	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();
	MeshType GetMeshType();
	bool IsInitialized();

protected:
	virtual void RenderBuffers(ID3D11DeviceContext*) = 0;
	virtual void ShutdownBuffers();

protected:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_instanceBuffer;
	int m_vertexCount, m_indexCount, m_instanceCount;
	bool m_initialized;
	MeshType m_meshType;
};

#endif // !_MESH_H_

