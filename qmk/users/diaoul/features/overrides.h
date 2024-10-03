#pragma once

#include QMK_KEYBOARD_H
#include "process_key_override.h"

enum {
    BSPC_DEL,
    DOT_COLN,
    COMM_SCLN,
    QUES_EXLM,
    KEY_OVERRIDE_COUNT,
};

extern const key_override_t *key_overrides[KEY_OVERRIDE_COUNT];
