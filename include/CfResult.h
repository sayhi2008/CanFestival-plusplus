#ifndef __CFRESULT_H__
#define __CFRESULT_H__

#if defined(WIN32) && !defined(__CYGWIN__)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
#endif
#include <string>

namespace canopenlib
{

class CfResult{
private:
	int id_;
	std::string descript_;

public:
	CfResult(int id, std::string des);

	std::string GetDescript() const;

	int GetId() const;


	static const CfResult CO_OK;
	static const CfResult CO_NORMAL_ERROR;
	static const CfResult CO_SDO_ERROR;
	static const CfResult CO_PDO_ERROR;
	static const CfResult CO_SDO_SIZE_ERROR;
	static const CfResult CO_NODE_PreInitialisation;
	static const CfResult CO_NODE_Initialisation;
	static const CfResult CO_NODE_Disconnected;
	static const CfResult CO_NODE_Connecting;
	static const CfResult CO_NODE_Preparing;
	static const CfResult CO_NODE_Stopped;
	static const CfResult CO_NODE_Operational;
	static const CfResult CO_NODE_Pre_operational;
	static const CfResult CO_NODE_UnknownState;
	static const CfResult CO_NMT_ERROR;
	static const CfResult CO_INITIAL_ERROR;
};



}

#endif
