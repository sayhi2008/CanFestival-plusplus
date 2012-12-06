#ifndef __CFNODE_401_H__
#define __CFNODE_401_H__

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
#include "CfNode.h"

namespace canopenlib
{

enum IO_OBJID
{
	   IOOBJID_DIN_8_VALUE			= 0x6000,  ///<  8-bit digital input value
	   IOOBJID_DIN_8_POL           	= 0x6002,  ///<  8-bit digital input polarity
	   IOOBJID_DIN_8_FILT           = 0x6003,  ///<  8-bit digital input filter constant
	   IOOBJID_DIN_INTENA           = 0x6005,  ///< Digital input interrupt enable
	   IOOBJID_DIN_8_MASK_ANY       = 0x6006,  ///<  8-bit digital input int mask, any change
	   IOOBJID_DIN_8_MASK_L2H       = 0x6007,  ///<  8-bit digital input int mask, low to high
	   IOOBJID_DIN_8_MASK_H2L       = 0x6008,  ///<  8-bit digital input int mask, high to low
	   IOOBJID_DIN_1_VALUE          = 0x6020,  ///<  1-bit digital input value
	   IOOBJID_DIN_1_POL            = 0x6030,  ///<  1-bit digital input polarity
	   IOOBJID_DIN_1_FILT           = 0x6038,  ///<  1-bit digital input filter constant
	   IOOBJID_DIN_1_MASK_ANY       = 0x6050,  ///<  1-bit digital input int mask, any change
	   IOOBJID_DIN_1_MASK_L2H       = 0x6060,  ///<  1-bit digital input int mask, low to high
	   IOOBJID_DIN_1_MASK_H2L       = 0x6070,  ///<  1-bit digital input int mask, high to low
	   IOOBJID_DIN_16_VALUE         = 0x6100,  ///< 16-bit digital input value
	   IOOBJID_DIN_16_POL           = 0x6102,  ///< 16-bit digital input polarity
	   IOOBJID_DIN_16_FILT          = 0x6103,  ///< 16-bit digital input filter constant
	   IOOBJID_DIN_16_MASK_ANY      = 0x6106,  ///< 16-bit digital input int mask, any change
	   IOOBJID_DIN_16_MASK_L2H      = 0x6107,  ///< 16-bit digital input int mask, low to high
	   IOOBJID_DIN_16_MASK_H2L      = 0x6108,  ///< 16-bit digital input int mask, high to low
	   IOOBJID_DIN_32_VALUE         = 0x6120,  ///< 32-bit digital input value
	   IOOBJID_DIN_32_POL           = 0x6122,  ///< 32-bit digital input polarity
	   IOOBJID_DIN_32_FILT          = 0x6123,  ///< 32-bit digital input filter constant
	   IOOBJID_DIN_32_MASK_ANY      = 0x6126,  ///< 32-bit digital input int mask, any change
	   IOOBJID_DIN_32_MASK_L2H      = 0x6127,  ///< 32-bit digital input int mask, low to high
	   IOOBJID_DIN_32_MASK_H2L      = 0x6128,  ///< 32-bit digital input int mask, high to low

	   IOOBJID_DOUT_8_VALUE         = 0x6200,  ///<  8-bit digital output value
	   IOOBJID_DOUT_8_POL           = 0x6202,  ///<  8-bit digital output polarity
	   IOOBJID_DOUT_8_ERRMODE       = 0x6206,  ///<  8-bit digital output error mode
	   IOOBJID_DOUT_8_ERRVAL        = 0x6207,  ///<  8-bit digital output error value
	   IOOBJID_DOUT_8_FILT          = 0x6208,  ///<  8-bit digital output filter mask
	   IOOBJID_DOUT_1_VALUE         = 0x6220,  ///<  1-bit digital output value
	   IOOBJID_DOUT_1_POL           = 0x6240,  ///<  1-bit digital output polarity
	   IOOBJID_DOUT_1_ERRMODE       = 0x6250,  ///<  1-bit digital output error mode
	   IOOBJID_DOUT_1_ERRVAL        = 0x6260,  ///<  1-bit digital output error value
	   IOOBJID_DOUT_1_FILT          = 0x6270,  ///<  1-bit digital output filter mask
	   IOOBJID_DOUT_16_VALUE        = 0x6300,  ///< 16-bit digital output value
	   IOOBJID_DOUT_16_POL          = 0x6302,  ///< 16-bit digital output polarity
	   IOOBJID_DOUT_16_ERRMODE      = 0x6306,  ///< 16-bit digital output error mode
	   IOOBJID_DOUT_16_ERRVAL       = 0x6307,  ///< 16-bit digital output error value
	   IOOBJID_DOUT_16_FILT         = 0x6308,  ///< 16-bit digital output filter mask
	   IOOBJID_DOUT_32_VALUE        = 0x6320,  ///< 32-bit digital output value
	   IOOBJID_DOUT_32_POL          = 0x6322,  ///< 32-bit digital output polarity
	   IOOBJID_DOUT_32_ERRMODE      = 0x6326,  ///< 32-bit digital output error mode
	   IOOBJID_DOUT_32_ERRVAL       = 0x6327,  ///< 32-bit digital output error value
	   IOOBJID_DOUT_32_FILT         = 0x6328,  ///< 32-bit digital output filter mask

	   IOOBJID_AIN_16_VALUE         = 0x6401,  ///< 16-bit analog input value
	   IOOBJID_AIN_INTENA           = 0x6423,  ///< Analog input interrupt enable

	   IOOBJID_AIN_32_UPLIM         = 0x6424,  ///< 32-bit analog input upper limit
	   IOOBJID_AIN_32_LWLIM         = 0x6425,  ///< 32-bit analog input lower limit
	   IOOBJID_AIN_32_UDELTA        = 0x6426,  ///< 32-bit analog input unsigned delta

	   IOOBJID_AIN_32_OFFSET        = 0x6431,  ///< 32-bit analog input offset
	   IOOBJID_AIN_32_SCALE       	= 0x6432,  ///< 32-bit analog input scaling

	   NODE_ID             			= 0x21B0,
};

struct DinSettings
{
   UNS8 din8Pol;
   UNS8 din8MaskAny;
   UNS8 din8MaskL2H;
   UNS8 din8MaskH2L;
   DinSettings(void)
   {
	   din8Pol = 0;
	   din8MaskAny = 0;
	   din8MaskL2H = 0;
	   din8MaskH2L = 0;

   }
};

struct DoutSettings
{
	UNS8 dout8Pol;
	UNS8 dout8ErrMode;
	UNS8 dout8ErrVal;

	DoutSettings(void)
	{
		dout8Pol = 0;
		dout8ErrMode = 0;
		dout8ErrVal = 0;
	}
};


struct AinSettings
{
	UNS32 ain16UpLim;
	UNS32 ain16LwLim;
	UNS32 ain16UDelta;
	INTEGER32 ainScale;
	INTEGER32 ainOffset;

	AinSettings(void)
	{
		ain16UpLim = 0;
		ain16LwLim = 0;
		ain16UDelta = 0;
		ainScale = 0;
		ainOffset = 0;
	}
};

class CfNode_401: public CfNode
{
public:
    const CfResult* setID(UNS8 id);
    //const CfResult* getID(UNS8* id);

    const CfResult* setDinPara(UNS8 din_id, DinSettings &setting);
    const CfResult* setDoutPara(UNS8 dout_id, DoutSettings &setting);
    const CfResult* setAinPara(UNS8 ain_id, AinSettings &setting);
    const CfResult* saveManuPara(void);
    const CfResult* loadManuPara(bool load);

    const CfResult* getDin8Value(UNS8 id, UNS8* value);
    const CfResult* setDin8Pol(UNS8 id, UNS8 value);
    const CfResult* getDin8Pol(UNS8 id, UNS8* value);
    const CfResult* setDin8Filt(UNS8 id, UNS8 value);
    const CfResult* getDin8Filt(UNS8 id, UNS8* value);
    const CfResult* setDin8Intena(bool value);
    const CfResult* getDin8Intena(bool* value);
    const CfResult* setDin8MaskAny(UNS8 id, UNS8 value);
    const CfResult* getDin8MaskAny(UNS8 id, UNS8* value);
    const CfResult* setDin8MaskL2H(UNS8 id, UNS8 value);
    const CfResult* getDin8MaskL2H(UNS8 id, UNS8* value);
    const CfResult* setDin8MaskH2L(UNS8 id, UNS8 value);
    const CfResult* getDin8MaskH2L(UNS8 id, UNS8* value);

    const CfResult* setDout8Value(UNS8 id, UNS8 value);
    const CfResult* getDout8Value(UNS8 id, UNS8* value);
    const CfResult* setDout8Pol(UNS8 id, UNS8 value);
    const CfResult* getDout8Pol(UNS8 id, UNS8* value);

    const CfResult* setDout8ErrMode(UNS8 id, UNS8 value);
    const CfResult* getDout8ErrMode(UNS8 id, UNS8* value);
    const CfResult* setDout8ErrVal(UNS8 id, UNS8 value);
    const CfResult* getDout8ErrVal(UNS8 id, UNS8* value);

    const CfResult* getAin16Value(UNS8 id, INTEGER16* value);
    const CfResult* setAinIneEna(bool value);
    const CfResult* getAinIneEna(bool* value);

    const CfResult* setAin16UpLim(UNS8 id, UNS32 value);
    const CfResult* getAin16UpLim(UNS8 id, UNS32* value);
    const CfResult* setAin16LwLim(UNS8 id, UNS32 value);
    const CfResult* getAin16LwLim(UNS8 id, UNS32* value);
    const CfResult* setAin16UDelta(UNS8 id, UNS32 value);
    const CfResult* getAin16UDelta(UNS8 id, UNS32* value);

    const CfResult* setAinOffset(UNS8 id, INTEGER32 value);
    const CfResult* getAinOffset(UNS8 id, INTEGER32* value);
    const CfResult* setAinScale(UNS8 id, INTEGER32 value);
    const CfResult* getAinScale(UNS8 id, INTEGER32* value);

};

}
#endif
