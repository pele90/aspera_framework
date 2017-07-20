#ifndef _SHADERMANAGER_H_
#define _SHADERMANAGER_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../D3D/D3D.h"
#include "../Shaders/ColorShaderClass.h"
#include "../Shaders/TextureShaderClass.h"
#include "../Shaders/FontShaderClass.h"
#include "../Shaders/LightShaderClass.h"
#include "../Shaders/TerrainShaderClass.h"
#include "../Shaders/SkyDomeShaderClass.h"
#include "../Shaders/TextureShaderInstanced.h"
#include "../Shaders/DepthShaderClass.h"
#include "../Shaders/ShadowShaderClass.h"
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
	ColorShaderClass* m_colorShader;
	TextureShaderClass* m_textureShader;
	LightShaderClass* m_lightShader;
	FontShaderClass* m_fontShader;
	TerrainShaderClass* m_terrainShader;
	SkyDomeShaderClass* m_skydomeShader;
	TextureShaderInstanced* m_textureShaderInstanced;
	DepthShaderClass* m_depthShader;
	ShadowShaderClass* m_shadowShader;
	MultipleShadowShader* m_multipleShadowShader;
};

#endif "_SHADERMANAGER_H_"