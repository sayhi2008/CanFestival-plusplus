/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   CfLib.cpp
/// \author Martin Reddy
/// \brief  An example of the CfLib design pattern.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///
#include "CfLib.h"
#include "CfResult.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

namespace canopenlib
{

void nothing(const int id)
{
	printf("==== Slave %d boot up ====\n", id);
}


CfLib &CfLib::GetInstance()
{
	static CfLib instance;
	return instance;
}

CfLib::CfLib()
{
	co_data_ = &HostNode_Data;
	memset(data_,1000,0);
	sucessful_ = false;
	size_ = 0;
	cout << "CfLib created" << endl;
}

CfLib::~CfLib()
{
	cout << "CfLib destroyed" << endl;
}

//void CfLib::init(s_BOARD channel)
//{
//	can_channel_ = channel;
//}

int CfLib::GetState()
{
	// this is where you could return the CfLib's state.
	// I'm keeping it simple for this example though
	return 42;
}


CAN_PORT CfLib::canOpen(s_BOARD board)
{
//	::TimerInit();
	return ::canOpen(&board, co_data_);
}

int CfLib::canClose()
{
//	::TimerCleanup();
	return ::canClose(co_data_);
}


void CfLib::setNodeId(UNS8 nodeId)
{
	::setNodeId(co_data_, nodeId);
}

UNS8 CfLib::getNodeId()
{
	return ::getNodeId(co_data_);
}

UNS8 CfLib::setState(e_nodeState newState)
{
	return ::setState(co_data_, newState);
}

e_nodeState CfLib::getState()
{
	return ::getState(co_data_);
}

UNS8 CfLib::masterSendNMTstateChange(UNS8 nodeId, UNS8 cs)
{
	return ::masterSendNMTstateChange(co_data_, nodeId, cs);
}

UNS8 CfLib::masterRequestNodeState(UNS8 nodeId)
{
	return ::masterRequestNodeState(co_data_, nodeId);
}

void CfLib::heartbeatInit()
{
	::heartbeatInit(CFLIB.co_data_);
}

UNS32 CfLib::cfWriteLocalDict(
		UNS16 wIndex,
		UNS8 bSubindex,
		void * pSourceData,
		UNS32 * pExpectedSize,
		UNS8 checkAccess)
{
	return ::writeLocalDict(
			co_data_,
			wIndex,
			bSubindex,
			pSourceData,
			pExpectedSize,
			checkAccess);
}

UNS32 CfLib::cfSetODentry(
		UNS16 wIndex,
		UNS8 bSubindex,
		void * pSourceData,
		UNS32 * pExpectedSize,
		UNS8 checkAccess)
{
	return ::setODentry(
			co_data_,
			wIndex,
			bSubindex,
			pSourceData,
			pExpectedSize,
			checkAccess);
}

UNS32 CfLib::cfReadLocalDict(
		UNS16 wIndex,
		UNS8 bSubindex,
		void * pDestData,
		UNS32 * pExpectedSize,
		UNS8 * pDataType,
		UNS8 checkAccess)
{
	return ::readLocalDict(
			co_data_,
			wIndex,
			bSubindex,
			pDestData,
			pExpectedSize,
			pDataType,
			checkAccess);
}

UNS32 CfLib::cfGetODentry(
		UNS16 wIndex,
		UNS8 bSubindex,
		void * pDestData,
		UNS32 * pExpectedSize,
		UNS8 * pDataType,
		UNS8 checkAccess)
{
	return ::getODentry(
			co_data_,
			wIndex,
			bSubindex,
			pDestData,
			pExpectedSize,
			pDataType,
			checkAccess);
}

e_nodeState CfLib::getNodeState(UNS8 nodeId)
{
	return ::getNodeState(CFLIB.co_data_, nodeId);
}



////
UNS32 CfLib::RegisterSetODentryCallBack(UNS16 wIndex, UNS8 bSubindex, std::function<void(const indextable *index, UNS8 bSubindex)> func)
{
	odCallback = func;
	return ::RegisterSetODentryCallBack(CFLIB.co_data_, wIndex, bSubindex, odCallbackFwd);
}

UNS32 CfLib::odCallbackFwd(CO_Data* d, const indextable *index, UNS8 bSubindex)
{
	odCallback(index, bSubindex);
	return 0;
}

std::function<void(const indextable *index, UNS8 bSubindex)> CfLib::odCallback;

////


UNS32 CfLib::setDataCb(UNS16 wIndex, UNS8 bSubindex, std::function<void(std::string)> func)
{
	std::map<UNS32, std::function<void(std::string)> >::const_iterator iter = CFLIB.dataCallback.find(wIndex*0x100+bSubindex);
    if (iter != CFLIB.dataCallback.end())
    	CFLIB.dataCallback[wIndex*0x100+bSubindex]=func;
    else
    	CFLIB.dataCallback.insert(std::make_pair(wIndex*0x100+bSubindex, func));

	return ::RegisterSetODentryCallBack(CFLIB.co_data_, wIndex, bSubindex, dataCallbackFwd);
}

UNS32 CfLib::delDataCb(UNS32 funcID)
{
	CFLIB.dataCallback.erase(funcID);
	return ::RegisterSetODentryCallBack(CFLIB.co_data_, funcID>>8, funcID&0xff, NULL);
}


UNS32 CfLib::dataCallbackFwd(CO_Data* d, const indextable *index, UNS8 bSubindex)
{
//	printf("###### %x\n", PDO283_2);
	std::string res;
	UNS32 size8 = sizeof(UNS8);
	UNS8 DataType = uint8;
	UNS8 data;

	for (int i = 0; i < bSubindex; i++)
	{
		CFLIB.cfReadLocalDict(index->index,i+1,&data,&size8,&DataType,RW);
		res.push_back(data);
	}

	std::map<UNS32, std::function<void(std::string)> >::const_iterator iter =
			CFLIB.dataCallback.find(index->index*0x100+bSubindex);
	if (iter == CFLIB.dataCallback.end())
	{
	    printf("No callback for this PDO!!\n");
	}
	else
		CFLIB.dataCallback[index->index*0x100+bSubindex](res);
	return 0;
}


//std::function<void(std::string)> CfLib::dataCallback;








void CfLib::setHeartBeatErrorCb(UNS8 heartbeatID, std::function<void()> func)
{
	CFLIB.heartBeatErrorCb.insert(std::make_pair(heartbeatID, func));
//	heartBeatErrorCb = func;
	CFLIB.co_data_->heartbeatError = heartBeatErrorCbFwd;
}

void CfLib::delHeartBeatErrorCb(UNS8 heartbeatID)
{
	CFLIB.heartBeatErrorCb.erase(heartbeatID);
}

void CfLib::heartBeatErrorCbFwd(CO_Data* d, UNS8 heartbeatID)
{
//	printf("HeartbeatError!!!!! %d\n", heartbeatID);
//	heartBeatErrorCb();
	std::map<UNS8, std::function<void()> >::const_iterator iter = CFLIB.heartBeatErrorCb.find(heartbeatID);
	if (iter == CFLIB.heartBeatErrorCb.end())
	{
//	    printf("Uninitialized Nodes Error:\n");
//	    printf("	ID: %d\n", heartbeatID);
	}
	else
		CFLIB.heartBeatErrorCb[heartbeatID]();
//	CFLIB.initHeartbeat();
}

//std::function<void()> CfLib::heartBeatErrorCb;

////
void CfLib::setInitialisationCb(std::function<void()> func)
{
	initialisationCb = func;
	CFLIB.co_data_->initialisation = initialisationCbFwd;
}

void CfLib::initialisationCbFwd(CO_Data* d)
{
	initialisationCb();
}

std::function<void()> CfLib::initialisationCb;

////
void CfLib::setPreOperationalCb(std::function<void()> func)
{
	preOperationalCb = func;
	CFLIB.co_data_->preOperational = preOperationalCbFwd;
}

void CfLib::preOperationalCbFwd(CO_Data* d)
{
	preOperationalCb();
}

std::function<void()> CfLib::preOperationalCb;

////
void CfLib::setOperationalCb(std::function<void()> func)
{
	operationalCb = func;
	CFLIB.co_data_->operational = operationalCbFwd;
}

void CfLib::operationalCbFwd(CO_Data* d)
{
	operationalCb();
}

std::function<void()> CfLib::operationalCb;

////
void CfLib::setStoppedCb(std::function<void()> func)
{
	stoppedCb = func;
	CFLIB.co_data_->stopped = stoppedCbFwd;
}

void CfLib::stoppedCbFwd(CO_Data* d)
{
	stoppedCb();
}

std::function<void()> CfLib::stoppedCb;

////
void CfLib::setPostSyncCb(std::function<void()> func)
{
	postSyncCb = func;
	CFLIB.co_data_->stopped = postSyncCbFwd;
}

void CfLib::postSyncCbFwd(CO_Data* d)
{
	postSyncCb();
}

std::function<void()> CfLib::postSyncCb;

////
void CfLib::setPostTPDOCb(std::function<void()> func)
{
	postTPDOCb = func;
	CFLIB.co_data_->stopped = postTPDOCbFwd;
}

void CfLib::postTPDOCbFwd(CO_Data* d)
{
	postTPDOCb();
}

std::function<void()> CfLib::postTPDOCb;

////
void CfLib::setPostSlaveBootupCb(std::function<void(const int id)> func)
{
	postSlaveBootupCb = func;
	CFLIB.co_data_->post_SlaveBootup = postSlaveBootupCbFwd;
}

void CfLib::postSlaveBootupCbFwd(CO_Data* d, UNS8 nodeid)
{
//	printf("==== Slave %d boot up ====\n", nodeid);
	postSlaveBootupCb(nodeid);
}

std::function<void(const int id)> CfLib::postSlaveBootupCb;

////
UNS8 CfLib::setSDO(
		UNS8 nodeId,
		UNS16 index,
		UNS8 subIndex,
		UNS8 dataType,
		void* data,
		UNS32 count,
		UNS8 useBlockMode)
{
	UNS8 res;
	res = ::writeNetworkDictCallBack (
			CFLIB.co_data_,
			nodeId,
			index,
			subIndex,
			count,
			dataType,
			data,
			setSDOCbFwd,
			useBlockMode);

	if(CFLIB.wait(100))
	{
		//printf("not time out \n");
	}
	else
		return res;

	if(CFLIB.isSucessful())
		return 0;

//	closeSDOtransfer(CFLIB.co_data_, nodeId, SDO_CLIENT);
	return res;

}

void CfLib::setSDOCbFwd(CO_Data* d, UNS8 nodeId)
{
	UNS32 abortCode;

	if (::getWriteResultNetworkDict(CFLIB.co_data_, nodeId, &abortCode) != SDO_FINISHED)
		printf("SDO Failed at Node %2.2x, AbortCode :%4.4x \n", nodeId, abortCode);
	else CFLIB.setData(0);

	/* Finalise last SDO transfer with this node */
	::closeSDOtransfer(CFLIB.co_data_, nodeId, SDO_CLIENT);
	CFLIB.notify();
}


////


UNS8 CfLib::getSDO(
		UNS8 nodeId,
		UNS16 index,
		UNS8 subIndex,
		UNS8 dataType,
		void* data,
		UNS32 size,
		UNS8 useBlockMode)
{
	UNS8 res;
	res = ::readNetworkDictCallback(
			CFLIB.co_data_,
			nodeId,
			index,
			subIndex,
			dataType,
			getSDOCbFwd,
			useBlockMode);

	if(CFLIB.wait(100))
	{
//		printf("not time out \n");
	}
	else
		return res;

	if(CFLIB.isSucessful())
	{
		if(size != CFLIB.getSize())
			return res;

		memcpy(data,CFLIB.getData(),size);
		return 0;
	}

	//closeSDOtransfer(CFLIB.co_data_, nodeId, SDO_CLIENT);
	return res;
}

void CfLib::getSDOCbFwd(CO_Data* d, UNS8 nodeId)
{
	UNS32 abortCode;
	UNS32 size=64;

	if (::getReadResultNetworkDict(CFLIB.co_data_, nodeId, CFLIB.getData(), &size, &abortCode) != SDO_FINISHED)
		printf("SDO Failed at Node %2.2x, AbortCode :%4.4x \n", nodeId, abortCode);
	else CFLIB.setData(size);

	/* Finalize last SDO transfer with this node */
	::closeSDOtransfer(CFLIB.co_data_, nodeId, SDO_CLIENT);
	CFLIB.notify();
}

//std::function<void(UNS8 nodeId)> CfLib::getSDOCb;

////

void CfLib::TimerInit(void)
{
	return ::TimerInit();
}
void CfLib::TimerCleanup(void)
{
	return ::TimerCleanup();
}


void CfLib::StartTimerLoop(std::function<void()> func)
{
	startTimerLoopCb = func;
	::StartTimerLoop(&startTimerLoopCbFwd);
}

void CfLib::startTimerLoopCbFwd(CO_Data* d, UNS32 id)
{
	startTimerLoopCb();
}

std::function<void()> CfLib::startTimerLoopCb;

////
void CfLib::StopTimerLoop(std::function<void()> func)
{
	stopTimerLoopCb = func;
	::StopTimerLoop(&stopTimerLoopCbFwd);
}

void CfLib::stopTimerLoopCbFwd(CO_Data* d, UNS32 id)
{
	stopTimerLoopCb();
}

std::function<void()> CfLib::stopTimerLoopCb;

////


//UNS8 CfLib::sendPDO()
//{
//	return ::sendPDOevent(co_data_);
//}
//
//UNS8 CfLib::sendOnePDO(UNS8 pdoNum)
//{
//	return ::sendOnePDOevent(co_data_, pdoNum);
//}



//void CfLib::Open()
//{
//
//}
//
//void CfLib::Close()
//{
//
//}


void * CfLib::getData()
{
	return data_;
}


void CfLib::setData( int size)
{
	sucessful_ = true;
	size_ = size;
}

int CfLib::getSize()
{
	return size_;
}

bool CfLib::isSucessful()
{
	return sucessful_;
}

bool CfLib::wait(int t)
{
	sucessful_ = false;
	std::unique_lock<std::mutex> lock(m_mutex_wait);
	auto const timeout= std::chrono::system_clock::now() + std::chrono::milliseconds(t);
	bool hasResult ;

	if(t < 0){
		m_cond_wait.wait(lock);
		return true;
	}
	else
		if(m_cond_wait.wait_until(lock, timeout) == std::cv_status::timeout)
			hasResult = false;
		else
			hasResult = true;

	return hasResult;
}

void CfLib::notify()
{
	std::unique_lock<std::mutex> lock(m_mutex_wait);
	m_cond_wait.notify_one();
}



}
