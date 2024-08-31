#ifndef __CREATEMOVE_H__
#define __CREATEMOVE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

extern void __stdcall CreateMoveProxy( int sequence_number, float input_sample_frameTime, bool active, bool& bSendPacket );

#endif