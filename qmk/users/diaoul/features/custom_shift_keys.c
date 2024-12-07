#include "custom_shift_keys.h"

const custom_shift_key_t custom_shift_keys[] = {
    [BSPC_DEL]  = {KC_BSPC, KC_DEL},
    [DOT_COLN]  = {KC_DOT, KC_COLN},
    [COMM_SCLN] = {KC_COMM, KC_SCLN},
    [QUES_EXLM] = {KC_QUES, KC_EXLM},
};

uint8_t NUM_CUSTOM_SHIFT_KEYS = CUSTOM_SHIFT_KEYS_COUNT;
