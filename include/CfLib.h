/**
 * @file   CfLib.h
 * @author Simon CHENG ye
 * @brief  Canfestival C++ wrapper header.
 */

#ifndef __CFLIB_H__
#define __CFLIB_H__



#if defined(WIN32) && !defined(__CYGWIN__)
	#include <windows.h>
	#define SLEEP(time) Sleep(time * 1000)
#else
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
#endif

#include "HostNode.h"
#include "canfestival.h"
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <mutex>
#include <thread>
#include <chrono>
#include <cassert>



namespace canopenlib
{
///
/// This class is a simple C++ singleton wrapper of some useful CanFestival functions.
///
class CfLib
{
public:

	/**
	 * @ingroup canfestival
	 * @brief Open a CANOpen device
	 * @param *board Pointer to the board structure that contains busname and
	 * baudrate
	 * @return
	 *       - CanFestival file descriptor is returned upon success.
	 *       - NULL is returned if the CANOpen board can't be opened.
	 */
	CAN_PORT
	canOpen(s_BOARD board);

	/**
	 * @ingroup canfestival
	 * @brief Close a CANOpen device
	 * @return
	 *       - 0 is returned upon success.
	 *       - errorcode if error. (if implemented)
	 */
	int
	canClose();

	/**
	 * @ingroup states
	 * @brief Define the node ID. Initialize the object dictionary
	 * @param nodeId The node ID to assign
	 */
	void
	setNodeId(UNS8 nodeId);

	/**
	 * @ingroup states
	 * @brief Returns the nodId
	 * @return The node state
	 */
	UNS8
	getNodeId();

	/**
	 * @ingroup states
	 * @brief Change the state of the node
	 * @param newState The state to assign
	 * @return
	 */
	UNS8
	setState(e_nodeState newState);

	/**
	 * @ingroup states
	 * @brief Returns the state of the node
	 * @return The node state
	 */
	e_nodeState
	getState();

	/**
	 * @ingroup nmtMaster
	 * @brief Transmit a NMT message on the network to the slave whose nodeId is node ID.
	 *
	 * @param *d Pointer to a CAN object data structure
	 * @param nodeId Id of the slave node
	 * @param cs The order of state changement \n\n
	 *
	 * Allowed states :
	 *  - cs =  NMT_Start_Node               // Put the node in operational mode
	 *  - cs =	NMT_Stop_Node		         // Put the node in stopped mode
	 *  - cs =	NMT_Enter_PreOperational     // Put the node in pre_operational mode
	 *  - cs =  NMT_Reset_Node		         // Put the node in initialization mode
	 *  - cs =  NMT_Reset_Comunication	     // Put the node in initialization mode
	 *
	 * The mode is changed according to the slave state machine mode :
	 *  - initialisation  ---> pre-operational (Automatic transition)
	 *  - pre-operational <--> operational
	 *  - pre-operational <--> stopped
	 *  - pre-operational, operational, stopped -> initialisation
	 * \n\n
	 * @return errorcode
	 *                   - 0 if the NMT message was send
	 *                   - 1 if an error occurs
	 */
	UNS8
	masterSendNMTstateChange(UNS8 nodeId, UNS8 cs);

	/**
	 * @ingroup nmtMaster
	 * @brief Ask the state of the slave node whose nodeId is node Id.
	 *
	 * To ask states of all nodes on the network (NMT broadcast), nodeId must be equal to 0
	 * @param nodeId Id of the slave node
	 */
	UNS8
	masterRequestNodeState(UNS8 nodeId);

	/** @fn UNS32 writeLocalDict(d, wIndex, bSubindex, pSourceData, pExpectedSize, checkAccess)
	 * @ingroup objacces
	 * @hideinitializer
	 * @brief Writes machine native SourceData to OD.
	 * @param wIndex The index in the object dictionary where you want to write
	 *               an entry
	 * @param bSubindex The subindex of the Index. e.g. mostly subindex 0 is
	 *                  used to tell you how many valid entries you can find
	 *                  in this index. Look at the canopen standard for further
	 *                  information
	 * @param *pSourceData Pointer to the variable that holds the value that should
	 *                     be copied into the object dictionary
	 * @param *pExpectedSize The size of the value (in Byte).
	 * @param checkAccess Flag that indicate if a check rights must be perfomed (0 : no , other than 0 : yes)
	 * @param endianize Data is not endianized and copied in machine native endianness
	 * @return
	 * - OD_SUCCESSFUL is returned upon success.
	 * - SDO abort code is returned if error occurs . (See file def.h)
	 * \n\n
	 * @code
	 * // Example usage:
	 * UNS8 B;
	 * B = 0xFF; // set transmission type
	 *
	 * retcode = writeLocalDict( (UNS16)0x1800, (UNS8)2, &B, sizeof(UNS8), 1 );
	 * @endcode
	 */
	UNS32
	cfWriteLocalDict(
			UNS16 wIndex, UNS8 bSubindex,
            void * pSourceData, UNS32 * pExpectedSize,
            UNS8 checkAccess);

	/**
	 * @ingroup objacces
	 * @brief setODentry converts SourceData from network byte order to machine native
	 * format, and writes that to OD.
	 * @code
	 * // Example usage:
	 * UNS8 B;
	 * B = 0xFF; // set transmission type
	 *
	 * retcode = setODentry( (UNS16)0x1800, (UNS8)2, &B, sizeof(UNS8), 1 );
	 * @endcode
	 * @param wIndex The index in the object dictionary where you want to write
	 *               an entry
	 * @param bSubindex The subindex of the Index. e.g. mostly subindex 0 is
	 *                  used to tell you how many valid entries you can find
	 *                  in this index. Look at the canopen standard for further
	 *                  information
	 * @param *pSourceData Pointer to the variable that holds the value that should
	 *                     be copied into the object dictionary
	 * @param *pExpectedSize The size of the value (in Byte).
	 * @param checkAccess Flag that indicate if a check rights must be perfomed (0 : no , other than 0 : yes)
	 * @param endianize Set to 1 : endianized into network byte order
	 * @return
	 * - OD_SUCCESSFUL is returned upon success.
	 * - SDO abort code is returned if error occurs . (See file def.h)
	 */
	UNS32
	cfSetODentry(
			UNS16 wIndex, UNS8 bSubindex,
            void * pSourceData, UNS32 * pExpectedSize,
            UNS8 checkAccess);

	/**
	 * @ingroup objacces
	 * @brief readLocalDict() reads an entry from the object dictionary, but in
	 * contrast to getODentry(), readLocalDict() doesn't endianize entry and reads
	 * entry in machine native endianness.
	 * @param wIndex The index in the object dictionary where you want to read
	 *                an entry
	 * @param bSubindex The subindex of the Index. e.g. mostly subindex 0 is
	 *                  used to tell you how many valid entries you can find
	 *                  in this index. Look at the canopen standard for further
	 *                  information
	 * @param *pDestData Pointer to the pointer which points to the variable where
	 *                   the value of this object dictionary entry should be copied
	 * @param pExpectedSize This function writes the size of the copied value (in Byte)
	 *                      into this variable.
	 * @param *pDataType Pointer to the type of the data. See objdictdef.h
	 * @param checkAccess if other than 0, do not read if the data is Write Only
	 *                    [Not used today. Put always 0].
	 * @param endianize Set to 0, data is not endianized and copied in machine native
	 *                  endianness
	 * @return
	 * - OD_SUCCESSFUL is returned upon success.
	 * - SDO abort code is returned if error occurs . (See file def.h)
	 */
	UNS32
	cfReadLocalDict(
			UNS16 wIndex, UNS8 bSubindex,
		    void * pDestData, UNS32 * pExpectedSize,
		    UNS8 * pDataType, UNS8 checkAccess);

	/**
	 * @ingroup objacces
	 * @brief getODentry() to read from object and endianize
	 * @param wIndex The index in the object dictionary where you want to read
	 *                an entry
	 * @param bSubindex The subindex of the Index. e.g. mostly subindex 0 is
	 *                  used to tell you how many valid entries you can find
	 *                  in this index. Look at the canopen standard for further
	 *                  information
	 * @param *pDestData Pointer to the pointer which points to the variable where
	 *                   the value of this object dictionary entry should be copied
	 * @param pExpectedSize This function writes the size of the copied value (in Byte)
	 *                      into this variable.
	 * @param *pDataType Pointer to the type of the data. See objdictdef.h
	 * @param checkAccess Flag that indicate if a check rights must be perfomed (0 : no , other than 0 : yes)
	 * @param endianize  Set to 1 : endianized into network byte order
	 * @return
	 * - OD_SUCCESSFUL is returned upon success.
	 * - SDO abort code is returned if error occurs . (See file def.h)
	 */
	UNS32
	cfGetODentry(
			UNS16 wIndex, UNS8 bSubindex,
		    void * pDestData, UNS32 * pExpectedSize,
		    UNS8 * pDataType, UNS8 checkAccess);


	static UNS32
	RegisterSetODentryCallBack(
			UNS16 wIndex, UNS8 bSubindex,
			std::function<void(const indextable *index, UNS8 bSubindex)> func);


	static UNS32
	setDataCb(UNS16 wIndex, UNS8 bSubindex, std::function<void(std::string)> func);

	static UNS32
	delDataCb(UNS32 funcID);

	/**
	 * @ingroup lifegrd
	 * @brief To read the state of a node
	 * This can be used by the master after having sent a life guard request,
	 * of by any node if it is waiting for heartbeat.
	 * @param nodeId Id of a node
	 * @return e_nodeState State of the node corresponding to the nodeId
	 */
	e_nodeState
	getNodeState(UNS8 nodeId);

	/**
	 * @brief Start heartbeat consumer and producer
	 * with respect to 0x1016 and 0x1017
	 * object dictionary entries
	 * @ingroup lifegrd
	 */
	void
	heartbeatInit();

	/**
	 * @ingroup sdo
	 * @brief Used to send a SDO request frame to write in a distant node dictionnary.
	 * @param nodeId Node Id of the slave
	 * @param index At index indicated
	 * @param subIndex At subIndex indicated
	 * @param dataType (defined in objdictdef.h) : put "visible_string" for strings, 0 for integers or reals or other value.
	 * @param *data Pointer to data
	 * @param count number of bytes to write in the dictionnary.
	 * @param useBlockMode
	 * @return
	 * - 0 is returned upon success.
	 * - 0xFE is returned when no sdo client to communicate with node.
	 * - 0xFF is returned when error occurs.
	 */
	UNS8
	setSDO(UNS8 nodeId, UNS16 index,
			UNS8 subIndex, UNS8 dataType,
			void* data, UNS32 count,
			UNS8 useBlockMode);

	/**
	 * @ingroup sdo
	 * @brief Used to send a SDO request frame to read in a distant node dictionnary.
	 * @param nodeId Node Id of the slave
	 * @param index At index indicated
	 * @param subIndex At subIndex indicated
	 * @param dataType (defined in objdictdef.h) : put "visible_string" for strings, 0 for integers or reals or other value.
	 * @param *data Pointer to data
	 * @param size number of bytes to write in the dictionnary.
	 * @param Callback Callback function
	 * @param useBlockMode
	 * @return
	 * - 0 is returned upon success.
	 * - 0xFE is returned when no sdo client to communicate with node.
	 * - 0xFF is returned when error occurs.
	 */
	UNS8
	getSDO(UNS8 nodeId, UNS16 index,
			UNS8 subIndex, UNS8 dataType,
			void* data, UNS32 size,
			UNS8 useBlockMode);

	// data.h
	static void
	setHeartBeatErrorCb(UNS8 heartbeatID, std::function<void()> func);

	static void
	delHeartBeatErrorCb(UNS8 heartbeatID);

	static void
	setInitialisationCb(std::function<void()> func);

	static void
	setPreOperationalCb(std::function<void()> func);

	static void
	setOperationalCb(std::function<void()> func);

	static void
	setStoppedCb(std::function<void()> func);

	static void
	setPostSyncCb(std::function<void()> func);

	static void
	setPostTPDOCb(std::function<void()> func);

	static void
	setPostSlaveBootupCb(std::function<void(const int id)> func);

	static void
	setPostEmcyCb(UNS8 nodeID, std::function<void(UNS16 errCode, UNS8 errReg)> func);

	static void
	delPostEmcyCb(UNS8 nodeID);

	/**
	 * @ingroup timers_driver
	 * @brief Initialize Timer
	 */
	void
	TimerInit(void);

	/**
	 * @ingroup timers_driver
	 * @brief Cleanup Timer
	 */
	void
	TimerCleanup(void);

	/**
	 * @ingroup timers_driver
	 * @brief Start the timer task
	 * @param func A callback function
	 */
	void
	StartTimerLoop(std::function<void()> func);

	/**
	 * @ingroup timers_driver
	 * @brief Stop the timer task
	 * @param func A callback function
	 */
	void
	StopTimerLoop(std::function<void()> func);


//	UNS8 sendPDO();
//	UNS8 sendOnePDO(UNS8 pdoNum);

	/// Return the single instance of this class
	static CfLib &GetInstance();

	/// Return some class-specific single-instance state
	int GetState();



private:
	CO_Data* co_data_ ;

	char data_[1000];
	int size_;
	bool sucessful_;
	std::mutex m_mutex_wait;
	std::condition_variable_any m_cond_wait;

	// Prevent construction and copying of this class
	CfLib();
	~CfLib();
	//void init(s_BOARD);
	CfLib(const CfLib &);
	const CfLib &operator =(const CfLib &);

	//Set OD Callback
	static std::function<void(const indextable *index, UNS8 bSubindex)> odCallback;
	static UNS32 odCallbackFwd(CO_Data* d, const indextable *index, UNS8 bSubindex);

	//Set Data Callback
	std::map<UNS32, std::function<void(std::string)> > dataCallback;
	static UNS32 dataCallbackFwd(CO_Data* d, const indextable *index, UNS8 bSubindex);

	//Set HeartBeatError Callback
	std::map<UNS8, std::function<void()> > heartBeatErrorCb;
	static void heartBeatErrorCbFwd(CO_Data* d, UNS8 heartbeatID);

	//Set PostEmcy Callback
	std::map<UNS8, std::function<void(UNS16 errCode, UNS8 errReg)> > postEmcyCb;
	static void postEmcyCbFwd(CO_Data* d, UNS8 nodeID, UNS16 errCode, UNS8 errReg);

	//Set Initialisation Callback
	static std::function<void()> initialisationCb;
	static void initialisationCbFwd(CO_Data* d);

	//Set PreOperational Callback
	static std::function<void()> preOperationalCb;
	static void preOperationalCbFwd(CO_Data* d);

	//Set Operational Callback
	static std::function<void()> operationalCb;
	static void operationalCbFwd(CO_Data* d);

	//Set Stopped Callback
	static std::function<void()> stoppedCb;
	static void stoppedCbFwd(CO_Data* d);

	//Set PostSync Callback
	static std::function<void()> postSyncCb;
	static void postSyncCbFwd(CO_Data* d);

	//Set PostTPDO Callback
	static std::function<void()> postTPDOCb;
	static void postTPDOCbFwd(CO_Data* d);

	//Set PostSlaveBootup Callback
	static std::function<void(const int id)> postSlaveBootupCb;
	static void postSlaveBootupCbFwd(CO_Data* d, UNS8 nodeid);

	//Set Write SDO Callback
	static void setSDOCbFwd(CO_Data* d, UNS8 nodeId);

	//Set Read SDO Callback
	static void getSDOCbFwd(CO_Data* d, UNS8 nodeId);

	//Set StartTimerLoop Callback
	static std::function<void()> startTimerLoopCb;
	static void startTimerLoopCbFwd(CO_Data* d, UNS32 id);

	//Set StopTimerLoop Callback
	static std::function<void()> stopTimerLoopCb;
	static void stopTimerLoopCbFwd(CO_Data* d, UNS32 id);

	void * getData();
	void setData(int size);
	int getSize();
	bool isSucessful();
	bool wait(int t);
	void notify();

};

void EnterMutex(void);

void LeaveMutex(void);

}

#define CFLIB canopenlib::CfLib::GetInstance()

#endif
