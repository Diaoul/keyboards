#pragma once

#include QMK_KEYBOARD_H

#include "definitions/layers.h"
#include "definitions/keycodes.h"
#ifdef OLED_ENABLE
#    include "features/oled.h"
#endif
#ifdef KEY_OVERRIDE_ENABLE
#    include "features/overrides.h"
#endif
#ifdef COMBO_ENABLE
#    include "features/combos.h"
#endif
#ifdef ACHORDION_ENABLE
#    include "features/getreuer/achordion.h"
#endif

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record);
bool     process_record_user(uint16_t keycode, keyrecord_t *record);
void     matrix_scan_user(void);
