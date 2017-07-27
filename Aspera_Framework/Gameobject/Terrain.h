#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "../Base/GameObject.h"
#include "../Component/Transform.h"
#include "../Component/Renderer.h"
#include "../Component/TerrainCell.h"
#include "../Graphics/Frustum.h"
#include <d3d11.h>
#include <directxmath.h>
#include <fstream>
#include <stdio.h>

using namespace DirectX;
using namespace std;

// Set the height and width of each terrain cell to a fixed 33x33 vertex array.
int const CELL_WIDTH = 33;
int const CELL_HEIGHT = 33;

class Terrain : public GameObject
{
private:
	struct HeightMapType
	{
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
		float r, g, b;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	Terrain();
	~Terrain();

	virtual bool Initialize();
	bool Initialize(char* setupFilename);
	virtual void Shutdown();

	bool Frame();
	bool RenderCell(ID3D11DeviceContext*, int, Frustum*);
	void RenderCellLines(ID3D11DeviceContext*, int);
	bool InitializeTerrainCells();
	bool LoadTerrainCells(ID3D11Device*);
	bool LoadTerrainCellsEx(ID3D11Device*);
	void ShutdownTerrainModel();

	int GetCellIndexCount(int);
	int GetCellLinesIndexCount(int);
	int GetCellCount();

	int GetRenderCount();
	int GetCellsDrawn();
	int GetCellsCulled();

private:
	bool LoadSetupFile(char*);
	bool LoadBitmapHeightMap();
	bool LoadRawHeightMap();
	void ShutdownHeightMap();
	void SetTerrainCoordinates();
	bool CalculateNormals();
	bool LoadColorMap();
	bool BuildTerrainModel();
	void CalculateTerrainVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);
	void ShutdownTerrainCells();

private:
	int m_terrainHeight, m_terrainWidth, m_vertexCount;
	float m_heightScale;
	char* m_terrainFilename, *m_colorMapFilename;
	HeightMapType* m_heightMap;
	ModelType* m_terrainModel;
	TerrainCell* m_terrainCells;
	Transform* m_transform;
	Renderer* m_renderer;
	int m_cellCount, m_renderCount, m_cellsDrawn, m_cellsCulled;
};

#endif // !_TERRAIN_H_