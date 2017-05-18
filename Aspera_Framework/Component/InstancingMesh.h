#ifndef _INSTANCING_MESH_H_
#define _INSTANCING_MESH_H_

#include "../Base/Mesh.h"

class InstancingMesh : public Mesh
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct InstanceType
	{
		XMFLOAT3 position;
	};

public:
	InstancingMesh();
	~InstancingMesh();

	virtual bool Initialize();
	virtual bool Initialize(char*);
	virtual bool Initialize(char*, int);
	virtual void Shutdown();
	virtual bool InitializeBuffers(ID3D11Device*);

protected:
	void ShutdownBuffers() override;

private:
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadModel(char*);
	void ReleaseModel();

private:
	ModelType* m_model;
};

#endif // !_INSTANCING_MESH_H_
