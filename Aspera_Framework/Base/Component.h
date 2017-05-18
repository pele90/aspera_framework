#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <vector>
using namespace std;

class Component
{
public:
	Component();
	Component(unsigned, char *);
	Component(const Component&);
	~Component();

	unsigned GetIndex();
	char* GetType();

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

private:
	unsigned m_index;
	char* m_type;
};

#endif // !_COMPONENT_H_

