#if defined(WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

#include "CfSystem.h"
//#include "HostNode.h"
//#include "canfestival.h"

namespace canopenlib {

CfSystem::CfSystem():nh_(CFLIB)
{}

CfSystem::~CfSystem()
{}

//void CfSystem::init(s_BOARD board, int id) {
//	node_id_ = id;
//	co_data_ = &HostNode_Data;
//	masterBoard = board;
//
//	TimerInit();
//}


void CfSystem::setID(UNS8 id)
{
	nh_.setNodeId(id);
}

UNS8 CfSystem::getID()
{
	return nh_.getNodeId();
}

const CfResult*  CfSystem::init(s_BOARD board, UNS8 id)
{
	nh_.TimerInit();
	nh_.canOpen(board);
	if(nh_.getNodeId() == 0)
	{
		nh_.setNodeId(id);
		nh_.setState(Initialisation);
		nh_.setState(Operational);
	}

}

std::vector<int> CfSystem::scan()
{
	sleep(1);
	UNS8 id;
	std::vector<int> slave_node_;
	for(id = 1; id < 128; id++)
		if(nh_.getNodeState(id) != 1 && nh_.getNodeState(id) != 0x0f && id != getID())
			slave_node_.push_back(id);

	return slave_node_;
}



const CfResult* CfSystem::cleanup()
{
	nh_.setState(Stopped);
	nh_.canClose();
	nh_.TimerCleanup();
}

const CfResult* CfSystem::goReset()
{
	UNS8 res;
	res = nh_.setState(Initialisation);
	if(res == 0xff)
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfSystem::goPreOperational()
{
	UNS8 res;
	res = nh_.setState(Pre_operational);
	if(res == 0xff)
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfSystem::goOperational()
{
	UNS8 res;
	res = nh_.setState(Operational);
	if(res == 0xff)
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfSystem::goStopped()
{
	UNS8 res;
	res = nh_.setState(Stopped);
	if(res == 0xff)
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfSystem::sysReset()
{
	if(nh_.masterSendNMTstateChange(0, NMT_Reset_Node))
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfSystem::sysPreOperational()
{
	if(nh_.masterSendNMTstateChange(0, NMT_Enter_PreOperational))
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfSystem::sysOperational()
{
	if(nh_.masterSendNMTstateChange(0, NMT_Start_Node))
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfSystem::sysStopped()
{
	if(nh_.masterSendNMTstateChange(0, NMT_Stop_Node))
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

}
