#include "Component.h"

Component::Component()
{

}

Component::Component(unsigned index, char* type)
{
	m_index = index;
	m_type = type;
}

Component::Component(const Component&){}

Component::~Component(){}

unsigned Component::GetIndex()
{
	return m_index;
}

char* Component::GetType()
{
	return m_type;
}