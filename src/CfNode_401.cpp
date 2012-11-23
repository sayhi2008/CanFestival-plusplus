#if defined(WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

#include "CfNode_401.h"
#include "HostNode.h"

namespace canopenlib {

const CfResult* CfNode_401::setID(UNS8 id)
{
	if(nh_.setSDO(node_id_, NODE_ID, 0, 0, &id, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
	{
		node_id_=id;
		return &CfResult::CO_OK;
	}
}

const CfResult* CfNode_401::setDinPara(UNS8 din_id, DinSettings &setting)
{
	const CfResult *e;
	e = setDin8Pol(din_id, setting.din8Pol);
	if(e->GetId())
		return e;

	e = setDin8MaskAny(din_id, setting.din8MaskAny);
	if(e->GetId())
		return e;

	e = setDin8MaskL2H(din_id, setting.din8MaskL2H);
	if(e->GetId())
		return e;

	e = setDin8MaskH2L(din_id, setting.din8MaskH2L);
	return e;
}


const CfResult* CfNode_401::setDoutPara(UNS8 dout_id, DoutSettings &setting)
{
	const CfResult *e;
	e = setDout8Pol(dout_id, setting.dout8Pol);
	if(e->GetId())
		return e;

	e = setDout8ErrMode(dout_id, setting.dout8ErrMode);
	if(e->GetId())
		return e;

	e = setDout8ErrVal(dout_id, setting.dout8ErrVal);
	return e;
}

const CfResult* CfNode_401::setAinPara(UNS8 ain_id, AinSettings &setting)
{
	const CfResult *e;
	e = setAin16UpLim(ain_id, setting.ain16UpLim);
	if(e->GetId())
		return e;

	e = setAin16LwLim(ain_id, setting.ain16LwLim);
	if(e->GetId())
		return e;

	e = setAin16UDelta(ain_id, setting.ain16UDelta);
	if(e->GetId())
		return e;

	e = setAinScale(ain_id, setting.ainScale);
	if(e->GetId())
		return e;

	e = setAinOffset(ain_id, setting.ainOffset);
	return e;
}

const CfResult*  CfNode_401::getDin8Value(UNS8 id, UNS8* value)
{
	if(nh_.setSDO(node_id_, IOOBJID_DIN_8_VALUE, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setDin8Pol(UNS8 id, UNS8 value)
{
	if(nh_.setSDO(node_id_, IOOBJID_DIN_8_POL, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;

}

const CfResult*  CfNode_401::getDin8Pol(UNS8 id, UNS8* value)
{
	if(nh_.getSDO(node_id_, IOOBJID_DIN_8_POL, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;

}

const CfResult*  CfNode_401::setDin8Filt(UNS8 id, UNS8 value)
{
	if(nh_.setSDO(node_id_, IOOBJID_DIN_8_FILT, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;

}

const CfResult*  CfNode_401::getDin8Filt(UNS8 id, UNS8* value)
{
	if(nh_.getSDO(node_id_, IOOBJID_DIN_8_FILT, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;

}

const CfResult*  CfNode_401::setDin8Intena(bool value) {
	if(nh_.setSDO(node_id_, IOOBJID_DIN_INTENA, 0, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getDin8Intena(bool* value) {
	if(nh_.getSDO(node_id_, IOOBJID_DIN_INTENA, 0, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setDin8MaskAny(UNS8 id, UNS8 value) {
	if(nh_.setSDO(node_id_, IOOBJID_DIN_8_MASK_ANY, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getDin8MaskAny(UNS8 id, UNS8* value) {
	if(nh_.getSDO(node_id_, IOOBJID_DIN_8_MASK_ANY, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setDin8MaskL2H(UNS8 id, UNS8 value) {
	if(nh_.setSDO(node_id_, IOOBJID_DIN_8_MASK_L2H, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getDin8MaskL2H(UNS8 id, UNS8* value) {
	if(nh_.getSDO(node_id_, IOOBJID_DIN_8_MASK_L2H, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setDin8MaskH2L(UNS8 id, UNS8 value) {
	if(nh_.setSDO(node_id_, IOOBJID_DIN_8_MASK_H2L, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getDin8MaskH2L(UNS8 id, UNS8* value) {
	if(nh_.getSDO(node_id_, IOOBJID_DIN_8_MASK_H2L, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

/* Digital output*/

const CfResult*  CfNode_401::setDout8Value(UNS8 id, UNS8 value) {
	if(nh_.setSDO(node_id_, IOOBJID_DOUT_8_VALUE, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getDout8Value(UNS8 id, UNS8* value) {
	if(nh_.getSDO(node_id_, IOOBJID_DOUT_8_VALUE, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setDout8Pol(UNS8 id, UNS8 value) {
	if(nh_.setSDO(node_id_, IOOBJID_DOUT_8_POL, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getDout8Pol(UNS8 id, UNS8* value) {
	if(nh_.getSDO(node_id_, IOOBJID_DOUT_8_POL, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}


const CfResult*  CfNode_401::setDout8ErrMode(UNS8 id, UNS8 value) {
	if(nh_.setSDO(node_id_, IOOBJID_DOUT_8_ERRMODE, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getDout8ErrMode(UNS8 id, UNS8* value) {
	if(nh_.getSDO(node_id_, IOOBJID_DOUT_8_ERRMODE, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setDout8ErrVal(UNS8 id, UNS8 value) {
	if(nh_.setSDO(node_id_, IOOBJID_DOUT_8_ERRVAL, id + 1, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getDout8ErrVal(UNS8 id, UNS8* value) {
	if(nh_.getSDO(node_id_, IOOBJID_DOUT_8_ERRVAL, id + 1, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

/*Analog input*/



const CfResult*  CfNode_401::getAin16Value(UNS8 id, INTEGER16* value) {
	if(nh_.getSDO(node_id_, IOOBJID_AIN_16_VALUE, id + 1, 0, value, 2, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}


const CfResult*  CfNode_401::setAinIneEna(bool value) {
	if(nh_.setSDO(node_id_, IOOBJID_AIN_INTENA, 0, 0, &value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getAinIneEna(bool* value) {
	if(nh_.getSDO(node_id_, IOOBJID_AIN_INTENA, 0, 0, value, 1, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setAin16UpLim(UNS8 id, UNS32 value) {
	if(nh_.setSDO(node_id_, IOOBJID_AIN_32_UPLIM, id + 1, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getAin16UpLim(UNS8 id, UNS32* value) {
	if(nh_.getSDO(node_id_, IOOBJID_AIN_32_UPLIM, id + 1, 0, value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setAin16LwLim(UNS8 id, UNS32 value) {
	if(nh_.setSDO(node_id_, IOOBJID_AIN_32_LWLIM, id + 1, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getAin16LwLim(UNS8 id, UNS32* value) {
	if(nh_.getSDO(node_id_, IOOBJID_AIN_32_LWLIM, id + 1, 0, value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setAin16UDelta(UNS8 id, UNS32 value) {
	if(nh_.setSDO(node_id_, IOOBJID_AIN_32_UDELTA, id + 1, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getAin16UDelta(UNS8 id, UNS32* value) {
	if(nh_.getSDO(node_id_, IOOBJID_AIN_32_UDELTA, id + 1, 0, value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}


const CfResult*  CfNode_401::setAinOffset(UNS8 id, INTEGER32 value) {
	if(nh_.setSDO(node_id_, IOOBJID_AIN_32_OFFSET, id + 1, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getAinOffset(UNS8 id, INTEGER32* value) {
	if(nh_.getSDO(node_id_, IOOBJID_AIN_32_OFFSET, id + 1, 0, value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::setAinScale(UNS8 id, INTEGER32 value) {
	if(nh_.setSDO(node_id_, IOOBJID_AIN_32_SCALE, id + 1, 0, &value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

const CfResult*  CfNode_401::getAinScale(UNS8 id, INTEGER32* value) {
	if(nh_.getSDO(node_id_, IOOBJID_AIN_32_SCALE, id + 1, 0, value, 4, 0))
		return &CfResult::CO_SDO_ERROR;
	else
		return &CfResult::CO_OK;
}

}
