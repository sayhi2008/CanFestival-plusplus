#ifndef __CFPARAMETER_H__
#define __CFPARAMETER_H__

#if defined(WIN32) && !defined(__CYGWIN__)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
#endif

#include <iostream>

#include "canfestival.h"
#include "CfResult.h"

namespace canopenlib
{

struct CommSettings
{
   UNS32 synchPeriod;
   UNS32 synchWindow;
   bool synchProducer;
   //bool timeProducer;
   //UNS16 inhibitTime;
   UNS16 heartbeatPeriod;
   //bool enableOnInit;
   //bool resetOnInit;
   CommSettings(void)
   {
	   synchProducer    = false;
	   synchPeriod      = 0x0007a120;	// 500ms
	   synchWindow      = 0x0003d090;	//250ms
	   //timeProducer     = false;
	   //inhibitTime		= 0;
	   heartbeatPeriod  = 0x03E8;	// 1s
	   //enableOnInit 	= true;
	   //resetOnInit 		= false;
   }
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

}
#endif
