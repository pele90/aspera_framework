#include "Mesh.h"

Mesh::Mesh()
{
	m_initialized = false;
}

Mesh::Mesh(unsigned index, char * type) : Component(index, type)
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
}

Mesh::~Mesh()
{

}

bool Mesh::Initialize() 
{
	bool result;

	return true;
}

void Mesh::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int Mesh::GetIndexCount()
{
	return m_indexCount;
}

void Mesh::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

int Mesh::GetVertexCount()
{
	return m_vertexCount;
}

int Mesh::GetInstanceCount()
{
	return m_instanceCount;
}

MeshType Mesh::GetMeshType()
{
	return m_meshType;
}

bool Mesh::IsInitialized()
{
	return m_initialized;
}