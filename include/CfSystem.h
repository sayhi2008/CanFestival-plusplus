/**
 * @file   CfSystem.h
 * @author Simon CHENG ye
 * @brief  CanOpen host node functions.
 */
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
///
/// This class is a CanOpen host node.
///
class CfSystem
{
private:
	CfLib &nh_;

public:
	/**
	 * @ingroup CfSystem
	 * @brief Constructor
	 */
	CfSystem();

	/**
	 * @ingroup CfSystem
	 * @brief Destructor
	 */
    ~CfSystem();

	/**
	 * @ingroup CfSystem
	 * @brief Initiate the host node
	 * @param *board Pointer to the board structure that contains busname and baudrate.
	 * @param id Host node ID
	 */
    const CfResult*
    init(s_BOARD board, UNS8 id);

	/**
	 * @ingroup CfSystem
	 * @brief Cleanup the host node. You should cleanup all device nodes before
	 * cleanup the host node.
	 * @return
	 */
    const CfResult*
    cleanup();

	/**
	 * @ingroup CfSystem
	 * @brief Make host node go into Initialisation state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    goReset();

	/**
	 * @ingroup CfSystem
	 * @brief Make host node go into PreOperational state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult* goPreOperational();

	/**
	 * @ingroup CfSystem
	 * @brief Make host node go into Operational state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    goOperational();

	/**
	 * @ingroup CfSystem
	 * @brief Make host node go into Stopped state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    goStopped();

	/**
	 * @ingroup CfSystem
	 * @brief Make all nodes in CAN net go into Initialisation state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    sysReset();

	/**
	 * @ingroup CfSystem
	 * @brief Make all nodes in CAN net go into PreOperational state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    sysPreOperational();

	/**
	 * @ingroup CfSystem
	 * @brief Make all nodes in CAN net go into Operational state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    sysOperational();

	/**
	 * @ingroup CfSystem
	 * @brief Make all nodes in CAN net go into Stopped state.
	 * @return
	 *       - CO_OK if operation is successful.
	 *       - CO_NMT_ERROR if operation is unsuccessful.
	 */
    const CfResult*
    sysStopped();

	/**
	 * @ingroup CfSystem
	 * @brief Set the host node ID
	 * @param id The new host node ID
	 */
    void
    setID(UNS8 id);

	/**
	 * @ingroup CfSystem
	 * @brief Get the host node ID
	 * @return The current host node ID.
	 */
    UNS8
    getID();

	/**
	 * @ingroup CfSystem
	 * @brief Collect all the nodes' ID in the CAN net.
	 * @return A vector contains the nodes' ID.
	 */
    std::vector<int>
    scan();
};

}

#endif
