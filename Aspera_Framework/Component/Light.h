#ifndef _LIGHT_
#define _LIGHT_

#include "..\Base\Component.h"

#include <directxmath.h>
using namespace DirectX;

class Light : public Component {

public:
	Light();
	~Light();

	virtual bool Initialize();
	virtual bool Initialize(XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor);
	virtual void Shutdown();

	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetDiffuseColor();

	void SetAmbientColor(XMFLOAT4);
	void SetDiffuseColor(XMFLOAT4);

private:
	XMFLOAT4 m_ambientColor;
	XMFLOAT4 m_diffuseColor;

};
#endif // !_LIGHT_

