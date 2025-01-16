#ifndef CONWAY_H
#define CONWAY_H

#include <ap_axi_sdata.h>
#include "ap_int.h"
#include "hls_stream.h"

typedef ap_axiu<24, 1, 1, 1> axis_pixel_t;
typedef hls::stream<axis_pixel_t> axis_t;

void conway(bool* start, ap_uint<1>* ready, axis_t& video_out);

#endif
