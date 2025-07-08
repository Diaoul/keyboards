#include "definitions/layers.h"
#include "definitions/keycodes.h"
#ifdef OLED_ENABLE
#    include "features/oled.h"
#endif

// Quick tap term
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    // Enable key repeating for some keys
    switch (keycode) {
        // Home row mods for ALT and GUI
        case HR_A:
        case HR_R:
        case HR_E:
        case HR_I:
            return QUICK_TAP_TERM;
        default:
            return 0;
    }
}

// Custom shift keys (https://getreuer.info/posts/keyboards/custom-shift-keys)
#ifdef COMMUNITY_MODULE_CUSTOM_SHIFT_KEYS_ENABLE
const custom_shift_key_t custom_shift_keys[] = {
    {KC_BSPC, KC_DEL},
    {KC_DOT, KC_COLN},
    {KC_COMM, KC_SCLN},
    {KC_QUES, KC_EXLM},
};
#endif // COMMUNITY_MODULE_CUSTOM_SHIFT_KEYS_ENABLE

// Key overrides (https://docs.qmk.fm/features/key_overrides)
#ifdef KEY_OVERRIDE_ENABLE
const key_override_t del_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t dot_key_override  = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);
const key_override_t comm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN);
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_QUES, KC_EXLM);

const key_override_t *key_overrides[] = {
    &del_key_override,
    &dot_key_override,
    &comm_key_override,
    &ques_key_override,
};
#endif // KEY_OVERRIDE_ENABLE

// Commbos (https://docs.qmk.fm/features/combo)
#ifdef COMBO_ENABLE
// top row left
const uint16_t PROGMEM fp_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM fw_combo[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM wp_combo[] = {KC_W, KC_P, COMBO_END};
// top row right
const uint16_t PROGMEM lu_combo[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM uy_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM ly_combo[] = {KC_L, KC_Y, COMBO_END};
// home row mixed
const uint16_t PROGMEM se_combo[] = {HR_S, HR_E, COMBO_END};

combo_t key_combos[] = {
    // top row
    COMBO(fp_combo, KC_LPRN),
    COMBO(fw_combo, KC_LBRC),
    COMBO(wp_combo, KC_LCBR),
    COMBO(lu_combo, KC_RPRN),
    COMBO(uy_combo, KC_RBRC),
    COMBO(ly_combo, KC_RCBR),
    // home row
    COMBO(se_combo, CW_TOGG),
};
#endif

// Chordal Hold
#ifdef CHORDAL_HOLD
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    // Exceptionally allow some one-handed chords for hotkeys + mouse usage
    switch (tap_hold_keycode) {
        case HR_T: // Left control
            switch (other_keycode) {
                case KC_A: // Select all
                case KC_X: // Cut
                case KC_C: // Copy
                case KC_V: // Paste (although hard to do this one)
                case KC_Z: // Undo
                case HR_R: // Reload
                case KC_W: // Close tab
                    return true;
            }
            break;
    }

    // Allow same-hand holds when the other key is in the rows below the alphas
    if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3) {
        return true;
    }

    return get_chordal_hold_default(tap_hold_record, other_record);
}
#endif
