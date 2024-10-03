#include "overrides.h"

const key_override_t del_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t dot_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);

const key_override_t *key_overrides[] = {
    [BSPC_DEL]  = &del_key_override,
    [DOT_COLN]  = &dot_key_override,
    [COMM_SCLN] = &comm_key_override,
    [QUES_EXLM] = &ques_key_override,
};
