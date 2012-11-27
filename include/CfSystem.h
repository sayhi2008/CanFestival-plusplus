#ifndef __CFSYSTEM_H__
#define __CFSYSTEM_H__

#if defined(WIN32) && !defined(__CYGWIN__)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
#endif

#include <vector>
#include "CfLib.h"
#include "CfResult.h"

namespace canopenlib
{

class CfSystem
{
private:
	CfLib &nh_;

public:
	CfSystem();
    ~CfSystem();
    const CfResult* init(s_BOARD board, UNS8 id);
    const CfResult* cleanup();

    const CfResult* goReset();
    const CfResult* goPreOperational();
    const CfResult* goOperational();
    const CfResult* goStopped();

    const CfResult* sysReset();
    const CfResult* sysPreOperational();
    const CfResult* sysOperational();
    const CfResult* sysStopped();

    void setID(UNS8 id);
    UNS8 getID();

    std::vector<int> scan();
};

}

#endif
