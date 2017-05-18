#ifndef _CPUCLASS_H_
#define _CPUCLASS_H_

/////////////
// LINKING //
/////////////
#pragma comment(lib, "pdh.lib")

//////////////
// INCLUDES //
//////////////
#include <pdh.h>

class CpuClass
{
public:
	CpuClass();
	CpuClass(const CpuClass&);
	~CpuClass();

	void Initialize();
	void Shutdown();
	void Frame();
	int GetCpuPercentage();

private:
	bool m_canReadCpu;
	HQUERY m_queryHandle;
	HCOUNTER m_counterHandle;
	unsigned long m_lastSampleTime;
	long m_cpuUsage;
};

#endif "_CPUCLASS_H_"