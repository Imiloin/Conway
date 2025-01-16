#include "conway.h"

#define GRID_WIDTH 160
#define GRID_HEIGHT 90
#define PIXEL_PER_CELL 8                             // 8x8 pixel per cell
#define VIDEO_WIDTH (GRID_WIDTH * PIXEL_PER_CELL)    // 1280
#define VIDEO_HEIGHT (GRID_HEIGHT * PIXEL_PER_CELL)  // 720

void conway(bool* start, ap_uint<1>* ready, axis_t& video_out) {
    // clang-format off
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=start bundle=control
#pragma HLS INTERFACE ap_none port=ready
#pragma HLS INTERFACE axis register both port=video_out
    // clang-format on

    static bool board[GRID_HEIGHT][GRID_WIDTH] = {false};
    bool next_board[GRID_HEIGHT][GRID_WIDTH] = {false};

    // clang-format off
#pragma HLS ARRAY_PARTITION variable=board complete dim=2
#pragma HLS ARRAY_PARTITION variable=next_board complete dim=2
    // clang-format on

// initialize
INIT: {
    // Gosper Glider Gun
    int offset_x = 5;
    int offset_y = 5;
    board[offset_y + 0][offset_x + 24] = true;
    board[offset_y + 1][offset_x + 22] = board[offset_y + 1][offset_x + 24] = true;
    board[offset_y + 2][offset_x + 12] = board[offset_y + 2][offset_x + 13] =
        board[offset_y + 2][offset_x + 20] = board[offset_y + 2][offset_x + 21] = true;
    board[offset_y + 2][offset_x + 34] = board[offset_y + 2][offset_x + 35] = true;
    board[offset_y + 3][offset_x + 11] = board[offset_y + 3][offset_x + 15] =
        board[offset_y + 3][offset_x + 20] = board[offset_y + 3][offset_x + 21] = true;
    board[offset_y + 3][offset_x + 34] = board[offset_y + 3][offset_x + 35] = true;
    board[offset_y + 4][offset_x + 0] = board[offset_y + 4][offset_x + 1] =
        board[offset_y + 4][offset_x + 10] = board[offset_y + 4][offset_x + 16] = true;
    board[offset_y + 4][offset_x + 20] = board[offset_y + 4][offset_x + 21] = true;
    board[offset_y + 5][offset_x + 0] = board[offset_y + 5][offset_x + 1] =
        board[offset_y + 5][offset_x + 10] = board[offset_y + 5][offset_x + 14] = true;
    board[offset_y + 5][offset_x + 16] = board[offset_y + 5][offset_x + 17] =
        board[offset_y + 5][offset_x + 22] = board[offset_y + 5][offset_x + 24] = true;
    board[offset_y + 6][offset_x + 10] = board[offset_y + 6][offset_x + 16] =
        board[offset_y + 6][offset_x + 24] = true;
    board[offset_y + 7][offset_x + 11] = board[offset_y + 7][offset_x + 15] = true;
    board[offset_y + 8][offset_x + 12] = board[offset_y + 8][offset_x + 13] = true;

    *ready = 1;  // set ready signal
}

    while (true) {
        if (*start) {
        // compute next frame
        CALC_NEXT_FRAME:
            for (unsigned int i = 0; i < GRID_HEIGHT; i++) {
                for (unsigned int j = 0; j < GRID_WIDTH; j++) {
#pragma HLS PIPELINE
                    int liveNeighbors = 0;
                    for (int ni = -1; ni <= 1; ni++) {
#pragma HLS INLINE
                        for (int nj = -1; nj <= 1; nj++) {
                            if (ni == 0 && nj == 0)
                                continue;
                            int x = j + nj;
                            int y = i + ni;

                            // toroidal boundary
                            if (x < 0)
                                x = GRID_WIDTH - 1;
                            if (x >= GRID_WIDTH)
                                x = 0;
                            if (y < 0)
                                y = GRID_HEIGHT - 1;
                            if (y >= GRID_HEIGHT)
                                y = 0;

                            if (board[y][x]) {
                                liveNeighbors++;
                            }
                        }
                    }

                    // rule 1: A cell survives in the next generation if it has 2 or 3 live
                    // neighbors.
                    // rule 2: A dead cell comes to life in the next generation if it has
                    // exactly 3 live neighbors.
                    if (board[i][j]) {
                        next_board[i][j] = (liveNeighbors == 2 || liveNeighbors == 3);
                    } else {
                        next_board[i][j] = (liveNeighbors == 3);
                    }
                }
            }

        // update current board
        UPDATE_BOARD: {
            for (unsigned int i = 0; i < GRID_HEIGHT; i++) {
                for (unsigned int j = 0; j < GRID_WIDTH; j++) {
#pragma HLS PIPELINE
                    board[i][j] = next_board[i][j];
                }
            }
        }

        // write to raw_video
        WRITE_OUTPUT: {
            for (unsigned int i = 0; i < VIDEO_HEIGHT; i++) {
                for (unsigned int j = 0; j < VIDEO_WIDTH; j++) {
#pragma HLS PIPELINE
                    axis_pixel_t pixel;
                    pixel.data =
                        board[i / PIXEL_PER_CELL][j / PIXEL_PER_CELL] ? 0x000000 : 0xFFFFFF;
                    // pixel.keep = 0x7;  // all three color channels are valid
                    // pixel.strb = 0x7;
                    pixel.user = (i == 0 && j == 0) ? 1 : 0;      // frame start
                    pixel.last = (j == VIDEO_WIDTH - 1) ? 1 : 0;  // line end
                    video_out << pixel;
                }
            }
        }
        }
    }
}
