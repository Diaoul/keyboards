#include "config.h"
#include "definitions/layers.h"
#include "definitions/keycodes.h"
#ifdef OLED_ENABLE
#    include "features/oled.h"
#endif

// Tap-hold configuration (https://docs.qmk.fm/tap_hold#tapping-term)
#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // Reduce tapping term for SHIFT home row mods
        case HR_S:
        case HR_E:
            return TAPPING_TERM - 40;
        default:
            return TAPPING_TERM;
    }
}
#endif // TAPPING_TERM_PER_KEY

#ifdef QUICK_TAP_TERM_PER_KEY
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    // Enable key repeating for some keys
    switch (keycode) {
        // Only for home row mods ALT and GUI
        case HR_A:
        case HR_R:
        case HR_E:
        case HR_I:
            return QUICK_TAP_TERM;
        default:
            return 0;
    }
}
#endif // QUICK_TAP_TERM_PER_KEY

#ifdef FLOW_TAP_TERM
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record,
                           uint16_t prev_keycode) {
    // Disable flow tap on hotkeys (CTRL, GUI and LALT)
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return 0;
    }

    switch (get_tap_keycode(prev_keycode)) {
        case KC_A ... KC_Z:
            switch (keycode) {
                // ALT and GUI
                case HR_A:
                case HR_R:
                case HR_I:
                case HR_O:
                    return FLOW_TAP_TERM;
                // CTRL
                case HR_T:
                case HR_N:
                    return FLOW_TAP_TERM - 25;
            }
    }

    return 0;
}
#endif // FLOW_TAP_TERM

#ifdef CHORDAL_HOLD
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    // Exceptionally allow some one-handed chords for hotkeys, mouse usage and on thumb
    switch (tap_hold_keycode) {
        case NUM_TAB:
        case NAV_SPC:
        case SYM_BSPC:
        case SYM_ENT:
            return true;
        case HR_T: // Left CTRL
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

    return get_chordal_hold_default(tap_hold_record, other_record);
}
#endif // CHORDAL_HOLD


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
// others
const uint16_t PROGMEM fn_combo[] = {KC_F, HR_N, COMBO_END};

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
    // others
    COMBO(fn_combo, OSL(FUN)),
};
#endif // COMBO_ENABLE

