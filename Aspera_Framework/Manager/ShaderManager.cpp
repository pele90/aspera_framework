#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	m_colorShader = 0;
	m_textureShader = 0;
	m_lightShader = 0;
	m_fontShader = 0;
	m_terrainShader = 0;
	m_skydomeShader = 0;
	m_textureShaderInstanced = 0;
	m_depthShader = 0;
	m_shadowShader = 0;
	m_multipleShadowShader = 0;
}

ShaderManager::ShaderManager(const ShaderManager& other){}

ShaderManager::~ShaderManager(){}

bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	// Create the terrain shader object.
	m_terrainShader = new TerrainShader;
	if (!m_terrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_terrainShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the color shader object.
	m_colorShader = new ColorShader;
	if (!m_colorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_colorShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the texture shader object.
	m_textureShader = new TextureShader;
	if (!m_textureShader)
	{
		return false;
	}

	// Create the texture shader object for instanced objects.
	m_textureShaderInstanced = new TextureShaderInstanced;
	if (!m_textureShaderInstanced)
	{
		return false;
	}

	// Create the light shader object.
	m_lightShader = new LightShader;
	if (!m_lightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_lightShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_textureShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Initialize the texture shader instanced object.
	result = m_textureShaderInstanced->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the font shader object.
	m_fontShader = new FontShader;
	if (!m_fontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_fontShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the sky dome shader object.
	m_skydomeShader = new SkyDomeShader;
	if (!m_skydomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_skydomeShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the depth shader object.
	m_depthShader = new DepthShader;
	if (!m_depthShader)
	{
		return false;
	}

	// Initialize the depth shader object.
	result = m_depthShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the shadow shader object.
	m_shadowShader = new ShadowShader;
	if (!m_shadowShader)
	{
		return false;
	}

	// Initialize the shadow shader object.
	result = m_shadowShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the multiple shadow shader object.
	m_multipleShadowShader = new MultipleShadowShader;
	if (!m_shadowShader)
	{
		return false;
	}

	// Initialize the multiple shadow shader object.
	result = m_multipleShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void ShaderManager::Shutdown()
{
	// Release the terrain shader object.
	if (m_terrainShader)
	{
		m_terrainShader->Shutdown();
		delete m_terrainShader;
		m_terrainShader = 0;
	}

	// Release the sky dome shader object.
	if (m_skydomeShader)
	{
		m_skydomeShader->Shutdown();
		delete m_skydomeShader;
		m_skydomeShader = 0;
	}

	// Release the font shader object.
	if (m_fontShader)
	{
		m_fontShader->Shutdown();
		delete m_fontShader;
		m_fontShader = 0;
	}

	// Release the light shader object.
	if (m_lightShader)
	{
		m_lightShader->Shutdown();
		delete m_lightShader;
		m_lightShader = 0;
	}

	// Release the texture shader object.
	if (m_textureShader)
	{
		m_textureShader->Shutdown();
		delete m_textureShader;
		m_textureShader = 0;
	}

	// Release the texture shader instanced object.
	if (m_textureShaderInstanced)
	{
		m_textureShaderInstanced->Shutdown();
		delete m_textureShaderInstanced;
		m_textureShaderInstanced = 0;
	}

	// Release the color shader object.
	if (m_colorShader)
	{
		m_colorShader->Shutdown();
		delete m_colorShader;
		m_colorShader = 0;
	}

	// Release the depth shader object.
	if (m_depthShader)
	{
		m_depthShader->Shutdown();
		delete m_depthShader;
		m_depthShader = 0;
	}

	// Release the shadow shader object.
	if (m_shadowShader)
	{
		m_shadowShader->Shutdown();
		delete m_shadowShader;
		m_shadowShader = 0;
	}

	// Release the multiple shadow shader object.
	if (m_multipleShadowShader)
	{
		m_multipleShadowShader->Shutdown();
		delete m_multipleShadowShader;
		m_multipleShadowShader = 0;
	}

	return;
}

bool ShaderManager::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix)
{
	return m_colorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
}

bool ShaderManager::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	return m_textureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
}

bool ShaderManager::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	return m_lightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, diffuseColor);
}

bool ShaderManager::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMVECTOR diffuseColor[], XMVECTOR lightPosition[])
{
	return m_lightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, diffuseColor, lightPosition);
}

bool ShaderManager::RenderFontShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT4 color)
{
	return m_fontShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, color);
}

bool ShaderManager::RenderTerrainShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* normalMap,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
	return m_terrainShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, normalMap, lightDirection, diffuseColor);
}

bool ShaderManager::RenderSkyDomeShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, XMFLOAT4 apexColor, XMFLOAT4 centerColor)
{
	return m_skydomeShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, apexColor, centerColor);
}

bool ShaderManager::RenderTextureShaderInstanced(ID3D11DeviceContext *deviceContext, int vertexCount, int instanceCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView *texture)
{
	return m_textureShaderInstanced->Render(deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
}

bool ShaderManager::RenderDepthShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix)
{
	return m_depthShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);
}

bool ShaderManager::RenderShadowShader(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, 
	XMMATRIX lightViewMatrix, XMMATRIX lightProjectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMapTexture, XMFLOAT3 lightPosition, 
	XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	return m_shadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, texture, depthMapTexture, lightPosition, ambientColor, diffuseColor);
}

bool ShaderManager::RenderMultipleShadowShader(ID3D11DeviceContext * deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, vector<XMMATRIX> lightViewMatrix, vector<XMMATRIX> lightProjectionMatrix, ID3D11ShaderResourceView * texture, vector<ID3D11ShaderResourceView*> depthMapTexture, vector<DirectionalLight*> lights)
{
	return m_multipleShadowShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, texture, depthMapTexture, lights);
}