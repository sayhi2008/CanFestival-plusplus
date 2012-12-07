/**
 * @file   CfNode.h
 * @author Simon CHENG ye
 * @brief  CanOpen device node functions.
 */
#ifndef __CFNODE_H__
#define __CFNODE_H__

#if defined(WIN32) && !defined(__CYGWIN__)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>

#endif

#include <iostream>
#include <functional>
#include "canfestival.h"
#include "CfResult.h"
#include "CfLib.h"

namespace canopenlib
{

enum COMM_OBJID
{
	TimeStamp 			= 0x1013,
	TPDO_PARAMETER		= 0x1800,
	TPDO_MAPPING		= 0x1A00
};

struct CommSettings
{
   UNS32 synchPeriod;
   UNS32 synchWindow;
   bool synchProducer;
   UNS16 heartbeatPeriod;
   CommSettings(void)
   {
	   synchProducer    = false;
	   synchPeriod      = 0x0007a120;
	   synchWindow      = 0x0003d090;
	   heartbeatPeriod  = 0x03E8;
   }
};

///
/// This class is a CanOpen device node.
///
class CfNode
{

protected:
	CfLib &nh_;
	UNS8 node_id_;

public:
    CfNode();
    ~CfNode();

	/**
	 * @ingroup CfNode
	 * @brief Initiate the device node
	 * @param id Device node ID
	 */
    const CfResult*
    init(UNS8 id);

	/**
	 * @ingroup CfNode
	 * @brief Cleanup the device node.
	 * @return
	 */
    const CfResult*
    cleanup();

	/**
	 * @ingroup CfNode
	 * @brief Make device node go into Initialisation state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    goReset();

	/**
	 * @ingroup CfNode
	 * @brief Make device node go into PreOperational state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    goPreOperational();

	/**
	 * @ingroup CfNode
	 * @brief Make device node go into Operational state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    goOperational();

	/**
	 * @ingroup CfNode
	 * @brief Make device node go into Stopped state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    goStopped();

	/**
	 * @ingroup CfNode
	 * @brief Setup the communication parameters of device node.
	 * @param &setting The struct address of communication parameters.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    setCommPara(CommSettings &setting);

	/**
	 * @ingroup CfNode
	 * @brief Save the communication parameters of device node to flash.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    saveCommPara(void);

	/**
	 * @ingroup CfNode
	 * @brief Load the communication parameters of device node from flash when device boot up.
	 * @param load
	 * 		- True if you want to load the communication parameters of device node from flash when device boot up.
	 * 		- False if you want to load the default communication parameters of device node.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    loadCommPara(bool load);

	/**
	 * @ingroup CfNode
	 * @brief Turn this device to be a sync signal producer.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    startSync(void);

	/**
	 * @ingroup CfNode
	 * @brief Turn this device NOT to be a sync signal producer.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    stopSync(void);

	/**
	 * @ingroup CfNode
	 * @brief Set the sync period of device node.
	 * @param period The period of sync signal (us)
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    setSyncPeriod(UNS32 period);

	/**
	 * @ingroup CfNode
	 * @brief Get the sync period of device node.
	 * @param period The variable stores the return value (us)
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    getSyncPeriod(UNS32* period);

	/**
	 * @ingroup CfNode
	 * @brief Set the sync window of device node.
	 * @param window The period of sync signal (us)
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    setSyncWindow(UNS32 window);

	/**
	 * @ingroup CfNode
	 * @brief Get the sync window of device node.
	 * @param window The variable stores the return value (us)
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    getSyncWindow(UNS32* window);

	/**
	 * @ingroup CfNode
	 * @brief Adjust the timer of device node.
	 * @param window The period of sync signal (us)
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    setTimeStamp(UNS32 time);

	/**
	 * @ingroup CfNode
	 * @brief Get current time of device node.
	 * @param time The variable stores the return value (us)
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    getTimeStamp(UNS32* time);

	/**
	 * @ingroup CfNode
	 * @brief Set the heart beat period of device node.
	 * @param period The period of sync signal (ms)
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    setHbPeriod(UNS16 period);

	/**
	 * @ingroup CfNode
	 * @brief Get the heart beat period of device node.
	 * @param period The variable stores the return value (us)
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    getHbPeriod(UNS16* period);

	/**
	 * @ingroup CfNode
	 * @brief Set a TPDO transmit type of device node.
	 * @param TPDO_id TPDO ID
	 * @param value transmit type
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_SDO_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    setTPDOTransType(UNS8 TPDO_id, UNS8 value);


    const CfResult* getTPDOTransType(UNS8 TPDO_id, UNS8* value);
    const CfResult* setTPDOInhibitTime(UNS8 TPDO_id, UNS16 value);
    const CfResult* getTPDOInhibitTime(UNS8 TPDO_id, UNS16* value);
    const CfResult* setTPDOCompEntry(UNS8 TPDO_id, UNS8 value);
    const CfResult* getTPDOCompEntry(UNS8 TPDO_id, UNS8* value);
    const CfResult* setTPDOEventTimer(UNS8 TPDO_id, UNS16 value);
    const CfResult* getTPDOEventTimer(UNS8 TPDO_id, UNS16* value);

    const CfResult* setTPDOMapping(UNS8 PDO_id, UNS8 sub_index,UNS32 value);
    const CfResult* getTPDOMapping(UNS8 PDO_id, UNS8 sub_index, UNS32 * value);
    const CfResult* subscribePDO(UNS8 PDO_id, std::function<void(std::string)> func);
    const CfResult* setHeartBeatErrorCb(std::function<void()> func);
    const CfResult* setPostEmcyCb(std::function<void(UNS16 errCode, UNS8 errReg)> func);

};
}
#endif
