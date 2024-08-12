#include "combos.h"

// top row
// left
const uint16_t PROGMEM f_p_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM f_w_combo[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM w_p_combo[] = {KC_W, KC_P, COMBO_END};
// right
const uint16_t PROGMEM l_u_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM u_y_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM l_y_combo[] = {KC_L, KC_Y, COMBO_END};
// home row
// left
const uint16_t PROGMEM s_t_combo[] = {HR_S, HR_T, COMBO_END};
// right
const uint16_t PROGMEM n_e_combo[] = {HR_N, HR_E, COMBO_END};
// mixed
const uint16_t PROGMEM s_e_combo[] = {HR_S, HR_E, COMBO_END};

combo_t key_combos[] = {
    // top row
    COMBO(f_p_combo, KC_LPRN),
    COMBO(f_w_combo, KC_LBRC),
    COMBO(w_p_combo, KC_LCBR),
    COMBO(l_u_combo, KC_RPRN),
    COMBO(u_y_combo, KC_RBRC),
    COMBO(l_y_combo, KC_RCBR),
    // home row
    COMBO(s_t_combo, KC_LPRN),
    COMBO(n_e_combo, KC_RPRN),
    COMBO(s_e_combo, CW_TOGG),
};
