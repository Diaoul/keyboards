#include "diaoul.h"

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

// Process record
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CUSTOM_SHIFT_KEYS_ENABLE
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }
#endif

    return true;
}

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
