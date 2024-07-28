#include QMK_KEYBOARD_H

#include "keymap.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK_DH] = LAYOUT_split_3x5_3(
  KC_Q , KC_W , KC_F , KC_P   , KC_B    ,                       KC_J    , KC_L     , KC_U    , KC_Y   , KC_QUOT,
  HC_A , HC_R , HC_S , HC_T   , KC_G    ,                       KC_M    , HC_N     , HC_E    , HC_I   , HC_O   ,
  KC_Z , KC_X , KC_C , KC_D   , KC_V    ,                       KC_K    , KC_H     , KC_COMM , KC_DOT , KC_SLSH,
                       KC_TAB , SPC_NAV , KC_ESC ,     KC_ESC , KC_BSPC , ENT_RSFT                             
),

[_SYM] = LAYOUT_split_3x5_3(
  KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0   ,
  KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                         KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN,
  KC_BSLS , KC_COLN , KC_SCLN , KC_MINS , _______ ,                         _______ , KC_UNDS , KC_COMM , KC_DOT  , KC_SLSH,
                                _______ , _______ , _______ ,     _______ , _______ , _______                              
),

[_NAV] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______,
  KC_LALT , KC_LSFT , KC_LGUI , KC_LCTL , _______ ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______,
  _______ , _______ , _______ , _______ , _______ ,                         KC_HOME , KC_PGDN , KC_PGUP , KC_END  , _______,
                                _______ , _______ , _______ ,     _______ , _______ , _______                              
),

[_FUN] = LAYOUT_split_3x5_3(
  KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                         KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10 ,
  KC_LALT , KC_LSFT , KC_LGUI , KC_LCTL , _______ ,                         _______ , KC_RCTL , KC_RGUI , KC_RSFT , KC_LALT,
  _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______,
                                _______ , _______ , _______ ,     _______ , _______ , _______                              
)
};
