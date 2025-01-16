// ==============================================================
// File generated on Sat Jan 11 17:13:50 +0800 2025
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xconway.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XConway_CfgInitialize(XConway *InstancePtr, XConway_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XConway_Set_start(XConway *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XConway_WriteReg(InstancePtr->Control_BaseAddress, XCONWAY_CONTROL_ADDR_START_DATA, Data);
}

u32 XConway_Get_start(XConway *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XConway_ReadReg(InstancePtr->Control_BaseAddress, XCONWAY_CONTROL_ADDR_START_DATA);
    return Data;
}

