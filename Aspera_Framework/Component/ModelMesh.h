#ifndef _MODELMESH_H_
#define _MODELMESH_H_

#include "../Base/Mesh.h"

class ModelMesh : public Mesh
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

public:
	ModelMesh();
	~ModelMesh();

	virtual bool Initialize();
	virtual bool Initialize(char*);
	virtual void Shutdown();
	virtual bool InitializeBuffers(ID3D11Device*);

private:
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadModel(char*);
	void ReleaseModel();

private:
	ModelType* m_model;

};

#endif _MODELMESH_H_