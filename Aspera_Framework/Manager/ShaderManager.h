#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../D3D/D3D.h"
#include "../Shaders/ColorShader.h"
#include "../Shaders/TextureShader.h"
#include "../Shaders/FontShader.h"
#include "../Shaders/LightShader.h"
#include "../Shaders/TerrainShader.h"
#include "../Shaders/SkyDomeShader.h"
#include "../Shaders/TextureShaderInstanced.h"
#include "../Shaders/DepthShader.h"
#include "../Shaders/ShadowShader.h"
#include "../Shaders/MultipleShadowShader.h"
#include "../Gameobject/DirectionalLight.h"

class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderColorShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);
	bool RenderTextureShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	bool RenderLightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);
	bool RenderLightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMVECTOR[], XMVECTOR[]);
	bool RenderFontShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);
	bool RenderTerrainShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*,
		XMFLOAT3, XMFLOAT4);
	bool RenderSkyDomeShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMFLOAT4, XMFLOAT4);
	bool RenderTextureShaderInstanced(ID3D11DeviceContext*, int, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	bool RenderDepthShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);
	bool RenderShadowShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, 
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4);
	bool RenderMultipleShadowShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, vector<XMMATRIX>, vector<XMMATRIX>, ID3D11ShaderResourceView* , vector<ID3D11ShaderResourceView*>, vector<DirectionalLight*>);

private:
	ColorShader* m_colorShader;
	TextureShader* m_textureShader;
	LightShader* m_lightShader;
	FontShader* m_fontShader;
	TerrainShader* m_terrainShader;
	SkyDomeShader* m_skydomeShader;
	TextureShaderInstanced* m_textureShaderInstanced;
	DepthShader* m_depthShader;
	ShadowShader* m_shadowShader;
	MultipleShadowShader* m_multipleShadowShader;
};

#endif "_SHADERMANAGER_H_"