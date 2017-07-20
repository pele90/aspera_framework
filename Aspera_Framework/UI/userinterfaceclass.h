#ifndef _USERINTERFACECLASS_H_
#define _USERINTERFACECLASS_H_

#include "../Graphics/TextClass.h"
#include "../Graphics/MiniMap.h"

class UserInterfaceClass
{
public:
	UserInterfaceClass();
	UserInterfaceClass(const UserInterfaceClass&);
	~UserInterfaceClass();

	bool Initialize(D3D*, int, int);
	void Shutdown();

	bool Frame(ID3D11DeviceContext*, int, XMFLOAT3);
	bool Render(D3D*, ShaderManager*, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool UpdateFpsString(ID3D11DeviceContext*, int);

private:
	FontClass* m_Font1;
	TextClass *m_FpsString;
	TextClass *m_VideoStrings;
	int m_previousFps;
	MiniMap* m_miniMap;
	//int m_previousPosition[6];
};

#endif