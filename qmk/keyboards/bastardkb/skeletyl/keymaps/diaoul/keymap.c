#include "diaoul.c"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK_DH] = LAYOUT_split_3x5_3(
  KC_Q , KC_W , KC_F , KC_P    , KC_B    ,                       KC_J     , KC_L    , KC_U    , KC_Y   , KC_QUOT,
  HR_A , HR_R , HR_S , HR_T    , KC_G    ,                       KC_M     , HR_N    , HR_E    , HR_I   , HR_O   ,
  KC_Z , KC_X , KC_C , KC_D    , KC_V    ,                       KC_K     , KC_H    , KC_COMM , KC_DOT , KC_SLSH,
                       NUM_TAB , NAV_SPC , KC_ESC ,     KC_ESC , SYM_BSPC , SYM_ENT
),

[_SYMBOLS] = LAYOUT_split_3x5_3(
  KC_AMPR , KC_COLN , KC_PLUS , KC_PERC , KC_TILD ,                        _______ , _______ , _______ , _______ , _______,
  KC_CIRC , KC_DLR  , KC_UNDS , KC_EQL  , KC_ASTR ,                        _______ , KC_RCTL , KC_RSFT , KC_RGUI , KC_RALT,
  KC_LT   , KC_PIPE , KC_MINS , KC_GT   , KC_SLSH ,                        _______ , _______ , _______ , _______ , _______,
                                KC_BSLS , KC_TAB  , KC_SPC ,     _______ , _______ , _______
),

[_NUMPAD] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,                         KC_PERC , KC_7   , KC_8 , KC_9 , KC_COLN ,
  KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                         KC_PLUS , KC_1   , KC_2 , KC_3 , KC_MINUS,
  _______ , _______ , _______ , _______ , _______ ,                         KC_ASTR , KC_4   , KC_5 , KC_6 , KC_SLSH ,
                                _______ , _______ , _______ ,     KC_BSPC , KC_0    , KC_DOT
),

[_NAVIGATION] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,                         RM_TOGG , RM_VALD , RM_VALU , RM_NEXT , RM_HUEU,
  KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , RM_SATU,
  _______ , _______ , _______ , _______ , _______ ,                         KC_HOME , KC_PGDN , KC_PGUP , KC_END  , RM_SPDU,
                                _______ , _______ , _______ ,     KC_BSPC , _______ , _______
),

[_FUNCTION] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,                         _______ , KC_F7   , KC_F8 , KC_F9 , KC_F10,
  KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                         _______ , KC_F1   , KC_F2 , KC_F3 , KC_F11,
  _______ , _______ , _______ , _______ , _______ ,                         _______ , KC_F4   , KC_F5 , KC_F6 , KC_F12,
                                _______ , _______ , _______ ,     _______ , _______ , _______
)
};
// clang-format on
