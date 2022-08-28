// Copyright 2022 Cody Bloemhard (@codybloemhard)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// general info

#define VENDOR_ID       0x0000
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0000
#define MANUFACTURER    Cody Bloemhard
#define PRODUCT         Eliza

// matrix

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { B7, F0, F1, D5 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B6, B5, E6, D7, C6, D4, D0 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

// features

#define ACTION_TAPPING
// uses: https://github.com/qmk/qmk_firmware/pull/9404
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// key settings

#define TAPPING_TERM 150
#define DEBOUNCE 5

// mouse settings

#define MOUSEKEY_DELAY 0
#define MK_3_SPEED
#define MK_C_OFFSET_UNMOD 1
#define MK_C_INTERVAL_UNMOD 16
#define MK_C_OFFSET_0 4
#define MK_C_INTERVAL_0 16
#define MK_C_OFFSET_1 8
#define MK_C_INTERVAL_1 16
#define MK_C_OFFSET_2 16
#define MK_C_INTERVAL_2 16

// optional

#define NO_ACTION_ONESHOT

