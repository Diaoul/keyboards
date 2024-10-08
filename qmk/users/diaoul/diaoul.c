#include "diaoul.h"

// Quick tap term
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    // Disable key repeating and force hold behavior for some keys
    switch (keycode) {
        case NAV_SPC:
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}

// Process record
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef ACHORDION_ENABLE
    if (!process_achordion(keycode, record)) {
        return false;
    }
#endif

    return true;
}

// Matrix scan
void matrix_scan_user(void) {
#ifdef ACHORDION_ENABLE
    achordion_task();
#endif
}

// Achordion
#ifdef ACHORDION_ENABLE
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    return 800;
}
bool achordion_eager_mod(uint8_t mod) {
    // Make all mods eager for more responsive mouse and OLED display
    switch (mod) {
        case MOD_LGUI:
        case MOD_LALT:
        case MOD_LSFT:
        case MOD_LCTL:
        case MOD_RCTL:
        case MOD_RSFT:
        case MOD_RGUI:
        case MOD_RALT:
            return true;
        default:
            return false;
    }
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    // Allow some same-hand holds on the left side for keyboard + mouse usage
    switch (tap_hold_keycode) {
        case HR_T: // Control
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

    return achordion_opposite_hands(tap_hold_record, other_record);
}
#endif
