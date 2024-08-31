#ifndef __DRAWMODELEXECUTE_H__
#define __DRAWMODELEXECUTE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "SDK.h"

//extern void __stdcall hkDrawModelExecute( PVOID pContext, const ValveSDK::DrawModelState_t& pState, const ValveSDK::ModelRenderInfo_t& pInfo, ValveSDK::matrix3x4* pCustomBoneToWorld );
extern void __fastcall hkDrawModelExecute( PVOID thiptr, int edx, PVOID pContext, const ValveSDK::DrawModelState_t& pState, const ValveSDK::ModelRenderInfo_t& pInfo, ValveSDK::matrix3x4* pCustomBoneToWorld );

#endif