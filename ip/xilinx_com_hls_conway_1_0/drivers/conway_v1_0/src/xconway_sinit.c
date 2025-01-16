// ==============================================================
// File generated on Sat Jan 11 17:13:50 +0800 2025
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xconway.h"

extern XConway_Config XConway_ConfigTable[];

XConway_Config *XConway_LookupConfig(u16 DeviceId) {
	XConway_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCONWAY_NUM_INSTANCES; Index++) {
		if (XConway_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XConway_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XConway_Initialize(XConway *InstancePtr, u16 DeviceId) {
	XConway_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XConway_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XConway_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

