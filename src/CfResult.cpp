
#include "CfResult.h"
#include <iostream>
#include <stdio.h>


namespace canopenlib
{


CfResult::CfResult(int id = 0, std::string des = ""):
		id_(id),
		descript_(des)
{}

std::string CfResult::GetDescript() const
{
	return descript_;
}

int CfResult::GetId() const
{
	return id_;
}

const CfResult CfResult::CO_OK		(0,"OK");
const CfResult CfResult::CO_NORMAL_ERROR 	(1,"no error");
const CfResult CfResult::CO_SDO_ERROR		(2,"sdo error");
const CfResult CfResult::CO_PDO_ERROR		(3,"pdo error");
const CfResult CfResult::CO_SDO_SIZE_ERROR	(4,"sdo size error");
const CfResult CfResult::CO_NODE_PreInitialisation	(5,"PreInitialisation");
const CfResult CfResult::CO_NODE_Initialisation		(6,"Initialisation");
const CfResult CfResult::CO_NODE_Disconnected		(7,"Disconnected");
const CfResult CfResult::CO_NODE_Connecting			(8,"Connecting");
const CfResult CfResult::CO_NODE_Preparing			(9,"Preparing");
const CfResult CfResult::CO_NODE_Stopped			(10,"Stopped");
const CfResult CfResult::CO_NODE_Operational		(11,"Operational");
const CfResult CfResult::CO_NODE_Pre_operational	(12,"Pre_operational");
const CfResult CfResult::CO_NODE_UnknownState		(13,"UnknownState");
const CfResult CfResult::CO_NMT_ERROR				(14,"NMT Error");
const CfResult CfResult::CO_INITIAL_ERROR						(15,"Node does not exist");


}



