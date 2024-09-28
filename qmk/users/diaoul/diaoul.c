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
