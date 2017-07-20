#ifndef MINIMAP_H_
#define MINIMAP_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Bitmap.h"
#include "../Manager/ShaderManager.h"

class MiniMap
{
public:
	MiniMap();
	MiniMap(const MiniMap&);
	~MiniMap();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, float, float);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, ShaderManager*, XMMATRIX, XMMATRIX, XMMATRIX);

	void PositionUpdate(float, float);

private:
	int m_mapLocationX, m_mapLocationY, m_pointLocationX, m_pointLocationY;
	float m_mapSizeX, m_mapSizeY, m_terrainWidth, m_terrainHeight;
	Bitmap* m_miniMapBitmap, *m_pointBitmap;
};

#endif
