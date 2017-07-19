#ifndef _MULTIPLE_SHADOW_SHADER_H_
#define _MULTIPLE_SHADOW_SHADER_H_

//////////////
// INCLUDES //
//////////////
#include "..\Gameobject\DirectionalLight.h"
#include "..\Component\Transform.h"
#include "..\Component\Light.h"
#include <algorithm>
#include <d3d11.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>
#include <fstream>
using namespace std;
using namespace DirectX;

const int MAX_NUM_LIGHTS = 4;

class MultipleShadowShader 
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView[MAX_NUM_LIGHTS];
		XMMATRIX lightProjection[MAX_NUM_LIGHTS];
	};

	struct PointLight
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightPosition;
		float padding;
	};

	struct LightBufferType
	{
		PointLight lights[MAX_NUM_LIGHTS];
	};

public:
	MultipleShadowShader();
	MultipleShadowShader(const MultipleShadowShader&);
	~MultipleShadowShader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, vector<XMMATRIX>, vector<XMMATRIX>, ID3D11ShaderResourceView*,
		vector<ID3D11ShaderResourceView*>, vector<DirectionalLight*>);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, vector<XMMATRIX>, vector<XMMATRIX>, ID3D11ShaderResourceView*, vector<ID3D11ShaderResourceView*>, vector<DirectionalLight*>);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleStateWrap;
	ID3D11SamplerState* m_sampleStateClamp;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
};

#endif // !_MULTIPLE_SHADOW_SHADER_H_

