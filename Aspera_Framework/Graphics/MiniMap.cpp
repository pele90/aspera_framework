#include "MiniMap.h"

MiniMap::MiniMap()
{
	m_miniMapBitmap = 0;
	m_pointBitmap = 0;
}

MiniMap::MiniMap(const MiniMap& other)
{
}

MiniMap::~MiniMap()
{
}

bool MiniMap::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int screenWidth, int screenHeight,
	float terrainWidth, float terrainHeight)
{
	bool result;

	// Set the size of the mini-map minus the borders.
	m_mapSizeX = 150.0f;
	m_mapSizeY = 150.0f;

	// Initialize the location of the mini-map on the screen.
	m_mapLocationX = screenWidth - (int)m_mapSizeX - 10;
	m_mapLocationY = 10;

	// Store the terrain size.
	m_terrainWidth = terrainWidth;
	m_terrainHeight = terrainHeight;

	// Create the mini-map bitmap object.
	m_miniMapBitmap = new Bitmap;
	if (!m_miniMapBitmap)
	{
		return false;
	}

	// Initialize the mini-map bitmap object.
	result = m_miniMapBitmap->Initialize(device, deviceContext, screenWidth, screenHeight, 154, 154,
		"../Aspera_Framework/data/minimap/minimap.tga");
	if (!result)
	{
		return false;
	}

	// Create the point bitmap object.
	m_pointBitmap = new Bitmap;
	if (!m_pointBitmap)
	{
		return false;
	}

	// Initialize the point bitmap object.
	result = m_pointBitmap->Initialize(device, deviceContext, screenWidth, screenHeight, 3, 3,
		"../Aspera_Framework/data/minimap/point.tga");
	if (!result)
	{
		return false;
	}

	return true;
}

void MiniMap::Shutdown()
{
	// Release the point bitmap object.
	if (m_pointBitmap)
	{
		m_pointBitmap->Shutdown();
		delete m_pointBitmap;
		m_pointBitmap = 0;
	}

	// Release the mini-map bitmap object.
	if (m_miniMapBitmap)
	{
		m_miniMapBitmap->Shutdown();
		delete m_miniMapBitmap;
		m_miniMapBitmap = 0;
	}

	return;
}

bool MiniMap::Render(ID3D11DeviceContext* deviceContext, ShaderManager* ShaderManager, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX orthoMatrix)
{
	bool result;

	// Put the mini-map bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_miniMapBitmap->Render(deviceContext, m_mapLocationX, m_mapLocationY);
	if (!result)
	{
		return false;
	}

	// Render the mini-map bitmap using the texture shader.
	result = ShaderManager->RenderTextureShader(deviceContext, m_miniMapBitmap->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_miniMapBitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Put the point bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_pointBitmap->Render(deviceContext, m_pointLocationX, m_pointLocationY);
	if (!result)
	{
		return false;
	}

	// Render the point bitmap using the texture shader.
	result = ShaderManager->RenderTextureShader(deviceContext, m_pointBitmap->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_pointBitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	return true;
}

void MiniMap::PositionUpdate(float positionX, float positionZ)
{
	float percentX, percentY;


	// Ensure the point does not leave the minimap borders even if the camera goes past the terrain borders.
	if (positionX < 0)
	{
		positionX = 0;
	}

	if (positionZ < 0)
	{
		positionZ = 0;
	}

	if (positionX > m_terrainWidth)
	{
		positionX = m_terrainWidth;
	}

	if (positionZ > m_terrainHeight)
	{
		positionZ = m_terrainHeight;
	}

	// Calculate the position of the camera on the minimap in terms of percentage.
	percentX = positionX / m_terrainWidth;
	percentY = 1.0f - (positionZ / m_terrainHeight);

	// Determine the pixel location of the point on the mini-map.
	m_pointLocationX = (m_mapLocationX + 2) + (int)(percentX * m_mapSizeX);
	m_pointLocationY = (m_mapLocationY + 2) + (int)(percentY * m_mapSizeY);

	// Subtract one from the location to center the point on the mini-map according to the 3x3 point pixel image size.
	m_pointLocationX = m_pointLocationX - 1;
	m_pointLocationY = m_pointLocationY - 1;

	return;
}