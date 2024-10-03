#include "combos.h"

// top row
// left
const uint16_t PROGMEM fp_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM fw_combo[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM wp_combo[] = {KC_W, KC_P, COMBO_END};
// right
const uint16_t PROGMEM lu_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM uy_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM ly_combo[] = {KC_L, KC_Y, COMBO_END};
// home row
// mixed
const uint16_t PROGMEM se_combo[] = {HR_S, HR_E, COMBO_END};

combo_t key_combos[] = {
    // top row
    [FP_LPRN] = COMBO(fp_combo, KC_LPRN),
    [FW_LBRC] = COMBO(fw_combo, KC_LBRC),
    [WP_LCBR] = COMBO(wp_combo, KC_LCBR),
    [LU_RPRN] = COMBO(lu_combo, KC_RPRN),
    [UY_RBRC] = COMBO(uy_combo, KC_RBRC),
    [LY_RCBR] = COMBO(ly_combo, KC_RCBR),
    // home row
    [SE_CW] = COMBO(se_combo, CW_TOGG),
};
