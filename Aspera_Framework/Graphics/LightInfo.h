#ifndef _LIGHT_INFO_H_
#define _LIGHT_INFO_H_

//////////////
// INCLUDES //
//////////////
#include <directxmath.h>
using namespace DirectX;

class LightInfo
{
public:
	LightInfo();
	LightInfo(const LightInfo&);
	~LightInfo();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetLookAt(float, float, float);
	void SetPosition(float, float, float);

	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetDiffuseColor();
	XMVECTOR GetLookAt();
	XMVECTOR GetPosition();

	void GenerateViewMatrix();
	void GenerateProjectionMatrix(float, float);

	void GetViewMatrix(XMMATRIX&);
	void GetProjectionMatrix(XMMATRIX&);

private:
	XMFLOAT4 m_ambientColor;
	XMFLOAT4 m_diffuseColor;
	XMVECTOR m_lookAt;
	XMVECTOR m_position;
	XMMATRIX m_viewMatrix;
	XMMATRIX m_projectionMatrix;
};

#endif "!_LIGHT_H_"