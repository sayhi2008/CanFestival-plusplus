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
#include "CfParameter.h"
#include "CfLib.h"

namespace canopenlib
{

enum COMM_OBJID
{
	   TPDO_PARAMETER		= 0x1800,
	   TPDO_MAPPING			= 0x1A00
};


class CfNode
{

protected:
	CfLib &nh_;
	UNS8 node_id_;

public:
    CfNode();
    ~CfNode();

    const CfResult* init(UNS8 id);
    const CfResult* cleanup();

    const CfResult* goReset();
    const CfResult* goPreOperational();
    const CfResult* goOperational();
    const CfResult* goStopped();

    const CfResult* setCommPara(CommSettings &setting);
    const CfResult* saveCommPara(void);

    const CfResult* startSync(void);
    const CfResult* stopSync(void);
    const CfResult* setSyncPeriod(UNS32 period);
    const CfResult* getSyncPeriod(UNS32* period);
    const CfResult* setSyncWindow(UNS32 window);
    const CfResult* getSyncWindow(UNS32* window);
    const CfResult* setHbPeriod(UNS16 period);
    const CfResult* getHbPeriod(UNS16* period);

    const CfResult* setTPDOTransType(UNS8 TPDO_id, UNS8 value);
    const CfResult* getTPDOTransType(UNS8 TPDO_id, UNS8* value);
    const CfResult* setTPDOInhibitTime(UNS8 TPDO_id, UNS16 value);
    const CfResult* getTPDOInhibitTime(UNS8 TPDO_id, UNS16* value);
    const CfResult* setTPDOCompEntry(UNS8 TPDO_id, UNS8 value);
    const CfResult* getTPDOCompEntry(UNS8 TPDO_id, UNS8* value);
    const CfResult* setTPDOEventTimer(UNS8 TPDO_id, UNS16 value);
    const CfResult* getTPDOEventTimer(UNS8 TPDO_id, UNS16* value);

    const CfResult* subscribePDO(UNS8 PDO_id, std::function<void(std::string)> func);
    const CfResult* setPDOMapping(UNS8 PDO_id, UNS8 sub_index,UNS32 value);
    const CfResult* getPDOMapping(UNS8 PDO_id, UNS8 sub_index, UNS32 * value);
    const CfResult* heartBeatErrorCb(std::function<void()> func);

};
}
#endif
