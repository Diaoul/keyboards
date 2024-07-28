#include QMK_KEYBOARD_H

#include "keymap.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK_DH] = LAYOUT_split_3x6_3(
  KC_GRV , KC_Q , KC_W , KC_F , KC_P    , KC_B    ,                         KC_J     , KC_L    , KC_U    , KC_Y   , KC_SCLN , KC_MINS,
  KC_ESC , HC_A , HC_R , HC_S , HC_T    , KC_G    ,                         KC_M     , HC_N    , HC_E    , HC_I   , HC_O    , KC_QUOT,
  KC_TAB , KC_Z , KC_X , KC_C , KC_D    , KC_V    ,                         KC_K     , KC_H    , KC_COMM , KC_DOT , KC_SLSH , KC_EQL ,
                                NAV_TAB , NAV_SPC , OS_LSFT ,     OS_RSFT , SYM_BSPC , SYM_ENT                                       
),

[_SYM] = LAYOUT_split_3x6_3(
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_MINS,
  KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                         KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_PLUS,
  KC_PIPE , KC_BSLS , KC_COLN , KC_SCLN , KC_MINS , _______ ,                         _______ , KC_UNDS , KC_COMM , KC_DOT  , KC_SLSH , KC_QUES,
                                          _______ , _______ , _______ ,     _______ , _______ , _______                                        
),

[_NAV] = LAYOUT_split_3x6_3(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______ , KC_DEL ,
  _______ , KC_LALT , KC_LSFT , KC_LGUI , KC_LCTL , _______ ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , KC_INS ,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         KC_HOME , KC_PGDN , KC_PGUP , KC_END  , _______ , KC_PSCR,
                                          _______ , _______ , _______ ,     _______ , _______ , _______                                        
)
};
// clang-format on
