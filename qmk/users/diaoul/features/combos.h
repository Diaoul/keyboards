#pragma once

#include QMK_KEYBOARD_H
#include "process_combo.h"

#include "../definitions/keycodes.h"

enum combos {
    FP_LPRN,
    FW_LBRC,
    WP_LCBR,
    LU_RPRN,
    UY_RBRC,
    LY_RCBR,
    SE_CW,
    COMBO_COUNT,
};

extern combo_t key_combos[COMBO_COUNT];
