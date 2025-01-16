#include "xconway.h"
#include "xparameters.h"

#define GRID_WIDTH 160
#define GRID_HEIGHT 90
#define VIDEO_WIDTH 1280
#define VIDEO_HEIGHT 720

int main() {
    int Status;

    XConway conway;

    Status = XConway_Initialize(&conway, XPAR_CONWAY_0_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        xil_printf("Initialization failed with error = %d\r\n", Status);
        return XST_FAILURE;
    }

    XConway_Set_start(&conway, 0xFFFFFFFF);
    int is_start = XConway_Get_start(&conway);
    xil_printf("Start signal: %d\r\n", is_start);

    while (1) {
    }

    return 0;
}
