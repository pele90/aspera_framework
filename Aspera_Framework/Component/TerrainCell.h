#ifndef _TERRAIN_CELL_H_
#define _TERRAIN_CELL_H_

//////////////
// INCLUDES //
//////////////
#include "../Base/Mesh.h"
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

class TerrainCell : public Mesh
{
private:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
		float r, g, b;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
		XMFLOAT3 color;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct ColorVertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	TerrainCell();
	TerrainCell(const TerrainCell&);
	~TerrainCell();

	virtual bool Initialize();
	
	virtual bool Initialize(char*);
	virtual bool InitializeBuffers(ID3D11Device*);
	virtual bool InitializeBuffers(ID3D11Device*, int, int, int, int, int, ModelType*);
	virtual void Shutdown();

	bool Initialize(ID3D11Device*, void*, int, int, int, int, int);
	void Render(ID3D11DeviceContext*);
	void RenderLineBuffers(ID3D11DeviceContext*);

	int GetVertexCount();
	int GetIndexCount();
	int GetLineBuffersIndexCount();
	void GetCellDimensions(float&, float&, float&, float&, float&, float&);

private:
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	void CalculateCellDimensions();
	bool BuildLineBuffers(ID3D11Device*);
	void ShutdownLineBuffers();

public:
	VectorType* m_vertexList;

private:
	int m_vertexCount, m_indexCount, m_lineIndexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer, *m_lineVertexBuffer, *m_lineIndexBuffer;;
	float m_maxWidth, m_maxHeight, m_maxDepth, m_minWidth, m_minHeight, m_minDepth;
	float m_positionX, m_positionY, m_positionZ;
};

#endif // !_TERRAIN_CELL_H_
