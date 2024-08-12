#include "diaoul.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COLEMAK_DH] = LAYOUT_split_3x6_3(
  KC_GRV  , KC_Q , KC_W , KC_F , KC_P   , KC_B    ,                          KC_J    , KC_L   , KC_U    , KC_Y   , KC_QUOT , KC_MINS,
  KC_ESC  , HR_A , HR_R , HR_S , HR_T   , KC_G    ,                          KC_M    , HR_N   , HR_E    , HR_I   , HR_O    , KC_QUES,
  KC_LPRN , KC_Z , KC_X , KC_C , KC_D   , KC_V    ,                          KC_K    , KC_H   , KC_COMM , KC_DOT , KC_SLSH , KC_RPRN,
                                 KC_ESC , NUM_TAB , NAV_SPC ,     SYM_BSPC , SYM_ENT , QK_REP                                       
),

[_SYMBOLS] = LAYOUT_split_3x6_3(
  KC_EXLM , KC_AMPR , KC_COLN , KC_PLUS , KC_PERC , KC_TILD ,                        _______ , _______ , _______ , _______ , _______ , _______,
  KC_HASH , KC_CIRC , KC_DLR  , KC_UNDS , KC_EQL  , KC_ASTR ,                        _______ , KC_RCTL , KC_RSFT , KC_RGUI , KC_RALT , _______,
  KC_AT   , KC_LT   , KC_PIPE , KC_MINS , KC_GT   , KC_SLSH ,                        _______ , _______ , _______ , _______ , _______ , _______,
                                          KC_BSLS , KC_TAB  , KC_SPC ,     _______ , _______ , _______                                        
),

[_NUMPAD] = LAYOUT_split_3x6_3(
  _______ , _______ , _______ , _______ , _______ , _______ ,                      KC_PERC , KC_7    , KC_8 , KC_9 , KC_COLN  , _______,
  _______ , KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                      KC_PLUS , KC_1    , KC_2 , KC_3 , KC_MINUS , _______,
  _______ , _______ , _______ , _______ , _______ , _______ ,                      KC_ASTR , KC_4    , KC_5 , KC_6 , KC_SLSH  , _______,
                                          _______ , _______ , _______ ,     KC_0 , KC_DOT  , KC_COMM                                   
),

[_NAVIGATION] = LAYOUT_split_3x6_3(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                         KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         KC_HOME , KC_PGDN , KC_PGUP , KC_END  , _______ , _______,
                                          _______ , _______ , _______ ,     _______ , _______ , _______                                        
),

[_FUNCTION] = LAYOUT_split_3x6_3(
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , KC_F7   , KC_F8 , KC_F9 , KC_F10 , _______,
  _______ , KC_LALT , KC_LGUI , KC_LSFT , KC_LCTL , _______ ,                         _______ , KC_F1   , KC_F2 , KC_F3 , KC_F11 , _______,
  _______ , _______ , _______ , _______ , _______ , _______ ,                         _______ , KC_F1   , KC_F5 , KC_F6 , KC_F12 , _______,
                                          _______ , _______ , _______ ,     _______ , _______ , _______                                   
)
};
// clang-format on

#ifdef OLED_ENABLE
static void render_logo(void) {
    // clang-format off
    static const char PROGMEM aurora_logo[] = {
        0x00, 0x00, 0x00, 0xe0, 0x00, 0xf8, 0xc0, 0xf8, 0xe0, 0xc0, 0xfc, 0x00, 0x7e, 0x18, 0x00, 0x80,
        0x00, 0x02, 0x80, 0xf0, 0x00, 0xc0, 0x80, 0xf8, 0xc0, 0xe0, 0x70, 0x60, 0x3c, 0x38, 0x3c, 0x1c,
        0x00, 0x3f, 0x0c, 0x0f, 0x1f, 0x03, 0x07, 0x01, 0xc3, 0x00, 0xe0, 0x80, 0x00, 0xe0, 0x80, 0xf8,
        0x80, 0xc0, 0xf7, 0xc7, 0x6f, 0x7b, 0x39, 0x30, 0x00, 0x80, 0x00, 0xc0, 0x00, 0xc0, 0xc2, 0xe0,
        0x00, 0x40, 0x38, 0x30, 0x38, 0x1e, 0x18, 0x1e, 0x0f, 0x0c, 0x07, 0x07, 0x07, 0x03, 0x03, 0x21,
        0x21, 0x31, 0x30, 0x18, 0x18, 0x1c, 0x08, 0x0c, 0x0e, 0x07, 0x06, 0x07, 0x03, 0xc3, 0x03, 0x01,
        0x4c, 0xcc, 0xc2, 0xc2, 0x41, 0x49, 0x09, 0x2b, 0x2a, 0x6a, 0x6e, 0x24, 0x24, 0x04, 0x92, 0x92,
        0xb1, 0xf1, 0xf1, 0xf2, 0xe6, 0xa4, 0xa4, 0x04, 0x04, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28
    };
    // clang-format on
    oled_write_raw_P(aurora_logo, sizeof(aurora_logo));
}

static void render_kb_LED_state(uint8_t col, uint8_t line) {
    led_t led_usb_state = host_keyboard_led_state();
    oled_set_cursor(col, line);
    oled_write_P(led_usb_state.num_lock ? PSTR("N ") : PSTR("  "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("C ") : PSTR("  "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("S") : PSTR(" "), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_logo();
        render_user(0, 5);
        render_kb_LED_state(0, 7);
        render_layer_state(0, 8);
        render_mod_status_alt_gui(get_mods() | get_oneshot_mods(), 0, 12);
        render_mod_status_shift_ctrl(get_mods() | get_oneshot_mods(), is_caps_word_on(), 0, 14);
    } else {
        // clang-format off
        static const char PROGMEM aurora_art[] = {
            0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x08, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x40,
            0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x80,
            0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x80, 0x00, 0xf0, 0x00, 0x00, 0xc0,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
            0x81, 0x00, 0xc0, 0x00, 0xfe, 0x00, 0xfc, 0x00, 0xff, 0x20, 0xff, 0xf0, 0x0f, 0xf0, 0x00, 0xff,
            0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00, 0xf8, 0x00, 0x00, 0xf8,
            0xff, 0x10, 0xff, 0x84, 0xff, 0x60, 0xff, 0x36, 0xff, 0x0f, 0xff, 0x3f, 0x00, 0x5f, 0x00, 0x05,
            0x80, 0x00, 0x80, 0x00, 0xc0, 0x38, 0x00, 0xec, 0xf0, 0x00, 0xfb, 0x80, 0xff, 0xf0, 0xff, 0xef,
            0xff, 0xe8, 0xff, 0x03, 0xff, 0x0c, 0xff, 0x00, 0xff, 0x00, 0x03, 0x00, 0x00, 0xf8, 0x00, 0x80,
            0xff, 0x20, 0xff, 0xd0, 0xff, 0xe0, 0xfe, 0xf8, 0xff, 0xfc, 0xff, 0xff, 0x0f, 0xff, 0x01, 0x3f,
            0xff, 0x00, 0x0f, 0x00, 0x01, 0x00, 0x03, 0x00, 0xfe, 0x80, 0xfe, 0x00, 0xc0, 0xff, 0xc4, 0xfb,
            0xff, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0x07, 0xff, 0x03, 0x3f, 0x00, 0x0f, 0xc0, 0x00,
            0x00, 0x00, 0xb8, 0x00, 0xff, 0x40, 0xbe, 0xf0, 0xff, 0xf1, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff,
            0x1f, 0xff, 0x67, 0x00, 0xef, 0x00, 0x1f, 0x00, 0x00, 0x07, 0x00, 0x00, 0xe0, 0x00, 0xff, 0xf0,
            0xff, 0x88, 0xff, 0xc4, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x7f, 0x0f, 0xff,
            0x00, 0x07, 0xfe, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xc0, 0x3f, 0xf8, 0xe7, 0xff,
            0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0x1f, 0x3f, 0x01, 0xff, 0x0b, 0x00, 0xff, 0x00, 0x00, 0x05,
            0x00, 0x00, 0x00, 0xe0, 0x00, 0xf8, 0x60, 0x80, 0xfe, 0xe3, 0xfc, 0xff, 0x1e, 0xff, 0xff, 0x23,
            0xff, 0x09, 0xff, 0x20, 0x00, 0x3f, 0x02, 0x00, 0x00, 0x0f, 0x00, 0x40, 0x00, 0xc0, 0x00, 0xfc,
            0xe0, 0xfc, 0xf0, 0xff, 0xff, 0x7f, 0xfc, 0xff, 0x0f, 0xff, 0x07, 0x1f, 0x00, 0x01, 0x0f, 0x00,
            0x0f, 0x00, 0x81, 0x70, 0x0c, 0xf0, 0x80, 0x00, 0x00, 0xe4, 0xf8, 0xe6, 0x70, 0x3f, 0xcf, 0xff,
            0x1f, 0xff, 0x48, 0xff, 0x0f, 0x00, 0x07, 0x00, 0x00, 0x43, 0x60, 0xf8, 0xf0, 0xfe, 0x38, 0xfe,
            0x00, 0xfc, 0x03, 0x00, 0xc8, 0x72, 0xcf, 0xfc, 0x00, 0x03, 0x0f, 0x01, 0xe0, 0x1c, 0xe0, 0x03,
            0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x06, 0xf9, 0x00, 0x03, 0x00, 0x07,
            0xff, 0x00, 0x10, 0x12, 0xc9, 0xf0, 0xcf, 0xb4, 0x7f, 0x80, 0xe0, 0x1e, 0x01, 0x40, 0x65, 0x5e,
            0xe0, 0x00, 0x00, 0xf0, 0x0c, 0xf0, 0x00, 0x80, 0x7e, 0x01, 0x80, 0x93, 0xfc, 0xc0, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x89, 0x18, 0x2c, 0x46, 0x00, 0x07, 0x21, 0x10, 0x10, 0x80, 0x09, 0x13,
            0x31, 0xbf, 0xff, 0x00, 0x08, 0x1a, 0xf7, 0x0f, 0x00, 0x00, 0x44, 0x45, 0x34, 0xbf, 0xb8, 0x00,
            0x10, 0xf0, 0x08, 0xf4, 0x18, 0x11, 0xfc, 0x18, 0xfb, 0x0e, 0x10, 0xf8, 0x04, 0xf8, 0x10, 0x20,
            0x18, 0x09, 0xff, 0x0c, 0xea, 0x1f, 0x28, 0x60, 0x30, 0xf8, 0x20, 0xc0, 0x42, 0x33, 0x21, 0x00
        };
        // clang-format on
        oled_write_raw_P(aurora_art, sizeof(aurora_art));
    }
    return false;
}
#endif

// TODO:
// Now
// - Visualizations with GitHub Actions
// - Add copy paste keys
// - Add getreuer's features in the repo like [rafaelromao](https://github.com/rafaelromao/qmk_userspace/) (SELWORD, etc.)
// Later
// - Add a layer for mouse keys
// - Add media keys
// - Autocorrection for colemak deficiencies with OLED indicator
// - Add RGB controls
// - Add bakcspace to the home row on layers
// - Fix layout formatting in qmk.nvim
//

/*
 * BASE layer
 * Goal is to type english text and markdown without quitting that layer
 * - We don't touch alphas
 * - Combos for brackets, especially ()
 * - Punctuation tweaed with better shifted symbols
 * - Quotes
 * SYM layer
 * - Underscore does not combine with any other symbol, putting it on the thumb cluster?
 * - Keep space on the thumb cluster to continue typing symbols like ` == `
 * - Home row contains =, _
 * - I don't need quotes on that layer, they don't combine with other symbols
 *
 */
