#if defined(WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

#include "CfNode.h"
#include "HostNode.h"



namespace canopenlib {




CfNode::CfNode():nh_(CFLIB){}

CfNode::~CfNode(){}

//bool CfNode::init(CfLib &node_handle, UNS8 id) {
//	nh_ = node_handle;
//	node_id_ = id;
//	return true;
//}


const CfResult* CfNode::init(UNS8 id)
{
	node_id_ = id;
//	if (nh_.getNetNodeState(id) == 1 || nh_.getNetNodeState(id) == 0x0F)
//		return &CfResult::CO_INITIAL_ERROR;
//	return goOperational();
	return &CfResult::CO_OK;
}

const CfResult* CfNode::cleanup()
{
	nh_.delHeartBeatErrorCb(node_id_);
	nh_.delPostEmcyCb(node_id_);
	const UNS8 offset = (node_id_-1)*4;
	for(int i=0x2000+offset; i<0x2000+offset+4; i++)
		for(int j=1; j<9; j++)
			nh_.delDataCb(i*0x100+j);
}


const CfResult* CfNode::goReset()
{
	if(nh_.masterSendNMTstateChange(node_id_, NMT_Reset_Node))
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::goPreOperational()
{
	if(nh_.masterSendNMTstateChange(node_id_, NMT_Enter_PreOperational))
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::goOperational()
{
	if(nh_.masterSendNMTstateChange(node_id_, NMT_Start_Node))
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::goStopped()
{
	if(nh_.masterSendNMTstateChange(node_id_, NMT_Stop_Node))
		return &CfResult::CO_NMT_ERROR;
	else
		return &CfResult::CO_OK;
}


const CfResult* CfNode::setCommPara(CommSettings &setting)
{
	const CfResult *e;
	e = setHbPeriod(setting.heartbeatPeriod);
	if(e->GetId())
		return e;

	if(setting.synchProducer)
		e = startSync();
	else
		e = stopSync();
	if(e->GetId())
		return e;

	e = setSyncPeriod(setting.synchPeriod);
	if(e->GetId())
		return e;

	e = setSyncWindow(setting.synchWindow);

	return e;

}

const CfResult* CfNode::saveCommPara(void)
{
	UNS32 value = 0x65766173;
	if(nh_.setSDO(node_id_, 0x1010, 2, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::loadCommPara(bool load)
{
	UNS32 value = 0x64616f6c;
	if(!load)
		value = 0;
	if(nh_.setSDO(node_id_, 0x1011, 2, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::startSync(void)
{
	UNS32 value = 0x40000080;
	if(nh_.setSDO(node_id_, 0x1005, 0, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::stopSync(void)
{
	UNS32 value = 0x00000080;
	if(nh_.setSDO(node_id_, 0x1005, 0, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::setSyncPeriod(UNS32 period)
{
	if(nh_.setSDO(node_id_, 0x1006, 0, 0, &period, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::getSyncPeriod(UNS32* period)
{
	if(nh_.getSDO(node_id_, 0x1006, 0, 0, period, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::setSyncWindow(UNS32 window)
{
	if(nh_.setSDO(node_id_, 0x1007, 0, 0, &window, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::getSyncWindow(UNS32* window)
{
	if(nh_.getSDO(node_id_, 0x1007, 0, 0, window, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::getTimeStamp(UNS32* value)
{
	if(nh_.getSDO(node_id_, TimeStamp, 0, 0, value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::setTimeStamp(UNS32 value)
{
	if(nh_.setSDO(node_id_, TimeStamp, 0, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::setHbPeriod(UNS16 period)
{
	UNS32 consumer_period = node_id_*0x10000 + 5 + period;
	UNS32 size = 4;
	nh_.cfWriteLocalDict(0x1016, node_id_, &consumer_period, &size, RW);
	if(nh_.setSDO(node_id_, 0x1017, 0, 0, &period, 2, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::getHbPeriod(UNS16* period)
{
	if(nh_.getSDO(node_id_, 0x1017, 0, 0, period, 2, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

//const CfResult* CfNode::getID(UNS8* id)
//{
//	*id = node_id_;
//	return &CfResult::CO_OK;
//}



const CfResult* CfNode::setHeartBeatErrorCb(std::function<void()> func)
{
	nh_.setHeartBeatErrorCb(node_id_, func);
}

const CfResult* CfNode::setPostEmcyCb(std::function<void(UNS16 errCode, UNS8 errReg)> func)
{
	nh_.setPostEmcyCb(node_id_, func);
}

const CfResult* CfNode::setTPDOTransType(UNS8 TPDO_id, UNS8 value)
{
	if(nh_.setSDO(node_id_, TPDO_PARAMETER + TPDO_id - 1, 2, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::getTPDOTransType(UNS8 TPDO_id, UNS8* value)
{
	if(nh_.getSDO(node_id_, TPDO_PARAMETER + TPDO_id - 1, 2, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::setTPDOInhibitTime(UNS8 TPDO_id, UNS16 value)
{
	if(nh_.setSDO(node_id_, TPDO_PARAMETER + TPDO_id - 1, 3, 0, &value, 2, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::getTPDOInhibitTime(UNS8 TPDO_id, UNS16* value)
{
	if(nh_.getSDO(node_id_, TPDO_PARAMETER + TPDO_id - 1, 3, 0, value, 2, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::setTPDOCompEntry(UNS8 TPDO_id, UNS8 value)
{
	if(nh_.setSDO(node_id_, TPDO_PARAMETER + TPDO_id - 1, 4, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::getTPDOCompEntry(UNS8 TPDO_id, UNS8* value)
{
	if(nh_.getSDO(node_id_, TPDO_PARAMETER + TPDO_id - 1, 4, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::setTPDOEventTimer(UNS8 TPDO_id, UNS16 value)
{
	if(nh_.setSDO(node_id_, TPDO_PARAMETER + TPDO_id - 1, 5, 0, &value, 2, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult* CfNode::getTPDOEventTimer(UNS8 TPDO_id, UNS16* value)
{
	if(nh_.getSDO(node_id_, TPDO_PARAMETER + TPDO_id - 1, 5, 0, value, 2, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}





const CfResult* CfNode::setTPDOMapping(UNS8 PDO_id, UNS8 sub_index,UNS32 value)
{
	if(nh_.setSDO(node_id_, TPDO_MAPPING + PDO_id - 1, sub_index, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}




const CfResult* CfNode::getTPDOMapping(UNS8 PDO_id, UNS8 sub_index, UNS32* value)
{
	if(nh_.getSDO(node_id_, TPDO_MAPPING + PDO_id - 1, sub_index, 0, value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}


const CfResult* CfNode::subscribePDO(UNS8 PDO_id, std::function<void(std::string)> func)
{
	UNS32 suboffset = 0;
	UNS32 value;
	UNS8 total;
	const UNS8 offset = (node_id_-1)*4+(PDO_id-1);
	UNS32 size32 = sizeof(UNS32);
	nh_.getSDO(node_id_, TPDO_MAPPING + PDO_id - 1, 0, 0, &total, 1, 0);

	for(int i=1; i<= total; i++)
	{
		nh_.getSDO(node_id_, TPDO_MAPPING + PDO_id - 1, i, 0, &value, 4, 0);
		suboffset += value;
	}
	suboffset = (suboffset & 0xff)/8;

	if(suboffset)
		nh_.setDataCb(0x2000+offset, suboffset , func);
}

}
